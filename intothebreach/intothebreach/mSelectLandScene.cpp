#include "mSelectLandScene.h"
#include "mInput.h"
#include "mSceneManager.h"
#include "mTransform.h"
#include "mBackground.h"
#include "mSelectGDI.h"
#include "mApplication.h"
#include "mComponent.h"
#include "mButton.h"
#include "Mech.h"
#include "mPlayerInfo.h"
#include "mImage.h"

extern m::Application application;

namespace m
{
	SelectLandScene::SelectLandScene()
		: Scene()
	{}
	SelectLandScene::~SelectLandScene()
	{}
	void SelectLandScene::Initialize()
	{
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

		for (int i = 0; i < (UINT)ISLAND_T::END; i++)
		{
			Background* p = new Background(MAKE_ISLAND_KEY((ISLAND_T)i), MAKE_ISLAND_PATH((ISLAND_T)i), 2, false, DEFAULT);
			Background* l = new Background(MAKE_ISLAND_KEY((ISLAND_T)i), MAKE_ISLAND_PATH((ISLAND_T)i), 2, false, DEFAULT);
			p->SetPos(Vector2(ISLANDS_POS[i].x, ISLANDS_POS[i].y));
			l->SetPos(Vector2(ISLANDS_POS[i].x, ISLANDS_POS[i].y));
			AddGameObject(p, LAYER_TYPE::BACKGROUND);
			AddGameObject(l, LAYER_TYPE::BACKGROUND);
			Islands.push_back(p);
			outLine.push_back(l);
		}

		upUiBox = new Button(L"..\\Resources\\texture\\ui\\selectLand\\up_box.bmp", NO_BACK);
		upUiBox->SetInner(true);
		upUiBox->UseInnerAlpha(false);
		upUiBox->SetPos(Vector2(application.GetResolutionWidth() / 2 - upUiBox->GetInnerImage()->GetWidth() / 2, 0));
		//upUiBox->SetInnerPos(Vector2(application.GetResolutionWidth() / 2 + upUiBox->GetInnerImage()->GetWidth() / 2, 0));

		AddGameObject(upUiBox, LAYER_TYPE::UI);

		for (int i = 0; i < MAX_GRID_POWER; i++)
		{
			wstring gridImageStr = L"";
			if (i < PlayerInfo::gridPower - 1) gridImageStr = L"..\\Resources\\texture\\ui\\combat\\grid_power_on.bmp";
			if (i == PlayerInfo::gridPower - 1) gridImageStr = L"..\\Resources\\texture\\ui\\combat\\grid_power_on_front.bmp";
			if (i > PlayerInfo::gridPower - 1) gridImageStr = L"..\\Resources\\texture\\ui\\combat\\grid_power_off.bmp";

			Button* gridPower = new Button(gridImageStr, NO_BACK);
			gridPower->SetInner(true);
			gridPower->UseInnerAlpha(false);
			gridPower->SetPos(Vector2(upUiBox->GetPos().x + 415 + (i * 20 + gridPower->GetInnerImage()->GetWidth())
				, upUiBox->GetInnerImage()->GetHeight() / 2 - 30 / 2));
			gridPower->SetState(GameObject::STATE::Visible);
			AddGameObject(gridPower, LAYER_TYPE::UI);
			gridPowers.push_back(gridPower);
		}


		for (int i = 0; i < 3; i++)
		{
			Button* back = new Button(L"", A_BTN_BACK);
			back->SetSize(Vector2(110, 45));
			back->SetPos(Vector2(45, 205 + 130 * i));
			back->SetState(GameObject::STATE::Visible);

			AddGameObject(back, LAYER_TYPE::UI);

			Mech* mech = new Mech(
				PlayerInfo::mMechs[i]->GetUnitName()
				, Vector2::Minus
				, 0
				, PlayerInfo::mMechs[i]->GetFullHp()
				, 99
			);
			mech->SetState(GameObject::STATE::NoMove);
			Image* img = mech->GetCurImage(COMBAT_CONDITION_T::NO_SHADOW);
			//mech->SetHpCOffset(false);
			//mech->SetHpBackOffset(Vector2(8, -35));
			//mech->SetHpOffset(Vector2(3, -41));
			Vector2 offset = img->GetOffset();
			mech->SetPos(Vector2(back->GetPos().x + offset.x + back->GetSize().x / 2 - img->GetWidth()
				, back->GetPos().y + img->GetHeight() - offset.y / 2));
			mech->SetVisibleHp(false);
			mech->SetImageMag(2);
			//mech->SetState(GameObject::STATE::Visible);

			infoUnits.push_back(mech);
			clickableMechs.push_back(back);
			AddGameObject(mech, LAYER_TYPE::UI);

		}

		Scene::Initialize();
	}
	void SelectLandScene::Update()
	{
		Scene::Update();
		for (int i = 0; i < clickableMechs.size(); i++)
		{
			if (clickableMechs[i]->GetHover())
			{
				clickableMechs[i]->SetTex(A_BTN_SELECT_BACK, A_BTN_SELECT_BACK);
			}
			else clickableMechs[i]->SetTex(A_BTN_BACK, A_BTN_BACK);
			if (clickableMechs[i]->GetClicked())
			{
				clickableMechs[i]->SetReSizeable(true);
				clickableMechs[i]->SetResize(Vector2(110, 110));
				clickableMechs[i]->SetClicked(false);
			}
		}
		for (int i = 0; i < Islands.size(); i++)
		{
			Background* p = Islands[i];
			if (math::CheckRectPos(p->GetPos(), p->GetScale(), MOUSE_POS))
			{
				outLine[i]->SetTex(MAKE_ISLAND_OUTLINE_KEY((ISLAND_T)i), MAKE_ISLAND_OUTLINE_PATH((ISLAND_T)i), (ISLAND_T)i);
			}
			else
			{
				outLine[i]->Clear();
			}
		}

		if (KEY_DOWN(KEYCODE_TYPE::LBTN))
		{
			for (int i = 0; i < Islands.size() - 1; i++)
			{
				Background* p = Islands[i];
				if (math::CheckRectPos(p->GetPos(), p->GetScale(), MOUSE_POS))
				{
					SceneManager::LoadScene((SCENE_TYPE)i);
					SceneManager::SelectLand(i);
				}
			}
		}
	}
	void SelectLandScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void SelectLandScene::Release()
	{
		Scene::Release();
	}
	void SelectLandScene::OnEnter()
	{}
	void SelectLandScene::OnExit()
	{}
}