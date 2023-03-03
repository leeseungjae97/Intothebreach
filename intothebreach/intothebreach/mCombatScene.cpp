#include "mCombatScene.h"
#include "Mech.h"
#include "mSceneManager.h"
#include "mInput.h"
#include "mTransform.h"
#include "mBackground.h"
#include "mSelectGDI.h"
#include "mApplication.h"
#include "mResources.h"
#include "mTile.h"
#include "mTileHead.h"
extern m::Application application;
namespace m {
	CombatScene::CombatScene() {
	}
	CombatScene::~CombatScene() {
	}
	void CombatScene::Initialize() {
		Scene::Initialize();

		Background* b0 = new Background(L"combatBackground1"
			, L"..\\Resources\\texture\\ui\\combat\\bg.bmp", 0, false, false);

		UINT _x = (UINT)(application.GetResolutionWidth() / b0->GetSize().x);
		UINT _y = (UINT)(application.GetResolutionHeight() / b0->GetSize().y);

		delete b0;

		for (UINT y = 0; y <= _y; y++) {
			for (UINT x = 0; x <= _x; x++) {
				Background* b_ = new Background(L"combatBackground1"
					, L"..\\Resources\\texture\\ui\\combat\\bg.bmp", 0, false, false);
				b_->SetPos(Vector2(b_->GetSize().x * x, b_->GetSize().y * y));
				AddGameObject(b_, LAYER_TYPE::BACKGROUND);
			}
		}
		
		MakeTile();
		
	}
	void CombatScene::MakeTile() {
		float fX, fY;
		float mX = (10.f * (TILE_SIZE_X / 2.f));
		float mY = TILE_SIZE_Y / 4.f;
		for (int i = 0; i < TILE_X; i++) {
			for (int j = 0; j < TILE_Y; j++) {
				Tile* tile = new Tile(Vector2(j, i));
				fX = (float)((TILE_SIZE_X / TILE_X_DIVIDE_RECT) * (j - i) + mX);
				fY = (float)((TILE_SIZE_Y / TILE_Y_DIVIDE_RECT) * (j + i) + mY);
				tile->SetPos(Vector2(fX * 2, fY * 2));
				tile->SetTileTexture(MAKE_TILE_KEY(TILE_T::GREEN, TILE_HEAD_T::ground)
									, MAKE_TILE_PATH(TILE_T::GREEN, TILE_HEAD_T::ground));
				mTiles.push_back(tile);

				Tile* posTile = new Tile(10);
				posTile->SetTileTexture(L"square", L"..\\Resources\\texture\\terrain\\square_line2.bmp");
				posTile->SetPos(Vector2(fX * 2, fY * 2));

				mPosTiles.push_back(posTile);

				AddGameObject(tile, LAYER_TYPE::TILE);
			}
		}

		for (size_t i = 0; i < mTiles.size(); i++) {
			if (mTiles[i]->GetCoord().x == 1 && mTiles[i]->GetCoord().y == 1) {
				TileHead* tHead = new TileHead();
			}
		}
	}
	bool CombatScene::CheckRhombusPos(Tile* tile) {
		float rY = MOUSE_POS.y;
		float rX = MOUSE_POS.x;

		Vector2 vv[4];
		float g[4];
		float in[4];

		//¿Þ
		vv[0].x = tile->GetPos().x;
		vv[0].y = tile->GetPos().y + (tile->GetScale().y / 2);

		//À§
		vv[1].x = tile->GetPos().x + (tile->GetScale().x / 2);
		vv[1].y = tile->GetPos().y;

		//¿À
		vv[2].x = tile->GetPos().x + tile->GetScale().x;
		vv[2].y = tile->GetPos().y + (tile->GetScale().y / 2);

		//¾Æ
		vv[3].x = tile->GetPos().x + (tile->GetScale().x / 2);
		vv[3].y = tile->GetPos().y + tile->GetScale().y;

		g[0] = ((vv[0].y - vv[1].y) / (vv[0].x - vv[1].x));
		g[1] = ((vv[1].y - vv[2].y) / (vv[1].x - vv[2].x));
		g[2] = ((vv[2].y - vv[3].y) / (vv[2].x - vv[3].x));
		g[3] = ((vv[3].y - vv[0].y) / (vv[3].x - vv[0].x));

		in[0] = vv[0].y - g[0] * vv[0].x;
		in[1] = vv[1].y - g[1] * vv[1].x;
		in[2] = vv[2].y - g[2] * vv[2].x;
		in[3] = vv[3].y - g[3] * vv[3].x;

		float c1 = g[0] * vv[0].x + in[0];
		float c2 = g[1] * vv[1].x + in[1];
		float c3 = g[2] * vv[2].x + in[2];
		float c4 = g[3] * vv[3].x + in[3];

		if (g[0] * rX + in[0] < rY
			&& g[1] * rX + in[1] < rY
			&& g[2] * rX + in[2] > rY
			&& g[3] * rX + in[3] > rY) {
			return true;
		}
		else return false;
	}
	void CombatScene::Update() {
		for (UINT i = 0; i < mPosTiles.size(); i++) {
			if (CheckRhombusPos(mPosTiles[i])) {
				mTiles[i]->SetTileTexture(MAKE_TILE_KEY(TILE_T::SAND, TILE_HEAD_T::ground)
					, MAKE_TILE_PATH(TILE_T::SAND, TILE_HEAD_T::ground));
			}
		}
		Scene::Update();
		if (Input::GetKeyState(KEYCODE_TYPE::N) == KEY_STATE::DOWN) {
			SceneManager::LoadScene(SCENE_TYPE::IN_LAND0);
		}
	}
	void CombatScene::Render(HDC hdc) {
		Scene::Render(hdc);
	}
	void CombatScene::Release() {
		Scene::Release();
	}
	void CombatScene::OnEnter() {
	}
	void CombatScene::OnExit() {
	}
}