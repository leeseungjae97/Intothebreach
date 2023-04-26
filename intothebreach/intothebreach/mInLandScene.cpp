#include "mInLandScene.h"
#include "mInput.h"
#include "mSceneManager.h"
#include "Mech.h"
#include "mTransform.h"
#include "mBackground.h"
#include "mApplication.h"
#include "mButton.h"
#include "mImage.h"
#include "mSelectGDI.h"
#include "mPlayerInfo.h"
extern m::Application application;
namespace m
{
	InLandScene::InLandScene(ISLAND_T _type)
		: mType(_type)
		//, Scene()
	{}
	InLandScene::~InLandScene()
	{}
	void InLandScene::Initialize()
	{
		Background* b = new Background(L"selectLandBg1", L"..\\Resources\\texture\\ui\\selectLand\\waterbg.bmp", 0, true, CENTER);

		AddGameObject(b, LAYER_TYPE::BACKGROUND);

		Background* b0 = new Background(MAKE_SECTION_KEY(mType, -1), MAKE_SECTION_PATH(mType, -1), 2, false, CENTER);
		b0->SetPos(Vector2(100.f, 100.f));
		AddGameObject(b0, LAYER_TYPE::BACKGROUND);
		Vector2* pos = ISLANDS_SECTION_POS[(UINT)mType];
		for (UINT i = 0; i < ISLANDS_SECTIONS[(UINT)mType]; i++)
		{
			Background* b_ = new Background(MAKE_SECTION_KEY(mType, i), MAKE_SECTION_PATH(mType, i), 2);
			b_->SetPos(pos[i]);
			mSections.push_back(b_);
			AddGameObject(b_, LAYER_TYPE::BACKGROUND);
		}
		boxBlackFade = new Background(ALPHA_BACK, ALPHA_BACK, 0, true, CENTER);
		boxBlackFade->SetAlpha(true);
		boxBlackFade->SetAlphaConstant(200);
		boxBlackFade->SetSize(Vector2(application.GetResolutionWidth(), application.GetResolutionHeight()));
		boxBlackFade->SetState(GameObject::STATE::Invisible);
		AddGameObject(boxBlackFade, LAYER_TYPE::UI);

		upUiBox = new Button(L"..\\Resources\\texture\\ui\\selectLand\\up_box.bmp", NO_BACK);
		upUiBox->SetInner(true);
		upUiBox->UseInnerAlpha(false);
		upUiBox->SetPos(Vector2(application.GetResolutionWidth() / 2 - upUiBox->GetInnerImage()->GetWidth() / 2, 0));
		//upUiBox->SetInnerPos(Vector2(application.GetResolutionWidth() / 2 + upUiBox->GetInnerImage()->GetWidth() / 2, 0));

		AddGameObject(upUiBox, LAYER_TYPE::UI);

		for (int i = 0; i < MAX_GRID_POWER; i++)
		{
			wstring gridImageStr = L"";
			if (i < GameComp::gridPower - 1) gridImageStr = L"..\\Resources\\texture\\ui\\combat\\grid_power_on.bmp";
			if (i == GameComp::gridPower - 1) gridImageStr = L"..\\Resources\\texture\\ui\\combat\\grid_power_on_front.bmp";
			if (i > GameComp::gridPower - 1) gridImageStr = L"..\\Resources\\texture\\ui\\combat\\grid_power_off.bmp";

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
			back->SetOSize(Vector2(110, 45));
			back->SetResize(Vector2(110, 110));
			back->SetResizeUnit(Vector2(30, 30));
			AddGameObject(back, LAYER_TYPE::UI);
			clickableMechs.push_back(back);
		}
		boxBattleResult = new Button(L"..\\Resources\\texture\\ui\\inLand\\secur_area_box.bmp", NO_BACK);
		boxBattleResult->SetInner(true);
		boxBattleResult->UseInnerAlpha(false);
		boxBattleResult->SetSize(boxBattleResult->GetInnerImage()->GetSize());
		boxBattleResult->SetPos(Vector2(application.GetResolutionWidth() / 2 - boxBattleResult->GetInnerImage()->GetWidth() / 2
			, application.GetResolutionHeight() / 2 - boxBattleResult->GetInnerImage()->GetHeight() / 2));
		boxBattleResult->SetState(GameObject::STATE::Invisible);
		AddGameObject(boxBattleResult, LAYER_TYPE::UI);

		btnResultClose = new Button(L"..\\Resources\\texture\\ui\\inLand\\result_okay.bmp", NO_BACK);
		btnResultClose->SetInner(true);
		btnResultClose->UseInnerAlpha(false);
		btnResultClose->SetSize(btnResultClose->GetInnerImage()->GetSize());
		btnResultClose->SetPos(Vector2(boxBattleResult->GetPos().x + boxBattleResult->GetInnerImage()->GetWidth() - btnResultClose->GetInnerImage()->GetWidth()
			, boxBattleResult->GetPos().y + boxBattleResult->GetInnerImage()->GetHeight()));
		btnResultClose->SetState(GameObject::STATE::Invisible);
		AddGameObject(btnResultClose, LAYER_TYPE::UI);

		mechInfo = new Button(L"..\\Resources\\texture\\ui\\inventory\\mech_info.bmp", NO_BACK);
		mechInfo->SetInner(true);
		mechInfo->UseInnerAlpha(false);
		mechInfo->SetSize(mechInfo->GetInnerImage()->GetSize());
		mechInfo->SetPos(Vector2(clickableMechs[0]->GetPos().x + clickableMechs[0]->GetSize().x + 40
			, /*clickableMechs[0]->GetPos().y - 50)*/ application.GetResolutionHeight() / 2 - mechInfo->GetInnerImage()->GetHeight() / 2));
		mechInfo->SetState(GameObject::STATE::Invisible);

		inventory = new Button(L"..\\Resources\\texture\\ui\\inventory\\inventory.bmp", NO_BACK);
		inventory->SetInner(true);
		inventory->UseInnerAlpha(false);
		inventory->SetSize(inventory->GetInnerImage()->GetSize());
		inventory->SetPos(Vector2(mechInfo->GetPos().x + mechInfo->GetSize().x + 30
			, application.GetResolutionHeight() / 2 - inventory->GetInnerImage()->GetHeight() / 2));
		inventory->SetState(GameObject::STATE::Invisible);

		boxDragPilot = new Button(PILOT_PATH[0], NO_BACK);
		boxDragPilot->SetInner(true);
		boxDragPilot->SetInnerMag(2);
		boxDragPilot->SetSize(boxDragPilot->GetInnerImage()->GetSize());
		boxDragPilot->SetPos(Vector2(mechInfo->GetPos().x + 45
			, application.GetResolutionHeight() / 2 - boxDragPilot->GetInnerImage()->GetHeight()));
		boxDragPilot->SetState(GameObject::STATE::Invisible);

		boxPilot = new Button(L"..\\Resources\\texture\\ui\\inventory\\inven_pilot_box.bmp", NO_BACK);
		boxPilot->SetInner(true);
		boxPilot->SetSize(boxPilot->GetInnerImage()->GetSize());
		boxPilot->SetPos(Vector2(mechInfo->GetPos().x + 45
			, application.GetResolutionHeight() / 2 - boxPilot->GetInnerImage()->GetHeight() / 2));
		boxPilot->SetState(GameObject::STATE::Invisible);

		boxSkill1 = new Button(L"..\\Resources\\texture\\ui\\inventory\\inven_pilot_box.bmp", NO_BACK);
		boxSkill1->SetInner(true);
		boxSkill1->SetSize(boxSkill1->GetInnerImage()->GetSize());
		boxSkill1->SetPos(Vector2(mechInfo->GetPos().x + 100
			, application.GetResolutionHeight() / 2 - boxSkill1->GetInnerImage()->GetHeight() / 2));
		boxSkill1->SetState(GameObject::STATE::Invisible);

		boxSkill2 = new Button(L"..\\Resources\\texture\\ui\\inventory\\inven_pilot_box.bmp", NO_BACK);
		boxSkill2->SetInner(true);
		boxSkill2->SetSize(boxSkill2->GetInnerImage()->GetSize());
		boxSkill2->SetPos(Vector2(mechInfo->GetPos().x + 150
			, application.GetResolutionHeight() / 2 - boxSkill2->GetInnerImage()->GetHeight() / 2));
		boxSkill2->SetState(GameObject::STATE::Invisible);



		AddGameObject(inventory, LAYER_TYPE::UI);
		AddGameObject(mechInfo, LAYER_TYPE::UI);
		AddGameObject(boxDragPilot, LAYER_TYPE::DRAG_PI);
		AddGameObject(boxPilot, LAYER_TYPE::UI);
		AddGameObject(boxSkill1, LAYER_TYPE::UI);
		AddGameObject(boxSkill2, LAYER_TYPE::UI);
		//AddGameObject(mM, LAYER_TYPE::);
	}
	void InLandScene::Update()
	{
		Scene::Update();
		if (btnResultClose->GetClicked())
		{
			btnResultClose->SetClicked(false);
			boxBattleResult->SetState(GameObject::STATE::Invisible);
			btnResultClose->SetState(GameObject::STATE::Invisible);
			boxBlackFade->SetState(GameObject::STATE::Invisible);
			for (int i = 0; i < boxResultPilots.size(); i++)
			{
				boxResultPilots[i]->SetState(GameObject::STATE::Invisible);
			}
			//GameComp::combatEnd = false;
		}
		bool btnClick = false;
		if (mM)
			mM->SetPos(MOUSE_POS - mM->GetSize() / 2);
		if (KEY_UP(KEYCODE_TYPE::LBTN))
		{
			if (mM && math::CheckRectPos(boxPilot->GetPos(), boxPilot->GetInnerImage()->GetSize(), MOUSE_POS))
			{
				mM->SetInnerMag(2);
				mM->SetPos(boxPilot->GetPos());
				mM = nullptr;
			}
			else if (mM && math::CheckRectPos(inventory->GetPos(), inventory->GetInnerImage()->GetSize(), MOUSE_POS))
			{
				mM->SetInnerMag(1);
				mM->SetPos(inventory->GetPos());
				mM = nullptr;
			}
		}
		if (KEY_DOWN(KEYCODE_TYPE::LBTN))
		{
			//if (mM)
			//{

			//}
			//else
			//{
			//	
			//}
			if (boxPilot->GetState() == GameObject::STATE::Visible
				&& math::CheckRectPos(boxPilot->GetPos(), boxPilot->GetInnerImage()->GetSize(), MOUSE_POS))
			{
				mM = boxDragPilot;
			}
			if (boxSkill1->GetState() == GameObject::STATE::Visible
				&& math::CheckRectPos(boxSkill1->GetPos(), boxSkill1->GetInnerImage()->GetSize(), MOUSE_POS))
			{
				mM = boxDragPilot;
			}
			if (boxSkill2->GetState() == GameObject::STATE::Visible
				&& math::CheckRectPos(boxSkill2->GetPos(), boxSkill2->GetInnerImage()->GetSize(), MOUSE_POS))
			{
				mM = boxDragPilot;
			}
						
		}
		for (int i = 0; i < clickableMechs.size(); i++)
		{
			if (clickableMechs[i]->GetHover())
			{
				clickableMechs[i]->SetTex(A_BTN_SELECT_BACK, A_BTN_SELECT_BACK);
			}
			else
			{
				clickableMechs[i]->SetTex(A_BTN_BACK, A_BTN_BACK);
			}
			if (KEY_PRESSED(KEYCODE_TYPE::LBTN))
			{
				if (!mechInfo->GetHover() && !inventory->GetHover())
				{
					boxBlackFade->SetState(GameObject::STATE::Invisible);
					mechInfo->SetState(GameObject::STATE::Invisible);
					inventory->SetState(GameObject::STATE::Invisible);
					boxDragPilot->SetState(GameObject::STATE::Invisible);
					boxPilot->SetState(GameObject::STATE::Invisible);
					boxSkill1->SetState(GameObject::STATE::Invisible);
					boxSkill2->SetState(GameObject::STATE::Invisible);
				}
			}
			if (clickableMechs[i]->GetClicked())
			{
				boxDragPilot->ChangeInner(PILOT_PATH[(UINT)GameComp::mPilots[i]]);
				boxDragPilot->SetState(GameObject::STATE::Visible);
				boxBlackFade->SetState(GameObject::STATE::Visible);
				boxPilot->SetState(GameObject::STATE::Visible);
				boxSkill1->SetState(GameObject::STATE::Visible);
				boxSkill2->SetState(GameObject::STATE::Visible);
				mechInfo->SetState(GameObject::STATE::Visible);
				inventory->SetState(GameObject::STATE::Visible);
				//clickableMechs[i]->SetClicked(false);
			}
		}
	}
	void InLandScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void InLandScene::Release()
	{}
	void InLandScene::OnEnter()
	{
		//for (int i = 0; i < boxResultPilots.size(); i++)
		//{
		//	boxResultPilots[i]->SetState(GameObject::STATE::Delete);
		//}
		//boxResultPilots.clear();
		bMouseDrag = false;
		for (int i = 0; i < 3; i++)
		{
			Button* pilot = new Button(PILOT_PATH[(UINT)GameComp::mPilots[i]], NO_BACK);
			pilot->SetInner(true);
			pilot->UseInnerAlpha(false);
			pilot->SetPos(Vector2(420 + 95 * i, 415));
			pilot->SetState(GameObject::STATE::Invisible);
			AddGameObject(pilot, LAYER_TYPE::UI);
			boxResultPilots.push_back(pilot);
		}
		//GameComp::combatEnd = true;
		if (GameComp::combatEnd)
		{
			boxBattleResult->SetState(GameObject::STATE::Visible);
			btnResultClose->SetState(GameObject::STATE::Visible);
			boxBlackFade->SetState(GameObject::STATE::Visible);
			for (int i = 0; i < boxResultPilots.size(); i++)
			{
				boxResultPilots[i]->SetState(GameObject::STATE::Visible);
			}
		}

		for (int i = 0; i < GameComp::mechInfos.size(); i++)
		{
			Mech* mech = new Mech(
				GameComp::mechInfos[i].unitNum
				, Vector2::Minus
				, 0
				, 1
				, 99
			);
			mech->SetState(GameObject::STATE::NoMove);
			Image* img = mech->GetCurImage(COMBAT_CONDITION_T::NO_SHADOW);
			//mech->SetHpCOffset(false);
			//mech->SetHpBackOffset(Vector2(8, -35));
			//mech->SetHpOffset(Vector2(3, -41));
			Vector2 offset = img->GetOffset();
			mech->SetPos(Vector2(clickableMechs[i]->GetPos().x + offset.x + clickableMechs[i]->GetSize().x / 2 - img->GetWidth()
				, clickableMechs[i]->GetPos().y + img->GetHeight() - offset.y / 2));
			mech->SetVisibleHp(false);
			mech->SetImageMag(2);
			//mech->SetState(GameObject::STATE::Visible);

			infoUnits.push_back(mech);
			AddGameObject(mech, LAYER_TYPE::UI);
		}
	}
	void InLandScene::OnExit()
	{
		for (int i = 0; i < boxResultPilots.size(); i++)
		{
			boxResultPilots[i]->SetState(GameObject::STATE::Delete);
		}
		boxResultPilots.clear();
		for (int i = 0; i < infoUnits.size(); i++)
		{
			infoUnits[i]->SetState(GameObject::STATE::Delete);
		}
		infoUnits.clear();
	}
}