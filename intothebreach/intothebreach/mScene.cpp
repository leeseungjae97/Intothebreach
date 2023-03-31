#include "mScene.h"
#include "mLayer.h"
#include "mUnit.h"
#include "mTile.h"
#include "Building.h"
#include "Mech.h"
#include "Alien.h"
#include "mSkill.h"
#include "mSelectGDI.h"
#include "mApplication.h"
#include "func.h"
#include "mInput.h"
extern m::Application application;
namespace m
{
	Scene::Scene()
		: mMouseFollower(nullptr)
		//, map(nullptr)
	{
		mLayers.reserve(5);
		mLayers.resize((UINT)LAYER_TYPE::END);
		playerTurn = true;
		curAttackAlien = 0;
	}
	Scene::~Scene()
	{

	}
	void Scene::Initialize()
	{
		//*(lmer)
		for (Layer& layer : mLayers)
		{
			layer.Initialize();
		}
	}
	void Scene::Update()
	{
		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}
	void Scene::Destroy()
	{
		vector<GameObject*> deleteGameObjects = {};
		vector<Alien*>::iterator iter = mAliens.begin();

		while (iter != mAliens.end())
		{
			if ((*iter)->GetState() == GameObject::STATE::Death)
			{
				//deleteGameObjects.push_back((*iter));
				iter = mAliens.erase(iter);
			}
			else
			{
				iter++;
			}
		}

		for (Layer& layer : mLayers)
		{
			vector<GameObject*>& gameObjects
				= layer.GetGameObjects();

			for (vector<GameObject*>::iterator iter = gameObjects.begin()
				; iter != gameObjects.end(); )
			{
				if ((*iter)->GetState() == GameObject::STATE::Death
					||
					(*iter)->GetState() == GameObject::STATE::Delete)
				{
					deleteGameObjects.push_back((*iter));
					iter = gameObjects.erase(iter);
				}
				else
				{
					iter++;
				}
			}
		}

		// ���� ��ġ���� �浹���� �ٸ� �浹ü�� �־��ٸ� Exit��
		// ȣ�� �����Ŀ� ���� ���־���Ѵ�.

		for (GameObject* deathObj : deleteGameObjects)
		{
			delete deathObj;
			deathObj = nullptr;
		}
	}
	void Scene::Render(HDC hdc)
	{
		wchar_t szFloat[500] = {};
		swprintf_s(szFloat, 500, L"playerTurn : %d", playerTurn);
		size_t iLen = wcsnlen_s(szFloat, 500);
		//left top right bottom
		RECT rt = { 50, 140, 400, 160 };
		DrawText(application.GetHdc(), szFloat, iLen, &rt, DT_LEFT | DT_WORDBREAK);

		for (Layer& layer : mLayers)
		{
			layer.Render(hdc);
		}
	}

