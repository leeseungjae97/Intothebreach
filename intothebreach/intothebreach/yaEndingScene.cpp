#include "yaEndingScene.h"
#include "yaInput.h"
#include "yaSceneManager.h"
namespace ya {
	EndingScene::EndingScene() {
	}
	EndingScene::~EndingScene() {
	}
	void EndingScene::Initialize() {
		Scene::Initialize();
	}
	void EndingScene::Update() {
		Scene::Update();
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down) {
			SceneManager::LoadScene(eSceneType::SelectLand);
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