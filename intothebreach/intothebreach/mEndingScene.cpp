#include "mEndingScene.h"
#include "mInput.h"
#include "mSceneManager.h"
#include "mSelectGDI.h"
#include "mApplication.h"
#include "mTile.h"
extern m::Application application;
namespace m {
	EndingScene::EndingScene() {
	}
	EndingScene::~EndingScene() {
	}
	void EndingScene::Initialize() {
		Scene::Initialize();
	}
	void EndingScene::Update() {
		Scene::Update();
		//if (Input::GetKeyState(KEYCODE_TYPE::N) == KEY_STATE::DOWN) {
		//	SceneManager::LoadScene(SCENE_TYPE::SELECT_LAND);
		//}


	}
	void EndingScene::Render(HDC hdc) {
		Scene::Render(hdc);

		Tile* tile = new Tile(10);
		tile->SetTileTexture(L"square", L"..\\Resources\\texture\\terrain\\square_line2.bmp");
		tile->SetPos(Vector2(100.f, 100.f));

		Tile* tile2 = new Tile();
		tile2->SetTileTexture(MAKE_TILE_KEY(TILE_T::GREEN, TILE_HEAD_T::ground)
						, MAKE_TILE_PATH(TILE_T::GREEN, TILE_HEAD_T::ground));
		tile2->SetPos(Vector2(100.f, 100.f));

		AddGameObject(tile2, LAYER_TYPE::TILE);
		AddGameObject(tile, LAYER_TYPE::TILE);

		PEN_TYPE pen = PEN_TYPE::GREEN;

		float rY = MOUSE_POS.y;
		float rX = MOUSE_POS.x;
		Vector2 vv[4];
		float g[4];
		float in[4];

		vv[0].x = tile->GetPos().x;
		vv[0].y = tile->GetPos().y + (tile->GetScale().y * 2) / 2;

		vv[1].x = tile->GetPos().x + (tile->GetScale().x * 2) / 2;
		vv[1].y = tile->GetPos().y;

		vv[2].x = tile->GetPos().x + (tile->GetScale().x * 2);
		vv[2].y = tile->GetPos().y + (tile->GetScale().y * 2) / 2;

		vv[3].x = tile->GetPos().x + (tile->GetScale().x * 2) / 2;
		vv[3].y = tile->GetPos().y + (tile->GetScale().y * 2);

		g[0] = ((vv[0].y - vv[1].y) / (vv[0].x - vv[1].x));
		g[1] = ((vv[1].y - vv[2].y) / (vv[1].x - vv[2].x));
		g[2] = ((vv[2].y - vv[3].y) / (vv[2].x - vv[3].x));
		g[3] = ((vv[3].y - vv[0].y) / (vv[3].x - vv[0].x));

		in[0] = vv[0].y - g[0] * vv[0].x;
		in[1] = vv[1].y - g[1] * vv[1].x;
		in[2] = vv[2].y - g[2] * vv[2].x;
		in[3] = vv[3].y - g[3] * vv[3].x;

		float c1 = g[0] * vv[0].x + in[0];
		float c2 = g[1] * vv[1].x + in[1];
		float c3 = g[2] * vv[2].x + in[2];
		float c4 = g[3] * vv[3].x + in[3];

		MoveToEx(hdc, rY, (g[0] * rX + in[0]), NULL);
		LineTo(hdc, rY, g[1] * rX + in[1]);

		/*MoveToEx(hdc, (g[1] * rX + in[1]), rY, NULL);
		LineTo(hdc, g[2] * rX + in[2], rY);

		MoveToEx(hdc, (g[2] * rX + in[2]), rY, NULL);
		LineTo(hdc, g[3] * rX + in[3], rY);

		MoveToEx(hdc, (g[3] * rX + in[3]), rY, NULL);
		LineTo(hdc, g[0] * rX + in[0], rY);*/


		if (   g[0] * rX + in[0] < rY
			&& g[1] * rX + in[1] < rY
			&& g[2] * rX + in[2] > rY
			&& g[3] * rX + in[3] > rY) {
			pen = PEN_TYPE::RED;
		}
		//Vector2 m = MOUSE_POS;
		//DWORD color = GetPixel(hdc, m.x, m.y);
		//unsigned int r = GetRValue(color);
		//unsigned int g = GetGValue(color);
		//unsigned int b = GetBValue(color);

		SelectGDI p1(hdc, BRUSH_TYPE::HOLLOW);
		SelectGDI p2(hdc, pen);

		Rectangle(hdc, 10, 10, 100, 100);

		wchar_t szFloat[100] = {};
		swprintf_s(szFloat, 100, L"CHECK = %f %f %f %f, MOUSE POS = %f %f", c1, c2, c3, c4, rX, rY);
		SetWindowText(application.GetHwnd(), szFloat);
	}
	void EndingScene::Release() {
		Scene::Release();
	}
	void EndingScene::OnEnter() {
	}
	void EndingScene::OnExit() {
	}
}