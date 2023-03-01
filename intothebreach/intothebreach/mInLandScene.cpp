#include "mInLandScene.h"
#include "Mech.h"
#include "mSceneManager.h"
#include "mInput.h"
#include "mTransform.h"
#include "mBackground.h"
#include "mSelectGDI.h"
#include "mApplication.h"
extern m::Application application;
namespace m {
	InLandScene::InLandScene() {
	}
	InLandScene::~InLandScene() {
	}
	void InLandScene::Initialize() {
		Background* b0 = new Background(L"", L"");
		AddGameObeject(b0, LAYER_TYPE::BACKGROUND);

	}
	void InLandScene::Update() {
		Scene::Update();
		if (Input::GetKeyState(KEYCODE_TYPE::N) == KEY_STATE::DOWN) {
			SceneManager::LoadScene(SCENE_TYPE::TITLE);
		}
	}
	void InLandScene::Render(HDC hdc) {
	}
	void InLandScene::Release() {
	}
	void InLandScene::OnEnter() {
	}
	void InLandScene::OnExit() {
	}
}