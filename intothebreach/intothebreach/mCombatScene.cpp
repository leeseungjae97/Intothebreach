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
#include "mTileHead.h"
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
		
		MakeTile();
		
	}
	void CombatScene::MakeTile() {
		float fX, fY;
		float mX = (10.f * (TILE_SIZE_X / 2.f));
		float mY = TILE_SIZE_Y / 4.f;
		for (int i = 0; i < TILE_X; i++) {
			for (int j = 0; j < TILE_Y; j++) {
				Tile* tile = new Tile(Vector2(j, i));
				fX = (float)((TILE_SIZE_X / TILE_X_DIVIDE_RECT) * (j - i) + mX);
				fY = (float)((TILE_SIZE_Y / TILE_Y_DIVIDE_RECT) * (j + i) + mY);
				tile->SetPos(Vector2(fX * 2, fY * 2));
				tile->SetTileTexture(MAKE_TILE_KEY(TILE_T::GREEN, TILE_HEAD_T::ground)
									, MAKE_TILE_PATH(TILE_T::GREEN, TILE_HEAD_T::ground));
				mTiles.push_back(tile);
				AddGameObject(tile, LAYER_TYPE::TILE);
			}
		}

		//for (size_t i = 0; i < mTiles.size(); i++) {
		//	if (mTiles[i]->GetCoord().x == 1 && mTiles[i]->GetCoord().y == 1) {
		//		TileHead* tHead = new TileHead();
		//	}
		//}
	}
	void CombatScene::Update() {
		Vector2 mCurM = MOUSE_POS;
		for (UINT i = 0; i < mTiles.size(); i++) {
			float centerY = mTiles[i]->GetPos().y / 2;


			if (mTiles[i]->GetPos() <= mCurM
				&& mTiles[i]->GetPos() + mTiles[i]->GetScale() >= mCurM) {
				

				Vector2 m = MOUSE_POS;
				DWORD color = GetPixel(application.GetHdc(), m.x, m.y);
				unsigned int r = GetRValue(color);
				unsigned int g = GetGValue(color);
				unsigned int b = GetBValue(color);

				//70, 75, 62
				//if (r == 70 && g == 75 && b == 62) {
				//	mTiles[i]->SetTileTexture(MAKE_TILE_KEY(TILE_T::SAND, TILE_HEAD_T::ground)
				//		, MAKE_TILE_PATH(TILE_T::SAND, TILE_HEAD_T::ground));
				//}
				wchar_t szFloat[50] = {};
				swprintf_s(szFloat, 50, L"RGB = %d %d %d", r,g,b);
				SetWindowText(application.GetHwnd(), szFloat);
			}
		}
		Scene::Update();
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