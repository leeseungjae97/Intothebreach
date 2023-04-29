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
		//: Scene()
	{}
	SelectLandScene::~SelectLandScene()
	{}
	void SelectLandScene::Initialize()
	{
		Scene::Initialize();
		curItemIndex = 2;
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

		boxPilot = new Button(L"..\\Resources\\texture\\ui\\inventory\\inven_pilot_box.bmp", NO_BACK);
		boxPilot->SetInner(true);
		boxPilot->SetSize(boxPilot->GetInnerImage()->GetSize());
		boxPilot->SetPos(Vector2(mechInfo->GetPos().x + 45
			, application.GetResolutionHeight() / 2 - boxPilot->GetInnerImage()->GetHeight() / 2));
		boxPilot->SetState(GameObject::STATE::Invisible);

		boxDragPilot = new Button(PILOT_PATH[0], NO_BACK);
		boxDragPilot->SetInner(true);
		boxDragPilot->SetInnerMag(2);
		boxDragPilot->SetSize(boxDragPilot->GetInnerImage()->GetSize());
		//boxDragPilot->SetPos(Vector2(mechInfo->GetPos().x + 45
		//	, application.GetResolutionHeight() / 2 - boxDragPilot->GetInnerImage()->GetHeight()));
		boxDragPilot->SetPos(Vector2(boxPilot->GetPos()));
		boxDragPilot->SetOriginPos(boxDragPilot->GetPos());
		boxDragPilot->SetState(GameObject::STATE::Invisible);
		boxDragPilot->SetButtonType(BTN_TYPE::DRAG_PI);

		boxSkill1 = new Button(L"..\\Resources\\texture\\ui\\inventory\\inven_skill_box.bmp", NO_BACK);
		boxSkill1->SetInner(true);
		boxSkill1->SetSize(boxSkill1->GetInnerImage()->GetSize());
		boxSkill1->SetPos(Vector2(boxPilot->GetPos().x + 305
			, application.GetResolutionHeight() / 2 - boxSkill1->GetInnerImage()->GetHeight() / 2 + 15));
		boxSkill1->SetState(GameObject::STATE::Invisible);

		boxSkill2 = new Button(L"..\\Resources\\texture\\ui\\inventory\\inven_skill_box.bmp", NO_BACK);
		boxSkill2->SetInner(true);
		boxSkill2->SetSize(boxSkill2->GetInnerImage()->GetSize());
		boxSkill2->SetPos(Vector2(boxSkill1->GetPos().x + 171
			, application.GetResolutionHeight() / 2 - boxSkill2->GetInnerImage()->GetHeight() / 2 + 15));
		boxSkill2->SetState(GameObject::STATE::Invisible);

		boxDragSkill1 = new Button(L"..\\Resources\\texture\\weapons\\PlayerWeapons\\support_smoke.bmp", NO_BACK);
		boxDragSkill1->SetInner(true);
		int __y = boxSkill1->GetInnerImage()->GetHeight() - boxDragSkill1->GetInnerImage()->GetHeight() * 2;
		boxDragSkill1->SetInnerMag(2);
		boxDragSkill1->SetSize(boxDragSkill1->GetInnerImage()->GetSize());
		boxDragSkill1->SetPos(Vector2(boxSkill1->GetPos().x + 1, boxSkill1->GetPos().y + __y));
		boxDragSkill1->SetOriginPos(boxDragSkill1->GetPos());
		boxDragSkill1->SetState(GameObject::STATE::Invisible);
		boxDragSkill1->SetButtonType(BTN_TYPE::DRAG_WE);
		boxDragSkill1->SetSkillBoxNum(0);

		boxDragSkill2 = new Button(L"..\\Resources\\texture\\weapons\\PlayerWeapons\\support_smoke.bmp", NO_BACK);
		boxDragSkill2->SetInner(true);
		boxDragSkill2->SetInnerMag(2);
		boxDragSkill2->SetSize(boxDragSkill2->GetInnerImage()->GetSize());
		boxDragSkill2->SetPos(Vector2(boxSkill2->GetPos().x + 1
			, boxSkill1->GetPos().y + __y));
		boxDragSkill2->SetOriginPos(boxDragSkill2->GetPos());
		boxDragSkill2->SetState(GameObject::STATE::Invisible);
		boxDragSkill2->SetButtonType(BTN_TYPE::DRAG_WE);
		boxDragSkill2->SetSkillBoxNum(1);

		AddGameObject(inventory, LAYER_TYPE::UI);
		AddGameObject(mechInfo, LAYER_TYPE::UI);


		AddGameObject(boxPilot, LAYER_TYPE::UI);
		AddGameObject(boxDragPilot, LAYER_TYPE::UI);

		AddGameObject(boxSkill1, LAYER_TYPE::UI);
		AddGameObject(boxSkill2, LAYER_TYPE::UI);
		AddGameObject(boxDragSkill1, LAYER_TYPE::UI);
		AddGameObject(boxDragSkill2, LAYER_TYPE::UI);

		btnInvenUp = new Button(L"..\\Resources\\texture\\ui\\inventory\\arrow_up_big_off.bmp", NO_BACK);
		btnInvenUp->SetInner(true);
		btnInvenUp->SetPos(Vector2(inventory->GetPos().x + inventory->GetSize().x / 2 - btnInvenUp->GetInnerImage()->GetWidth() / 2
			, inventory->GetPos().y + btnInvenUp->GetInnerImage()->GetHeight() + 10));
		btnInvenUp->SetSize(btnInvenUp->GetInnerImage()->GetSize());
		btnInvenUp->SetState(GameObject::STATE::Invisible);

		btnInvenDown = new Button(L"..\\Resources\\texture\\ui\\inventory\\arrow_down_big_off.bmp", NO_BACK);
		btnInvenDown->SetInner(true);
		btnInvenDown->SetPos(Vector2(inventory->GetPos().x + inventory->GetSize().x / 2 - btnInvenDown->GetInnerImage()->GetWidth() / 2
			, inventory->GetPos().y + inventory->GetSize().y - btnInvenDown->GetInnerImage()->GetHeight() - 50));
		btnInvenDown->SetSize(btnInvenDown->GetInnerImage()->GetSize());
		btnInvenDown->SetState(GameObject::STATE::Invisible);

		AddGameObject(btnInvenUp, LAYER_TYPE::UI);
		AddGameObject(btnInvenDown, LAYER_TYPE::UI);

		for (int i = 0; i < 3; i++)
		{
			Button* inven = new Button(L"..\\Resources\\texture\\ui\\inventory\\inventory_empty_space.bmp", NO_BACK);
			inven->SetInner(true);
			inven->SetPos(Vector2(inventory->GetPos().x + inventory->GetSize().x / 2 - inven->GetInnerImage()->GetWidth() / 2
				, 30 + inventory->GetPos().y + (30 + inven->GetInnerImage()->GetHeight() * i * 2)));
			inven->SetOriginPos(inven->GetPos());
			inven->SetState(GameObject::STATE::Invisible);
			inven->SetFromInven(true);
			AddGameObject(inven, LAYER_TYPE::UI);
			inventoryColumns.push_back(inven);
		}
		inventoryParts.push_back(inventory);
		inventoryParts.push_back(btnInvenUp);
		inventoryParts.push_back(btnInvenDown);
	}
	void SelectLandScene::Update()
	{

		Scene::Update();
		for (int i = curItemIndex - 2; i < curItemIndex + 1; i++)
		{
			if (GameComp::inventoryItems.size() <= i)
			{
				inventoryColumns[i % 3]->ChangeInner(L"..\\Resources\\texture\\ui\\inventory\\inventory_empty_space.bmp");
				inventoryColumns[i % 3]->SetTex(NO_BACK, NO_BACK);
				inventoryColumns[i % 3]->SetSize(Vector2::One);
			}
			else
			{
				inventoryColumns[i % 3]->SetInnerMag(1);
				inventoryColumns[i % 3]->SetMag(1);
				inventoryColumns[i % 3]->SetInvenIdx(i);
				inventoryColumns[i % 3]->SetItem(GameComp::inventoryItems[i].item);
				if (GameComp::inventoryItems[i].type == (int)BTN_TYPE::DRAG_PI)
				{
					inventoryColumns[i % 3]->ChangeInner(PILOT_PATH[GameComp::inventoryItems[i].item]);
					inventoryColumns[i % 3]->SetTex(L"..\\Resources\\texture\\ui\\inventory\\inven_pilot_b.bmp", L"..\\Resources\\texture\\ui\\inventory\\inven_pilot_b.bmp");
					//inventoryColumns[i % 3]->SetSize(Vector2(inventoryColumns[i % 3]->GetInnerImage()->GetSize().x + 3, inventoryColumns[i % 3]->GetInnerImage()->GetSize().y + 3));
					inventoryColumns[i % 3]->SetSize(inventoryColumns[i % 3]->GetInnerImage()->GetSize() + 3.f);
					inventoryColumns[i % 3]->SetInnerPos(Vector2::One);
					inventoryColumns[i % 3]->SetButtonType(BTN_TYPE::DRAG_PI);
				}
				if (GameComp::inventoryItems[i].type == (int)BTN_TYPE::DRAG_WE)
				{
					inventoryColumns[i % 3]->ChangeInner(WEAPON_IMAGES[GameComp::inventoryItems[i].item]);
					inventoryColumns[i % 3]->SetTex(L"..\\Resources\\texture\\ui\\inventory\\inventory_empty_space.bmp", L"..\\Resources\\texture\\ui\\inventory\\inventory_empty_space.bmp");
					//inventoryColumns[i % 3]->SetSize(Vector2(inventoryColumns[i % 3]->GetInnerImage()->GetSize().x + 3, inventoryColumns[i % 3]->GetInnerImage()->GetSize().y + 3));
					inventoryColumns[i % 3]->SetSize(inventoryColumns[i % 3]->GetInnerImage()->GetSize() + 3.f);
					inventoryColumns[i % 3]->SetInnerPos(Vector2::One);
					inventoryColumns[i % 3]->SetButtonType(BTN_TYPE::DRAG_WE);
				}
				if (GameComp::inventoryItems[i].type == (int)BTN_TYPE::NONE)
				{
					//L"..\\Resources\\texture\\ui\\inventory\\inventory_empty_space.bmp", NO_BACK
					inventoryColumns[i % 3]->ChangeInner(L"..\\Resources\\texture\\ui\\inventory\\inventory_empty_space.bmp");
					inventoryColumns[i % 3]->SetTex(NO_BACK, NO_BACK);
					inventoryColumns[i % 3]->SetSize(Vector2::One);
				}
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
				if (nullptr == mM && !mechInfo->GetHover() && !inventory->GetHover())
				{
					boxBlackFade->SetState(GameObject::STATE::Invisible);
					mechInfo->SetState(GameObject::STATE::Invisible);
					inventory->SetState(GameObject::STATE::Invisible);
					boxDragPilot->SetState(GameObject::STATE::Invisible);
					boxPilot->SetState(GameObject::STATE::Invisible);
					boxSkill1->SetState(GameObject::STATE::Invisible);
					boxSkill2->SetState(GameObject::STATE::Invisible);
					boxDragSkill1->SetState(GameObject::STATE::Invisible);
					boxDragSkill2->SetState(GameObject::STATE::Invisible);
					for (int i = 0; i < inventoryColumns.size(); i++) inventoryColumns[i]->SetState(GameObject::STATE::Invisible);
					for (int i = 0; i < inventoryParts.size(); i++) inventoryParts[i]->SetState(GameObject::STATE::Invisible);
				}
			}
			if (clickableMechs[i]->GetClicked())
			{
				curMech = i;

				boxDragSkill1->SetInner(true);
				boxDragSkill2->SetInner(true);
				boxDragPilot->SetInner(true);


				boxDragPilot->ChangeInner(PILOT_PATH[(UINT)GameComp::mPilots[i]]);
				boxDragPilot->SetItem((int)GameComp::mPilots[i]);

				if (GameComp::mechInfos[i].weapons[0] == WEAPON_T::NONE) boxDragSkill1->SetInner(false);
				if (GameComp::mechInfos[i].weapons[1] == WEAPON_T::NONE) boxDragSkill2->SetInner(false);

				boxDragSkill1->SetItem((int)GameComp::mechInfos[i].weapons[0]);
				boxDragSkill2->SetItem((int)GameComp::mechInfos[i].weapons[1]);
				boxDragSkill1->ChangeInner(WEAPON_IMAGES[(UINT)GameComp::mechInfos[i].weapons[0]]);
				boxDragSkill2->ChangeInner(WEAPON_IMAGES[(UINT)GameComp::mechInfos[i].weapons[1]]);

				boxDragSkill1->SetState(GameObject::STATE::Visible);
				boxDragSkill2->SetState(GameObject::STATE::Visible);
				boxDragPilot->SetState(GameObject::STATE::Visible);
				boxBlackFade->SetState(GameObject::STATE::Visible);
				boxPilot->SetState(GameObject::STATE::Visible);
				boxSkill1->SetState(GameObject::STATE::Visible);
				boxSkill2->SetState(GameObject::STATE::Visible);
				mechInfo->SetState(GameObject::STATE::Visible);
				for (int i = 0; i < inventoryColumns.size(); i++) inventoryColumns[i]->SetState(GameObject::STATE::Visible);
				for (int i = 0; i < inventoryParts.size(); i++) inventoryParts[i]->SetState(GameObject::STATE::Visible);
				clickableMechs[i]->SetClicked(false);
			}
		}
		if (GameComp::inventoryItems.size() > 3)
		{
			btnInvenDown->ChangeInner(L"..\\Resources\\texture\\ui\\inventory\\arrow_down_big_on.bmp");
			if (btnInvenDown->GetHover())
			{
				btnInvenDown->ChangeInner(L"..\\Resources\\texture\\ui\\inventory\\arrow_down_big_select.bmp");
			}
			else btnInvenDown->ChangeInner(L"..\\Resources\\texture\\ui\\inventory\\arrow_down_big_on.bmp");
			if (curItemIndex > 2)
			{
				btnInvenUp->ChangeInner(L"..\\Resources\\texture\\ui\\inventory\\arrow_up_big_on.bmp");
			}
			if (btnInvenUp->GetHover())
			{
				btnInvenUp->ChangeInner(L"..\\Resources\\texture\\ui\\inventory\\arrow_up_big_select.bmp");
			}
			else btnInvenUp->ChangeInner(L"..\\Resources\\texture\\ui\\inventory\\arrow_up_big_on.bmp");

			if (btnInvenDown->GetClicked())
			{
				if (GameComp::inventoryItems.size() - 1 > curItemIndex)
					curItemIndex += 3;

				btnInvenDown->SetClicked(false);
			}
			if (btnInvenUp->GetClicked())
			{
				if (curItemIndex > 2)
					curItemIndex -= 3;
				btnInvenUp->SetClicked(false);
			}
			if (GameComp::inventoryItems.size() - 1 <= curItemIndex) btnInvenDown->ChangeInner(L"..\\Resources\\texture\\ui\\inventory\\arrow_down_big_off.bmp");
			if (curItemIndex <= 2)btnInvenUp->ChangeInner(L"..\\Resources\\texture\\ui\\inventory\\arrow_up_big_off.bmp");
		}

		bool btnClick = false;
		if (mM)
		{
			mM->SetPos(MOUSE_POS - mM->GetSize() / 2);
			Scene::ObjectGoFront(mM, LAYER_TYPE::UI);
		}

		if (KEY_UP(KEYCODE_TYPE::LBTN))
		{
			if (mM && boxPilot->GetHover()/*math::CheckRectPos(boxPilot->GetPos(), boxPilot->GetInnerImage()->GetSize(), MOUSE_POS)*/)
			{
				if (mM->GetButtonType() == BTN_TYPE::DRAG_PI)
				{
					GameComp::mPilots[curMech] = (PILOT_T)mM->GetItem();
					//mM->SetInnerMag(2);
					//mM->SetPos(boxPilot->GetPos());
					//boxDragPilot->Set
					mM->SetItem(0);
					mM->SetPos(mM->GetOriginPos());
					if (mM->GetFromInven()) GameComp::inventoryItems.erase(GameComp::inventoryItems.begin() + mM->GetInvenIdx());
				}
				else
				{
					mM->SetPos(mM->GetOriginPos());
				}
				clickableMechs[curMech]->SetClicked(true);
			}
			else if (mM && math::CheckRectPos(boxSkill1->GetPos(), boxSkill1->GetInnerImage()->GetSize(), MOUSE_POS))
			{
				if (mM->GetButtonType() == BTN_TYPE::DRAG_WE)
				{
					GameComp::mechInfos[curMech].weapons[0] = (WEAPON_T)mM->GetItem();
					//mM->SetInnerMag(2);
					//mM->SetSkillBoxNum(0);
					//boxDragSkill1()
					mM->SetItem(0);
					mM->SetPos(mM->GetOriginPos());
					//mM->SetPos(Vector2(boxSkill1->GetPos().x, boxSkill1->GetPos().y + boxSkill1->GetInnerImage()->GetHeight() - boxDragSkill1->GetInnerImage()->GetHeight() * 2));
					if (mM->GetFromInven()) GameComp::inventoryItems.erase(GameComp::inventoryItems.begin() + mM->GetInvenIdx());
				}
				else
				{
					mM->SetPos(mM->GetOriginPos());
				}
				clickableMechs[curMech]->SetClicked(true);
			}
			else if (mM && math::CheckRectPos(boxSkill2->GetPos(), boxSkill2->GetInnerImage()->GetSize(), MOUSE_POS))
			{
				if (mM->GetButtonType() == BTN_TYPE::DRAG_WE)
				{
					GameComp::mechInfos[curMech].weapons[1] = (WEAPON_T)mM->GetItem();
					//mM->SetInnerMag(2);
					//mM->SetSkillBoxNum(1);
					mM->SetItem(0);
					mM->SetPos(mM->GetOriginPos());
					//mM->SetPos(Vector2(boxSkill2->GetPos().x, boxSkill2->GetPos().y + boxSkill2->GetInnerImage()->GetHeight() - boxDragSkill2->GetInnerImage()->GetHeight() * 2));
					if (mM->GetFromInven()) GameComp::inventoryItems.erase(GameComp::inventoryItems.begin() + mM->GetInvenIdx());
				}
				else
				{
					mM->SetPos(mM->GetOriginPos());
				}
				clickableMechs[curMech]->SetClicked(true);
			}
			else if (mM && math::CheckRectPos(inventory->GetPos(), inventory->GetInnerImage()->GetSize(), MOUSE_POS))
			{
				if (!mM->GetFromInven())
				{
					GameComp::inventoryItems.push_back(GameComp::Inven{ (int)mM->GetButtonType(), mM->GetItem() });
					if (mM->GetButtonType() == BTN_TYPE::DRAG_WE)
					{
						GameComp::mechInfos[curMech].weapons[mM->GetSkillBoxNum()] = WEAPON_T::NONE;
					}
					if (mM->GetButtonType() == BTN_TYPE::DRAG_PI)
					{
						GameComp::mPilots[curMech] = PILOT_T::Pilot_Artificial;
					}
					mM->SetItem(0);
					//mM->SetInner(false);
					mM->SetPos(mM->GetOriginPos());

					if (GameComp::inventoryItems.size() > 2)
					{
						curItemIndex = ((GameComp::inventoryItems.size() / 3)
							+ (GameComp::inventoryItems.size() % 3 != 0 ? 1 : 0)) * 3;
						curItemIndex--;
					}
					clickableMechs[curMech]->SetClicked(true);
				}
				//clickableMechs[curMech]->SetClicked(true);
				//mM->SetInnerMag(1);
				//if (mM->GetButtonType() == BTN_TYPE::DRAG_WE)
				//	mM->ChangeInner(L"..\\Resources\\texture\\ui\\inventory\\inven_skill_box_.bmp");
				//if (mM->GetButtonType() == BTN_TYPE::DRAG_PI)
				//	mM->ChangeInner(L"..\\Resources\\texture\\ui\\inventory\\inven_pilot_box_.bmp");
				//inventoryColumns.push_back(mM);
			}
			else if (mM) mM->SetPos(mM->GetOriginPos());

			mM = nullptr;
		}
		if (KEY_DOWN(KEYCODE_TYPE::LBTN))
		{
			if (boxPilot->GetState() == GameObject::STATE::Visible
				&& boxDragPilot->GetItem() != (int)PILOT_T::Pilot_Artificial
				/*&& boxDragPilot->GetClicked()*/
				&& math::CheckRectPos(boxDragPilot->GetPos(), boxDragPilot->GetInnerImage()->GetSize() * 2, MOUSE_POS))
			{
				if (boxDragPilot->GetItem() != (int)PILOT_T::Pilot_Artificial)
					mM = boxDragPilot;
			}
			if (boxSkill1->GetState() == GameObject::STATE::Visible
				&& boxDragSkill1->GetItem() != (int)WEAPON_T::NONE
				//&& boxDragSkill1->GetClicked()
				&& math::CheckRectPos(boxDragSkill1->GetPos(), boxDragSkill1->GetInnerImage()->GetSize() * 2, MOUSE_POS))
			{
				if (boxDragSkill1->GetItem() != (int)WEAPON_T::NONE)
					mM = boxDragSkill1;
				//boxDragSkill1->SetClicked(false);
			}
			if (boxSkill2->GetState() == GameObject::STATE::Visible
				&& boxDragSkill2->GetItem() != (int)WEAPON_T::NONE
				//&& boxDragSkill2->GetClicked()
				&& math::CheckRectPos(boxDragSkill2->GetPos(), boxDragSkill2->GetInnerImage()->GetSize() * 2, MOUSE_POS))
			{
				if (boxDragSkill2->GetItem() != (int)WEAPON_T::NONE)
					mM = boxDragSkill2;
			}

		}
		for (int i = 0; i < 3; i++)
		{
			if (KEY_DOWN(KEYCODE_TYPE::LBTN))
			{
				if (nullptr == mM)
				{
					if (math::CheckRectPos(inventoryColumns[i]->GetPos(), inventoryColumns[i]->GetInnerImage()->GetSize(), MOUSE_POS))
					{
						mM = inventoryColumns[i];
						//mM->SetInnerMag(2);
						//mM->SetTex(NO_BACK, NO_BACK);
						//mM->SetMag(1);
					}
				}
			}
		}

		if (boxBlackFade->GetState() == GameObject::STATE::Invisible)
		{
			for (int i = 0; i < Islands.size(); i++)
			{
				if (GameComp::checkClearLand[i] == 1)
				{
					outLine[i]->SetTex(MAKE_ISLAND_OUTLINE_KEY((ISLAND_T)i, true), MAKE_ISLAND_OUTLINE_PATH((ISLAND_T)i, true), (ISLAND_T)i);
				}
				else
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
	{
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
	void SelectLandScene::OnExit()
	{
		for (int i = 0; i < infoUnits.size(); i++)
		{
			infoUnits[i]->SetState(GameObject::STATE::Delete);
		}
		infoUnits.clear();
	}
}