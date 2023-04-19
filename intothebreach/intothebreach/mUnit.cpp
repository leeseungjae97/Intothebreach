#include "mUnit.h"
#include "mAnimator.h"
#include "mTransform.h"
#include "mCamera.h"
#include "mResources.h"
#include "mBackground.h"
#include "mSelectGDI.h"
#include "mSkill.h"
#include "func.h"
#include "mInput.h"
namespace m
{
	Unit::Unit(Vector2 _coord, int _range, int hp, int skillType, size_t idx, int unitName)
		: mPilot(nullptr)
		, curImage(nullptr)
		, mAnimator(nullptr)
		, endMove(false)
		, endAttack(false)
		, drag(false)
		, unitName(unitName)
		, mWeaponType(BASIC_WEAPON_TYPE[(UINT)unitName])
		, mCoord(_coord)
		, mFinalCoord(_coord)
		, mFinalPos(Vector2::Minus)
		//, unitCoord(Vector2::One)
		, moveRange(_range)
		, mHp(hp)
		, curHp(hp)
		, skillIdx(-1)
		, mIdx(idx)
	{
		SetSkill(skillType);
		AddComponent(new Animator());
		AddComponent(new Transform());
		mAnimator = GetComponent<Animator>();

		hpImage = Resources::Load<Image>(HP_BAR, HP_BAR);
		hpImage->SetOffset(Vector2(10.f, -45.f));

		hpBack = Resources::Load<Image>(HP_BAR_BACK, HP_BAR_BACK);
		hpBack->SetOffset(Vector2(16.f, -39.f));

		mSkills.resize(MAX_WEAPONS);
	}
	Unit::Unit(Unit& _origin)
		: GameObject(_origin)
		, curImage(_origin.curImage)
		, mCoord(_origin.mCoord)
		, mFinalCoord(_origin.mFinalCoord)
		, mFinalPos(_origin.mFinalPos)
		, moveRange(_origin.moveRange)
	{
		SetState(_origin.GetState());
		mAnimator = GetComponent<Animator>();
	}
	Unit::Unit(Vector2 _coord)
		: mPilot(nullptr)
		, mCoord(_coord)
		, mFinalCoord(_coord)
		, curImage(nullptr)
		, mAnimator(nullptr)
		, endMove(false)
		, endAttack(false)
		, drag(false)
		, mFinalPos(Vector2::One)
		//, unitCoord(Vector2::One)
		, mHp(0)
		, curHp(0)

	{
		AddComponent(new Animator());
		AddComponent(new Transform());
		mAnimator = GetComponent<Animator>();
	}
	Unit::Unit()
	{}
	Unit::~Unit()
	{
		//pathQueue.clear();
		//directQueue.clear();
		//arrowDirectQueue.clear();
		//mechMoveSave.clear();
		//Safe_Delete_X_Vec(moveDusts);
		//Safe_Delete_X_Vec(hpBar);

		//if(nullptr != mAnimator)
		//	delete mAnimator;
		//if (nullptr != curAttactSkill)
		//	curAttactSkill = nullptr;
		//if (nullptr != curImage)
		//	delete curImage;
		//if (nullptr != hpBack)
		//	delete hpBack;
	}
	void Unit::Initialize()
	{
		GameObject::Initialize();
	}
	void Unit::Update()
	{
		GameObject::Update();
		if (GetState() == GameObject::STATE::Death
			||
			GetState() == GameObject::STATE::Broken)
		{
			if(mCoord != Vector2::Minus)
				SceneManager::GetActiveScene()->RemoveEffectUnit(mCoord);
		}
		pathQueue.clear();
	}
	void Unit::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		Vector2 mPos = GetPos();

