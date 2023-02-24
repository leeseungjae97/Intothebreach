#include "yaTitleScene.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaBackground.h"
namespace ya {
	TitleScene::TitleScene() {

	}
	TitleScene::~TitleScene() {

	}
	void TitleScene::Initialize() {
		Background* b1 = new Background(L"title1",L"..\\Resources\\texture\\ui\\title\\calibration.bmp", 0, true, false);
		AddGameObeject(b1, eLayerType::BackGround);
		Scene::Initialize();
	}
	void TitleScene::Update() {
		Scene::Update();
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down) {
			SceneManager::LoadScene(eSceneType::SelectRobot);
		}
	}
	void TitleScene::Render(HDC hdc) {
		Scene::Render(hdc);
	}
	void TitleScene::Release() {
		Scene::Release();
	}
	void TitleScene::OnEnter() {

	}
	void TitleScene::OnExit() {
	}
}