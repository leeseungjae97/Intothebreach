#include "Alien.h"
#include "mAnimator.h"
#include "mAnimation.h"
#include "mTransform.h"
#include "mResources.h"
#include "mInput.h"
#include "mScene.h"
#include "mSkill.h"
#include "mTile.h"
#include "mTime.h"
#include "mSceneManager.h"
#include "mPlayerInfo.h"
#include "mImage.h"
#include "mSound.h"
namespace m
{
	Alien::Alien(int unitType, Vector2 _coord, size_t idx, ALIENS_RANK _rType)
		: Unit(_coord
			, ALIEN_MOVE_RANGE[unitType - (int)MECHS::tele - 1]
			, ALIEN_HP[unitType - (int)MECHS::tele - 1] + (int)(_rType == ALIENS_RANK::NORMAL ? 0 : (int)_rType + 1)
			, BASIC_WEAPON_TYPE[unitType]
			, idx
			, unitType
		)
		, rType(_rType)
		, randMoveSoundPlayed(false)
	{
		finalMoveCoord = Vector2::Minus;
		tarGetCoord = Vector2::Minus;
		moveCnt = 1;


		vector<Image*> vImage = GetMImages();
		vImage.resize((UINT)ALIEN_CONDITION::END + 1);
		
		for (UINT i = 0; i < (UINT)ALIEN_CONDITION::END; i++)
		{
			if (ALIENS_APL_COND[GetUnitName()][i] != 1) continue;
			vImage[i] = Resources::Load<Image>(
				MAKE_UNIT_KEY((ALIENS)GetUnitName(), (ALIEN_CONDITION)i)
				, MAKE_UNIT_PATH((ALIENS)GetUnitName(), (ALIEN_CONDITION)i));

			if (nullptr == vImage[i]) continue;

			vImage[i]->SetOffset(ALIEN_OFFSET[(UINT)GetUnitName()][i]);
		}
		vImage[vImage.size() - 1] = Resources::Load<Image>(L"emerge_loop", L"..\\Resources\\texture\\combat\\emerge_loop.bmp");
		if (nullptr == GetAnimator()->FindAnimation(L"emerge_loop"))
		{
			float fWid = (float)vImage[vImage.size() - 1]->GetWidth() / 6;
			GetAnimator()->CreateAnimation(
				L"emerge_loop"
				, vImage[vImage.size() - 1]
				, Vector2::Zero
				, Vector2(fWid, (float)vImage[vImage.size() - 1]->GetHeight())
				, vImage[vImage.size() - 1]->GetOffset()
				, 6
				, 0.1f
				, (UINT)AC_SRC_OVER
			);
		}
		for (int i = 0; i < 3; i++)
		{
			Vector2 size = ALIENS_SIZES[GetUnitName()][i];
			UINT len = (UINT)((float)vImage[(int)i]->GetWidth() / size.x);

			GetAnimator()->CreateAnimation(
				MAKE_UNIT_KEY((ALIENS)GetUnitName(), (ALIEN_CONDITION)i)
				, vImage[i]
				, Vector2(0, size.y * (int)rType)
				, Vector2(size.x, size.y)
				, vImage[i]->GetOffset()
				, len
				, 0.2f
				, (UINT)AC_SRC_OVER
			);
			if (i == (int)ALIEN_CONDITION::EMERGE)
			{
				GetAnimator()->CreateAnimation(
					L"reverse_emerge"
					, vImage[i]
					, Vector2(0, size.y * (int)rType)
					, Vector2(size.x, size.y)
					, vImage[i]->GetOffset()
					, len
					, 0.2f
					, (bool)true
					, (UINT)AC_SRC_OVER
				);
			}
		}
		GetAnimator()->Play(MAKE_UNIT_KEY((ALIENS)GetUnitName(), ALIEN_CONDITION::IDLE), true);
		SetState(STATE::Emerge_loop);

		SetSkillIdx(0);
		SetCurAttackSkill();
	}
	Alien::Alien(Alien& _origin)
	{}
	Alien::~Alien()
	{}
	void Alien::Initialize()
	{

	}
	void Alien::Update()
	{
		Unit::Update();
		//if (KEY_PRESSED(KEYCODE_TYPE::Q))
		//{
		//	SetState(STATE::Broken);
		//}
		//if (KEY_PRESSED(KEYCODE_TYPE::R))
		//{
		//	SetState(STATE::Emerge);
		//}
		//if (KEY_PRESSED(KEYCODE_TYPE::E))
		//{
		//	SetState(STATE::Idle);
		//}
		//if (KEY_PRESSED(KEYCODE_TYPE::T))
		//{
		//	SetState(STATE::Emerge_loop);
		//}

		if (Unit::GetCurHp() == 0)
		{
			SetState(STATE::Broken);
		}
		//else
		//{
		//	SetState(STATE::Idle);
		//}
		switch (GetState())
		{
		case STATE::Idle:
			idle();
			break;
		case STATE::Broken:
			if (GetAnimator()->GetStopAnimator())
			{
				SetState(STATE::Death);
				if (rType == ALIENS_RANK::BOSS) GameComp::bKillLeader = true;
				SceneManager::GetActiveScene()->RemoveAffectUnit(GetCoord(), this);
				vector<Alien*>::iterator iter = GameComp::mAliens.begin();
				while (iter != GameComp::mAliens.end())
				{
					if ((*iter) == this) iter = GameComp::mAliens.erase(iter);
					else iter++;
				}
			}
			broken();
			
			break;
		case STATE::Water:
			water();
			break;
		case STATE::Emerge:
		{
			int i = rand() % 4;
			Sound* emergeSound = Resources::Load<Sound>(EMERGE_SOUND[i], EMERGE_SOUND[i]);
			if (!emergeSoundPlayed)
			{
				emergeSound->Play(false);
				emergeSoundPlayed = true;
			}
			if (GetAnimator()->GetStopAnimator())
			{
				SetState(STATE::Idle);
			}
			emerge();
		}
			break;
		case STATE::Emerge_loop:
		{
			emerger_loop();
		}
			break;
		case STATE::Death:
		{
			
		}
			break;
		case STATE::End:
			break;
		case STATE::Retreat:
		{
			retreat();
			if (GetAnimator()->GetStopAnimator())
			{
				SetState(STATE::Death);
				SceneManager::GetActiveScene()->RemoveAffectUnit(GetCoord(), this);
			}
		}
			break;
		default:
			break;
		}
	}
	bool Alien::AlienMoveToAttackCheck(Vector2 _alienCoord)
	{
		Scene* scene = SceneManager::GetActiveScene();

		ClearSkillRangeMap();

		list<Vector2_1>queue;

		Vector2 stPos = _alienCoord;
		queue.push_back(Vector2_1(stPos, 0, -1));

		scene->SetMap();

		// right, up, down, left
		float direct[4][2] = { {0, 1},{-1, 0} ,{1, 0},{0, -1} };

		//Vector2 attackCoord = Vector2::Zero;
		int idx = -1;
		while (!queue.empty())
		{
			Vector2_1 now = queue.front();
			queue.pop_front();
			idx++;
			for (int i = 0; i < 4; i++)
			{
				float dy = now.coord.y + direct[i][0];
				float dx = now.coord.x + direct[i][1];

				if (dx < 0 || dy < 0 || dx > TILE_X - 1 || dy > TILE_Y - 1) continue;
				if (GetSkillMap((int)dy, (int)dx) != 0) continue;
				if (scene->GetMap((int)dy, (int)dx) == MOUNTAIN) continue;
				if (scene->SearchAffectUnit((int)dy, (int)dx, GameObject::STATE::Broken)) continue;
				if (scene->GetMap((int)dy, (int)dx) == ALIEN) continue;

				if (WEAPON_RANGE[(UINT)GetWeaponType()] < now.level + 1)
				{
					return false;
				}

				if (stPos.x == dx || stPos.y == dy)
				{
					queue.push_back(Vector2_1(Vector2(dx, dy), now.level + 1, idx));
					SetSkillMap((int)dy, (int)dx, MOVE);

					//if (!scene->GetPlayerTurn())
					//{
					//	GetCurAttackSkill()->SetGuideLinePos(
					//		scene->GetPosTile((int)dy, (int)dx)->GetCenterPos()
					//	);
					//	GetCurAttackSkill()->SetGuideLineCoord(Vector2(dx, dy));
					//}
					//scene->SetPosTiles((int)dy, (int)dx
					//	, TILE_T::MOVE_RANGE, MOVE_TILE_T::square_r);
					
						//if (!scene->GetPlayerTurn())
						//{
						//	SetTargetCoord(Vector2(dx, dy));
						//	return true;
						//}
					if (scene->SearchAffectUnitM((int)dy, (int)dx, LAYER_TYPE::MONSTER))
					{
						//GetCurAttackSkill()->SetGuideLinePos();
						if (!scene->GetPlayerTurn())
						{
						}
						SetTargetCoord(Vector2(dx, dy));
						return true;
					}

					//for (int i = 0; i < scene->GetMap((int)dy, (int)dx).size(); i++)
					//{
					//	if (scene->GetEffectUnit((int)dy, (int)dx)[i]->GetLayerType() == LAYER_TYPE::PLAYER &&
					//		scene->GetEffectUnit((int)dy, (int)dx)[i]->GetState() != GameObject::STATE::Broken)
					//	{
					//		//GetCurAttackSkill()->SetGuideLinePos();
					//		if (!scene->GetPlayerTurn())
					//		{
					//			SetTargetCoord(Vector2(dx, dy));
					//			return true;
					//		}
					//	}
					//}
				}
			}
		}
		return false;
	}
	void Alien::AlienMoveCheck(int& curAlien)
	{
		if (GetFinalMoveCoord() == Vector2::Minus) return;
		
		moveDelay += Time::fDeltaTime();
		if (moveDelay >= 0.1f)
		{
			moveDelay = 0.f;
		}
		else return;
		Scene* scene = SceneManager::GetActiveScene();

		int moveLimit = GetMoveRange();


		Vector2_1 iter = Vector2_1(GetFinalMoveCoord(), 0, 0);

		if (alienPathQueue.size() != 0) iter = alienPathQueue.back();

		if (directQueue.size() == 0 && alienPathQueue.size() != 0)
		{
			while (iter.parentIdx != alienPathQueue.front().parentIdx)
			{
				directQueue.push_back(Vector2_1(iter));
				iter = alienPathQueue[iter.parentIdx];
			}
		}
		Vector2_1 curCoord = iter;
		//if(directQueue.size() <= moveCnt)
		//if (directQueue.size() != 0)
		//	curCoord = directQueue[directQueue.size() - moveCnt];
		//else if (directQueue.size() <= moveCnt)
		//{
		//	curCoord = directQueue[directQueue.size() - 1];
		//}
		if (directQueue.size() > 0)
		{
			curCoord = directQueue.back();
			directQueue.pop_back();
			moveCnt++;
		}

		Vector2 _coord = curCoord.coord;
		//Vector2 _pos = scene->GetPosTiles()[(int)curCoord.coord.y][(int)curCoord.coord.x]->GetCenterPos();

		scene->MoveAffectUnit(this, _coord);
		int i = rand() % 3;
		randMoveSound = Resources::Load<Sound>(ALIEN_MOVE_SOUNDS[GetUnitName()][i], ALIEN_MOVE_SOUNDS[GetUnitName()][i]);
		if (!randMoveSoundPlayed)
		{
			randMoveSound->SetVolume(10.f);
			randMoveSound->Play(false);
			randMoveSoundPlayed = true;
		}
		DrawMoveDust();
		//SetPos(_pos);
		//SetFinalPos(_pos);
		//SetCoord(_coord);
		//SetFinalCoord(_coord);
		//scene->SetPosTiles((int)GetTargetCoord().y, (int)GetTargetCoord().x
		//	, TILE_T::MOVE_RANGE, MOVE_TILE_T::square_g);

		if (GetFinalMoveCoord() == _coord)
		{
			//DrawSkill(GetTargetCoord(), GetCurAttackSkill()->GetGuideLineCoord());
			//ActiveSkill(GetTargetCoord());
			if (GetTargetCoord() != Vector2::Minus)
			{
				GetCurAttackSkill()->SetStartRender(true);
				ActiveSkill(GetTargetCoord());
			}
			directQueue.clear();
			moveCnt = 1;
			curAlien++;
			randMoveSoundPlayed = false;
		}
		if (moveCnt > moveLimit)
		{
			directQueue.clear();
			moveCnt = 1;
			curAlien++;
			randMoveSoundPlayed = false;
		}
	}
	void Alien::ActiveSkill(Vector2 otherPos)
	{
		if (otherPos == Vector2::Minus) return;
		Scene* scene = SceneManager::GetActiveScene();
		Vector2 endCoord = Vector2::Minus;
		Vector2 drawGuideLineEndCoord = Vector2::Minus;

		//if (skill_range_map[(int)otherPos.y][(int)otherPos.x] != MOVE)
		//{
		//	return;
		//}
		if (GetCurAttackSkill()->GetSkillType()
			== SKILL_T::RANGE_ST)
		{
			if (otherPos.x > GetCoord().x)
			{
				endCoord = Vector2(GetCoord().x + WEAPON_RANGE[(UINT)GetWeaponType()], GetCoord().y);
			}
			else if (otherPos.x < GetCoord().x)
			{
				endCoord = Vector2(GetCoord().x - WEAPON_RANGE[(UINT)GetWeaponType()], GetCoord().y);
			}
			else if (otherPos.y > GetCoord().y)
			{
				endCoord = Vector2(GetCoord().x, GetCoord().y + WEAPON_RANGE[(UINT)GetWeaponType()]);
			}
			else if (otherPos.y < GetCoord().y)
			{
				endCoord = Vector2(GetCoord().x, GetCoord().y - WEAPON_RANGE[(UINT)GetWeaponType()]);
			}
		}
		if (GetCurAttackSkill()->GetSkillType()
			== SKILL_T::ST)
		{
			int st = 0;
			int end = 0;
			int IDVar = 1;
			bool cY = false;
			if (otherPos.x > GetCoord().x)
			{
				st = (int)GetCoord().x + 1;
				end = TILE_X - 1;
				endCoord = Vector2((float)end, GetCoord().y);
			}
			else if (otherPos.x < GetCoord().x)
			{
				st = (int)GetCoord().x - 1;
				end = 0;
				endCoord = Vector2((float)end, GetCoord().y);
			}
			else if (otherPos.y > GetCoord().y)
			{
				st = (int)GetCoord().y + 1;
				end = TILE_Y - 1;
				endCoord = Vector2(GetCoord().x, (float)end);
				cY = true;
			}
			else if (otherPos.y < GetCoord().y)
			{
				st = (int)GetCoord().y - 1;
				end = 0;
				endCoord = Vector2(GetCoord().x, (float)end);
				cY = true;
			}

			if (end == 0)
			{
				IDVar = -1;
			}
			for (int i = st; i != end + IDVar; i += IDVar)
			{
				if (cY
					&& scene->SearchAffectUnit(i, (int)GetCoord().x)
					/*&& !scene->SearchAffectUnit(i, (int)GetCoord().x, GameObject::STATE::Broken)*/)
				{
					endCoord = Vector2(GetCoord().x, (float)i);
					break;
				}
				if (!cY
					&& scene->SearchAffectUnit((int)GetCoord().y, i))
				{
					endCoord = Vector2((float)i, GetCoord().y);
					break;
				}

				if (cY)drawGuideLineEndCoord = Vector2(otherPos.x, (float)i);
				else drawGuideLineEndCoord = Vector2((float)i, otherPos.y);
			}
		}
		if (GetCurAttackSkill()->GetSkillType()
			== SKILL_T::ARC)
		{
			endCoord = otherPos;
		}

		if (drawGuideLineEndCoord == Vector2::Minus) drawGuideLineEndCoord = endCoord;
		if (endCoord != Vector2::Minus)
		{
			//scene->SetPosTiles((int)endCoord.y, (int)endCoord.x
			//	, TILE_T::MOVE_RANGE, MOVE_TILE_T::square_r);
			//if (GetCurAttackSkill()->GetStartRender())
			//if(scene->GetEffectUnit((int)endCoord.y, (int)endCoord.x) != nullptr)
			//if (drawGuideLineEndCoord.x <= Vector2::Minus.x
			//	|| drawGuideLineEndCoord.y <= Vector2::Minus.y) 
			//{
			//	drawGuideLineEndCoord = endCoord;
			//}
			//else
			//{
			//	
			//}
			//scene->GetPosTiles()[endCoord.y][endCoord.x]->GetCenterPos();
			//Scene* scene = SceneManager::GetActiveScene();
			//scene->SetPosTiles(drawGuideLineEndCoord.y, drawGuideLineEndCoord.x, TILE_T::MOVE_RANGE, COMBAT_ANIM_TILE_T::warning_sprite, 100);
			//scene->GetPosTiles()[endCoord.y][endCoord.x]->SetCombatTileAnimator(COMBAT_ANIM_TILE_T::warning_sprite, 100);
			//scene->GetPosTile(endCoord.y, endCoord.x)->SetCombatTileAnimator(COMBAT_ANIM_TILE_T::warning_sprite, 100);
			//if (!scene->GetPlayerTurn())
			//{
			//	
			//	//GetCurAttackSkill()->SetStartRender(true);
			//}
			//else
			//{
			//	Vector2 pos = scene->GetPosTile(drawGuideLineEndCoord.y, drawGuideLineEndCoord.x)->GetPos();
			//	GetCurAttackSkill()->SetGuideLineCoord(drawGuideLineEndCoord);
			//	GetCurAttackSkill()->SetGuideLinePos(pos);
			//}
			DrawSkill(endCoord, drawGuideLineEndCoord);
		}

		if (GetCurAttackSkill()->GetStartRender() &&
			endCoord.x >= 0 && endCoord.y >= 0)
			scene->SetPosTiles((int)endCoord.y, (int)endCoord.x
				, TILE_T::COMMON, COMBAT_ANIM_TILE_T::warning_sprite, 125);

		// 공격완료하면 clear
		ClearSkillRangeMap();
	}
	void Alien::AlienMapCheck(int curAlien)
	{
		if (GetMIdx() != curAlien) return;
		/*if (alienPathQueue.size() != 0) return;*/
		alienPathQueue.clear();
		ClearSearchMap();
		Scene* scene = SceneManager::GetActiveScene();

		if (moveCnt == 0 && !scene->GetPlayerTurn()) DrawMoveRangeTile();

		list<Vector2_1>queue;

		Vector2 stPos = GetFinalCoord();
		scene->SetMap();
		queue.push_back(Vector2_1(stPos, 0, -1));
		alienPathQueue.push_back(Vector2_1(stPos, 0, -1));

		
		if (AlienMoveToAttackCheck(Vector2(stPos.x, stPos.y)))
		{
			//scene->SetPosTiles((int)stPos.y, (int)stPos.x
			//	, TILE_T::MOVE_RANGE, MOVE_TILE_T::square_r);
			SetFinalMoveCoord(Vector2(stPos.x, stPos.y));
			return;
		}


		float direct[4][2] = { {0, 1},{-1, 0} ,{1, 0},{0, -1} };

		bool find = false;

		int idx = -1;

		while (!queue.empty())
		{
			Vector2_1 now = queue.front();
			queue.pop_front();
			idx++;
			for (int i = 0; i < 4; i++)
			{
				float dy = now.coord.y + direct[i][0];
				float dx = now.coord.x + direct[i][1];

				if (dx < 0 || dy < 0 || dx > TILE_X - 1 || dy > TILE_Y - 1) continue;

				//if (abs(dx - stPos.x) >= moveLimit 
				//	|| abs(dy - stPos.y) >= moveLimit) continue;

				if (stPos.x == dx
					&& stPos.y == dy) continue;
				//if (scene->GetMap((int)dy, (int)dx) == MOUNTAIN) continue;
				//if (scene->GetMap((int)dy, (int)dx) == BUILDING) continue;
				if (scene->GetMap((int)dy, (int)dx) != 0) continue;
				if (scene->SearchAffectUnit((int)dy, (int)dx, GameObject::STATE::Broken)) continue;
				if (searchMap[(int)dy][(int)dx] != 0) continue;

				if (AlienMoveToAttackCheck(Vector2(dx, dy)))
				{
					//if (!scene->GetPlayerTurn())
					//{
					//	
					//}
					//scene->SetPosTiles((int)dy, (int)dx
					//	, TILE_T::MOVE_RANGE, MOVE_TILE_T::square_r);
					SetFinalMoveCoord(Vector2(dx, dy));

					find = true;
				}

				searchMap[(int)dy][(int)dx] = now.level + 1;
				queue.push_back(Vector2_1(Vector2(dx, dy), now.level + 1, idx));
				alienPathQueue.push_back(Vector2_1(Vector2(dx, dy), now.level + 1, idx));
				if (find) break;
			}
			if (find) break;
		}
		// 공격할 대상을 찾지 못했을때.
		if (!find)
		{
			SetTargetCoord(Vector2(-1, -1));
			int randIdx = rand() % alienPathQueue.size();
			SetFinalMoveCoord(alienPathQueue[randIdx].coord);
		}
	}
	void Alien::Render(HDC hdc)
	{
		Unit::Render(hdc);
		if (rType == ALIENS_RANK::BOSS)
		{
			Image* bossIcon = Resources::Load<Image>(L"bossIcon", L"..\\Resources\\texture\\combat\\overlay\\icon_boss.bmp");
			Image* bossIconShadow = Resources::Load<Image>(L"bossIconShadow", L"..\\Resources\\texture\\combat\\overlay\\icon_boss_glow.bmp");
			Vector2 mCenterPos = SceneManager::GetActiveScene()->GetPosTile((int)GetCoord().y, (int)GetCoord().x)->GetCenterPos();
			TransparentBlt(hdc
				,(int)(mCenterPos.x + 20)
				,(int)(mCenterPos.y - 20.f)
				,(int)(bossIcon->GetWidth() * 2)
				,(int)(bossIcon->GetHeight() * 2)
				, bossIcon->GetHdc()
				, 0
				, 0
				, (int)bossIcon->GetWidth()
				, (int)bossIcon->GetHeight()
				, RGB(255, 0 , 255)
			);
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			func.SourceConstantAlpha = 50;

			AlphaBlend(hdc
				, (int)(mCenterPos.x + 20)
				, (int)(mCenterPos.y - 20)
				, (int)(bossIconShadow->GetWidth() * 2)
				, (int)(bossIconShadow->GetHeight() * 2)
				, bossIconShadow->GetHdc()
				, 0
				, 0
				, (int)bossIconShadow->GetWidth()
				, (int)bossIconShadow->GetHeight()
				, func
			);
		}
	}
	void Alien::Release()
	{
		Unit::Release();
	}
	void Alien::idle()
	{
		SetVisibleHp(true);
		GetAnimator()->Play(MAKE_UNIT_KEY((ALIENS)GetUnitName(), ALIEN_CONDITION::IDLE), true);
		SetCurImage(nullptr);
	}
	void Alien::broken()
	{
		GetAnimator()->Stop();
		GetAnimator()->Play(MAKE_UNIT_KEY((ALIENS)GetUnitName(), ALIEN_CONDITION::DEATH), false);

		SetCurImage(nullptr);
	}
	void Alien::water()
	{
		GetAnimator()->Stop();
		SetCurImage(GetMImages()[(UINT)ALIEN_CONDITION::WATER]);
	}
	void Alien::emerge()
	{
		GetAnimator()->Stop();
		GetAnimator()->Play(MAKE_UNIT_KEY((ALIENS)GetUnitName(), ALIEN_CONDITION::EMERGE), false);
		SetCurImage(nullptr);
	}
	void Alien::emerger_loop()
	{
		GetAnimator()->Stop();
		GetAnimator()->Play(L"emerge_loop", true);
		SetCurImage(nullptr);
	}
	void Alien::retreat()
	{
		GetAnimator()->Stop();
		GetAnimator()->Play(L"reverse_emerge", false);
		SetVisibleHp(false);
		GetCurAttackSkill()->SetStartRender(false);
		//GetAnimator()->GetActiveAnimation()->SetReverse(true);
		SetCurImage(nullptr);
	}
}