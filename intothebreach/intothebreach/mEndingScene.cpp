#include "mEndingScene.h"
#include "mInput.h"
#include "mSceneManager.h"
namespace m {
	EndingScene::EndingScene() {
	}
	EndingScene::~EndingScene() {
	}
	void EndingScene::Initialize() {
		Scene::Initialize();
	}
	void EndingScene::Update() {
		Scene::Update();
		if (Input::GetKeyState(KEYCODE_TYPE::N) == KEY_STATE::DOWN) {
			SceneManager::LoadScene(SCENE_TYPE::SELECT_LAND);
		}
	}
	void EndingScene::Render(HDC hdc) {
		Scene::Render(hdc);
	}
	void EndingScene::Release() {
		Scene::Release();
	}
	void EndingScene::OnEnter() {
	}
	void EndingScene::OnExit() {
	}
}