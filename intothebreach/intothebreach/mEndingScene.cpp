#include "mEndingScene.h"
#include "mInput.h"
#include "mSceneManager.h"
#include "mSelectGDI.h"
#include "mApplication.h"
#include "mBackground.h"
#include "mCamera.h"
#include "mTime.h"
#include "mTile.h"
#include "mPlayerInfo.h"
extern m::Application application;
namespace m {
	EndingScene::EndingScene() {
	}
	EndingScene::~EndingScene() {
	}
	void EndingScene::Initialize() {
		Scene::Initialize();

		stars = new Background(L"space_star", L"..\\Resources\\texture\\ui\\end\\space_stars.bmp", 1, true);
		stars->SetEC(true);
		stars->SetCutPos(true);

		stars2 = new Background(L"space_star", L"..\\Resources\\texture\\ui\\end\\space_stars.bmp", 1, true);
		stars2->SetPos(Vector2(stars->GetPos().x,
			stars->GetPos().y + application.GetResolutionHeight()));
		stars2->SetEC(true);

		stars3 = new Background(L"space_star", L"..\\Resources\\texture\\ui\\end\\space_stars.bmp", 1, true);
		stars3->SetPos(Vector2(stars2->GetPos().x,
			stars2->GetPos().y + application.GetResolutionHeight()));
		stars3->SetEC(true);

		plant = new Background(L"plant", L"..\\Resources\\texture\\ui\\end\\space_planet.bmp", 1, true);
		plant->SetEC(true);
		plant->SetCutPos(true);

		plantglow = new Background(L"plantglow", L"..\\Resources\\texture\\ui\\end\\space_planet_glow.bmp", 1 , true);
		plantglow->SetEC(true);
		//plantglow->SetPos(plant->GetPos());
		plantglow->SetAlpha(true);
		plantglow->SetAlphaConstant(10);

		plantglow2 = new Background(L"plantglow2", L"..\\Resources\\texture\\ui\\end\\space_pg.bmp", 1, true);
		plantglow2->SetEC(true);
		//plantglow->SetPos(plant->GetPos());
		plantglow2->SetAlpha(true);
		plantglow2->SetAlphaConstant(10);

		explsion = new Background(L"space_expl", L"..\\Resources\\texture\\ui\\end\\space_explosion.bmp");
		explsion->SetEC(true);
		//mx = 690;
		//my = 390;
		mx = 670;
		my = 370;
		explsion->SetPos(Vector2(mx, my));
		explsion->SetSizeUp(true);
		explsion->SetSizeUpxUnit(1.01f);
		explsion->SetSizeUpyUnit(1.01f);


		lines = new Background(L"space_lines", L"..\\Resources\\texture\\ui\\end\\space_lines.bmp", 4);
		lines->SetAlpha(true);
		lines->SetAlphaConstant(125);
		lines->SetPos(Vector2((explsion->GetPos().x - 120) - lines->GetSize().x * 2
			, (explsion->GetPos().y - 20) - lines->GetSize().y * 2));
		lines->SetEC(true);

		spaceglow = new Background(L"space_glow", L"..\\Resources\\texture\\ui\\end\\space_glow.bmp");
		spaceglow->SetSizeUp(true);
		spaceglow->SetSizeUpxUnit(1.01f);
		spaceglow->SetSizeUpyUnit(1.01f);
		spaceglow->SetAlpha(true);
		spaceglow->SetAlphaConstant(10);
		spaceglow->SetPos(Vector2((explsion->GetPos().x - 5) - spaceglow->GetSize().x / 2
			, (explsion->GetPos().y + 30) - spaceglow->GetSize().y / 2));
		spaceglow->SetEC(true);


		scrollText = new Background(L"scroll_text", L"..\\Resources\\texture\\ui\\end\\ending_credit.bmp");
		scrollText->SetPos(Vector2(0, 
			application.GetResolutionHeight() * 2 - scrollText->GetSize().y / 2));
		scrollText->SetEC(true);
		AddGameObject(stars, LAYER_TYPE::UI);
		AddGameObject(stars2, LAYER_TYPE::UI);
		AddGameObject(stars3, LAYER_TYPE::UI);
		AddGameObject(plant, LAYER_TYPE::UI);
		AddGameObject(plantglow, LAYER_TYPE::UI);
		AddGameObject(plantglow2, LAYER_TYPE::UI);
		AddGameObject(lines, LAYER_TYPE::UI);
		AddGameObject(spaceglow, LAYER_TYPE::UI);
		AddGameObject(explsion, LAYER_TYPE::UI);
		AddGameObject(scrollText, LAYER_TYPE::UI);
		timer = 0;
		//GameComp::savedPeople = 500;
		wstring wstr2 = std::to_wstring(GameComp::savedPeople);
		for (int i = 0; i < wstr2.size(); i++)
		{
			wchar_t ch = wstr2[i];
			savePeopleNum[i] = new Background(BOLD_NUM_PATH[ch - 48], BOLD_NUM_PATH[ch - 48], 4);
			savePeopleNum[i]->SetPos(Vector2(scrollText->GetPos().x + 580 + (i * 17 * 2)
				, scrollText->GetPos().y + scrollText->GetSize().y - 200.f));
			savePeopleNum[i]->SetTex(BOLD_NUM_PATH[ch - 48], BOLD_NUM_PATH[ch - 48]);
			savePeopleNum[i]->SetState(GameObject::STATE::Visible);
			savePeopleNum[i]->SetEC(true);
			AddGameObject(savePeopleNum[i], LAYER_TYPE::UI);
		}
	}
	void EndingScene::Update() {
		Scene::Update();
		if (mx != 690) mx++;
		if (my != 390) my++;
		explsion->SetPos(Vector2(mx - explsion->GetWid() / 2
			, my - explsion->GetHei() / 2));
		spaceglow->SetPos(Vector2(685 - spaceglow->GetWid() / 2
			, 340 - spaceglow->GetHei() / 2));
		//Camera::PushEffect(CAMERA_EFFECT_TYPE::Fade_In, 0.5f);
		timer += Time::fDeltaTime();
		if (explsion->GetWid() > explsion->GetSize().x * 4 && explsion->GetSizeUp())
		{
			timer = 0;
			spaceglow->SetSizeUp(false);
			explsion->SetSizeUp(false);
			Camera::SetMoveTime(3.f);
			Camera::SetLookAt(Vector2((float)application.GetResolutionWidth() / 2.f
				, application.GetResolutionHeight() * 2));
		}
		if (explsion->GetWid() > explsion->GetSize().x * 4 
			&& timer > 3.f 
			&& KEY_PRESSED(KEYCODE_TYPE::LBTN))
		{
			SceneManager::LoadScene(SCENE_TYPE::TITLE);
		}
	}
	void EndingScene::Render(HDC hdc) {
		Scene::Render(hdc);

	}
	void EndingScene::Release() {
		Scene::Release();
	}
	void EndingScene::OnEnter() {
	}
	void EndingScene::OnExit() {
	}
}