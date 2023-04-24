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


		for (int i = 0; i < GameComp::mSaveMechs.size(); i++)
		{
			Button* back = new Button(L"", A_BTN_BACK);
			back->SetSize(Vector2(110, 45));
			back->SetPos(Vector2(45, 205 + 130 * i));
			back->SetState(GameObject::STATE::Visible);
			back->SetOSize(Vector2(110, 45));
			back->SetResize(Vector2(110, 110));
			back->SetResizeUnit(Vector2(30, 30));
			AddGameObject(back, LAYER_TYPE::UI);

			//Mech* mech = new Mech(
			//	PlayerInfo::mMechs[i]->GetUnitName()
			//	, Vector2::Minus
			//	, 0
			//	, PlayerInfo::mMechs[i]->GetFullHp()
			//	, 99
			//);
			//mech->SetState(GameObject::STATE::NoMove);
			//Image* img = mech->GetCurImage(COMBAT_CONDITION_T::NO_SHADOW);
			////mech->SetHpCOffset(false);
			////mech->SetHpBackOffset(Vector2(8, -35));
			////mech->SetHpOffset(Vector2(3, -41));
			//Vector2 offset = img->GetOffset();
			//mech->SetPos(Vector2(back->GetPos().x + offset.x + back->GetSize().x / 2 - img->GetWidth()
			//	, back->GetPos().y + img->GetHeight() - offset.y / 2));
			//mech->SetVisibleHp(false);
			//mech->SetImageMag(2);
			////mech->SetState(GameObject::STATE::Visible);

			//infoUnits.push_back(mech);
			//clickableMechs.push_back(back);
			//AddGameObject(mech, LAYER_TYPE::UI);
		}
	}
	void InLandScene::Update()
	{
		Scene::Update();
		if (KEY_DOWN(KEYCODE_TYPE::LBTN))
		{
			SceneManager::LoadScene(SCENE_TYPE::COMBAT);
		}
		if (KEY_DOWN(KEYCODE_TYPE::RBTN))
		{
			SceneManager::LoadScene(SCENE_TYPE::SELECT_LAND);
		}
	}
	void InLandScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void InLandScene::Release()
	{}
	void InLandScene::OnEnter()
	{}
	void InLandScene::OnExit()
	{}
}