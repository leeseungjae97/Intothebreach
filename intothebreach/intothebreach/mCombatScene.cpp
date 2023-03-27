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
			, L"..\\Resources\\texture\\ui\\combat\\bg.bmp", 0, false, false);

		UINT _x = (UINT)(application.GetResolutionWidth() / b0->GetSize().x);
		UINT _y = (UINT)(application.GetResolutionHeight() / b0->GetSize().y);

		delete b0;

		for (UINT y = 0; y <= _y; y++) {
			for (UINT x = 0; x <= _x; x++) {
				Background* b_ = new Background(L"combatBackground1"
					, L"..\\Resources\\texture\\ui\\combat\\bg.bmp", 0, false, false);
				b_->SetPos(Vector2(b_->GetSize().x * x, b_->GetSize().y * y));
				mBacks.push_back(b_);
				AddGameObject(b_, LAYER_TYPE::BACKGROUND);
			}
		}

		
		// 임시로 메카위치 설정
		// 마우스로 클릭한 땅에 메카가 떨어지게 설정해야됨

		Mech* mech1 = object::Instantiate(Vector2(1, 4), LAYER_TYPE::PLAYER, MECHS::artillery);
		Mech* mech2 = object::Instantiate(Vector2(4, 7), LAYER_TYPE::PLAYER, MECHS::tank);
		Mech* mech3 = object::Instantiate(Vector2(7, 4), LAYER_TYPE::PLAYER, MECHS::punch);

		Alien* alien1 = object::Instantiate(Vector2(4, 4), LAYER_TYPE::MONSTER, ALIENS::Hornet);
		Alien* alien2 = object::Instantiate(Vector2(0, 7), LAYER_TYPE::MONSTER, ALIENS::Leaper);
		Alien* alien3 = object::Instantiate(Vector2(2, 3), LAYER_TYPE::MONSTER, ALIENS::Firefly);
	}
	void CombatScene::Update() {
		Scene::Update();
		Scene::MoveMech();
		Scene::MoveSkill();
		Scene::CheckNumInput();
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