		if (nullptr != GetCurImage())
		{
			Image* curImage = GetCurImage();
			mPos += curImage->GetOffset();
			mPos = Camera::CalculatePos(mPos);
			if (unitConstant != 0)
			{
				BLENDFUNCTION func = {};
				func.BlendOp = AC_SRC_OVER;
				func.BlendFlags = 0;
				func.AlphaFormat = AC_SRC_ALPHA;
				func.SourceConstantAlpha = (BYTE)unitConstant;

				AlphaBlend(hdc
					, (int)(mPos.x - curImage->GetWidth() / 2.f)
					, (int)(mPos.y - curImage->GetHeight() / 2.f)
					, (int)(curImage->GetWidth() * 2)
					, (int)(curImage->GetHeight() * 2)
					, curImage->GetHdc()
					, 0
					, 0
					, (int)(curImage->GetWidth())
					, (int)(curImage->GetHeight())
					, func);
			}
			else
			{
				TransparentBlt(hdc
					, (int)(mPos.x - curImage->GetWidth() / 2.f)
					, (int)(mPos.y - curImage->GetHeight() / 2.f)
					, (int)(curImage->GetWidth() * 2)
					, (int)(curImage->GetHeight() * 2)
					, curImage->GetHdc()
					, 0
					, 0
					, (int)(curImage->GetWidth())
					, (int)(curImage->GetHeight())
					, RGB(255, 0, 255));
			}
		
			
		}
		//if (lType == LAYER_TYPE::CLONE) return;

		if (visibleHp)
		{
			mPos = GetComponent<Transform>()->GetPos();
			if (nullptr != hpImage && 0 != mHp)
			{
				mPos += hpImage->GetOffset();
				mPos = Camera::CalculatePos(mPos);
				TransparentBlt(hdc
					, (int)(mPos.x - hpImage->GetWidth() / 2.f)
					, (int)(mPos.y - hpImage->GetHeight() / 2.f)
					, (int)(hpImage->GetWidth() * 2)
					, (int)(hpImage->GetHeight() * 2)
					, hpImage->GetHdc()
					, 0
					, 0
					, (int)(hpImage->GetWidth())
					, (int)(hpImage->GetHeight())
					, RGB(255, 0, 255));
			}
			mPos = GetComponent<Transform>()->GetPos();
			if (nullptr != hpBack && 0 != mHp)
			{
				mPos += hpBack->GetOffset();
				mPos = Camera::CalculatePos(mPos);

				int px = (int)(mPos.x - hpBack->GetWidth() / 2.f);
				int py = (int)(mPos.y - hpBack->GetHeight() / 2.f);
				if (mHp == 0) return;
				int hpWidth = (hpBack->GetWidth() * 2) / mHp;
				int hpHeight = hpBack->GetHeight() * 2;
				for (int i = 0; i < curHp; i++)
				{
					SelectGDI p(hdc, BRUSH_TYPE::GREEN);
					Rectangle(hdc
						, (int)(px + hpWidth * i)
						, (int)(py)
						, (int)(px + hpWidth * (i + 1))
						, (int)(py + hpHeight));
				}
			}
		}
		
