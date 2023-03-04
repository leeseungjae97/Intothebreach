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
		TILES mPosTiles = (TILES)Scene::GetPosTiles();
		TILES mTiles = (TILES)Scene::GetTiles();
		vector<Mech*> mMechs = Scene::GetMechs();
		
		if (KEY_UP(KEYCODE_TYPE::LBTN)) {
			if (nullptr != mMouseFollower) {
				mMouseFollower->SetFinalPos(mMouseFollower->GetPos());
				mMouseFollower->SetFinalCoord(mMouseFollower->GetCoord());
				mMouseFollower = nullptr;
			}
			else {
				for (int y = 0; y < mPosTiles.size(); y++) {
					for (int x = 0; x < mPosTiles[y].size(); x++) {
						if (Scene::CheckRhombusPos(mPosTiles[y][x], MOUSE_POS)) {
							for (UINT _i = 0; _i < mMechs.size(); _i++) {
								if (mPosTiles[y][x]->GetCoord() == mMechs[_i]->GetCoord()) {
									mMouseFollower = mMechs[_i];
								}
							}
						}
					}
				}
			}	
		}
		if (nullptr != mMouseFollower) {
			for (int y = 0; y < mPosTiles.size(); y++) {
				for (int x = 0; x < mPosTiles[y].size(); x++) {
					if (Scene::CheckRhombusPos(mPosTiles[y][x], MOUSE_POS)) {
						mMouseFollower->SetCoord(mPosTiles[y][x]->GetCoord());
						mMouseFollower->SetPos(mPosTiles[y][x]->GetCenterPos());


						//BFS
						if (mPosTiles[y][x]->GetCoord() == mMouseFollower->GetFinalCoord()) continue;
						int map[TILE_X][TILE_Y]{};
						/*int **map;

						map = new int* [mPosTiles.size()]{};
						for (int i = 0; i < mPosTiles.size(); i++)
							map[i] = new int[mPosTiles[i].size()]{};*/


						list<Vector2> queue;

						map[(int)mMouseFollower->GetFinalCoord().x][(int)mMouseFollower->GetFinalCoord().y] = 1;
						queue.push_back(mMouseFollower->GetFinalCoord());

						float direct[4][2] = {
								{0, 1}
							,{-1, 0} ,{1, 0}
								,{0, -1}
						};
						bool find = false;
						int level = 0;
						
						for (int y = 0; y < mPosTiles.size(); y++) {
							for (int x = 0; x < mPosTiles[y].size(); x++) {
								mTiles[y][x]->SetTileTexture(MAKE_TILE_KEY(TILE_T::GREEN, TILE_HEAD_T::ground)
									, MAKE_TILE_PATH(TILE_T::GREEN, TILE_HEAD_T::ground));
							}
						}

						while (!queue.empty()) {
							Vector2 now = queue.front();
							
							queue.pop_front();
							/*mTiles[(int)dx][(int)dy]->SetTileTexture(MAKE_TILE_KEY(TILE_T::SNOW, TILE_HEAD_T::ground)
								, MAKE_TILE_PATH(TILE_T::SNOW, TILE_HEAD_T::ground));*/
							for (int y = 0; y < mPosTiles.size(); y++) {
								for (int x = 0; x < mPosTiles[y].size(); x++) {
									for (int i = 0; i < 4; i++) {
										float dx = now.x + direct[i][0];
										float dy = now.y + direct[i][1];

										if (dx < 0 || dx >= mPosTiles[y].size() || dy < 0 || dy >= mPosTiles.size()) continue;
										if (map[(int)dx][(int)dy] == 1) continue;
										if (mMouseFollower->GetCoord().x == dx
											&& mMouseFollower->GetCoord().y == dy) {
											find = true;
											break;
										}

										map[(int)dx][(int)dy] = 1;
										mTiles[(int)dx][(int)dy]->SetTileTexture(MAKE_TILE_KEY(TILE_T::SAND, TILE_HEAD_T::ground)
											, MAKE_TILE_PATH(TILE_T::SAND, TILE_HEAD_T::ground));
										queue.push_back(Vector2(dx, dy));
									}
									if (find) break;
								}
								if (find) break;
							}
							if (find) break;
						}
					}
				}
			}
		}
		if (nullptr != mMouseFollower) {
			if (KEY_UP(KEYCODE_TYPE::RBTN)) {
				for (int y = 0; y < mPosTiles.size(); y++) {
					for (int x = 0; x < mPosTiles[y].size(); x++) {
						mTiles[y][x]->SetTileTexture(MAKE_TILE_KEY(TILE_T::GREEN, TILE_HEAD_T::ground)
							, MAKE_TILE_PATH(TILE_T::GREEN, TILE_HEAD_T::ground));
					}
				}

				mMouseFollower->SetPos(mMouseFollower->GetFinalPos());
				mMouseFollower->SetCoord(mMouseFollower->GetFinalCoord());
				mMouseFollower = nullptr;
			}
		}
		Scene::HighlightTile();
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