#include "mTitleScene.h"
#include "mInput.h"
#include "mSceneManager.h"
#include "mBackground.h"
namespace m {
	TitleScene::TitleScene() {

	}
	TitleScene::~TitleScene() {

	}
	void TitleScene::Initialize() {
		Background* b1 = new Background(L"title1",L"..\\Resources\\texture\\ui\\title\\calibration.bmp", 0, true, false);
		AddGameObject(b1, LAYER_TYPE::BACKGROUND);
		Scene::Initialize();
	}
	void TitleScene::Update() {
		Scene::Update();
		if (KEY_DOWN(KEYCODE_TYPE::LBTN)) {
			SceneManager::LoadScene(SCENE_TYPE::SELECT_ROBOT);
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