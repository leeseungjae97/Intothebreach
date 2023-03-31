#include "Alien.h"
#include "mAnimator.h"
#include "mTransform.h"
#include "mResources.h"
#include "mInput.h"
#include "mScene.h"
#include "mSkill.h"
#include "mTile.h"
#include "mSceneManager.h"
namespace m
{
	Alien::Alien(ALIENS mType, Vector2 _coord, int idx)
		: Unit(_coord
			, ALIEN_MOVE_RANGE[(UINT)mType]
			, ALIEN_HP[(UINT)mType]
			, ALIEN_BASIC_WEAPON[(UINT)mType]
		)
		, mAlienType(mType)
		, mIdx(idx)
	{
		vector<Image*> vImage = GetMImages();
		vImage.resize((UINT)ALIEN_CONDITION::END);

		for (UINT i = 0; i < (UINT)ALIEN_CONDITION::END; i++)
		{
			if (ALIENS_APL_COND[(UINT)mType][i] != 1) continue;
			vImage[i] = Resources::Load<Image>(
				MAKE_ALIEN_KEY(mAlienType, (ALIEN_CONDITION)i)
				, MAKE_ALIEN_PATH(mAlienType, (ALIEN_CONDITION)i));
			if (nullptr == vImage[i]) continue;
			vImage[i]->SetOffset(ALIEN_OFFSET[(UINT)mAlienType]);
		}
		for (int i = 0; i < 3; i++)
		{
			Vector2 size = ALIENS_SIZES[(UINT)mAlienType][i];
			UINT len = (UINT)((float)vImage[(int)i]->GetWidth() / size.x);

			GetAnimator()->CreateAnimation(
				MAKE_ALIEN_KEY(mAlienType, (ALIEN_CONDITION)i)
				, vImage[i]
				, Vector2(Vector2::Zero)
				, Vector2(size.x, size.y)
				, vImage[i]->GetOffset()
				, len
				, 0.2f
				, AC_SRC_OVER
			);
		}
		GetAnimator()->Play(MAKE_ALIEN_KEY(mAlienType, ALIEN_CONDITION::IDLE), true);
		SetState(STATE::Idle);

		SetSkillIdx(0);
		SetCurAttackSkill();
	}
	Alien::Alien(Alien& _origin)
		: mAlienType(_origin.mAlienType)
	{}
	Alien::~Alien()
	{}
	void Alien::Initialize()
	{

	}
	void Alien::Update()
	{
		Unit::Update();
		if (KEY_PRESSED(KEYCODE_TYPE::Q))
		{
			SetState(STATE::Broken);
		}
		if (KEY_PRESSED(KEYCODE_TYPE::R))
		{
			SetState(STATE::Emerge);
		}
		if (KEY_PRESSED(KEYCODE_TYPE::E))
		{
			SetState(STATE::Idle);
		}

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
			}
			broken();
			break;
		case STATE::Water:
			water();
			break;
		case STATE::Emerge:
		{
			if (GetAnimator()->GetStopAnimator())
			{
				SetState(STATE::Idle);
			}
			emerge();
		}
			break;
		case STATE::End:
			break;
		default:
			break;
		}
	}
	bool Alien::AlienMoveToAttackCheck(Vector2 _alienCoord, int curAlien)
	{
		if (mIdx != curAlien) return false;
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
				float dx = now.coord.x + direct[i][0];
				float dy = now.coord.y + direct[i][1];

				if (dx < 0 || dy < 0 || dx >= TILE_X - 1|| dy >= TILE_Y - 1) continue;
				if (GetSkillMap((int)dy, (int)dx) != 0) continue;
				if (scene->GetMap((int)dy, (int)dx) == BUILDING) continue;
				if (scene->GetMap((int)dy, (int)dx) == ALIEN) continue;
				if ((stPos.y != dy && stPos.x == dx)
					|| (stPos.x != dx && stPos.y == dy))
				{
					queue.push_back(Vector2_1(Vector2(dx, dy), now.level + 1, idx));
					SetSkillMap((int)dy, (int)dx, MOVE);
					if (GetCurAttackSkill()->GetSkillType() == SKILL_T::ST)
					{
						// ¹ß°ß.
						if (scene->GetMap((int)dy, (int)dx) == MECH)
						{
							if (scene->GetEffectUnit((int)dy, (int)dx)[0]->GetState() == GameObject::STATE::Broken)
							{
								continue;
							}
							SetTargetCoord(Vector2(dx, dy));
							return true;
						}
					}
				}
			}
		}
		return false;
	}
	void Alien::AlienMoveCheck(int& curAlien)
	{
		if (mIdx != curAlien) return;

		Scene* scene = SceneManager::GetActiveScene();
		int moveLimit = GetMoveRange();

		if (alienPathQueue.size() == 0)
		{
			//curAlien->DrawSkill(curAlien->GetTargetCoord());
			//curAlien->GetCurAttackSkill()->SetStartRender(true);
			return;
		}

		vector<Vector2> directQue;
		Vector2_1 now = alienPathQueue.back();

		while (now.coord != GetCoord())
		{
			directQue.push_back(Vector2(now.coord.x, now.coord.y));
			now = alienPathQueue[now.parentIdx];
		}
		alienPathQueue.clear();

		if (directQue.size() == 0) return;

		if (moveLimit >= directQue.size()) moveLimit = 0;

		Vector2 _coord = directQue[moveLimit > 0 ? moveLimit : 0];
		Vector2 _pos = scene->GetPosTiles()[(int)_coord.y][(int)_coord.x]->GetCenterPos();

		scene->MoveEffectUnit(this, _coord);
		SetPos(_pos);
		SetFinalPos(_pos);
		SetCoord(_coord);
		SetFinalCoord(_coord);

		if (GetFinalMoveCoord() == _coord)
		{
			DrawSkill(GetTargetCoord());
			GetCurAttackSkill()->SetStartRender(true);
		}

		curAlien++;
		if (curAlien >= scene->GetAliens().size())
		{
			scene->SetPlayerTurn(true);
			curAlien = 0;
		}
	}
	void Alien::AlienMapCheck(int curAlien)
	{
		Scene* scene = SceneManager::GetActiveScene();
		alienPathQueue.clear();
		DrawMoveRangeTile();
		int moveLimit = GetMoveRange();

		list<Vector2_1>queue;

		Vector2 stPos = GetFinalCoord();

		if (AlienMoveToAttackCheck(Vector2(stPos.x, stPos.y), curAlien))
		{
			scene->SetPosTiles((int)stPos.y, (int)stPos.x
				, TILE_T::MOVE_RANGE, MOVE_TILE_T::square_r);
			SetFinalMoveCoord(Vector2(stPos.x, stPos.y));
			return;
		}

		queue.push_back(Vector2_1(stPos, 0, -1));
		alienPathQueue.push_back(Vector2_1(stPos, 0, -1));
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
				float dx = now.coord.x + direct[i][0];
				float dy = now.coord.y + direct[i][1];

				if (dx < 0 || dy < 0 || dx >= TILE_X - 1 || dy >= TILE_Y - 1) continue;
				if (stPos.x == dx
					&& stPos.y == dy) continue;
				if (scene->GetMap((int)dy, (int)dx) == BUILDING) continue;
				if (scene->GetMap((int)dy, (int)dx) == ALIEN) continue;

				if (AlienMoveToAttackCheck(Vector2(dx, dy), curAlien))
				{
					scene->SetPosTiles((int)stPos.y, (int)stPos.x
						, TILE_T::MOVE_RANGE, MOVE_TILE_T::square_r);
					SetFinalMoveCoord(Vector2(dx, dy));
					find = true;
				}

				queue.push_back(Vector2_1(Vector2(dx, dy), now.level + 1, idx));
				alienPathQueue.push_back(Vector2_1(Vector2(dx, dy), now.level + 1, idx));
				if (find) break;
			}
			if (find) break;
		}
	}
	void Alien::Render(HDC hdc)
	{
		Unit::Render(hdc);
	}
	void Alien::Release()
	{
		Unit::Release();
	}
	void Alien::idle()
	{
		GetAnimator()->Play(MAKE_ALIEN_KEY(mAlienType, ALIEN_CONDITION::IDLE), true);
		SetCurImage(nullptr);
	}
	void Alien::broken()
	{
		GetAnimator()->Stop();
		GetAnimator()->Play(MAKE_ALIEN_KEY(mAlienType, ALIEN_CONDITION::DEATH), false);

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
		GetAnimator()->Play(MAKE_ALIEN_KEY(mAlienType, ALIEN_CONDITION::EMERGE), false);
		SetCurImage(nullptr);
	}
}