		if (bStructure)
		{
			// TODO building. energy status
		}

	}
	void Unit::Release()
	{
		GameObject::Release();
	}
	void Unit::ClearSearchMap()
	{
		for (int y = 0; y < TILE_Y; y++)
			for (int x = 0; x < TILE_X; x++)
				searchMap[y][x] = 0;
	}
	void Unit::DrawMoveDirectionTile()
	{
		Scene* scene = SceneManager::GetActiveScene();
		if (CheckSkillFiring()) return;
		for (int y = 0; y < TILE_Y; y++)
		{
			for (int x = 0; x < TILE_X; x++)
			{
				Tile* p = scene->GetPosTile(y, x);
				if (math::CheckRhombusPos(p->GetPos(), p->GetScale(), MOUSE_POS))
				{

					// 이동가능 거리 인지 확인
					if (scene->GetMap(y, x) == MECH)
					{
						if (GetCoord().x != x &&
							GetCoord().y != y)
						{
							continue;
						}
					}
					if (GetFinalCoord() == GetCoord()) continue;
					if (scene->GetMap(y, x) != MOVE)
					{
						scene->SetAlphaState(GameObject::STATE::Invisible);
						continue;
					}

					Vector2 prevCoord = GetFinalCoord();
					Vector2 curCoord = GetCoord();

					scene->SetAlphaState(GameObject::STATE::Visible);

					//list<Vector2> directQue;
					Vector2_1 now(Vector2(Vector2::Minus), 0, 0);

					arrowDirectQueue.clear();
					directQueue.clear();

					while (!pathQueue.empty() && now.coord != curCoord)
					{
						now = pathQueue.back();
						pathQueue.pop_back();
					}
					arrowDirectQueue.push_back(Vector2_1(Vector2(now.coord.x, now.coord.y), 0, 0));
					directQueue.push_back(Vector2_1(Vector2(now.coord.x, now.coord.y), 0, 0));

					while (!pathQueue.empty() && now.coord != prevCoord)
					{
						now = pathQueue[now.parentIdx];
						arrowDirectQueue.push_back(Vector2_1(Vector2(now.coord.x, now.coord.y), 0, 0));
						directQueue.push_back(Vector2_1(Vector2(now.coord.x, now.coord.y), 0, 0));
					}

					MOVE_ARROW_T type = (MOVE_ARROW_T)0;

					Vector2 coord = Vector2::Zero;
					Vector2 nCoord = Vector2::Zero;

					vector<Vector2> mVec;
					while (!arrowDirectQueue.empty())
					{
						coord = arrowDirectQueue.back().coord;
						mVec.push_back(Vector2(coord.x, coord.y));
						arrowDirectQueue.pop_back();
						if (!arrowDirectQueue.empty())
						{
							nCoord = arrowDirectQueue.back().coord;
							// 나오는 pos들은 장애물의 위치가 배제된 것이기 때문에 생각하지 안해도 된다.
							if (coord.y != nCoord.y)
							{
								type = MOVE_ARROW_T::ARROW_D_U;
								if (coord.y < nCoord.y)
								{
									if (mVec.size() > 1 && coord.x < mVec[mVec.size() - 2].x) type = MOVE_ARROW_T::ARROW_COR_R_D;
									if (mVec.size() > 1 && coord.x > mVec[mVec.size() - 2].x) type = MOVE_ARROW_T::ARROW_COR_L_D;
								}
								if (coord.y > nCoord.y)
								{
									if (mVec.size() > 1 && coord.x < mVec[mVec.size() - 2].x) type = MOVE_ARROW_T::ARROW_COR_R_U;
									if (mVec.size() > 1 && coord.x > mVec[mVec.size() - 2].x) type = MOVE_ARROW_T::ARROW_COR_L_U;
								}
							}
							else if (coord.x != nCoord.x)
							{
								type = MOVE_ARROW_T::ARROW_L_R;
								if (coord.x < nCoord.x)
								{
									if (mVec.size() > 1 && coord.y < mVec[mVec.size() - 2].y) type = MOVE_ARROW_T::ARROW_COR_R_D;
									if (mVec.size() > 1 && coord.y > mVec[mVec.size() - 2].y) type = MOVE_ARROW_T::ARROW_COR_R_U;
								}
								if (coord.x > nCoord.x)
								{
									if (mVec.size() > 1 && coord.y < mVec[mVec.size() - 2].y) type = MOVE_ARROW_T::ARROW_COR_L_D;
									if (mVec.size() > 1 && coord.y > mVec[mVec.size() - 2].y) type = MOVE_ARROW_T::ARROW_COR_L_U;
								}
							}
							if (coord == prevCoord)
							{
								if (coord.x < nCoord.x) type = MOVE_ARROW_T::ARROW_ST_L;
								if (coord.x > nCoord.x) type = MOVE_ARROW_T::ARROW_ST_R;
								if (coord.y < nCoord.y) type = MOVE_ARROW_T::ARROW_ST_U;
								if (coord.y > nCoord.y) type = MOVE_ARROW_T::ARROW_ST_D;
							}
						}
						if (mVec.size() > 1 && coord == curCoord)
						{
							if (mVec[mVec.size() - 2].x < curCoord.x) type = MOVE_ARROW_T::ARROW_R;
							if (mVec[mVec.size() - 2].x > curCoord.x) type = MOVE_ARROW_T::ARROW_L;
							if (mVec[mVec.size() - 2].y < curCoord.y) type = MOVE_ARROW_T::ARROW_D;
							if (mVec[mVec.size() - 2].y > curCoord.y) type = MOVE_ARROW_T::ARROW_U;
						}
						if (coord.x < 0 || coord.y < 0) continue;
						scene->SetArrowTiles((int)coord.y, (int)coord.x, type);
					}
				}
			}
		}
	}
	void Unit::DrawMoveDust()
	{
		for (int i = 0; i < 5; i++)
		{

			int c = rand() % 2;

			Background* dust = new Background(
				MAKE_DUST_KEY(TILE_T::GREEN, c),
				MAKE_DUST_PATH(TILE_T::GREEN, c),
				2);
			dust->SetCutPos(true);
			dust->SetAlpha(true);

			float randConstant = (float)(rand() % 255) + 125;
			dust->SetAlphaConstant((int)randConstant);
			int randPM = 1;
			
			if (c) randPM *= -1;

			float randX = GetPos().x + (rand() % 30) * randPM;
			float randY = GetPos().y + (rand() % 20) * randPM;

			dust->SetPos(Vector2(randX, randY));

			Vector2 dir = Vector2(0, -1.f);

			dust->SetMovement(dir);

			moveDusts.push_back(dust);
			SceneManager::GetActiveScene()->AddGameObject(dust, LAYER_TYPE::UI);
		}
	}
	void Unit::DrawMoveRangeTile()
	{
		//if (mMouseFollower->CheckSkillFiring()) return;
		Scene* scene = SceneManager::GetActiveScene();
		//if (GetLayerType() == LAYER_TYPE::MONSTER && scene->GetPlayerTurn()) return;
		if (CheckSkillFiring()) return;
		int moveLimit = GetMoveRange();

		list<Vector2_1>queue;

		Vector2 stPos = GetFinalCoord();
		queue.push_back(Vector2_1(stPos, 0, -1));
		pathQueue.push_back(Vector2_1(stPos, 0, -1));

		scene->SetMap();
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

				if (dx < 0 || dy < 0 || dx >= TILE_X || dy >= TILE_Y) continue;
				if (stPos.x == dx
					&& stPos.y == dy) continue;
				if (scene->GetMap((int)dy, (int)dx) != 0) continue;
				if (now.level >= moveLimit)
				{
					find = true;
					break;
				}


				queue.push_back(Vector2_1(Vector2(dx, dy), now.level + 1, idx));
				//if (GetLayerType() == LAYER_TYPE::PLAYER)
				pathQueue.push_back(Vector2_1(Vector2(dx, dy), now.level + 1, idx));

				if (scene->GetMap((int)dy, (int)dx) == MECH
					|| scene->GetMap((int)dy, (int)dx) == ALIEN) continue;
				//if (nullptr != scene->GetEffectUnit((int)dy, (int)dx)) continue;
				scene->SetMap((int)dy, (int)dx, MOVE);
				scene->SetPosTiles((int)dy, (int)dx, TILE_T::MOVE_RANGE, MOVE_TILE_T::square_g);
			}
			if (find) break;
		}
		DrawOutLineTile((int)MOVE_TILE_T::square_g_l);
	}
	void Unit::DrawOutLineTile(int _type)
	{
		Scene* scene = SceneManager::GetActiveScene();
		for (int y = 0; y < TILE_Y; y++)
		{
			for (int x = 0; x < TILE_X; x++)
			{
				if (scene->GetPosTiles()[y][x]->GetTileType() == TILE_T::MOVE_RANGE)
				{
					// x,y 타일 주변 4방향으로 검사해서 MOVE tile이 아니면 외곽선 추가.
					if (x - 1 >= 0
						&& scene->GetPosTiles()[y][x - 1]->GetTileType() != TILE_T::MOVE_RANGE)
					{
						scene->SetBoundaryTiles(y, x, (MOVE_TILE_T)(_type));
					}
					if (x + 1 < scene->GetPosTiles()[y].size()
						&& scene->GetPosTiles()[y][x + 1]->GetTileType() != TILE_T::MOVE_RANGE)
					{
						scene->SetBoundaryTiles(y, x, (MOVE_TILE_T)(_type + 1));
					}
					if (y - 1 >= 0
						&& scene->GetPosTiles()[y - 1][x]->GetTileType() != TILE_T::MOVE_RANGE)
					{
						scene->SetBoundaryTiles(y, x, (MOVE_TILE_T)(_type + 2));
					}
					if (y + 1 < scene->GetPosTiles().size()
						&& scene->GetPosTiles()[y + 1][x]->GetTileType() != TILE_T::MOVE_RANGE)
					{
						scene->SetBoundaryTiles(y, x, (MOVE_TILE_T)(_type + 3));
					}
				}
			}
		}
	}
	void Unit::ClearSkillRangeMap()
	{
		for (int y = 0; y < TILE_Y; y++)
		{
			for (int x = 0; x < TILE_X; x++)
			{
				skill_range_map[y][x] = 0;
			}
		}
	}
	void Unit::ActiveSkill(Vector2 targetUnitPos)
	{
		Scene* scene = SceneManager::GetActiveScene();
		Vector2 endCoord = Vector2::Minus;
		Vector2 drawGuideLineEndCoord = Vector2::Minus;
		for (int y = 0; y < TILE_Y; y++)
		{
			for (int x = 0; x < TILE_X; x++)
			{
				Tile* p = scene->GetPosTiles()[y][x];
				if (p->GetCoord() == GetFinalCoord()) continue;
				if (math::CheckRhombusPos(p->GetPos(), p->GetScale(), targetUnitPos))
				{
					if (skill_range_map[(int)p->GetCoord().y][(int)p->GetCoord().x] != MOVE)
					{
						GetCurAttackSkill()->SetStartRender(false);
						continue;
					}
					if (GetCurAttackSkill()->GetSkillType()
						== SKILL_T::RANGE_ST)
					{
						if (p->GetCoord().x > GetCoord().x)
						{
							endCoord = Vector2(GetCoord().x + WEAPON_RANGE[(UINT)GetWeaponType()], GetCoord().y);
						}
						if (p->GetCoord().x < GetCoord().x)
						{
							endCoord = Vector2(GetCoord().x - WEAPON_RANGE[(UINT)GetWeaponType()], GetCoord().y);
						}
						if (p->GetCoord().y > GetCoord().y)
						{
							endCoord = Vector2(GetCoord().x, GetCoord().y + WEAPON_RANGE[(UINT)GetWeaponType()]);
						}
						if (p->GetCoord().y < GetCoord().y)
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
						if (p->GetCoord().x > GetCoord().x)
						{
							st = (int)GetCoord().x + 1;
							end = TILE_X - 1;
							endCoord = Vector2((float)end, p->GetCoord().y);
						}
						if (p->GetCoord().x < GetCoord().x)
						{
							st = (int)GetCoord().x - 1;
							end = 0;
							endCoord = Vector2((float)end, p->GetCoord().y);
						}
						if (p->GetCoord().y > GetCoord().y)
						{
							st = (int)GetCoord().y + 1;
							end = TILE_Y - 1;
							endCoord = Vector2(p->GetCoord().x, (float)end);
							cY = true;
						}
						if (p->GetCoord().y < GetCoord().y)
						{
							st = (int)GetCoord().y - 1;
							end = 0;
							endCoord = Vector2(p->GetCoord().x, (float)end);
							cY = true;
						}
						if (end == 0)
						{
							IDVar *= -1;
						}
						for (int i = st; i != end + IDVar; i += IDVar)
						{
							if (cY && nullptr != scene->GetEffectUnit(i, (int)GetCoord().x)
								|| scene->GetEffectUnit(i, (int)GetCoord().x)->GetState() != STATE::Emerge_loop)
							{
								endCoord = Vector2(p->GetCoord().x, (float)i);
								break;
							}
							if (!cY && nullptr != scene->GetEffectUnit((int)GetCoord().y, i)
								|| scene->GetEffectUnit(i, (int)GetCoord().x)->GetState() != STATE::Emerge_loop)
							{
								endCoord = Vector2((float)i, p->GetCoord().y);
								break;
							}

							if (cY)drawGuideLineEndCoord = Vector2(p->GetCoord().x, (float)i);
							else drawGuideLineEndCoord = Vector2((float)i, p->GetCoord().y);
						}
					}
					if (GetCurAttackSkill()->GetSkillType()
						== SKILL_T::ARC)
					{
						endCoord = p->GetCoord();
						break;
					}
				}
			}
		}
		if (drawGuideLineEndCoord == Vector2::Minus) drawGuideLineEndCoord = endCoord;
		if (endCoord != Vector2::Minus)
		{
			//scene->GetPosTiles()[endCoord.y][endCoord.x]->GetCenterPos();
			//Scene* scene = SceneManager::GetActiveScene();
			//scene->SetPosTiles(drawGuideLineEndCoord.y, drawGuideLineEndCoord.x, TILE_T::MOVE_RANGE, COMBAT_ANIM_TILE_T::warning_sprite, 100);
			//scene->GetPosTiles()[endCoord.y][endCoord.x]->SetCombatTileAnimator(COMBAT_ANIM_TILE_T::warning_sprite, 100);
			//scene->GetPosTile(endCoord.y, endCoord.x)->SetCombatTileAnimator(COMBAT_ANIM_TILE_T::warning_sprite, 100);
			DrawSkill(endCoord, drawGuideLineEndCoord);
			if (GetLayerType() == LAYER_TYPE::MONSTER)
			{
				if (GetCurAttackSkill()->GetStartRender())
					scene->SetPosTiles((int)endCoord.y, (int)endCoord.x
						, TILE_T::COMMON, COMBAT_ANIM_TILE_T::warning_sprite, 125);
			}else  GetCurAttackSkill()->SetStartRender(true);
		}
		// 공격완료하면 clear
		ClearSkillRangeMap();
	}
	void Unit::DrawSkillRangeTile()
	{
		Scene* scene = SceneManager::GetActiveScene();
		list<Vector2_1>queue;

		Vector2 stPos = GetFinalCoord();
		queue.push_back(Vector2_1(stPos, 0, -1));
		pathQueue.push_back(Vector2_1(stPos, 0, -1));

		scene->SetMap();

		// right, up, down, left
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
				if (skill_range_map[(int)dy][(int)dx] != 0) continue;

				bool rangeCheck = false;

				// 스킬 반경 설정
				for (int _i = 0; _i < 4; _i++)
				{
					if (stPos.x + direct[_i][0] == dx
						&& stPos.y + direct[_i][1] == dy) rangeCheck = true;
				}
				// 4방향체크
				//if ((stPos.y != dy && stPos.x == dx)
				//	|| (stPos.x != dx && stPos.y == dy))
				if (stPos.y == dy || stPos.x == dx)
				{

					if (GetCurAttackSkill()->GetSkillType() == SKILL_T::ST)
					{

						if (scene->GetMap((int)dy, (int)dx) != 0)
						{
							skill_range_map[(int)dy][(int)dx] = MOVE;
							continue;
						}
					}
					if (WEAPON_RANGE[(UINT)GetWeaponType()] < now.level + 1)
					{
						find = true;
						continue;
					}
					queue.push_back(Vector2_1(Vector2(dx, dy), now.level + 1, idx));

					if (GetCurAttackSkill()->GetSkillType() == SKILL_T::ARC
						&& rangeCheck) continue;

					skill_range_map[(int)dy][(int)dx] = MOVE;
					scene->SetPosTiles((int)dy, (int)dx, TILE_T::MOVE_RANGE, MOVE_TILE_T::square_r);
					//scene->SetPosTiles((int)dy, (int)dx, TILE_T::MOVE_RANGE, COMBAT_ANIM_TILE_T::warning_sprite, 125);
					if (find) break;
				}
				if (find) break;
			}
			if (find) break;
		}
		DrawOutLineTile((int)MOVE_TILE_T::square_r_l);
	}
	bool Unit::CheckSkillFiring()
	{
		if (nullptr == this) return false;
		if (nullptr == curAttactSkill) return false;

		if (curAttactSkill->GetEndFire()
			&& !curAttactSkill->GetStartFire()) return false;

		if (!curAttactSkill->GetEndFire()
			&& !curAttactSkill->GetStartFire()) return false;

		if (!curAttactSkill->GetEndFire()
			&& curAttactSkill->GetStartFire()) return true;
		return false;
	}
	void Unit::DrawSkill(Vector2 pos, Vector2 guideLinePos)
	{
		SetCurAttackSkill();
		if (pos == Vector2::Minus) return;
		if (nullptr == curAttactSkill)return;
		curAttactSkill->ReInit(this->GetFinalCoord(), pos, guideLinePos, curAttactSkill->GetSkillType());
	}
	void Unit::SetSkill()
	{}
	void Unit::SetSkill(int type)
	{
		object::Instantiate(mSkills, (SKILL_T)type, this);
	}
	void Unit::SetSkill(int idx, SKILL_T type)
	{
		object::Instantiate(mSkills, (SKILL_T)type, idx);
	}
	Skill* Unit::GetSkill(int idx)
	{
		if (mSkills.size() <= idx) return nullptr;
		return mSkills[idx];
	}
	void Unit::SetSkillIdx(int _idx) { skillIdx = _idx; }
	//SKILL_T Unit::GetSkill(int idx)
	//{
	//	//return mSkills[idx];
	//}
	void Unit::ChangePilotSlot()
	{}
	void Unit::SetCurAttackSkill()
	{
		assert(this);
		if (skillIdx == -1) return;

		curAttactSkill = mSkills[skillIdx];
	}
}