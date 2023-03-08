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
				mBacks.push_back(b_);
				AddGameObject(b_, LAYER_TYPE::BACKGROUND);
			}
		}
		Scene::MakeTile(TILE_X, TILE_Y, TILE_T::GREEN, TILE_HEAD_T::ground);


		// 임시로 메카위치 설정
		// 마우스로 클릭한 땅에 메카가 떨어지게 설정해야됨
		Mech* mech1 = new Mech(MECHS::artillery, Vector2(2, 2));
		mech1->SetPos(Scene::GetPosTiles()[2][2]->GetCenterPos());
		mech1->SetFinalPos(mech1->GetPos());

		AddGameObject(mech1, LAYER_TYPE::PLAYER);

		GetMechs().push_back(mech1);

		Mech* mech2 = new Mech(MECHS::tank, Vector2(4, 4));
		mech2->SetPos(Scene::GetPosTiles()[4][4]->GetCenterPos());
		mech2->SetFinalPos(mech2->GetPos());

		AddGameObject(mech2, LAYER_TYPE::PLAYER);

		GetMechs().push_back(mech2);

		Mech* mech3 = new Mech(MECHS::punch, Vector2(6, 6));
		mech3->SetPos(Scene::GetPosTiles()[6][6]->GetCenterPos());
		mech3->SetFinalPos(mech3->GetPos());

		AddGameObject(mech3, LAYER_TYPE::PLAYER);

		GetMechs().push_back(mech3);

	}
	void CombatScene::Update() {
		Scene::Update();

		Mech* mMouseFollower = Scene::GetMouseFollower();
		Scene::ClearMTiles(TILE_T::GREEN, TILE_HEAD_T::ground);
		Scene::HighlightTile();

		if (nullptr != mMouseFollower) {
			Scene::DrawMoveRangeTile();
			Scene::DrawMoveDirectionTile();
			Scene::CheckMouseOutOfMapRange();
		}

		if (KEY_DOWN(KEYCODE_TYPE::RBTN) && nullptr != mMouseFollower) {
			mMouseFollower->SetPos(mMouseFollower->GetFinalPos());
			mMouseFollower->SetCoord(mMouseFollower->GetFinalCoord());
			Scene::SetMouseFollower(nullptr);
		}
		
		if (KEY_DOWN(KEYCODE_TYPE::LBTN)) {
			if (nullptr != mMouseFollower) {
				mMouseFollower->SetFinalPos(mMouseFollower->GetPos());
				mMouseFollower->SetFinalCoord(mMouseFollower->GetCoord());
				Scene::SetMouseFollower(nullptr);
			}
			else {
				Scene::RobotDrag();
			}	
		}
		
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