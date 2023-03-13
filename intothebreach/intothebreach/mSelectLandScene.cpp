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
		Background* b1 = new Background(L"selectLandBg1", L"..\\Resources\\texture\\ui\\selectLand\\waterbg.bmp", 0, true, true);
		AddGameObject(b1, LAYER_TYPE::BACKGROUND);

		for (int i = 0; i < (UINT)ISLAND_T::END; i++) {
			Background* p = new Background(MAKE_ISLAND_KEY((ISLAND_T)i), MAKE_ISLAND_PATH((ISLAND_T)i), 2, false, false);
			Background* l = new Background(MAKE_ISLAND_KEY((ISLAND_T)i), MAKE_ISLAND_PATH((ISLAND_T)i), 2, false, false);
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
			if (math::CheckRectPos(Islands[i]->GetPos(), Islands[i]->GetScale(),MOUSE_POS)) {
				outLine[i]->SetTex(MAKE_ISLAND_OUTLINE_KEY((ISLAND_T)i), MAKE_ISLAND_OUTLINE_PATH((ISLAND_T)i), (ISLAND_T)i);
			}
			else {
				outLine[i]->Clear();
			}
		}

		if (KEY_DOWN(KEYCODE_TYPE::LBTN)) {
			for (int i = 0; i < Islands.size() - 1; i++) {
				if (math::CheckRectPos(Islands[i]->GetPos(), Islands[i]->GetScale(), MOUSE_POS)) {
					SceneManager::LoadScene((SCENE_TYPE)i);
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