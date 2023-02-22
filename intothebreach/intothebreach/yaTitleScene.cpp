#include "yaTitleScene.h"
#include "yaInput.h"
#include "yaSceneManager.h"
namespace ya {
	TitleScene::TitleScene() {

	}
	TitleScene::~TitleScene() {

	}
	void TitleScene::Initialize() {
		Scene::Initialize();
	}
	void TitleScene::Update() {
		Scene::Update();
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down) {
			SceneManager::LoadScene(eSceneType::Play);
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