	/// <summary>
	/// Ÿ�� ��ü ����
	/// ���߿� Ÿ���� �����ϸ� �ҷ��ö�
	/// �� Ÿ�Ͽ� ���� ó�� ���־�ߵ�
	/// </summary>
	/// <param name="iX">Ÿ�� x ũ��</param>
	/// <param name="iY">Ÿ�� y ũ��</param>
	/// <param name="_type">��ü Ÿ���� �� Ÿ��</param>
	/// <param name="_type2">��ü Ÿ���� Ÿ��</param>
	void Scene::MakeTile(int iX, int iY, TILE_T _type, TILE_HEAD_T _type2)
	{
		mTiles.resize(iY, vector<Tile*>());
		mPosTiles.resize(iY, vector<Tile*>());
		mPosOutLineTiles.resize(iY, vector<Tile*>());
		mBoundaryTiles.resize(iY, vector<Tile*>());
		mArrowTiles.resize(iY, vector<Tile*>());
		mStruturesTiles.resize(iY, vector<Building*>());
		mEffectedTiles.resize(iY, vector<Tile*>());
		mEnemyEmerge.resize(iY, vector<Tile*>());
		for (int y = 0; y < iY; y++)
		{
			mTiles[y].resize(iX);
			mPosTiles[y].resize(iX);
			mPosOutLineTiles[y].resize(iX);
			mBoundaryTiles[y].resize(iX);
			mArrowTiles[y].resize(iX);
			mStruturesTiles[y].resize(iX);
			mEffectedTiles[y].resize(iX);
			mEnemyEmerge[y].resize(iX);
		}
		float fX, fY;
		float mX = (10.f * (TILE_SIZE_X / 2.f));
		float mY = TILE_SIZE_Y / 4.f;
		for (int y = 0; y < iY; y++)
		{
			for (int x = 0; x < iX; x++)
			{
				Tile* tile = new Tile(Vector2((float)x, (float)y));
				//Building* b_ = new Building(STRUCTURES_T::Mountain, Vector2((float)x, (float)y));
				fX = (float)((TILE_SIZE_X / TILE_X_DIVIDE_RECT) * (x - y) + mX);
				fY = (float)((TILE_SIZE_Y / TILE_Y_DIVIDE_RECT) * (x + y) + mY);
				tile->SetPos(Vector2(fX * 2, fY * 2));
				tile->SetTileType(_type);
				tile->SetTileTexture(MAKE_TILE_KEY(_type, _type2)
					, MAKE_TILE_PATH(_type, _type2));
				mTiles[y][x] = tile;

				AddGameObject(tile, LAYER_TYPE::TILE);
			}
		}
		MakeVariTile(iY, iX);
		Building* stTile = new Building(STRUCTURES_T::Mountain, mTiles[3][3]->GetCoord());
		stTile->SetPos(mTiles[3][3]->GetCenterPos());
		mStruturesTiles[3][3] = stTile;

		AddGameObject(stTile, LAYER_TYPE::STRUCT);

		Building* stTile1 = new Building(STRUCTURES_T::Mountain, mTiles[1][2]->GetCoord());
		stTile1->SetPos(mTiles[1][2]->GetCenterPos());
		mStruturesTiles[1][2] = stTile1;

		AddGameObject(stTile1, LAYER_TYPE::STRUCT);

		Building* stTile2 = new Building(STRUCTURES_T::Mountain, mTiles[2][0]->GetCoord());
		stTile2->SetPos(mTiles[2][0]->GetCenterPos());
		mStruturesTiles[2][0] = stTile2;

		AddGameObject(stTile2, LAYER_TYPE::STRUCT);

		SetMap();
	}
	/// <summary>
	/// ������ ������Ʈ ǥ�ø� ���� ���� �ʱ�ȭ.
	/// </summary>
	/// <param name="iX"></param>
	/// <param name="iY"></param>
	void Scene::MakeVariTile(int iX, int iY)
	{
		/*for (int y = iY - 1; y >= 0; y--) {
			for (int x = iX - 1; x >= 0; x--) {*/
		for (int y = 0; y < iY; y++)
		{
			for (int x = 0; x < iX; x++)
			{
				Tile* posTile = new Tile(mTiles[y][x]->GetCoord());
				Tile* etcTile = new Tile(mTiles[y][x]->GetCoord());
				Tile* awTile = new Tile(mTiles[y][x]->GetCoord());
				Building* stTile = new Building(STRUCTURES_T::C_Building, mTiles[y][x]->GetCoord());

				posTile->SetTileTexture(SQUARE__KEY, SQUARE__PATH);
				posTile->SetPos(mTiles[y][x]->GetPos());

				awTile->SetTileTexture(SQUARE__KEY, SQUARE__PATH);
				awTile->SetPos(mTiles[y][x]->GetPos());

				etcTile->InitETCTiles(4);
				etcTile->SetPos(mTiles[y][x]->GetPos());
				mPosTiles[y][x] = posTile;
				mBoundaryTiles[y][x] = etcTile;
				mArrowTiles[y][x] = awTile;
				mStruturesTiles[y][x] = stTile;

				AddGameObject(etcTile, LAYER_TYPE::TILE);
				AddGameObject(stTile, LAYER_TYPE::TILE);
				AddGameObject(awTile, LAYER_TYPE::TILE);
				AddGameObject(posTile, LAYER_TYPE::TILE);

			}
		}
		for (int y = 0; y < iY; y++)
		{
			for (int x = 0; x < iX; x++)
			{
				Tile* posLineTile = new Tile(mTiles[y][x]->GetCoord());
				posLineTile->SetTileTexture(SQUARE__KEY, SQUARE__PATH);
				posLineTile->SetPos(mTiles[y][x]->GetPos());
				mPosOutLineTiles[y][x] = posLineTile;
				AddGameObject(posLineTile, LAYER_TYPE::TILE);
			}
		}
	}

