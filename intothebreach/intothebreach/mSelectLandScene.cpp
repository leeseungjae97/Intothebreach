#include "mSelectLandScene.h"
#include "mInput.h"
#include "mSceneManager.h"
#include "mTransform.h"
#include "mBackground.h"
#include "mSelectGDI.h"
#include "mApplication.h"
#include "mComponent.h"
extern m::Application application;

namespace m {
	SelectLandScene::SelectLandScene() {
	}
	SelectLandScene::~SelectLandScene() {
	}
	void SelectLandScene::Initialize() {
		Background* b1 = new Background(L"selectLandBg1", L"..\\Resources\\texture\\ui\\selectLand\\waterbg.bmp", 0, true, true);
		AddGameObject(b1, LAYER_TYPE::BACKGROUND);
		
		Background* island1 = new Background(L"selectLandIsland1", L"..\\Resources\\texture\\ui\\selectLand\\island1x_0.bmp", 2, false, false);
		island1->SetPos(Vector2(100, 80));
		Background* island2 = new Background(L"selectLandIsland2", L"..\\Resources\\texture\\ui\\selectLand\\island1x_1.bmp", 2, false, false);
		island2->SetPos(Vector2(250, 370));
		Background* island3 = new Background(L"selectLandIsland3", L"..\\Resources\\texture\\ui\\selectLand\\island1x_2.bmp", 2, false, false);
		island3->SetPos(Vector2(580, 250));
		Background* island4 = new Background(L"selectLandIsland4", L"..\\Resources\\texture\\ui\\selectLand\\island1x_3.bmp", 2, false, false);
		island4->SetPos(Vector2(900, 440));
		Background* island5 = new Background(L"selectLandIsland5", L"..\\Resources\\texture\\ui\\selectLand\\island1x_4.bmp", 2, false, false);
		island5->SetPos(Vector2(500, 50));

		AddGameObject(island1, LAYER_TYPE::BACKGROUND);
		AddGameObject(island2, LAYER_TYPE::BACKGROUND);
		AddGameObject(island3, LAYER_TYPE::BACKGROUND);
		AddGameObject(island4, LAYER_TYPE::BACKGROUND);
		AddGameObject(island5, LAYER_TYPE::BACKGROUND);
		Scene::Initialize();
	}
	void SelectLandScene::Update() {
		Scene::Update();
		if (Input::GetKeyState(KEYCODE_TYPE::N) == KEY_STATE::DOWN) {
			SceneManager::LoadScene(SCENE_TYPE::IN_LAND0);
		}
	}
	void SelectLandScene::Render(HDC hdc) {
		Scene::Render(hdc);
	}
	void SelectLandScene::Release() {
		Scene::Release();
	}
	void SelectLandScene::OnEnter() {
	}
	void SelectLandScene::OnExit() {
	}
}