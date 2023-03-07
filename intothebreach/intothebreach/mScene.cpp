#include "mScene.h"
#include "mTile.h"
#include "mInput.h"
#include "Building.h"
#include "Mech.h"
namespace m
{
	Scene::Scene()
		: mMouseFollower(nullptr)
		//, map(nullptr)
	{
		mLayers.reserve(5);
		mLayers.resize((UINT)LAYER_TYPE::END);
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
	void Scene::Render(HDC hdc)
	{
		for (Layer& layer : mLayers)
		{
			layer.Render(hdc);
		}
	}
	/// <summary>
	/// 타일 전체 생성
	/// 나중에 타일을 저장하면 불러올때
	/// 각 타일에 대한 처리 해주어야됨
	/// </summary>
	/// <param name="iX">타일 x 크기</param>
	/// <param name="iY">타일 y 크기</param>
	/// <param name="_type">전체 타일의 땅 타입</param>
	/// <param name="_type2">전체 타일의 타입</param>
	void Scene::MakeTile(int iX, int iY, TILE_T _type, TILE_HEAD_T _type2) {
		mTiles.resize(iY, vector<Tile*>());
		mPosTiles.resize(iY, vector<Tile*>());
		mBoundaryTiles.resize(iY, vector<Tile*>());
		mArrowTiles.resize(iY, vector<Tile*>());
		mStruturesTiles.resize(iY, vector<Building*>());
		mEffectedTiles.resize(iY, vector<Tile*>());
		mEnemyEmerge.resize(iY, vector<Tile*>());

		float fX, fY;
		float mX = (10.f * (TILE_SIZE_X / 2.f));
		float mY = TILE_SIZE_Y / 4.f;
		for (int y = 0; y < iY; y++) {
			for (int x = 0; x < iX; x++) {
				Tile* tile = new Tile(Vector2((float)x, (float)y));
				//Building* b_ = new Building(STRUCTURES_T::Mountain, Vector2((float)x, (float)y));
				fX = (float)((TILE_SIZE_X / TILE_X_DIVIDE_RECT) * (x - y) + mX);
				fY = (float)((TILE_SIZE_Y / TILE_Y_DIVIDE_RECT) * (x + y) + mY);
				tile->SetPos(Vector2(fX * 2, fY * 2));
				tile->SetTileType(_type);
				tile->SetTileTexture(MAKE_TILE_KEY(_type, _type2)
					, MAKE_TILE_PATH(_type, _type2));
				mTiles[y].push_back(tile);

				AddGameObject(tile, LAYER_TYPE::TILE);				
			}
		}
		for (int y = 0; y < iY; y++) {
			for (int x = 0; x < iX; x++) {
				Tile* posTile = new Tile(mTiles[y][x]->GetCoord());
				Tile* etcTile = new Tile(mTiles[y][x]->GetCoord());
				Tile* awTile = new Tile(mTiles[y][x]->GetCoord());
				Building* stTile = new Building(STRUCTURES_T::C_Building , mTiles[y][x]->GetCoord());
				//Tile* efTile = new Tile(mTiles[y][x]->GetCoord());
				//Tile* enETile = new Tile(mTiles[y][x]->GetCoord());

				posTile->SetTileTexture(SQUARE__KEY, SQUARE__PATH);
				posTile->SetPos(mTiles[y][x]->GetPos());	

				awTile->SetTileTexture(SQUARE__KEY, SQUARE__PATH);
				awTile->SetPos(mTiles[y][x]->GetPos());

				etcTile->InitETCTiles(4);
				etcTile->SetPos(mTiles[y][x]->GetPos());

				//stTile->SetTileTexture(SQUARE__KEY, SQUARE__PATH);
				
				//efTile->SetTileTexture(SQUARE__KEY, SQUARE__PATH);
				//efTile->SetPos(mTiles[y][x]->GetPos());

				//enETile->SetTileTexture(SQUARE__KEY, SQUARE__PATH);
				//enETile->SetPos(mTiles[y][x]->GetPos());

				mPosTiles[y].push_back(posTile);
				mBoundaryTiles[y].push_back(etcTile);
				mArrowTiles[y].push_back(awTile);
				mStruturesTiles[y].push_back(stTile);
				//mEffectedTiles[y].push_back(efTile);
				//mEnemyEmerge[y].push_back(enETile);

				AddGameObject(posTile, LAYER_TYPE::TILE);
				AddGameObject(stTile, LAYER_TYPE::TILE);
				//AddGameObject(stTile, LAYER_TYPE::TILE);
				//AddGameObject(efTile, LAYER_TYPE::TILE);
				//AddGameObject(enETile, LAYER_TYPE::TILE);

				AddGameObject(awTile, LAYER_TYPE::TILE);
				AddGameObject(etcTile, LAYER_TYPE::TILE);
			}
		}
		Building* stTile = new Building(STRUCTURES_T::Mountain, mTiles[3][3]->GetCoord());
		stTile->SetPos(mTiles[3][3]->GetCenterPos());
		mStruturesTiles[3][3] =stTile;

		AddGameObject(stTile, LAYER_TYPE::TILE);

		Building* stTile1 = new Building(STRUCTURES_T::Mountain, mTiles[1][2]->GetCoord());
		stTile1->SetPos(mTiles[1][2]->GetCenterPos());
		mStruturesTiles[1][2] = stTile1;

		AddGameObject(stTile1, LAYER_TYPE::TILE);

		SetMap(iY, iX);
	}
	/// <summary>
	/// 표기했던 이동가능거리 초기화.
	/// 메카의 위치(FinalPos)가 바뀌면 불러옴.
	/// </summary>
	void Scene::ClearMap() {
		for (int y = 0; y < mPosTiles.size(); y++) {
			for (int x = 0; x < mPosTiles[y].size(); x++) {
				map[y][x] = 0;
				cmap[y][x] = 0;
			}
		}
	}

	void Scene::t(int level) {
		float direct[4][2] = { {0, 1},{-1, 0} ,{1, 0},{0, -1} };
	}
	/// <summary>
	/// 최단거리의 이동거리 출력
	/// 화살표 리소스의 분기문 처리해야됨
	/// </summary>
	void Scene::DrawMoveDirectionTile() {
		for (int y = 0; y < mPosTiles.size(); y++) {
			for (int x = 0; x < mPosTiles[y].size(); x++) {
				if (Scene::CheckRhombusPos(mPosTiles[y][x], MOUSE_POS)) {
					// 이동가능 거리 인지 확인
					if (map[y][x] != 1) continue;
					if (mMouseFollower->GetFinalCoord() == mMouseFollower->GetCoord()) continue;

					int moveLimit = 3;

					struct Vector2_1 {
						Vector2 pos;
						int level;
					};
					list<Vector2_1> queue;

					queue.push_back(Vector2_1(mMouseFollower->GetFinalCoord(), 0));

					float direct[4][2] = { {0, 1},{-1, 0} ,{1, 0},{0, -1} };

					bool find = false;

					while (!queue.empty()) {
						Vector2_1 now = queue.front();
						queue.pop_front();

						for (int i = 0; i < 4; i++) {
							float dx = now.pos.x + direct[i][0];
							float dy = now.pos.y + direct[i][1];

							if (dx < 0 || dy < 0 || dx >= mTiles[0].size() || dy >= mTiles.size()) continue;
							if (mMouseFollower->GetFinalCoord().x == dx
								&& mMouseFollower->GetFinalCoord().y == dy) continue;
							if (map[(int)dy][(int)dx] == -1) continue;
							queue.push_back(Vector2_1(Vector2(dx, dy), now.level + 1));
							shortQue.push_back(Vector2(dx, dy));
							cmap[(int)dy][(int)dx] = 1;
							break;
						}
						if (find) break;
					}


					//Vector2 prevPos = mMouseFollower->GetFinalCoord();
					//Vector2 curPos = mMouseFollower->GetCoord();
					//// 클릭 후 마우스가 메카에서 벗어나야지 화살표를 찍음.
					//if (prevPos == curPos) continue;

					//// 첫 화살표의 표시는 while문에 걸리지 않음.

					//ARROW_T type = (ARROW_T)0;
					//Vector2 mp{};
					/*while (prevPos != curPos) {
						
						mp = prevPos;
						if (prevPos.y < curPos.y && map[(int)prevPos.y + 1][(int)prevPos.x] != -1) {
							prevPos.y++;
							if (prevPos.y == curPos.y) {
								if (prevPos.x < curPos.x) type = ARROW_T::ARROW_COR_R_U;
								if (prevPos.x > curPos.x) type = ARROW_T::ARROW_COR_L_U;
							}
							else {
								type = ARROW_T::ARROW_D_U;
							}
						}
						else if (prevPos.y > curPos.y && map[(int)prevPos.y - 1][(int)prevPos.x] != -1) {
							prevPos.y--;
							if (prevPos.y == curPos.y) {
								if (prevPos.x < curPos.x) type = ARROW_T::ARROW_COR_R_D;
								if (prevPos.x > curPos.x) type = ARROW_T::ARROW_COR_L_D;
							}
							else {
								type = ARROW_T::ARROW_D_U;
							}
						}
						else if (prevPos.x < curPos.x && map[(int)prevPos.y][(int)prevPos.x + 1] != -1) {
							prevPos.x++;
							type = ARROW_T::ARROW_L_R;
						}
						else if (prevPos.x > curPos.x && map[(int)prevPos.y][(int)prevPos.x - 1] != -1) {
							prevPos.x--;
							type = ARROW_T::ARROW_L_R;
						}
						
						shortQue.push_back(Vector2(prevPos.x, prevPos.y));
						mArrowTiles[(int)prevPos.y][(int)prevPos.x]->SetTileTexture(MAKE_ARROW_TILE_KEY(type),
							MAKE_ARROW_TILE_PATH(type));
					}
					if(mp.x < prevPos.x) type = ARROW_T::ARROW_R;
					if(mp.x > prevPos.x) type = ARROW_T::ARROW_L;
					if(mp.y < prevPos.y) type = ARROW_T::ARROW_D;
					if(mp.y > prevPos.y) type = ARROW_T::ARROW_U;

					mArrowTiles[(int)prevPos.y][(int)prevPos.x]->SetTileTexture(MAKE_ARROW_TILE_KEY(type),
						MAKE_ARROW_TILE_PATH(type));*/
				}
			}
		}
	}
	/// <summary>
	/// 마우스의 위치에 따라 메카 위치 설정
	/// </summary>
	void Scene::CheckMouseOutOfMapRange() {
		for (int y = 0; y < mPosTiles.size(); y++) {
			for (int x = 0; x < mPosTiles[y].size(); x++) {
				if (CheckRhombusPos(mPosTiles[y][x], MOUSE_POS)) {
					// 마우스의 위치가 이동가능 범위가 아닐때
					if (map[y][x] != 1) {
						mMouseFollower->SetCoord(mMouseFollower->GetFinalCoord());
						mMouseFollower->SetPos(mMouseFollower->GetFinalPos());
					}
					// 마우스의 위치가 이동가능 범위일때
					if (map[y][x] == 1) {
						mMouseFollower->SetCoord(mPosTiles[y][x]->GetCoord());
						mMouseFollower->SetPos(mPosTiles[y][x]->GetCenterPos());
					}
				}
			}
		}
	}
	/// <summary>
	/// 마우스 위치에 메카
	/// </summary>
	void Scene::RobotDrag() {
		for (int y = 0; y < mPosTiles.size(); y++) {
			for (int x = 0; x < mPosTiles[y].size(); x++) {
				// 마우스의 위치있는 메카 마우스에 따라오게
				if (CheckRhombusPos(mPosTiles[y][x], MOUSE_POS)) {
					for (UINT _i = 0; _i < mMechs.size(); _i++) {
						if (mPosTiles[y][x]->GetCoord() == mMechs[_i]->GetCoord()) {
							SetMouseFollower(mMechs[_i]);
						}
					}
				}
			}
		}
	}
	/// <summary>
	/// 이동범위 타일 바꾸는 BFS
	/// </summary>
	void Scene::DrawMoveRangeTile() {
		// 임시 이동 범위
		int moveLimit = 3;

		// 임시 구조체 레벨이 포함됨.
		struct Vector2_1 {
			Vector2 pos;
			int level;
		};
		list<Vector2_1> queue;
		queue.push_back(Vector2_1(mMouseFollower->GetFinalCoord(), 0));
		mPosTiles[(int)mMouseFollower->GetFinalCoord().y][(int)mMouseFollower->GetFinalCoord().x]->SetTileType(TILE_T::MOVE_RANGE);
		mPosTiles[(int)mMouseFollower->GetFinalCoord().y][(int)mMouseFollower->GetFinalCoord().x]->SetTileTexture(
			MAKE_MOVE_TILE_KEY(MOVE_TILE_T::square_g)
			, MAKE_MOVE_TILE_PATH(MOVE_TILE_T::square_g));

		for (int y = 0; y < mStruturesTiles.size(); y++) {
			for (int x = 0; x < mStruturesTiles[y].size(); x++) {
				if (mStruturesTiles[y][x]->GetType() == STRUCTURES_T::Mountain) {
					map[y][x] = -1;
					cmap[y][x] = -1;
				}
			}
		}
		float direct[4][2] = {{0, 1},{-1, 0} ,{1, 0},{0, -1}};

		bool find = false;

		while (!queue.empty()) {
			Vector2_1 now = queue.front();
			queue.pop_front();

			for (int i = 0; i < 4; i++) {
				float dx = now.pos.x + direct[i][0];
				float dy = now.pos.y + direct[i][1];

				if (dx < 0 || dy < 0 || dx >= mTiles[0].size() || dy >= mTiles.size()) continue;
				if (mMouseFollower->GetFinalCoord().x == dx
					&& mMouseFollower->GetFinalCoord().y == dy) continue;
				if (map[(int)dy][(int)dx] == -1) continue;
				if (now.level >= moveLimit) {
					find = true;
					break;
				}
				map[(int)dy][(int)dx] = 1;

				
				queue.push_back(Vector2_1(Vector2(dx, dy), now.level + 1));
				mPosTiles[(int)dy][(int)dx]->SetTileType(TILE_T::MOVE_RANGE);
				mPosTiles[(int)dy][(int)dx]->SetTileTexture(MAKE_MOVE_TILE_KEY(MOVE_TILE_T::square_g)
					, MAKE_MOVE_TILE_PATH(MOVE_TILE_T::square_g));
			}
			if (find) break;
		}
		// 이동범위 경계선 그리기
		for (int y = 0; y < mPosTiles.size(); y++) {
			for (int x = 0; x < mPosTiles[y].size(); x++) {
				if (mPosTiles[y][x]->GetTileType() == TILE_T::MOVE_RANGE) {
					MOVE_TILE_T type = (MOVE_TILE_T)0;
					if (y + 1 < mPosTiles.size() && mPosTiles[y + 1][x]->GetTileType() != TILE_T::MOVE_RANGE) {
						mBoundaryTiles[y][x]->SetETCTiles(MAKE_MOVE_TILE_KEY(MOVE_TILE_T::square_g_d)
							, MAKE_MOVE_TILE_PATH(MOVE_TILE_T::square_g_d));
					}
					if (y - 1 >= 0 && mPosTiles[y - 1][x]->GetTileType() != TILE_T::MOVE_RANGE) {
						mBoundaryTiles[y][x]->SetETCTiles(MAKE_MOVE_TILE_KEY(MOVE_TILE_T::square_g_u)
							, MAKE_MOVE_TILE_PATH(MOVE_TILE_T::square_g_u));
					}
					if (x - 1 >= 0 &&  mPosTiles[y][x - 1]->GetTileType() != TILE_T::MOVE_RANGE) {
						mBoundaryTiles[y][x]->SetETCTiles(MAKE_MOVE_TILE_KEY(MOVE_TILE_T::square_g_l)
							, MAKE_MOVE_TILE_PATH(MOVE_TILE_T::square_g_l));
					}
					if (x + 1 < mPosTiles[y].size() && mPosTiles[y][x+1]->GetTileType() != TILE_T::MOVE_RANGE) {
						mBoundaryTiles[y][x]->SetETCTiles(MAKE_MOVE_TILE_KEY(MOVE_TILE_T::square_g_r)
							, MAKE_MOVE_TILE_PATH(MOVE_TILE_T::square_g_r));
					}
					
					
				}
			}
		}
	}
	/// <summary>
	/// 전체 타일 초기화.
	/// 나중에 맵위에 다른 타일의 정보에 대한 분기가 필요함
	/// </summary>
	/// <param name="_type">땅 종류</param>
	/// <param name="_hT">타일 타입</param>
	void Scene::ClearMTiles(TILE_T _type, TILE_HEAD_T _hT) {
		for (int y = 0; y < mPosTiles.size(); y++) {
			for (int x = 0; x < mPosTiles[y].size(); x++) {
				
				mBoundaryTiles[y][x]->ClearAddETCTiles();
				mArrowTiles[y][x]->SetTileTexture(SQUARE__KEY, SQUARE__PATH);
				mPosTiles[y][x]->SetTileType(TILE_T::COMMON);
				mTiles[y][x]->SetTileType(TILE_T::GREEN);
				mTiles[y][x]->SetTileTexture(MAKE_TILE_KEY(TILE_T::GREEN, TILE_HEAD_T::ground)
					, MAKE_TILE_PATH(TILE_T::GREEN, TILE_HEAD_T::ground));
			}
		}
	}
	/// <summary>
	/// 사각형 땅의 각 꼭짓점을 구하고
	/// 꼭짓점끼리의 절편과 기울기를 이용해 마름모의 좌표를 구함
	/// </summary>
	/// <param name="tile">꼭짓점을 추출할 타일</param>
	/// <param name="_pos">현재 위치(마우스커서)</param>
	/// <returns>현재위치가 타일의 마름모 좌표 내부에 있는지 여부</returns>
	bool Scene::CheckRhombusPos(Tile* tile, Vector2 _pos) {
		Vector2 vertex[4];
		float gradient[4];
		float intercept[4];
		float direct[4][2] = {
			{0, (tile->GetScale().y / 2)},
			{(tile->GetScale().x / 2), 0},
			{tile->GetScale().x, (tile->GetScale().y / 2)},
			{(tile->GetScale().x / 2), tile->GetScale().y}
		};
		for (size_t i = 0; i < 4; i++) {
			vertex[i].x = tile->GetPos().x + direct[i][0];
			vertex[i].y = tile->GetPos().y + direct[i][1];
		}
		for (size_t i = 0; i < 4; i++) {
			gradient[i] = ((vertex[i].y - vertex[(i + 1) % 4].y) / (vertex[i].x - vertex[(i + 1) % 4].x));
			intercept[i] = vertex[i].y - gradient[i] * vertex[i].x;
		}
		float rY = _pos.y;
		float rX = _pos.x;

		if (gradient[0] * rX + intercept[0] < rY
			&& gradient[1] * rX + intercept[1] < rY
			&& gradient[2] * rX + intercept[2] > rY
			&& gradient[3] * rX + intercept[3] > rY) {
			return true;
		}
		else return false;
	}
	/// <summary>
	/// 마우스 위치의 타일 바꿈
	/// </summary>
	void Scene::HighlightTile() {
		for (int y = 0; y < mPosTiles.size(); y++) {
			for (int x = 0; x < mPosTiles[y].size(); x++) {
				if (Scene::CheckRhombusPos(mPosTiles[y][x], MOUSE_POS)) {
					mPosTiles[y][x]->SetTileTexture(SQUARE_Y_LINE__KEY, SQUARE_Y_LINE__PATH);
				}
				else {
					mPosTiles[y][x]->SetTileTexture(SQUARE__KEY, SQUARE__PATH);
				}
			}
		}
	}
	void Scene::Release()
	{
		Safe_Delete_Y_Vec(mTiles);
		Safe_Delete_Y_Vec(mPosTiles);
		Safe_Delete_Y_Vec(mBoundaryTiles);
		Safe_Delete_Y_Vec(mArrowTiles);
		Safe_Delete_Y_Vec(mEnemyEmerge);
		Safe_Delete_Y_Vec(mEffectedTiles);
		Safe_Delete_Y_Vec(mStruturesTiles);
	}
	void Scene::AddGameObject(GameObject* obj, LAYER_TYPE layer)
	{
		mLayers[(UINT)layer].AddGameObject(obj);
	}
}
