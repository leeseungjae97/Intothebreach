#include "mCombatScene.h"
#include "Mech.h"
#include "mSceneManager.h"
#include "mInput.h"
#include "mTransform.h"
#include "mBackground.h"
#include "mSelectGDI.h"
#include "mApplication.h"
#include "mResources.h"
#include "mTile.h"
#include "Mech.h"

extern m::Application application;
namespace m {
	CombatScene::CombatScene() {
	}
	CombatScene::~CombatScene() {
	}
	void CombatScene::Initialize() {
		Scene::Initialize();

		Background* b0 = new Background(L"combatBackground1"
			, L"..\\Resources\\texture\\ui\\combat\\bg.bmp", 0, false, false);

		UINT _x = (UINT)(application.GetResolutionWidth() / b0->GetSize().x);
		UINT _y = (UINT)(application.GetResolutionHeight() / b0->GetSize().y);

		delete b0;

		for (UINT y = 0; y <= _y; y++) {
			for (UINT x = 0; x <= _x; x++) {
				Background* b_ = new Background(L"combatBackground1"
					, L"..\\Resources\\texture\\ui\\combat\\bg.bmp", 0, false, false);
				b_->SetPos(Vector2(b_->GetSize().x * x, b_->GetSize().y * y));
				AddGameObject(b_, LAYER_TYPE::BACKGROUND);
			}
		}
		Scene::MakeTile(TILE_X, TILE_Y, TILE_T::GREEN, TILE_HEAD_T::ground);


		Mech* mech1 = new Mech(MECHS::artillery);
		mech1->SetPos(Scene::GetPosTiles()[0][0]->GetCenterPos());
		mech1->SetFinalPos(mech1->GetPos());

		mech1->SetCoord(Scene::GetPosTiles()[0][0]->GetCoord());
		mech1->SetFinalCoord(mech1->GetCoord());

		AddGameObject(mech1, LAYER_TYPE::PLAYER);

		GetMechs().push_back(mech1);

	}
	void CombatScene::Update() {
		Scene::Update();

		Mech* mMouseFollower = Scene::GetMouseFollower();

		Scene::ClearMTiles(TILE_T::GREEN, TILE_HEAD_T::ground);
		Scene::HighlightTile();

		if (nullptr != mMouseFollower) {
			Scene::DrawMoveRangeTile();
			Scene::DrawMoveDirectionTile();
		}

		Scene::CheckMouseOutOfMapRange();

		if (KEY_DOWN(KEYCODE_TYPE::RBTN) && nullptr != mMouseFollower) {
			Scene::ClearMap();
			mMouseFollower->SetPos(mMouseFollower->GetFinalPos());
			mMouseFollower->SetCoord(mMouseFollower->GetFinalCoord());
			Scene::SetMouseFollower(nullptr);
		}
		
		if (KEY_DOWN(KEYCODE_TYPE::LBTN)) {
			if (nullptr != mMouseFollower) {
				Scene::ClearMap();
				mMouseFollower->SetFinalPos(mMouseFollower->GetPos());
				mMouseFollower->SetFinalCoord(mMouseFollower->GetCoord());
				Scene::SetMouseFollower(nullptr);
			}
			else {
				Scene::RobotDrag();
			}	
		}
		
		int a = 0;
		if (Input::GetKeyState(KEYCODE_TYPE::N) == KEY_STATE::DOWN) {
			SceneManager::LoadScene(SCENE_TYPE::IN_LAND0);
		}
	}
	void CombatScene::Render(HDC hdc) {
		Scene::Render(hdc);
	}
	void CombatScene::Release() {
		Scene::Release();
	}
	void CombatScene::OnEnter() {
	}
	void CombatScene::OnExit() {
	}
}