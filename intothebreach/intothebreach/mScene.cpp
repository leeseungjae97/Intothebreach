#include "mScene.h"
#include "mLayer.h"
#include "mUnit.h"
#include "mTile.h"
#include "Building.h"
#include "Mech.h"
#include "Alien.h"
#include "mSkill.h"

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
		index = -1;
		isAttack = false;
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
		for (Layer& layer : mLayers)
		{
			vector<GameObject*>& gameObjects
				= layer.GetGameObjects();

			for (vector<GameObject*>::iterator iter = gameObjects.begin()
				; iter != gameObjects.end(); )
			{
				if ((*iter)->GetState() == GameObject::STATE::Death)
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
		swprintf_s(szFloat, 500, L"index : %d", index);
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

		AddGameObject(stTile, LAYER_TYPE::TILE);

		Building* stTile1 = new Building(STRUCTURES_T::Mountain, mTiles[1][2]->GetCoord());
		stTile1->SetPos(mTiles[1][2]->GetCenterPos());
		mStruturesTiles[1][2] = stTile1;

		AddGameObject(stTile1, LAYER_TYPE::TILE);

		Building* stTile2 = new Building(STRUCTURES_T::Mountain, mTiles[2][0]->GetCoord());
		stTile2->SetPos(mTiles[2][0]->GetCenterPos());
		mStruturesTiles[2][0] = stTile2;

		AddGameObject(stTile2, LAYER_TYPE::TILE);

		SetMap(0, 0);
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
	void Scene::ClearSkillRangeMap()
	{
		for (int y = 0; y < mPosTiles.size(); y++)
		{
			for (int x = 0; x < mPosTiles[y].size(); x++)
			{
				skill_range_map[y][x] = 0;
			}
		}
	}
	/// <summary>
	/// �ִܰŸ��� �̵��Ÿ� ���
	/// ȭ��ǥ ���ҽ��� �б⹮ ó���ؾߵ�
	/// </summary>
	void Scene::DrawMoveDirectionTile()
	{
		for (int y = 0; y < mPosTiles.size(); y++)
		{
			for (int x = 0; x < mPosTiles[y].size(); x++)
			{
				Tile* p = mPosTiles[y][x];
				if (math::CheckRhombusPos(p->GetPos(), p->GetScale(), MOUSE_POS))
				{

					// �̵����� �Ÿ� ���� Ȯ��
					if (map[y][x] == MECH)
					{
						if (mMouseFollower->GetCoord().x != x &&
							mMouseFollower->GetCoord().y != y)
						{
							continue;
						}
					}
					if (mMouseFollower->GetFinalCoord() == mMouseFollower->GetCoord()) continue;
					if (map[y][x] != MOVE)
					{
						SetAlphaState(GameObject::STATE::Death);
						continue;
					}

					Vector2 prevCoord = mMouseFollower->GetFinalCoord();
					Vector2 curCoord = mMouseFollower->GetCoord();

					SetAlphaState(GameObject::STATE::Idle);

					list<Vector2> directQue;
					Vector2_1 now(Vector2(Vector2::Minus), 0, 0);

					while (!pathQueue.empty() && now.coord != curCoord)
					{
						now = pathQueue.back();
						pathQueue.pop_back();
					}
					directQue.push_back(Vector2(now.coord.x, now.coord.y));

					while (!pathQueue.empty() && now.coord != prevCoord)
					{
						now = pathQueue[now.parentIdx];
						directQue.push_back(Vector2(now.coord.x, now.coord.y));
					}

					ARROW_T type = (ARROW_T)0;

					Vector2 coord = Vector2::Zero;
					Vector2 nCoord = Vector2::Zero;

					vector<Vector2> mVec;
					while (!directQue.empty())
					{
						coord = directQue.back();
						mVec.push_back(Vector2(coord.x, coord.y));
						directQue.pop_back();
						if (!directQue.empty())
						{
							nCoord = directQue.back();
							// ������ pos���� ��ֹ��� ��ġ�� ������ ���̱� ������ �������� ���ص� �ȴ�.
							if (coord.y != nCoord.y)
							{
								type = ARROW_T::ARROW_D_U;
								if (coord.y < nCoord.y)
								{
									if (mVec.size() > 1 && coord.x < mVec[mVec.size() - 2].x) type = ARROW_T::ARROW_COR_R_D;
									if (mVec.size() > 1 && coord.x > mVec[mVec.size() - 2].x) type = ARROW_T::ARROW_COR_L_D;
								}
								if (coord.y > nCoord.y)
								{
									if (mVec.size() > 1 && coord.x < mVec[mVec.size() - 2].x) type = ARROW_T::ARROW_COR_R_U;
									if (mVec.size() > 1 && coord.x > mVec[mVec.size() - 2].x) type = ARROW_T::ARROW_COR_L_U;
								}
							}
							else if (coord.x != nCoord.x)
							{
								type = ARROW_T::ARROW_L_R;
								if (coord.x < nCoord.x)
								{
									if (mVec.size() > 1 && coord.y < mVec[mVec.size() - 2].y) type = ARROW_T::ARROW_COR_R_D;
									if (mVec.size() > 1 && coord.y > mVec[mVec.size() - 2].y) type = ARROW_T::ARROW_COR_R_U;
								}
								if (coord.x > nCoord.x)
								{
									if (mVec.size() > 1 && coord.y < mVec[mVec.size() - 2].y) type = ARROW_T::ARROW_COR_L_D;
									if (mVec.size() > 1 && coord.y > mVec[mVec.size() - 2].y) type = ARROW_T::ARROW_COR_L_U;
								}
							}
							if (coord == prevCoord)
							{
								if (coord.x < nCoord.x) type = ARROW_T::ARROW_ST_L;
								if (coord.x > nCoord.x) type = ARROW_T::ARROW_ST_R;
								if (coord.y < nCoord.y) type = ARROW_T::ARROW_ST_U;
								if (coord.y > nCoord.y) type = ARROW_T::ARROW_ST_D;
							}
						}
						if (mVec.size() > 1 && coord == curCoord)
						{
							if (mVec[mVec.size() - 2].x < curCoord.x) type = ARROW_T::ARROW_R;
							if (mVec[mVec.size() - 2].x > curCoord.x) type = ARROW_T::ARROW_L;
							if (mVec[mVec.size() - 2].y < curCoord.y) type = ARROW_T::ARROW_D;
							if (mVec[mVec.size() - 2].y > curCoord.y) type = ARROW_T::ARROW_U;
						}
						if (coord.x < 0 || coord.y < 0) continue;
						mArrowTiles[(int)coord.y][(int)coord.x]->SetTileTexture(MAKE_ARROW_TILE_KEY(type),
							MAKE_ARROW_TILE_PATH(type));
					}
				}
			}
		}
	}
	/// <summary>
	/// ���콺�� ��ġ�� ���� ��ī ��ġ ����
	/// </summary>
	void Scene::CheckMouseOutOfMapRange()
	{
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
							SetMouseFollower(mMechs[_i]);
							SetAlphaFollower(object::Instantiate(mMouseFollower->GetFinalCoord(), LAYER_TYPE::CLONE, mMouseFollower->GetMechType()));
						}
					}
				}
			}
		}
	}
	void Scene::SetMap(int y, int x)
	{
		//map = new int* [y];
		//for (int i = 0; i < y; i++) {
		//	map[i] = new int[x];
		//}
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
	/// �̵����� Ÿ�� �ٲٴ� BFS
	/// </summary>
	void Scene::DrawMoveRangeTile()
	{
		int moveLimit = mMouseFollower->GetMove();

		list<Vector2_1>queue;

		Vector2 stPos = mMouseFollower->GetFinalCoord();
		queue.push_back(Vector2_1(stPos, 0, -1));
		pathQueue.push_back(Vector2_1(stPos, 0, -1));

		SetMap(0, 0);
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

				if (dx < 0 || dy < 0 || dx >= mTiles[0].size() || dy >= mTiles.size()) continue;
				if (stPos.x == dx
					&& stPos.y == dy) continue;
				if (map[(int)dy][(int)dx] == BUILDING) continue;
				if (map[(int)dy][(int)dx] == MOVE) continue;
				if (now.level >= moveLimit)
				{
					find = true;
					break;
				}


				queue.push_back(Vector2_1(Vector2(dx, dy), now.level + 1, idx));
				pathQueue.push_back(Vector2_1(Vector2(dx, dy), now.level + 1, idx));

				if (map[(int)dy][(int)dx] == MECH
					|| map[(int)dy][(int)dx] == ALIEN) continue;
				mPosTiles[(int)dy][(int)dx]->SetTileType(TILE_T::MOVE_RANGE);
				map[(int)dy][(int)dx] = MOVE;
				mPosTiles[(int)dy][(int)dx]->SetTileTexture(MAKE_MOVE_TILE_KEY(MOVE_TILE_T::square_g)
					, MAKE_MOVE_TILE_PATH(MOVE_TILE_T::square_g));
			}
			if (find) break;
		}



		DrawOutLineTile();
	}
	//// �̵����� ��輱 �׸���
	void Scene::DrawOutLineTile()
	{
		for (int y = 0; y < mPosTiles.size(); y++)
		{
			for (int x = 0; x < mPosTiles[y].size(); x++)
			{
				if (mPosTiles[y][x]->GetTileType() == TILE_T::MOVE_RANGE)
				{
					// x,y Ÿ�� �ֺ� 4�������� �˻��ؼ� MOVE tile�� �ƴϸ� �ܰ��� �߰�.
					if (y + 1 < mPosTiles.size()
						&& mPosTiles[y + 1][x]->GetTileType() != TILE_T::MOVE_RANGE)
					{
						mBoundaryTiles[y][x]->SetETCTiles(MAKE_MOVE_TILE_KEY(MOVE_TILE_T::square_g_d)
							, MAKE_MOVE_TILE_PATH(MOVE_TILE_T::square_g_d));
					}
					if (y - 1 >= 0
						&& mPosTiles[y - 1][x]->GetTileType() != TILE_T::MOVE_RANGE)
					{
						mBoundaryTiles[y][x]->SetETCTiles(MAKE_MOVE_TILE_KEY(MOVE_TILE_T::square_g_u)
							, MAKE_MOVE_TILE_PATH(MOVE_TILE_T::square_g_u));
					}
					if (x - 1 >= 0
						&& mPosTiles[y][x - 1]->GetTileType() != TILE_T::MOVE_RANGE)
					{
						mBoundaryTiles[y][x]->SetETCTiles(MAKE_MOVE_TILE_KEY(MOVE_TILE_T::square_g_l)
							, MAKE_MOVE_TILE_PATH(MOVE_TILE_T::square_g_l));
					}
					if (x + 1 < mPosTiles[y].size()
						&& mPosTiles[y][x + 1]->GetTileType() != TILE_T::MOVE_RANGE)
					{
						mBoundaryTiles[y][x]->SetETCTiles(MAKE_MOVE_TILE_KEY(MOVE_TILE_T::square_g_r)
							, MAKE_MOVE_TILE_PATH(MOVE_TILE_T::square_g_r));
					}


				}
			}
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
				pathQueue.clear();
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
					if (map[y][x] != MOVE)
					{
						mPosOutLineTiles[y][x]->SetTileTexture(SQUARE_Y_LINE__KEY, SQUARE_Y_LINE__PATH);
					}
				}
				else
				{
					mPosOutLineTiles[y][x]->SetTileTexture(SQUARE__KEY, SQUARE__PATH);
				}
			}
		}
	}
	void Scene::ActiveSkill()
	{
		if (index == -1) return;

		for (int y = 0; y < mPosTiles.size(); y++)
		{
			for (int x = 0; x < mPosTiles[y].size(); x++)
			{
				//if (skill_range_map[y][x] != MOVE) continue;
				Tile* p = mPosTiles[y][x];
				if (math::CheckRhombusPos(p->GetPos(), p->GetScale(), MOUSE_POS))
				{
					mMouseFollower->DrawSkill(p->GetCoord(), index);
					mMouseFollower->GetCurAttackSkill()->SetStartRender(true);
					if (KEY_DOWN(KEYCODE_TYPE::LBTN))
					{
						mMouseFollower->GetCurAttackSkill()->SetStFire(true);
					}
				}
			}
		}
		// ���ݿϷ��ϸ� clear
		ClearSkillRangeMap();
	}
	void Scene::DrawSkillRangeTile()
	{
		if (nullptr == mMouseFollower) return;
		if (index == -1) return;

		list<Vector2_1>queue;

		Vector2 stPos = mMouseFollower->GetFinalCoord();
		queue.push_back(Vector2_1(stPos, 0, -1));
		pathQueue.push_back(Vector2_1(stPos, 0, -1));

		SetMap(0, 0);
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

				if (dx < 0 || dy < 0 || dx >= mTiles[0].size() || dy >= mTiles.size()) continue;
				if (skill_range_map[(int)dy][(int)dx] == MOVE) continue;
				bool rangeCheck = false;
				for (int _i = 0; _i < 4; _i++)
				{
					if (stPos.x + direct[_i][0] == dx
						&& stPos.y + direct[_i][1] == dy) rangeCheck = true;
				}

				if ((stPos.y != dy && stPos.x == dx)
					|| (stPos.x != dx && stPos.y == dy))
				{
					queue.push_back(Vector2_1(Vector2(dx, dy), now.level + 1, idx));

					if (rangeCheck) continue;
					mPosTiles[(int)dy][(int)dx]->SetTileType(TILE_T::MOVE_RANGE);
					skill_range_map[(int)dy][(int)dx] = MOVE;
					mPosTiles[(int)dy][(int)dx]->SetTileTexture(MAKE_MOVE_TILE_KEY(MOVE_TILE_T::square_r)
						, MAKE_MOVE_TILE_PATH(MOVE_TILE_T::square_r));
				}
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
	void Scene::MoveMech()
	{
		Scene::ClearMTiles(TILE_T::GREEN, TILE_HEAD_T::ground);
		if (nullptr != mMouseFollower)
		{
			if (isAttack == -1)
			{
				Scene::DrawMoveRangeTile();
				Scene::DrawMoveDirectionTile();
			}
			else
			{
				Scene::DrawSkillRangeTile();
				Scene::ActiveSkill();
			}
			Scene::CheckMouseOutOfMapRange();
		}

		if (KEY_DOWN(KEYCODE_TYPE::RBTN) && nullptr != mMouseFollower)
		{
			if(index != -1 ) mMouseFollower->GetCurAttackSkill()->SetStartRender(false);
			isAttack = -1;
			index = -1;
			mMouseFollower->SetPos(mMouseFollower->GetFinalPos());
			mMouseFollower->SetCoord(mMouseFollower->GetFinalCoord());
			SetMouseFollower(nullptr);
		}

		if (KEY_DOWN(KEYCODE_TYPE::LBTN))
		{
			isAttack = -1;
			
			if (nullptr != mMouseFollower 
				&& nullptr != mMouseFollower->GetCurAttackSkill()
				&& !mMouseFollower->GetCurAttackSkill()->GetStFire())
			{
				//mMouseFollower->GetSkill(index)->SetStartRender(false);
				MoveEffectUnit(mMouseFollower);
				mMouseFollower->SetFinalPos(mMouseFollower->GetPos());
				mMouseFollower->SetFinalCoord(mMouseFollower->GetCoord());

				SetMouseFollower(nullptr);
			}
			else
			{
				Scene::RobotDrag();
			}
			
		}

		Scene::DrawFootTile();
		Scene::HighlightTile();

		if (index != -1 
			&& nullptr != mMouseFollower 
			&& nullptr != mMouseFollower->GetCurAttackSkill()
			&& mMouseFollower->GetCurAttackSkill()->GetEndFire())
		{
			Skill* p = mMouseFollower->GetCurAttackSkill();
			if(effectUnits[(UINT)p->GetEndCoord().y][(UINT)p->GetEndCoord().x].size() != 0)
				effectUnits[(UINT)p->GetEndCoord().y][(UINT)p->GetEndCoord().x][0]->Hit(1);
			p->SetEndFire(false);
			p->SetStFire(false);
			p->SetStartRender(false);
			SetMouseFollower(nullptr);
			index = -1;
		}
		if (KEY_UP(KEYCODE_TYPE::NUM_1)) { index = 0; }
		if (KEY_UP(KEYCODE_TYPE::NUM_2)) { index = 1; }
		if (KEY_UP(KEYCODE_TYPE::NUM_3)) { index = 2; }
		if (KEY_UP(KEYCODE_TYPE::NUM_1)
			|| KEY_UP(KEYCODE_TYPE::NUM_2)
			|| KEY_UP(KEYCODE_TYPE::NUM_3))
		{
			isAttack *= -1;
			if (nullptr != mMouseFollower)
			{
				GetAlphaFollower()->SetState(GameObject::STATE::Death);
			}
		}

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
			}
		}
	}
	void Scene::AddGameObject(GameObject* obj, LAYER_TYPE layer)
	{
		mLayers[(UINT)layer].AddGameObject(obj);

		if (nullptr != dynamic_cast<Unit*>(obj) && layer != LAYER_TYPE::CLONE)
		{
			Vector2 idx = ((Unit*)obj)->GetCoord();
			effectUnits[(UINT)idx.y][(UINT)idx.x].push_back(dynamic_cast<Unit*>(obj));
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
