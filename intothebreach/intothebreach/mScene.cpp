#include "mScene.h"
#include "mTile.h"
#include "mInput.h"
#include "Mech.h"
namespace m
{
	Scene::Scene()
		: mMouseFollower(nullptr)
		, map(nullptr)
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
	void Scene::MakeTile(int iX, int iY, TILE_T _type, TILE_HEAD_T _type2) {
		mTiles.resize(iX, vector<Tile*>());
		mPosTiles.resize(iY, vector<Tile*>());

		float fX, fY;
		float mX = (10.f * (TILE_SIZE_X / 2.f));
		float mY = TILE_SIZE_Y / 4.f;
		for (int y = 0; y < iY; y++) {
			for (int x = 0; x < iX; x++) {
				Tile* tile = new Tile(Vector2((float)x, (float)y));
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
				posTile->SetTileTexture(SQUARE__KEY, SQUARE__PATH);
				posTile->SetPos(mTiles[y][x]->GetPos());
				mPosTiles[y].push_back(posTile);
				AddGameObject(posTile, LAYER_TYPE::TILE);
			}
		}
		SetMap(iY, iX);
	}
	void Scene::ClearMap() {
		for (int y = 0; y < mPosTiles.size(); y++) {
			for (int x = 0; x < mPosTiles[y].size(); x++) {
				map[y][x] = 0;
			}
		}
	}
	void Scene::DrawMoveDirectionTile() {
		for (int y = 0; y < mPosTiles.size(); y++) {
			for (int x = 0; x < mPosTiles[y].size(); x++) {
				if (Scene::CheckRhombusPos(mPosTiles[y][x], MOUSE_POS)) {
					if (map[y][x] != 1) continue;

					Vector2 prevPos = mMouseFollower->GetFinalCoord();
					Vector2 curPos = mMouseFollower->GetCoord();
					list<Vector2> shortQue;
					mTiles[(int)curPos.y][(int)curPos.x]->SetTileTexture(MAKE_TILE_KEY(TILE_T::SNOW, TILE_HEAD_T::ground)
						, MAKE_TILE_PATH(TILE_T::SNOW, TILE_HEAD_T::ground));

					while (prevPos != curPos) {
						mTiles[(int)prevPos.y][(int)prevPos.x]->SetTileTexture(MAKE_TILE_KEY(TILE_T::SNOW, TILE_HEAD_T::ground)
							, MAKE_TILE_PATH(TILE_T::SNOW, TILE_HEAD_T::ground));

						if (prevPos.y < curPos.y) shortQue.push_back(Vector2(prevPos.x, ++prevPos.y));
						else if (prevPos.y > curPos.y) shortQue.push_back(Vector2(prevPos.x, --prevPos.y));
						else if (prevPos.x < curPos.x) shortQue.push_back(Vector2(++prevPos.x, prevPos.y));
						else if ((prevPos.x > curPos.x)) shortQue.push_back(Vector2(--prevPos.x, prevPos.y));
					}
				}
			}
		}
	}
	void Scene::CheckMouseOutOfMapRange() {
		for (int y = 0; y < mPosTiles.size(); y++) {
			for (int x = 0; x < mPosTiles[y].size(); x++) {
				if (CheckRhombusPos(mPosTiles[y][x], MOUSE_POS)) {
					if (map[y][x] != 1 && nullptr != mMouseFollower) {
						mMouseFollower->SetCoord(mMouseFollower->GetFinalCoord());
						mMouseFollower->SetPos(mMouseFollower->GetFinalPos());
					}
					if (map[y][x] == 1 && nullptr != mMouseFollower) {
						mMouseFollower->SetCoord(mPosTiles[y][x]->GetCoord());
						mMouseFollower->SetPos(mPosTiles[y][x]->GetCenterPos());
					}
				}
			}
		}
	}
	void Scene::RobotDrag() {
		for (int y = 0; y < mPosTiles.size(); y++) {
			for (int x = 0; x < mPosTiles[y].size(); x++) {
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
	void Scene::DrawMoveRangeTile() {
		int moveLimit = 3;
		struct Vector2_1 {
			Vector2 pos;
			int level;
		};
		list<Vector2_1> queue;

		queue.push_back(Vector2_1(mMouseFollower->GetFinalCoord(), 0));

		float direct[4][2] = {{0, 1},{-1, 0} ,{1, 0},{0, -1}};

		bool find = false;

		while (!queue.empty()) {
			Vector2_1 now = queue.front();
			queue.pop_front();

			for (int i = 0; i < 4; i++) {
				float dx = now.pos.x + direct[i][0];
				float dy = now.pos.y + direct[i][1];

				if (dx < 0 || dy < 0 || dx >= mTiles[0].size() || dy >= mTiles.size()) continue;
				//if (map[(int)dy][(int)dx] == 1) continue;

				if (now.level == moveLimit) {
					find = true;
					break;
				}
				map[(int)dy][(int)dx] = 1;
				mTiles[(int)dy][(int)dx]->SetTileTexture(MAKE_TILE_KEY(TILE_T::SAND, TILE_HEAD_T::ground)
					, MAKE_TILE_PATH(TILE_T::SAND, TILE_HEAD_T::ground));

				queue.push_back(Vector2_1(Vector2(dx, dy), now.level + 1));
			}
			if (find) break;
		}
	}
	void Scene::ClearMTiles(TILE_T _type, TILE_HEAD_T _hT) {
		for (int y = 0; y < mPosTiles.size(); y++) {
			for (int x = 0; x < mPosTiles[y].size(); x++) {
				mTiles[y][x]->SetTileTexture(MAKE_TILE_KEY(_type, _hT)
					, MAKE_TILE_PATH(_type, _hT));
			}
		}
	}
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

	}
	void Scene::AddGameObject(GameObject* obj, LAYER_TYPE layer)
	{
		mLayers[(UINT)layer].AddGameObject(obj);
	}
}
