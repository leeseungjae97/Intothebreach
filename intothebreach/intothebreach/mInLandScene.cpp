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
	InLandScene::InLandScene(ISLAND_T _type)
		: mType(_type)
	{
	}
	InLandScene::~InLandScene() {
	}
	void InLandScene::Initialize() {
		Background* b = new Background(L"selectLandBg1", L"..\\Resources\\texture\\ui\\selectLand\\waterbg.bmp", 0, true, true);

		AddGameObeject(b, LAYER_TYPE::BACKGROUND);

		Background* b0 = new Background(MAKE_ISLAND_KEY(mType, -1), MAKE_ISLAND_PATH(mType, -1), 2 , false, true);
		b0->SetPos(Vector2(100.f, 100.f));
		AddGameObeject(b0, LAYER_TYPE::BACKGROUND);

		for (UINT i = 0; i < ISLANDS_SECTIONS[(UINT)mType]; i++) {
			Background* b_ = new Background(MAKE_ISLAND_KEY(mType, i), MAKE_ISLAND_PATH(mType, i), 2);
			b_->SetPos(ISLAND_POS[i]);
			mSections.push_back(b_);
			AddGameObeject(b_, LAYER_TYPE::BACKGROUND);
		}
		

		/*Background* b1= new Background(L"island1", L"..\\Resources\\texture\\ui\\inLand\\island1\\island1.bmp");

		Background* b2 = new Background(L"island2", L"..\\Resources\\texture\\ui\\inLand\\island2\\island2.bmp");

		Background* b3 = new Background(L"island3", L"..\\Resources\\texture\\ui\\inLand\\island3\\island3.bmp");

		Background* b4 = new Background(L"island4", L"..\\Resources\\texture\\ui\\inLand\\island4\\island4.bmp");*/

		
		

	}
	void InLandScene::Update() {
		Scene::Update();
		if (Input::GetKeyState(KEYCODE_TYPE::N) == KEY_STATE::DOWN) {
			SceneManager::LoadScene(SCENE_TYPE::TITLE);
		}
	}
	void InLandScene::Render(HDC hdc) {
		Scene::Render(hdc);
	}
	void InLandScene::Release() {
	}
	void InLandScene::OnEnter() {
	}
	void InLandScene::OnExit() {
	}
}