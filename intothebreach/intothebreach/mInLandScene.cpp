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
#include "mSound.h"
#include "mResources.h"
#include "mCamera.h"
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
		curItemIndex = 2;
		Background* b = new Background(L"selectLandBg1", L"..\\Resources\\texture\\ui\\selectLand\\waterbg.bmp", 0, true, CENTER);
		
		AddGameObject(b, LAYER_TYPE::BACKGROUND);

		sectionHoverSound = Resources::Load<Sound>(L"mapHoverSound", L"..\\Resources\\sound\\sfx\\ui_map_highlight_region.wav");
		std::fill_n(sectionHoverPlayed, 8, false);
		bBossShake = false;
		Background* b0 = new Background(MAKE_SECTION_KEY(mType, -1), MAKE_SECTION_PATH(mType, -1), 2, false, CENTER);
		b0->SetPos(Vector2(100.f, 100.f));
		AddGameObject(b0, LAYER_TYPE::BACKGROUND);
		Vector2* pos = ISLANDS_SECTION_POS[(UINT)mType];
		for (UINT i = 0; i < ISLANDS_SECTIONS[(UINT)mType]; i++)
		{
			Background* b_ = new Background(MAKE_SECTION_KEY(mType, i)
				, MAKE_SECTION_PATH(mType, i), 2);
			b_->SetPos(pos[i]);
			mSections.push_back(b_);
			AddGameObject(b_, LAYER_TYPE::BACKGROUND);

			Background* mission = new Background(MAKE_MISSION_KEY((int)mType, i)
				, MAKE_MISSION_PATH((int)mType, i));
			if (b_->GetPos().x + b_->GetSize().x * 2 + mission->GetSize().x > application.GetResolutionWidth())
				mission->SetPos(Vector2(b_->GetPos().x - b_->GetSize().x * 3, b_->GetPos().y));
			else
				mission->SetPos(Vector2(b_->GetPos().x + b_->GetSize().x * 2, b_->GetPos().y));
			mMissionsPreview.push_back(mission);
			mission->SetState(GameObject::STATE::Invisible);
			AddGameObject(mission, LAYER_TYPE::UI);

			Background* b_b = new Background(MAKE_SECTION_OL_KEY(mType, i, true)
				, MAKE_SECTION_OL_PATH(mType, i, true), 2);
			b_b->SetPos(pos[i]);
			b_b->SetState(GameObject::STATE::Invisible);
			mSectionsOL.push_back(b_b);
			AddGameObject(b_b, LAYER_TYPE::BACKGROUND);
		}

		//if (mType == ISLAND_T::ISLAND0)
		//{
		//	for (UINT i = 0; i < ISLANDS_SECTIONS[(UINT)mType]; i++)
		//	{
		//		Background* b_ = new Background(MAKE_SECTION_DETECT_KEY(mType, i), MAKE_SECTION_DETECT_PATH(mType, i), 2);
		//		b_->SetPos(pos[i]);
		//		mFunctionSections.push_back(b_);
		//		AddGameObject(b_, LAYER_TYPE::FUNCTIONCAL_BACK);
		//	}
		//}


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
			upGridPowers.push_back(gridPower);
		}
		for (int i = 0; i < 5; i++)
		{
			savePeopleNum[i] = new Background(L"", L"",2);
			reactorNum[i] = new Background(L"", L"",2);
			starNum[i] = new Background(L"", L"",2);
			defenceNum[i] = new Background(L"", L"",2);

			starNum[i]->SetPos(Vector2(upUiBox->GetPos().x + 75 + (i * 17)
				, upUiBox->GetPos().y + upUiBox->GetSize().y / 2));
			reactorNum[i]->SetPos(Vector2(upUiBox->GetPos().x + 215 + (i * 17)
				, upUiBox->GetPos().y + upUiBox->GetSize().y / 2));
			savePeopleNum[i]->SetPos(Vector2(upUiBox->GetPos().x + 780 + (i * 17)
				, upUiBox->GetPos().y + upUiBox->GetSize().y / 2));
			defenceNum[i]->SetPos(Vector2(upUiBox->GetPos().x + 610 + (i * 17)
				, upUiBox->GetPos().y + upUiBox->GetSize().y / 2));

			savePeopleNum[i]->SetState(GameObject::STATE::Invisible);
			starNum[i] ->SetState(GameObject::STATE::Invisible);
			reactorNum[i]->SetState(GameObject::STATE::Invisible);
			defenceNum[i] ->SetState(GameObject::STATE::Invisible);
			AddGameObject(defenceNum[i], LAYER_TYPE::UI);
			AddGameObject(reactorNum[i], LAYER_TYPE::UI);
			AddGameObject(starNum[i], LAYER_TYPE::UI);
			AddGameObject(savePeopleNum[i], LAYER_TYPE::UI);
		}
		

		for (int i = 0; i < 3; i++)
		{
			Button* back = new Button(L"", A_BTN_BACK);
			back->SetSize(Vector2(110, 45));
			back->SetPos(Vector2(45, 205 + 130 * i));
			back->SetState(GameObject::STATE::Visible);
			AddGameObject(back, LAYER_TYPE::UI);

			clickableMechs.push_back(back);
		}
		for (int i = 0; i < 3; i++)
		{
			Background* bM = new Background(MAKE_UNIT_KEY((MECHS)GameComp::mechInfos[i].unitNum, COMBAT_CONDITION_T::NO_SHADOW),
				MAKE_UNIT_PATH((MECHS)GameComp::mechInfos[i].unitNum, COMBAT_CONDITION_T::NO_SHADOW), 2);
			bM->SetUseOffset(false);
			bM->SetPos(Vector2(clickableMechs[i]->GetPos().x + clickableMechs[i]->GetSize().x / 2 - bM->GetWidth()
				, clickableMechs[i]->GetPos().y + clickableMechs[i]->GetSize().y / 2 - bM->GetHeight()));
			infoUnits.push_back(bM);
			AddGameObject(bM, LAYER_TYPE::UI);
		}
		boxBlackFade2 = new Background(ALPHA_BACK, ALPHA_BACK, 0, true, CENTER);
		boxBlackFade2->SetAlpha(true);
		boxBlackFade2->SetAlphaConstant(200);
		boxBlackFade2->SetSize(Vector2(application.GetResolutionWidth(), application.GetResolutionHeight()));
		boxBlackFade2->SetState(GameObject::STATE::Invisible);
		AddGameObject(boxBlackFade2, LAYER_TYPE::FRONT_UI);

		boxBattleResult = new Button(L"..\\Resources\\texture\\ui\\inLand\\secur_area_box.bmp", NO_BACK);
		boxBattleResult->SetInner(true);
		boxBattleResult->UseInnerAlpha(false);
		boxBattleResult->SetSize(boxBattleResult->GetInnerImage()->GetSize());
		boxBattleResult->SetPos(Vector2(application.GetResolutionWidth() / 2 - boxBattleResult->GetInnerImage()->GetWidth() / 2
			, application.GetResolutionHeight() / 2 - boxBattleResult->GetInnerImage()->GetHeight() / 2));
		boxBattleResult->SetState(GameObject::STATE::Invisible);
		AddGameObject(boxBattleResult, LAYER_TYPE::FRONT_UI);


		for (int i = 0; i < 3; i++)
		{
			Button* pilot = new Button(L"", L"");
			pilot->SetInner(true);
			pilot->UseInnerAlpha(false);
			pilot->SetPos(Vector2(420 + 95 * i, 415));
			pilot->SetState(GameObject::STATE::Invisible);
			AddGameObject(pilot, LAYER_TYPE::FRONT_UI);
			boxResultPilots.push_back(pilot);
		}

		text1 = new Background(L"", L"");
		text1->SetState(GameObject::STATE::Invisible);
		text2 = new Background(L"", L"");
		text2->SetState(GameObject::STATE::Invisible);

		AddGameObject(text1, LAYER_TYPE::FRONT_UI);
		AddGameObject(text2, LAYER_TYPE::FRONT_UI);
		for (int i = 0; i < 3; i++)
		{
			resultPeopleNum[i] = new Background(L"", L"", 2);
			resultPeopleNum[i]->SetPos(Vector2(boxBattleResult->GetPos().x + 390 + (i * 17),
				boxBattleResult->GetPos().y + boxBattleResult->GetSize().y - 100));
			resultPeopleNum[i]->SetState(GameObject::STATE::Invisible);
			AddGameObject(resultPeopleNum[i], LAYER_TYPE::FRONT_UI);
		}
		for (int i = 0; i < 2; i++)
		{
			Background* gridPower = new Background(L"", L"");
			Background* star = new Background(L"", L"");
			star->SetState(GameObject::STATE::Invisible);
			gridPower->SetState(GameObject::STATE::Invisible);
			stars.push_back(star);
			gridPowers.push_back(gridPower);

			AddGameObject(gridPower, LAYER_TYPE::FRONT_UI);
			AddGameObject(star, LAYER_TYPE::FRONT_UI);
		}

		btnResultClose = new Button(L"..\\Resources\\texture\\ui\\inLand\\result_okay.bmp", NO_BACK);
		btnResultClose->SetInner(true);
		btnResultClose->UseInnerAlpha(false);
		btnResultClose->SetSize(btnResultClose->GetInnerImage()->GetSize());
		btnResultClose->SetPos(Vector2(boxBattleResult->GetPos().x + boxBattleResult->GetInnerImage()->GetWidth() - btnResultClose->GetInnerImage()->GetWidth()
			, boxBattleResult->GetPos().y + boxBattleResult->GetInnerImage()->GetHeight()));
		btnResultClose->SetState(GameObject::STATE::Invisible);
		AddGameObject(btnResultClose, LAYER_TYPE::FRONT_UI);

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
		int _y = boxSkill1->GetInnerImage()->GetHeight() - boxDragSkill1->GetInnerImage()->GetHeight() * 2;
		boxDragSkill1->SetInnerMag(2);
		boxDragSkill1->SetSize(boxDragSkill1->GetInnerImage()->GetSize());
		boxDragSkill1->SetPos(Vector2(boxSkill1->GetPos().x + 1, boxSkill1->GetPos().y + _y));
		boxDragSkill1->SetOriginPos(boxDragSkill1->GetPos());
		boxDragSkill1->SetState(GameObject::STATE::Invisible);
		boxDragSkill1->SetButtonType(BTN_TYPE::DRAG_WE);
		boxDragSkill1->SetSkillBoxNum(0);

		boxDragSkill2 = new Button(L"..\\Resources\\texture\\weapons\\PlayerWeapons\\support_smoke.bmp", NO_BACK);
		boxDragSkill2->SetInner(true);
		boxDragSkill2->SetInnerMag(2);
		boxDragSkill2->SetSize(boxDragSkill2->GetInnerImage()->GetSize());
		boxDragSkill2->SetPos(Vector2(boxSkill2->GetPos().x + 1
			, boxSkill1->GetPos().y + _y));
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
	void InLandScene::Update()
	{
		Scene::Update();
		if (KEY_PRESSED(KEYCODE_TYPE::RBTN))
		{
			GameComp::curLandSection = 0;
			SceneManager::LoadScene(SCENE_TYPE::SELECT_LAND);
		}
		//int n1 = 10;
		wstring wstr1 = std::to_wstring(GameComp::defence);
		for (int i = 0; i < wstr1.size(); i++)
		{
			wchar_t ch = wstr1[i];
			defenceNum[i]->SetTex(BOLD_NUM_PATH[ch - 48], BOLD_NUM_PATH[ch - 48]);
			defenceNum[i]->SetState(GameObject::STATE::Visible);
			defenceNum[i + 1]->SetTex(L"percente", L"..\\Resources\\texture\\ui\\percent.bmp");
			defenceNum[i + 1]->SetState(GameObject::STATE::Visible);
		}
		wstring wstr2 = std::to_wstring(GameComp::savedPeople);
		for (int i = 0; i < wstr2.size(); i++)
		{
			wchar_t ch = wstr2[i];
			savePeopleNum[i]->SetTex(BOLD_NUM_PATH[ch - 48], BOLD_NUM_PATH[ch - 48]);
			savePeopleNum[i]->SetState(GameObject::STATE::Visible);
		}
		wstring wstr3 = std::to_wstring(GameComp::reactor);
		for (int i = 0; i < wstr3.size(); i++)
		{
			wchar_t ch = wstr3[i];
			reactorNum[i]->SetTex(BOLD_NUM_PATH[ch - 48], BOLD_NUM_PATH[ch - 48]);
			reactorNum[i]->SetState(GameObject::STATE::Visible);
		}
		wstring wstr4 = std::to_wstring(GameComp::star);
		for (int i = 0; i < wstr4.size(); i++)
		{
			wchar_t ch = wstr4[i];
			starNum[i]->SetTex(BOLD_NUM_PATH[ch - 48], BOLD_NUM_PATH[ch - 48]);
			starNum[i]->SetState(GameObject::STATE::Visible);
		}
		for (int i = 0; i < MAX_GRID_POWER; i++)
		{
			wstring gridImageStr = L"";
			if (i < GameComp::gridPower - 1) gridImageStr = L"..\\Resources\\texture\\ui\\combat\\grid_power_on.bmp";
			if (i == GameComp::gridPower - 1) gridImageStr = L"..\\Resources\\texture\\ui\\combat\\grid_power_on_front.bmp";
			if (i > GameComp::gridPower - 1) gridImageStr = L"..\\Resources\\texture\\ui\\combat\\grid_power_off.bmp";
			upGridPowers[i]->ChangeInner(gridImageStr);
		}
		COLORREF color = GetPixel(application.GetHdc(), MOUSE_POS.x, MOUSE_POS.y);
		int checkFinal = 0;

		boxDragSkill2->ChangeInner(WEAPON_IMAGES[(UINT)GameComp::mechInfos[curMech].weapons[1]]);

		for (int i = 0; i < mSections.size(); i++)
		{
			/*if (math::CheckRectPos(mSections[i]->GetPos(), mSections[i]->GetSize() * 2, MOUSE_POS))
			{

			}*/
			if (GameComp::clearLandMatric[GameComp::curLand][i] == CLEAR)
			{
				checkFinal++;
				mSections[i]->SetTex(MAKE_SECTION_KEY(mType, i, true), MAKE_SECTION_PATH(mType, i, true));
				mSectionsOL[i]->SetState(GameObject::STATE::Invisible);

				for (int _i = 0; _i < 8; _i++)
				{
					if (landAdjacencyMatrix[GameComp::curLand][i][_i] == CLEAR)
					{
						if (GameComp::clearLandMatric[GameComp::curLand][_i] != CLEAR
							&& GameComp::curLandSection != _i)
						{
							GameComp::clearLandMatric[GameComp::curLand][_i] = INVASION;

							mSections[_i]->SetTex(MAKE_SECTION_KEY(mType, _i, false, true)
								, MAKE_SECTION_PATH(mType, _i, false, true));
							mSectionsOL[_i]->SetState(GameObject::STATE::Visible);
							mMissionsPreview[_i]->SetState(GameObject::STATE::Invisible);
						}
					}
				}
			}
			else
			{
				if (color == ISLAND_SECTION_DETECT_COLOR3[i])
				{
					mSections[i]->SetTex(MAKE_SECTION_KEY(mType, i, false, true, true)
						, MAKE_SECTION_PATH(mType, i, false, true, true));
					mSectionsOL[i]->SetState(GameObject::STATE::Invisible);
					GameComp::curLandSection = i;
				}
				else if (color == RGB(255, 79, 76))
				{
					mMissionsPreview[GameComp::curLandSection]->SetState(GameObject::STATE::Visible);
					if (KEY_DOWN(KEYCODE_TYPE::LBTN))
					{
						GameComp::clearLandMatric[GameComp::curLand][GameComp::curLandSection] = CLEAR;
						mMissionsPreview[GameComp::curLandSection]->SetState(GameObject::STATE::Invisible);
						//SceneManager::SelectLand(GameComp::curLandSection);
						SceneManager::LoadScene(SCENE_TYPE::COMBAT);
						return;
					}
					if (!sectionHoverPlayed[i])
					{
						sectionHoverSound->Play(false);
						sectionHoverPlayed[i] = true;
					}
					// select
				}
				else if (color == RGB(70, 92, 61))
				{
					// green
				}
				else
				{
					sectionHoverPlayed[i] = false;
					if (GameComp::clearLandMatric[GameComp::curLand][i] == NOR
						&& GameComp::curLandSection != i)
					{
						mSections[i]->SetTex(MAKE_SECTION_KEY(mType, i)
							, MAKE_SECTION_PATH(mType, i));
						mSectionsOL[i]->SetState(GameObject::STATE::Invisible);
					}
					//mSections[GameComp::curLandSection]->SetTex(MAKE_SECTION_KEY(mType, GameComp::curLandSection, false, true)
					//	, MAKE_SECTION_PATH(mType, GameComp::curLandSection, false, true));
					//mSectionsOL[GameComp::curLandSection]->SetState(GameObject::STATE::Visible);
					mMissionsPreview[GameComp::curLandSection]->SetState(GameObject::STATE::Invisible);
				}
			}
		}
		if (checkFinal == 5)
		{
			for (int i = 1; i < 8; i++)
			{
				GameComp::clearLandMatric[GameComp::curLand][i] = CLEAR;
			}
			GameComp::clearLandMatric[GameComp::curLand][0] = INVASION;
		}
		if (checkFinal > 7)
		{
			if (!bBossShake)
			{
				//Camera::PushEffect(CAMERA_EFFECT_TYPE::Shake, 6.f, 100);
				bBossShake = true;
			}
			if (Camera::GetEffectSize() == 0)
			{
				GameComp::checkClearLand[GameComp::curLand] = CLEAR;
				SceneManager::LoadScene(SCENE_TYPE::SELECT_LAND);
			}
			
		}


		if (btnResultClose->GetClicked())
		{
			btnResultClose->SetClicked(false);
			boxBattleResult->SetState(GameObject::STATE::Invisible);
			btnResultClose->SetState(GameObject::STATE::Invisible);
			boxBlackFade->SetState(GameObject::STATE::Invisible);
			text1->SetState(GameObject::STATE::Invisible);
			text2->SetState(GameObject::STATE::Invisible);
			for (int i = 0; i < 2; i++)
			{
				stars[i]->SetState(GameObject::STATE::Invisible);
				gridPowers[i]->SetState(GameObject::STATE::Invisible);
			}
			for (int i = 0; i < boxResultPilots.size(); i++)
			{
				boxResultPilots[i]->SetState(GameObject::STATE::Invisible);
			}
			for(int i = 0 ; i < 3; i++) resultPeopleNum[i]->SetState(GameObject::STATE::Invisible);
			//GameComp::combatEnd = false;
		}
		for (int i = 0; i < clickableMechs.size(); i++)
		{
			//if (clickableMechs[i]->GetHover())
			//{
			//	clickableMechs[i]->SetTex(A_BTN_SELECT_BACK, A_BTN_SELECT_BACK);
			//}
			//else
			//{
			//	clickableMechs[i]->SetTex(A_BTN_BACK, A_BTN_BACK);
			//}
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
		boxDragSkill1->SetInner(true);
		boxDragSkill2->SetInner(true);
		boxDragPilot->SetInner(true);

		boxDragPilot->ChangeInner(PILOT_PATH[(UINT)GameComp::mPilots[curMech]]);
		boxDragPilot->SetItem((int)GameComp::mPilots[curMech]);

		if (GameComp::mechInfos[curMech].weapons[0] == WEAPON_T::NONE) boxDragSkill1->SetInner(false);
		if (GameComp::mechInfos[curMech].weapons[1] == WEAPON_T::NONE) boxDragSkill2->SetInner(false);

		boxDragSkill1->SetItem((int)GameComp::mechInfos[curMech].weapons[0]);
		boxDragSkill2->SetItem((int)GameComp::mechInfos[curMech].weapons[1]);
		boxDragSkill1->ChangeInner(WEAPON_IMAGES[(UINT)GameComp::mechInfos[curMech].weapons[0]]);

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
				//boxPilot->SetTex(A_BTN_SELECT_BACK, A_BTN_SELECT_BACK);
				//boxSkill1->SetTex(A_BTN_SELECT_BACK, A_BTN_SELECT_BACK);
				//boxSkill2->SetTex(A_BTN_SELECT_BACK, A_BTN_SELECT_BACK);
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
					GameComp::mechInfos[curMech].weapons[mM->GetSkillBoxNum()] = WEAPON_T::NONE;

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
					GameComp::mechInfos[curMech].weapons[mM->GetSkillBoxNum()] = WEAPON_T::NONE;

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
				else
				{
					mM->SetPos(mM->GetOriginPos());
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
		if (nullptr == mM)
		{
			if (KEY_DOWN(KEYCODE_TYPE::LBTN))
			{
				if (boxPilot->GetState() == GameObject::STATE::Visible
					&& boxDragPilot->GetItem() != (int)PILOT_T::Pilot_Artificial
					&& math::CheckRectPos(boxDragPilot->GetPos(), boxDragPilot->GetInnerImage()->GetSize() * 2, MOUSE_POS))
				{
					if (boxDragPilot->GetItem() != (int)PILOT_T::Pilot_Artificial)
					{
						mM = boxDragPilot;
						mM->SetFromInfos(true);
					}

				}
				if (boxSkill1->GetState() == GameObject::STATE::Visible
					&& boxDragSkill1->GetItem() != (int)WEAPON_T::NONE
					&& math::CheckRectPos(boxDragSkill1->GetPos(), boxDragSkill1->GetInnerImage()->GetSize() * 2, MOUSE_POS))
				{
					if (boxDragSkill1->GetItem() != (int)WEAPON_T::NONE)
					{
						mM = boxDragSkill1;
						mM->SetFromInfos(true);
					}
				}
				if (boxSkill2->GetState() == GameObject::STATE::Visible
					&& boxDragSkill2->GetItem() != (int)WEAPON_T::NONE
					&& math::CheckRectPos(boxDragSkill2->GetPos(), boxDragSkill2->GetInnerImage()->GetSize() * 2, MOUSE_POS))
				{
					if (boxDragSkill2->GetItem() != (int)WEAPON_T::NONE)
					{
						mM = boxDragSkill2;
						mM->SetFromInfos(true);
					}
				}
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
						if (inventoryColumns[i]->GetItem() != 0)
							mM = inventoryColumns[i];
						//mM->SetInnerMag(2);
						//mM->SetTex(NO_BACK, NO_BACK);
						//mM->SetMag(1);
					}
				}
			}
		}

		for (int i = curItemIndex - 2; i < curItemIndex + 1; i++)
		{
			inventoryColumns[i % 3]->SetFromInven(true);

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
	}
	void InLandScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void InLandScene::Release()
	{}
	void InLandScene::OnEnter()
	{

		GameComp::curLand = (int)mType;
		GameComp::clearLandMatric[GameComp::curLand][0] = 1;
		if (GameComp::checkClearLand[GameComp::curLand])
		{
			SceneManager::LoadScene(SCENE_TYPE::SELECT_LAND);
		}
		//GameComp::combatEnd = true;
		//GameComp::curLandSection = 5;
		//GameComp::curLand = 2;
		

		if (GameComp::combatEnd)
		{
			GameComp::savedPeople += GameComp::saveTurnPeople;
			Sound* victorySound2 = Resources::Load<Sound>(L"victorysound", L"..\\Resources\\sound\\music\\ui_battle_victory.wav");
			victorySound2->Play(false);

			if (GameComp::bKillLeader || GameComp::curLandSection == 0)
			{
				victorySound3 = Resources::Load<Sound>(L"loopBoss", L"..\\Resources\\sound\\music\\mus_victory_boss_loop.wav");
				victorySound3->Play(true);
			}
			else
			{
				inLandTheme = Resources::Load<Sound>(themes[GameComp::curLand], themes[GameComp::curLand]);
				inLandTheme->Play(true);
			}
			for (int i = 0; i < 3; i++)
			{
				boxResultPilots[i]->ChangeInner(PILOT_PATH[(UINT)GameComp::mPilots[i]]);
				boxResultPilots[i]->SetTex(NO_BACK, NO_BACK);
				boxResultPilots[i]->SetState(GameObject::STATE::Visible);
			}

			wstring wstr1 = std::to_wstring(GameComp::saveTurnPeople);
			for (int i = 0; i < wstr1.size(); i++)
			{
				wchar_t ch = wstr1[i];
				resultPeopleNum[i]->SetTex(BOLD_NUM_PATH[ch - 48]
					, BOLD_NUM_PATH[ch - 48]);
				resultPeopleNum[i]->SetState(GameObject::STATE::Visible);
			}
			//GameComp::star += MISSION_REWARD[GameComp::curLand][GameComp::curLandSection][0];
			//if (MAX_GRID_POWER >= 8) GameComp::defence += MISSION_REWARD[GameComp::curLand][GameComp::curLandSection][1];
			//else  GameComp::gridPower += MISSION_REWARD[GameComp::curLand][GameComp::curLandSection][1];

			if (MISSION_REWARD[GameComp::curLand][GameComp::curLandSection][0] != 0)
			{
				int size = MISSION_REWARD[GameComp::curLand][GameComp::curLandSection][0] - 1;
				bool questClear = false;
				bool p2 = false;
				switch ((MISSIONS)MISSION_HASH_VALUE[GameComp::curLand][GameComp::curLandSection][0])
				{
				case MISSIONS::LEADER:
				{
					if (GameComp::bKillLeader) questClear = true;
				}
				break;
				case MISSIONS::KILLCNT:
				{
					if (GameComp::iKillEnCnt >= 5) questClear = true;
				}
				break;
				case MISSIONS::PROTECT:
				{
					if (GameComp::bStructureAlive) questClear = true;
				}
				break;
				case MISSIONS::GRID_D:
				{
					if (GameComp::iGridDamageCnt < 3) questClear = true;
				}
				break;
				case MISSIONS::MECH_D3:
				{
					if (GameComp::iMechDamageCnt < 3) questClear = true;
				}
				break;
				case MISSIONS::MECH_D4:
				{
					if (GameComp::iMechDamageCnt < 4) questClear = true;
				}
				break;
				case MISSIONS::BLOCKCNT:
				{
					if (GameComp::iBlockCnt >= 3) questClear = true;
				}
				break;
				case MISSIONS::NO_D:
				{
					if (GameComp::iMechDamageCnt == 0) questClear = true;
				}
				break;
				}
				for (int i = 0; i < MISSION_REWARD[GameComp::curLand][GameComp::curLandSection][0]; i++)
				{
					if (MISSIONS::PROTECT_2 == (MISSIONS)MISSION_HASH_VALUE[GameComp::curLand][GameComp::curLandSection][0])
					{
						if (i <= GameComp::iStructDesCnt) stars[i]->SetTex(L"mission_star_off", L"..\\Resources\\texture\\ui\\inLand\\mission\\overlayMission\\star_off.bmp");
						else
						{
							stars[i]->SetTex(L"mission_star_on", L"..\\Resources\\texture\\ui\\inLand\\mission\\overlayMission\\star.bmp");
							GameComp::star += MISSION_REWARD[GameComp::curLand][GameComp::curLandSection][0];
						}
					}
					else
					{
						if (!questClear) stars[i]->SetTex(L"mission_star_off", L"..\\Resources\\texture\\ui\\inLand\\mission\\overlayMission\\star_off.bmp");
						else
						{
							stars[i]->SetTex(L"mission_star_on", L"..\\Resources\\texture\\ui\\inLand\\mission\\overlayMission\\star.bmp");
							GameComp::star += MISSION_REWARD[GameComp::curLand][GameComp::curLandSection][0];
						}
					}
					

					stars[i]->SetPos(Vector2(boxBattleResult->GetPos().x + 160 + (i * stars[i]->GetSize().x), boxBattleResult->GetPos().y + 80));
					stars[i]->SetState(GameObject::STATE::Visible);
				}
				text1->SetTex(MISSION_TEXT[GameComp::curLand][GameComp::curLandSection][0],
					MISSION_TEXT[GameComp::curLand][GameComp::curLandSection][0]);
				text1->SetPos(Vector2(stars[size]->GetPos().x + stars[size]->GetSize().x + 15,
					stars[size]->GetPos().y + stars[size]->GetSize().y / 2 - text1->GetSize().y / 2));
				text1->SetState(GameObject::STATE::Visible);
			}

			if (MISSION_REWARD[GameComp::curLand][GameComp::curLandSection][1] != 0)
			{
				int size = MISSION_REWARD[GameComp::curLand][GameComp::curLandSection][1] - 1;
				bool questClear = false;
				bool p2 = false;
				switch ((MISSIONS)MISSION_HASH_VALUE[GameComp::curLand][GameComp::curLandSection][1])
				{
				case MISSIONS::LEADER:
				{
					if (GameComp::bKillLeader) questClear = true;
				}
				break;
				case MISSIONS::KILLCNT:
				{
					if (GameComp::iKillEnCnt >= 5) questClear = true;
				}
				break;
				case MISSIONS::PROTECT:
				{
					if (GameComp::bStructureAlive) questClear = true;
				}
				break;
				case MISSIONS::PROTECT_2:
				{
					if (GameComp::iStructDesCnt < 2) questClear = true;
					p2 = true;
				}
				break;
				case MISSIONS::GRID_D:
				{
					if (GameComp::iGridDamageCnt < 3) questClear = true;
				}
				break;
				case MISSIONS::MECH_D3:
				{
					if (GameComp::iMechDamageCnt < 3) questClear = true;
				}
				break;
				case MISSIONS::MECH_D4:
				{
					if (GameComp::iMechDamageCnt < 4) questClear = true;
				}
				break;
				case MISSIONS::BLOCKCNT:
				{
					if (GameComp::iBlockCnt >= 3) questClear = true;
				}
				break;
				case MISSIONS::NO_D:
				{
					if (GameComp::iMechDamageCnt == 0) questClear = true;
				}
				break;
				}

				for (int i = 0; i < MISSION_REWARD[GameComp::curLand][GameComp::curLandSection][1]; i++)
				{
					if (MISSIONS::PROTECT_2 == (MISSIONS)MISSION_HASH_VALUE[GameComp::curLand][GameComp::curLandSection][1])
					{
						if (i <= GameComp::iStructDesCnt) gridPowers[i]->SetTex(L"mission_grid_off", L"..\\Resources\\texture\\ui\\inLand\\mission\\overlayMission\\power_off.bmp");
						else
						{
							gridPowers[i]->SetTex(L"mission_grid_on", L"..\\Resources\\texture\\ui\\inLand\\mission\\overlayMission\\power.bmp");
							if (GameComp::gridPower >= MAX_GRID_POWER) GameComp::defence += MISSION_REWARD[GameComp::curLand][GameComp::curLandSection][1];
							else  GameComp::gridPower += MISSION_REWARD[GameComp::curLand][GameComp::curLandSection][1];
						}
					}
					else
					{
						if (!questClear) gridPowers[i]->SetTex(L"mission_power_off", L"..\\Resources\\texture\\ui\\inLand\\mission\\overlayMission\\power_off.bmp");
						else
						{
							gridPowers[i]->SetTex(L"mission_power_on", L"..\\Resources\\texture\\ui\\inLand\\mission\\overlayMission\\power.bmp");
							if (GameComp::gridPower >= MAX_GRID_POWER) GameComp::defence += MISSION_REWARD[GameComp::curLand][GameComp::curLandSection][1];
							else  GameComp::gridPower += MISSION_REWARD[GameComp::curLand][GameComp::curLandSection][1];
						}
					}

					gridPowers[i]->SetPos(Vector2(boxBattleResult->GetPos().x + 160 + (i * gridPowers[i]->GetSize().x), boxBattleResult->GetPos().y + 120));
					gridPowers[i]->SetState(GameObject::STATE::Visible);
				}
				text2->SetTex(MISSION_TEXT[GameComp::curLand][GameComp::curLandSection][1],
					MISSION_TEXT[GameComp::curLand][GameComp::curLandSection][1]);
				text2->SetPos(Vector2(gridPowers[size]->GetPos().x + gridPowers[size]->GetSize().x + 15
					, gridPowers[size]->GetPos().y + gridPowers[size]->GetSize().y / 2 - text2->GetSize().y / 2));
				text2->SetState(GameObject::STATE::Visible);
				
			}


			boxBattleResult->SetState(GameObject::STATE::Visible);
			btnResultClose->SetState(GameObject::STATE::Visible);
			boxBlackFade->SetState(GameObject::STATE::Visible);
			for (int i = 0; i < boxResultPilots.size(); i++)
			{
				boxResultPilots[i]->SetState(GameObject::STATE::Visible);
			}
			GameComp::combatEnd = false;
		}
		else
		{
			inLandTheme = Resources::Load<Sound>(themes[GameComp::curLand], themes[GameComp::curLand]);
			inLandTheme->Play(true);
		}

		for (int i = 0; i < GameComp::mechInfos.size(); i++)
		{
			infoUnits[i]->SetTex(MAKE_UNIT_KEY((MECHS)GameComp::mechInfos[i].unitNum, COMBAT_CONDITION_T::NO_SHADOW)
				, MAKE_UNIT_PATH((MECHS)GameComp::mechInfos[i].unitNum, COMBAT_CONDITION_T::NO_SHADOW));
			infoUnits[i]->SetPos(Vector2(clickableMechs[i]->GetPos().x + clickableMechs[i]->GetSize().x / 2 - infoUnits[i]->GetWidth()
				, clickableMechs[i]->GetPos().y + clickableMechs[i]->GetSize().y / 2 - infoUnits[i]->GetHeight()));
			infoUnits[i]->SetState(GameObject::STATE::Visible);
		}
	}
	void InLandScene::OnExit()
	{
		if(inLandTheme)
			inLandTheme->Stop(true);
		if (victorySound3)
			victorySound3->Stop(true);
		bBossShake = false;
	}
}