	/// <summary>
	/// ǥ���ߴ� �̵����ɰŸ� �ʱ�ȭ.
	/// ��ī�� ��ġ(FinalPos)�� �ٲ�� �ҷ���.
	/// </summary>
	void Scene::ClearMap()
	{
		for (int y = 0; y < mPosTiles.size(); y++)
		{
			for (int x = 0; x < mPosTiles[y].size(); x++)
			{
				map[y][x] = 0;
			}
		}
	}

	void Scene::CheckMouseOutOfMapRange()
	{
		Vector2 bigRhombusPos(mPosTiles[7][0]->GetPos().x, mPosTiles[0][0]->GetPos().y);

		Vector2 bigRhombusDownPos(
			mPosTiles[0][7]->GetPos().x + mPosTiles[0][7]->GetScale().x,
			mPosTiles[7][7]->GetPos().y + mPosTiles[7][7]->GetScale().y);

		Vector2 bigRhombusScale(bigRhombusDownPos.x - bigRhombusPos.x, bigRhombusDownPos.y - bigRhombusPos.y);


		if (!math::CheckRhombusPos(bigRhombusPos, bigRhombusScale, MOUSE_POS))
		{
			if (!mMouseFollower->GetMove())
			{
				mMouseFollower->GetCurAttackSkill()->SetStartRender(false);
			}
			mMouseFollower->SetCoord(mMouseFollower->GetFinalCoord());
			mMouseFollower->SetPos(mMouseFollower->GetFinalPos());
		}
		for (int y = 0; y < mPosTiles.size(); y++)
		{
			for (int x = 0; x < mPosTiles[y].size(); x++)
			{
				Tile* p = mPosTiles[y][x];
				if (math::CheckRhombusPos(p->GetPos(), p->GetScale(), MOUSE_POS))
				{
					// ���콺�� ��ġ�� �̵����� ������ �ƴҶ�
					// ���� ��ġ�� ���ư�
					if (map[y][x] != MOVE)
					{
						mMouseFollower->SetCoord(mMouseFollower->GetFinalCoord());
						mMouseFollower->SetPos(mMouseFollower->GetFinalPos());
					}
					// ���콺�� ��ġ�� �̵����� �����϶�
					// ���콺��ġ�� Ÿ�Ϸ� �̵�
					if (map[y][x] == MOVE)
					{
						mMouseFollower->SetCoord(mPosTiles[y][x]->GetCoord());
						mMouseFollower->SetPos(mPosTiles[y][x]->GetCenterPos());
					}
				}
			}
		}
	}
	/// <summary>
	/// ���콺 ��ġ�� ��ī
	/// </summary>
	void Scene::RobotDrag()
	{
		for (int y = 0; y < mPosTiles.size(); y++)
		{
			for (int x = 0; x < mPosTiles[y].size(); x++)
			{
				// ���콺�� ��ġ�ִ� ��ī ���콺�� �������
				Tile* p = mPosTiles[y][x];
				if (math::CheckRhombusPos(p->GetPos(), p->GetScale(), MOUSE_POS))
				{
					for (UINT _i = 0; _i < mMechs.size(); _i++)
					{
						if (mPosTiles[y][x]->GetCoord() == mMechs[_i]->GetCoord())
						{
							if (mMechs[_i]->GetState() == GameObject::STATE::Broken) continue;
							//mMechs[_i]->SetMove(true);
							SetMouseFollower(mMechs[_i]);
							SetAlphaFollower(object::Instantiate(mMouseFollower->GetFinalCoord(), LAYER_TYPE::CLONE, mMouseFollower->GetMechType()));
							break;
						}
					}
				}
			}
		}
	}
	void Scene::SetMap()
	{
		for (int y = 0; y < mStruturesTiles.size(); y++)
		{
			for (int x = 0; x < mStruturesTiles[y].size(); x++)
			{
				if (mStruturesTiles[y][x]->GetType() == STRUCTURES_T::Mountain)
				{
					map[y][x] = BUILDING;
				}
			}
		}
		for (int i = 0; i < mMechs.size(); i++)
		{
			Vector2 mp = mMechs[i]->GetFinalCoord();
			map[(int)mp.y][(int)mp.x] = MECH;
		}
		for (int i = 0; i < mAliens.size(); i++)
		{
			Vector2 mp = mAliens[i]->GetFinalCoord();
			map[(int)mp.y][(int)mp.x] = ALIEN;
		}
	}
	void Scene::DrawFootTile()
	{
		for (UINT _i = 0; _i < mAliens.size(); _i++)
		{
			if (nullptr == mAliens[_i] || mAliens[_i]->GetFinalCoord() == Vector2::Zero) continue;
			Vector2 mCoord = mAliens[_i]->GetFinalCoord();
			mPosTiles[(int)mCoord.y][(int)mCoord.x]->SetTileType(TILE_T::MONSTER);
			mPosTiles[(int)mCoord.y][(int)mCoord.x]->SetSourceConstantAlpha(100);
			mPosTiles[(int)mCoord.y][(int)mCoord.x]->SetTileTexture(
				MAKE_MOVE_TILE_KEY(MOVE_TILE_T::square_gy)
				, MAKE_MOVE_TILE_PATH(MOVE_TILE_T::square_gy));
		}
		for (UINT _i = 0; _i < mMechs.size(); _i++)
		{
			Vector2 mCoord = mMechs[_i]->GetFinalCoord();
			mPosTiles[(int)mCoord.y][(int)mCoord.x]->SetTileType(TILE_T::PLAYER);
			mPosTiles[(int)mCoord.y][(int)mCoord.x]->SetSourceConstantAlpha(150);
			mPosTiles[(int)mCoord.y][(int)mCoord.x]->SetTileTexture(
				MAKE_MOVE_TILE_KEY(MOVE_TILE_T::square_b)
				, MAKE_MOVE_TILE_PATH(MOVE_TILE_T::square_b));
		}
	}
	/// <summary>
	/// ��ü Ÿ�� �ʱ�ȭ.
	/// ���߿� ������ �ٸ� Ÿ���� ������ ���� �бⰡ �ʿ���
	/// </summary>
	/// <param name="_type">�� ����</param>
	/// <param name="_hT">Ÿ�� Ÿ��</param>
	void Scene::ClearMTiles(TILE_T _type, TILE_HEAD_T _hT)
	{
		for (int y = 0; y < mPosTiles.size(); y++)
		{
			for (int x = 0; x < mPosTiles[y].size(); x++)
			{
				ClearMap();
				mBoundaryTiles[y][x]->ClearAddETCTiles();
				mArrowTiles[y][x]->SetTileTexture(SQUARE__KEY, SQUARE__PATH);
				mPosTiles[y][x]->SetTileType(TILE_T::COMMON);
				mPosTiles[y][x]->SetSourceConstantAlpha(50);
				mPosTiles[y][x]->SetTileTexture(SQUARE__KEY, SQUARE__PATH);
				mTiles[y][x]->SetTileType(TILE_T::GREEN);
				mTiles[y][x]->SetTileTexture(MAKE_TILE_KEY(TILE_T::GREEN, TILE_HEAD_T::ground)
					, MAKE_TILE_PATH(TILE_T::GREEN, TILE_HEAD_T::ground));
			}
		}
	}
	/// <summary>
	/// ���콺 ��ġ�� Ÿ�� �ٲ�
	/// </summary>
	void Scene::HighlightTile()
	{
		for (int y = 0; y < mPosOutLineTiles.size(); y++)
		{
			for (int x = 0; x < mPosOutLineTiles[y].size(); x++)
			{
				Tile* p = mPosTiles[y][x];
				if (math::CheckRhombusPos(p->GetPos(), p->GetScale(), MOUSE_POS))
				{
					if (map[y][x] != MOVE) mPosOutLineTiles[y][x]->SetTileTexture(SQUARE_Y_LINE__KEY, SQUARE_Y_LINE__PATH);
				}
				else mPosOutLineTiles[y][x]->SetTileTexture(SQUARE__KEY, SQUARE__PATH);
			}
		}
	}
	void Scene::Release()
	{
		Safe_Delete_Y_Vec(mTiles);
		Safe_Delete_Y_Vec(mPosTiles);
		Safe_Delete_Y_Vec(mPosOutLineTiles);
		Safe_Delete_Y_Vec(mBoundaryTiles);
		Safe_Delete_Y_Vec(mArrowTiles);
		Safe_Delete_Y_Vec(mEnemyEmerge);
		Safe_Delete_Y_Vec(mEffectedTiles);
		Safe_Delete_Y_Vec(mStruturesTiles);
	}
	void Scene::CheckNumInput()
	{
		if (nullptr == mMouseFollower) return;
		if (KEY_DOWN(KEYCODE_TYPE::NUM_1)) { mMouseFollower->SetSkillIdx(0); }
		if (KEY_DOWN(KEYCODE_TYPE::NUM_2)) { mMouseFollower->SetSkillIdx(1); }
		if (KEY_DOWN(KEYCODE_TYPE::NUM_3)) { mMouseFollower->SetSkillIdx(2); }
		if (KEY_DOWN(KEYCODE_TYPE::NUM_1)
			|| KEY_DOWN(KEYCODE_TYPE::NUM_2)
			|| KEY_DOWN(KEYCODE_TYPE::NUM_3))
		{
			mMouseFollower->SetPos(mMouseFollower->GetFinalPos());
			mMouseFollower->SetCoord(mMouseFollower->GetFinalCoord());

			if (!mMouseFollower->GetMove()) // ������ ��ҵǰ� �̵����ɻ��·�
			{
				mMouseFollower->SetMove(true);
				mMouseFollower->GetCurAttackSkill()->SetStartRender(false);

				mMouseFollower->SetSkillIdx(-1);
			}
			else // �̵��� ��ҵǰ� ���ݰ��ɻ��·�
			{
				mMouseFollower->SetCurAttackSkill();
				mMouseFollower->SetMove(false);
			}
		}

	}
	void Scene::MoveAlienSkill()
	{
		if (playerTurn) return;

		bool n = false;
		for (int i = 0; i < mMechs.size(); i++)
			if (mMechs[i]->GetState() == GameObject::STATE::Idle) n = true;
		if (!n) return;

		if (mAliens.size() == curAttackAlien) return;

		Alien* curAlien = mAliens[curAttackAlien];
		if (nullptr != curAlien->GetCurAttackSkill()
			&& curAlien->GetCurAttackSkill()->GetStartRender())
		{
			curAlien->SetSkillIdx(0);
			curAlien->SetCurAttackSkill();
			curAlien->SetEndAttack(true);
			curAlien->GetCurAttackSkill()->SetStartFire(true);
			//curAlien->GetCurAttackSkill()->SetEndFire(false);
		}
		if (nullptr != curAlien->GetCurAttackSkill()
			&& curAlien->GetCurAttackSkill()->GetStartFire())
		{
			curAlien->GetCurAttackSkill()->CheckDirection();
		}

		if (curAlien->GetCurAttackSkill()->CheckSkillFiring()) return;

		if (curAlien->GetEndAttack())
		{
			curAlien->GetCurAttackSkill()->SetStartRender(false);
			curAlien->GetCurAttackSkill()->SetStartFire(false);
			curAlien->GetCurAttackSkill()->SetEndFire(false);
			curAlien->SetEndAttack(false);
			return;
		}

		curAlien->AlienMapCheck(curAttackAlien);

		curAlien->AlienMoveCheck(curAttackAlien);
	}
	void Scene::MoveSkill()
	{
		if (nullptr == mMouseFollower
			|| mMouseFollower->GetMove()
			|| nullptr == mMouseFollower->GetCurAttackSkill()) return;

		if (mMouseFollower->GetCurAttackSkill()->GetStartFire())
		{
			mMouseFollower->GetCurAttackSkill()->CheckDirection();
		}

		if (mMouseFollower->CheckSkillFiring()) return;

		mMouseFollower->ActiveSkill();
		mMouseFollower->DrawSkillRangeTile();

		Scene::CheckMouseOutOfMapRange();

		if (KEY_DOWN(KEYCODE_TYPE::RBTN)
			&& !mMouseFollower->GetCurAttackSkill()->GetStartFire())
		{
			mMouseFollower->GetCurAttackSkill()->SetStartRender(false);
			mMouseFollower->SetMove(true);
		}

		if (KEY_DOWN(KEYCODE_TYPE::LBTN))
		{

			if (mMouseFollower->GetCurAttackSkill()->GetStartRender())
			{
				if (mMouseFollower->GetCurAttackSkill()->GetEndCoord() != Vector2::Zero)
				{
					// ����.
					mMouseFollower->GetCurAttackSkill()->SetStartFire(true);
					mMouseFollower->GetCurAttackSkill()->SetEndFire(false);
					moveSave.clear();
				}
			}
		}
	}
	void Scene::DrawTile()
	{
		Scene::ClearMTiles(TILE_T::GREEN, TILE_HEAD_T::ground);

		Scene::DrawFootTile();
		Scene::HighlightTile();
	}
	void Scene::UndoMove()
	{
		if (moveSave.size() != 0)
		{
			Mech* mech = mMechs[moveSave[moveSave.size() - 1].mechIdx];
			mech->SetEndMove(false);
			mech->SetCoord(Vector2(moveSave[moveSave.size() - 1].coord));
			mech->SetFinalCoord(mech->GetCoord());
			mech->SetPos(Vector2(moveSave[moveSave.size() - 1].pos));
			mech->SetFinalPos(mech->GetPos());
			moveSave.pop_back();
		}
	}
	void Scene::MoveMech()
	{
		if (KEY_DOWN(KEYCODE_TYPE::SPACE))
		{
			if (!playerTurn) playerTurn = true;
			else playerTurn = false;
			// TODO: TURN END
		}

		if (nullptr != mMouseFollower)
		{
			if (!mMouseFollower->GetMove()) return;
		}

		if (nullptr != mMouseFollower)
		{
			if (mMouseFollower->GetMove())
			{
				mMouseFollower->DrawMoveRangeTile();
				mMouseFollower->DrawMoveDirectionTile();
			}
			Scene::CheckMouseOutOfMapRange();
		}

		if (KEY_DOWN(KEYCODE_TYPE::LSHIFT))
		{
			Scene::UndoMove();
		}

		if (KEY_DOWN(KEYCODE_TYPE::RBTN)
			&& nullptr != mMouseFollower)
		{
			mMouseFollower->SetPos(mMouseFollower->GetFinalPos());
			mMouseFollower->SetCoord(mMouseFollower->GetFinalCoord());

			SetMouseFollower(nullptr);
		}

		if (KEY_DOWN(KEYCODE_TYPE::LBTN))
		{
			if (nullptr != mMouseFollower)
			{
				MoveEffectUnit(mMouseFollower);
				moveSave.push_back(Vector2_2(mMouseFollower->GetFinalCoord(), mMouseFollower->GetFinalPos(), mMouseFollower->GetMechIdx()));
				mMouseFollower->SetEndMove(true);
				mMouseFollower->SetFinalPos(mMouseFollower->GetPos());
				mMouseFollower->SetFinalCoord(mMouseFollower->GetCoord());
				SetMouseFollower(nullptr);
			}
			else
			{
				Scene::RobotDrag();
			}
		}
	}
	void Scene::MoveEffectUnit(Unit* unit, Vector2 _coord)
	{
		Vector2 idx = unit->GetFinalCoord();

		vector<Unit*>::iterator iter = effectUnits[(UINT)idx.y][(UINT)idx.x].begin();
		for (int i = 0; i < effectUnits[(UINT)idx.y][(UINT)idx.x].size(); i++)
		{
			if (effectUnits[(UINT)idx.y][(UINT)idx.x][i] == unit)
			{
				effectUnits[(UINT)idx.y][(UINT)idx.x].erase(iter + i);
				effectUnits[(int)_coord.y][(int)_coord.x].push_back(unit);
				unit->SetUnitIdx(effectUnits[(int)_coord.y][(int)_coord.x].size() - 1);
			}
		}
		unit->SetPos(mPosTiles[(int)_coord.y][(int)_coord.x]->GetCenterPos());
		unit->SetCoord(_coord);
		unit->SetFinalCoord(unit->GetCoord());
		unit->SetFinalPos(unit->GetPos());
	}
	void Scene::SetPosTiles(int _y, int _x, TILE_T _type1, MOVE_TILE_T _type2)
	{
		mPosTiles[_y][_x]->SetTileType(_type1);
		mPosTiles[_y][_x]->SetTileTexture(MAKE_MOVE_TILE_KEY(_type2)
			, MAKE_MOVE_TILE_PATH(_type2));
	}
	void Scene::SetBoundaryTiles(int y, int x, MOVE_TILE_T _type)
	{
		mBoundaryTiles[y][x]->SetETCTiles(MAKE_MOVE_TILE_KEY(_type)
			, MAKE_MOVE_TILE_PATH(_type));
	}
	void Scene::MoveEffectUnit(Unit* unit)
	{
		Vector2 idx = unit->GetFinalCoord();
		Vector2 nIdx = unit->GetCoord();

		vector<Unit*>::iterator iter = effectUnits[(UINT)idx.y][(UINT)idx.x].begin();
		for (int i = 0; i < effectUnits[(UINT)idx.y][(UINT)idx.x].size(); i++)
		{
			if (effectUnits[(UINT)idx.y][(UINT)idx.x][i] == unit)
			{
				effectUnits[(UINT)idx.y][(UINT)idx.x].erase(iter + i);
				effectUnits[(UINT)nIdx.y][(UINT)nIdx.x].push_back(unit);
				unit->SetUnitIdx(effectUnits[(UINT)nIdx.y][(UINT)nIdx.x].size() - 1);
			}
		}
	}
	void Scene::SetArrowTiles(int _y, int _x, MOVE_ARROW_T _type)
	{
		mArrowTiles[_y][_x]->SetTileTexture(MAKE_MOVE_ARROW_TILE_KEY(_type),
			MAKE_MOVE_ARROW_TILE_PATH(_type));
	}
	void Scene::AddGameObject(GameObject* obj, LAYER_TYPE layer)
	{
		mLayers[(UINT)layer].AddGameObject(obj);

		if (nullptr != dynamic_cast<Unit*>(obj) && layer != LAYER_TYPE::CLONE)
		{
			Vector2 idx = ((Unit*)obj)->GetCoord();
			effectUnits[(UINT)idx.y][(UINT)idx.x].push_back(dynamic_cast<Unit*>(obj));
			((Unit*)obj)->SetUnitIdx(effectUnits[(UINT)idx.y][(UINT)idx.x].size() - 1);
		}
	}
	Vector2 Scene::GetCoordCenterPos(Vector2 _coord)
	{
		return mPosTiles[(int)_coord.y][(int)_coord.x]->GetCenterPos();
	}
	void Scene::SetAlphaState(GameObject::STATE state)
	{
		mAlphaFollower->SetState(state);
	}

	void Scene::SetAlphaFollower(Mech* _mM)
	{
		if (nullptr != mAlphaFollower)
		{
			object::Destory(GetAlphaFollower());
			//SetAlphaState(GameObject::STATE::Death);
		}
		mAlphaFollower = _mM;
	}
	void Scene::SetMouseFollower(Mech* _mM)
	{
		mMouseFollower = _mM;
		if (nullptr == _mM) SetAlphaFollower(_mM);
	}
}
