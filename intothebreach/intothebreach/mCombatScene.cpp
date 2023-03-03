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
#include "Mech.h"

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
		

		
		
		Scene::MakeTile(TILE_X, TILE_Y);
	}
	void CombatScene::Update() {
		Scene::Update();
		vector<Tile*> mPosTiles = Scene::GetPosTiles();
		vector<Tile*> mTiles = Scene::GetTiles();
		if (KEY_UP(KEYCODE_TYPE::LBTN)) {
			
			for (UINT i = 0; i < mPosTiles.size(); i++) {
				if (Scene::CheckRhombusPos(mPosTiles[i], MOUSE_POS)) {
					//Tile* pHeadTile = new Tile(mPosTiles[i]->GetCoord());
					//pHeadTile->SetPos(mPosTiles[i]->GetPos());
					//pHeadTile->SetTileType(TILE_T::GREEN);
					//pHeadTile->SetTileTexture(MAKE_TILE_KEY(TILE_T::GREEN, TILE_HEAD_T::forest)
					//					, MAKE_TILE_PATH(TILE_T::GREEN, TILE_HEAD_T::forest));
					//AddGameObject(pHeadTile, LAYER_TYPE::TILE_HEAD);
					vector<Tile*> mPosTiles = Scene::GetPosTiles();
					Mech* mech1 = new Mech(MECHS::artillery);
					mech1->SetPos(mPosTiles[i]->GetCenterPos());
					AddGameObject(mech1, LAYER_TYPE::PLAYER);
				}
			}
		}
		if (KEY_UP(KEYCODE_TYPE::RBTN)) {
			for (UINT i = 0; i < mPosTiles.size(); i++) {
				if (Scene::CheckRhombusPos(mPosTiles[i], MOUSE_POS)) {
					Tile* pHeadTile = new Tile(mPosTiles[i]->GetCoord());
					pHeadTile->SetPos(mPosTiles[i]->GetPos());
					pHeadTile->SetTileType(TILE_T::GREEN);
					pHeadTile->SetTileTexture(MAKE_TILE_KEY(TILE_T::GREEN, TILE_HEAD_T::building)
										, MAKE_TILE_PATH(TILE_T::GREEN, TILE_HEAD_T::building));
					AddGameObject(pHeadTile, LAYER_TYPE::TILE_HEAD);

				}
			}
		}
		for (UINT i = 0; i < mPosTiles.size(); i++) {
			if (CheckRhombusPos(mPosTiles[i], MOUSE_POS)) {
				mTiles[i]->SetTileType(TILE_T::SAND);
				mTiles[i]->SetTileTexture(MAKE_TILE_KEY(TILE_T::SAND, TILE_HEAD_T::ground)
					, MAKE_TILE_PATH(TILE_T::SAND, TILE_HEAD_T::ground));
			}
		}
		
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