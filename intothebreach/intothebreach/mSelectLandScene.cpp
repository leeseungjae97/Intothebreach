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
		Background* b1 = new Background(L"selectLandBg1", L"..\\Resources\\texture\\ui\\selectLand\\waterbg.bmp", 0, true, CENTER);
		AddGameObject(b1, LAYER_TYPE::BACKGROUND);

		Background* water = new Background(L"water", L"..\\Resources\\texture\\ui\\selectLand\\watertile.bmp", 0, false);

		UINT _x = (UINT)(application.GetResolutionWidth() / water->GetWidth());
		UINT _y = (UINT)(application.GetResolutionHeight() / water->GetHeight());

		delete water;
		for (UINT y = 0; y <= _y; y++)
		{
			for (UINT x = 0; x <= _x; x++)
			{
				Background* w_ = new Background(L"water", L"..\\Resources\\texture\\ui\\selectLand\\watertile.bmp", 0, false);
				w_->SetCutPos(true);
				w_->SetAlpha(true);
				w_->SetAlphaConstant(50);
				w_->SetPos(Vector2(w_->GetWidth() * x, w_->GetHeight() * y));
				AddGameObject(w_, LAYER_TYPE::BACKGROUND);
			}
		}

		for (int i = 0; i < (UINT)ISLAND_T::END; i++) {
			Background* p = new Background(MAKE_ISLAND_KEY((ISLAND_T)i), MAKE_ISLAND_PATH((ISLAND_T)i), 2, false, DEFAULT);
			Background* l = new Background(MAKE_ISLAND_KEY((ISLAND_T)i), MAKE_ISLAND_PATH((ISLAND_T)i), 2, false, DEFAULT);
			p->SetPos(Vector2(ISLANDS_POS[i].x, ISLANDS_POS[i].y));
			l->SetPos(Vector2(ISLANDS_POS[i].x, ISLANDS_POS[i].y));
			AddGameObject(p, LAYER_TYPE::BACKGROUND);
			AddGameObject(l, LAYER_TYPE::BACKGROUND);
			Islands.push_back(p);
			outLine.push_back(l);
		}
		Scene::Initialize();
	}
	void SelectLandScene::Update() {
		Scene::Update();
		for (int i = 0; i < Islands.size(); i++) {
			Background* p = Islands[i];
			if (math::CheckRectPos(p->GetPos(), p->GetScale(), MOUSE_POS)) {
				outLine[i]->SetTex(MAKE_ISLAND_OUTLINE_KEY((ISLAND_T)i), MAKE_ISLAND_OUTLINE_PATH((ISLAND_T)i), (ISLAND_T)i);
			}
			else {
				outLine[i]->Clear();
			}
		}

		if (KEY_DOWN(KEYCODE_TYPE::LBTN)) {
			for (int i = 0; i < Islands.size() - 1; i++) {
				Background* p = Islands[i];
				if (math::CheckRectPos(p->GetPos(), p->GetScale(), MOUSE_POS)) {
					SceneManager::LoadScene((SCENE_TYPE)i);
					SceneManager::SelectLand(i);
				}
			}
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