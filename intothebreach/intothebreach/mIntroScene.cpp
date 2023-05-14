#include "mIntroScene.h"
#include "mSceneManager.h"
#include "mCamera.h"
#include "mInput.h"
#include "mApplication.h"
extern m::Application application;
namespace m {
	IntroScene::IntroScene() {
	}
	IntroScene::~IntroScene() {
	}
	void IntroScene::Initialize() {
	}
	void IntroScene::Update() {
		if (KEY_PRESSED(KEYCODE_TYPE::N))
		{
			SceneManager::LoadScene(SCENE_TYPE::TITLE);
		}
	}
	void IntroScene::Render(HDC hdc) {
	}
	void IntroScene::Release() {
	}
	void IntroScene::OnEnter() {
		Camera::SetLookAt(Vector2(0, application.GetResolutionHeight() / 2));
	}
	void IntroScene::OnExit() {
		
	}
}