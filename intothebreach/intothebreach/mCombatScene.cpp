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
#include "func.h"
#include "Building.h"
#include "Alien.h"
#include "mSkill.h"
extern m::Application application;
namespace m {
	CombatScene::CombatScene() {
	}
	CombatScene::~CombatScene() {
	}
	void CombatScene::Initialize() {
		Scene::Initialize();
		Scene::MakeTile(TILE_X, TILE_Y, TILE_T::GREEN, TILE_HEAD_T::ground);

		Background* b0 = new Background(L"combatBackground1"
			, L"..\\Resources\\texture\\ui\\combat\\bg.bmp", 0, false, DEFAULT);

		UINT _x = (UINT)(application.GetResolutionWidth() / b0->GetWidth());
		UINT _y = (UINT)(application.GetResolutionHeight() / b0->GetHeight());

		delete b0;

		

		for (UINT y = 0; y <= _y; y++) {
			for (UINT x = 0; x <= _x; x++) {
				Background* b_ = new Background(L"combatBackground1"
					, L"..\\Resources\\texture\\ui\\combat\\bg.bmp", 0, false, DEFAULT);
				b_->SetPos(Vector2(b_->GetWidth() * x, b_->GetHeight() * y));
				mBacks.push_back(b_);
				AddGameObject(b_, LAYER_TYPE::BACKGROUND);
			}
		}
		// 임시로 메카위치 설정
		// 마우스로 클릭한 땅에 메카가 떨어지게 설정해야됨

		Mech* mech1 = object::Instantiate(Vector2(0, 0), LAYER_TYPE::PLAYER, MECHS::artillery);
		Mech* mech2 = object::Instantiate(Vector2(2, 1), LAYER_TYPE::PLAYER, MECHS::tank);
		Mech* mech3 = object::Instantiate(Vector2(0, 2), LAYER_TYPE::PLAYER, MECHS::punch);

		Alien* alien1 = object::Instantiate(Vector2(5, 5), LAYER_TYPE::MONSTER, ALIENS::Hornet);
		Alien* alien2 = object::Instantiate(Vector2(5, 4), LAYER_TYPE::MONSTER, ALIENS::Leaper);
		Alien* alien3 = object::Instantiate(Vector2(5, 3), LAYER_TYPE::MONSTER, ALIENS::Firefly);

		//object::Instantiate(Vector2(0, 0), LAYER_TYPE::STRUCT, STRUCTURES::airfield);
		//object::Instantiate(Vector2(1, 0), LAYER_TYPE::STRUCT, STRUCTURES::bar);
		//object::Instantiate(Vector2(2, 0), LAYER_TYPE::STRUCT, STRUCTURES::battry);
		//object::Instantiate(Vector2(2, 0), LAYER_TYPE::STRUCT, STRUCTURES::energy);
		//object::Instantiate(Vector2(3, 0), LAYER_TYPE::STRUCT, STRUCTURES::factory);
		//object::Instantiate(Vector2(4, 0), LAYER_TYPE::STRUCT, STRUCTURES::hospital);
		//object::Instantiate(Vector2(5, 0), LAYER_TYPE::STRUCT, STRUCTURES::military);
		//object::Instantiate(Vector2(6, 0), LAYER_TYPE::STRUCT, STRUCTURES::power);
		//object::Instantiate(Vector2(7, 0), LAYER_TYPE::STRUCT, STRUCTURES::radar);
		//object::Instantiate(Vector2(0, 1), LAYER_TYPE::STRUCT, STRUCTURES::recycle);
		//object::Instantiate(Vector2(1, 1), LAYER_TYPE::STRUCT, STRUCTURES::research);
		//object::Instantiate(Vector2(2, 1), LAYER_TYPE::STRUCT, STRUCTURES::shield);
		//object::Instantiate(Vector2(3, 1), LAYER_TYPE::STRUCT, STRUCTURES::supply);
		//object::Instantiate(Vector2(2, 1), LAYER_TYPE::STRUCT, STRUCTURES::timelab);
		object::Instantiate(Vector2(3, 1), LAYER_TYPE::STRUCT, STRUCTURES::tower);
		//object::Instantiate(Vector2(4, 1), LAYER_TYPE::STRUCT, STRUCTURES::wind);

		//Building* stTile3 = object::Instantiate(Vector2(3, 1), LAYER_TYPE::STRUCT, STRUCTURES::solar);

		//stTile->SetPos(mTiles[3][3]->GetCenterPos());
		//mStruturesTiles[3][3] = stTile;
		//AddGameObject(stTile, LAYER_TYPE::STRUCT);
		//Building* stTile1 = new Building(STRUCTURES_T::Mountain, mTiles[1][2]->GetCoord());
		//stTile1->SetPos(mTiles[1][2]->GetCenterPos());
		//mStruturesTiles[1][2] = stTile1;
		//AddGameObject(stTile1, LAYER_TYPE::STRUCT);
		//Building* stTile2 = new Building(STRUCTURES_T::Mountain, mTiles[2][0]->GetCoord());
		//stTile2->SetPos(mTiles[2][0]->GetCenterPos());
		//mStruturesTiles[2][0] = stTile2;
		//AddGameObject(stTile2, LAYER_TYPE::STRUCT);
	}
	void CombatScene::Update() {
		Scene::Update();
		Scene::MoveMech();
		Scene::MoveSkill();
		//Scene::CheckNumInput();
		Scene::AlienAlgorithm();
		//Scene::MoveAlien();
		if (KEY_DOWN(KEYCODE_TYPE::N)) {
			SceneManager::LoadScene(SCENE_TYPE::TITLE);
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