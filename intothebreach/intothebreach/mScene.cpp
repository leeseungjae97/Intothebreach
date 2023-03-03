#include "mScene.h"
#include "mTile.h"
namespace m
{
	Scene::Scene()
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
	void Scene::MakeTile(int iX, int iY) {
		float fX, fY;
		float mX = (10.f * (TILE_SIZE_X / 2.f));
		float mY = TILE_SIZE_Y / 4.f;
		for (int i = 0; i < iX; i++) {
			for (int j = 0; j < iY; j++) {
				Tile* tile = new Tile(Vector2((float)j, (float)i));
				fX = (float)((TILE_SIZE_X / TILE_X_DIVIDE_RECT) * (j - i) + mX);
				fY = (float)((TILE_SIZE_Y / TILE_Y_DIVIDE_RECT) * (j + i) + mY);
				tile->SetPos(Vector2(fX * 2, fY * 2));
				tile->SetTileTexture(MAKE_TILE_KEY(TILE_T::GREEN, TILE_HEAD_T::ground)
					, MAKE_TILE_PATH(TILE_T::GREEN, TILE_HEAD_T::ground));
				mTiles.push_back(tile);

				Tile* posTile = new Tile(1);
				posTile->SetTileTexture(L"square", L"..\\Resources\\texture\\terrain\\tile_square.bmp");
				posTile->SetPos(Vector2(fX * 2, fY * 2));
				mPosTiles.push_back(posTile);

				AddGameObject(posTile, LAYER_TYPE::TILE);
				AddGameObject(tile, LAYER_TYPE::TILE);
			}
		}
	}
	bool Scene::CheckRhombusPos(Tile* tile, Vector2 _pos) {
		Vector2 vv[4];
		float g[4];
		float in[4];
		float direct[4][2] = {
			{0, (tile->GetScale().y / 2)},
			{(tile->GetScale().x / 2), 0},
			{tile->GetScale().x, (tile->GetScale().y / 2)},
			{(tile->GetScale().x / 2), tile->GetScale().y}
		};
		for (size_t i = 0; i < 4; i++) {
			vv[i].x = tile->GetPos().x + direct[i][0];
			vv[i].y = tile->GetPos().y + direct[i][1];
		}
		for (size_t i = 0; i < 4; i++) {
			g[i] = ((vv[i].y - vv[(i + 1) % 4].y) / (vv[i].x - vv[(i + 1) % 4].x));
			in[i] = vv[i].y - g[i] * vv[i].x;
		}
		float rY = _pos.y;
		float rX = _pos.x;

		if (g[0] * rX + in[0] < rY
			&& g[1] * rX + in[1] < rY
			&& g[2] * rX + in[2] > rY
			&& g[3] * rX + in[3] > rY) {
			return true;
		}
		else return false;
	}

	void Scene::Release()
	{

	}
	void Scene::AddGameObject(GameObject* obj, LAYER_TYPE layer)
	{
		mLayers[(UINT)layer].AddGameObject(obj);
	}
}
