#include "yaSelectLandScene.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaTransform.h"
#include "yaBackground.h"
#include "yaSelectGDI.h"
#include "yaApplication.h"
#include "yaComponent.h"
extern ya::Application application;

namespace ya {
	SelectLandScene::SelectLandScene() {
	}
	SelectLandScene::~SelectLandScene() {
	}
	void SelectLandScene::Initialize() {
		Background* b1 = new Background(L"selectLandBg1", L"..\\Resources\\texture\\ui\\selectLand\\waterbg.bmp", 0, true, false);
		AddGameObeject(b1, eLayerType::BackGround);
		
		Background* island1 = new Background(L"selectLandIsland1", L"..\\Resources\\texture\\ui\\selectLand\\island1x_0.bmp", 2, false, false);
		island1->SetPos(Vector2(100, 50));
		Background* island2 = new Background(L"selectLandIsland2", L"..\\Resources\\texture\\ui\\selectLand\\island1x_1.bmp", 2, false, false);
		island2->SetPos(Vector2(200, 300));
		Background* island3 = new Background(L"selectLandIsland3", L"..\\Resources\\texture\\ui\\selectLand\\island1x_2.bmp", 2, false, false);
		island3->SetPos(Vector2(500, 200));
		Background* island4 = new Background(L"selectLandIsland4", L"..\\Resources\\texture\\ui\\selectLand\\island1x_3.bmp", 2, false, false);
		island4->SetPos(Vector2(600, 400));
		Background* island5 = new Background(L"selectLandIsland5", L"..\\Resources\\texture\\ui\\selectLand\\island1x_4.bmp", 2, false, false);
		island5->SetPos(Vector2(500, 50));

		AddGameObeject(island1, eLayerType::BackGround);
		AddGameObeject(island2, eLayerType::BackGround);
		AddGameObeject(island3, eLayerType::BackGround);
		AddGameObeject(island4, eLayerType::BackGround);
		AddGameObeject(island5, eLayerType::BackGround);
		Scene::Initialize();
	}
	void SelectLandScene::Update() {
		Scene::Update();
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down) {
			SceneManager::LoadScene(eSceneType::Combat);
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