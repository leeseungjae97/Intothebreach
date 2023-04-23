#include "mCombatScene.h"
#include "Mech.h"
#include "mSceneManager.h"
#include "mInput.h"
#include "mTransform.h"
#include "mBackground.h"
#include "mButton.h"
#include "mSelectGDI.h"
#include "mApplication.h"
#include "mResources.h"
#include "mBackground.h"
#include "mTile.h"
#include "Mech.h"
#include "func.h"
#include "Building.h"
#include "Alien.h"
#include "mSkill.h"
#include "mTime.h"
#include "mCamera.h"
extern m::Application application;
namespace m
{
	CombatScene::CombatScene()
		: Scene()
		, endGame(false)
		, bSetPosition(false)
		, showEnd(false)
	{}
	CombatScene::~CombatScene()
	{}
	void CombatScene::Initialize()
	{
		Scene::Initialize();
		Scene::MakeTile(TILE_X, TILE_Y, TILE_T::GREEN, TILE_HEAD_T::ground);
		mechIdx = 0;
		iTurn = 7;
		Background* b0 = new Background(L"combatBackground1"
			, L"..\\Resources\\texture\\ui\\combat\\bg.bmp", 0, false, DEFAULT);

		UINT _x = (UINT)(application.GetResolutionWidth() / b0->GetWidth());
		UINT _y = (UINT)(application.GetResolutionHeight() / b0->GetHeight());

		delete b0;

		for (UINT y = 0; y <= _y; y++)
		{
			for (UINT x = 0; x <= _x; x++)
			{
				Background* b_ = new Background(L"combatBackground1"
					, L"..\\Resources\\texture\\ui\\combat\\bg.bmp", 0, false, DEFAULT);
				b_->SetPos(Vector2(b_->GetWidth() * x, b_->GetHeight() * y));
				mBacks.push_back(b_);
				AddGameObject(b_, LAYER_TYPE::BACKGROUND);
			}
		}
		for (UINT y = 0; y <= _y; y++)
		{
			for (UINT x = 0; x <= _x; x++)
			{
				Background* b_ = new Background(L"combatBackground2"
					, L"..\\Resources\\texture\\ui\\combat\\background_warning.bmp", 0, false, DEFAULT);
				b_->SetPos(Vector2(b_->GetWidth() * x, b_->GetHeight() * y));
				b_->SetAlpha(true);
				b_->SetAlphaConstant(0);
				b_->SetIdVar(15);
				combatBack.push_back(b_);
				AddGameObject(b_, LAYER_TYPE::BACKGROUND);
			}
		}

		textDeploy = new Button(COMBAT_UI_TEXT_PATH[(UINT)COMBAT_UI_TEXT::DEPLOYING_TEXT], A_BTN_BACK);
		textDeploy->SetInner(true);
		textDeploy->SetAlpha(true);
		textDeploy->UseInnerAlpha(false);
		textDeploy->SetInnerPos(Vector2(10.f, 10.f));
		textDeploy->SetPos(Vector2(10.f, 10.f));
		textDeploy->SetSize(Vector2(300.f, 80.f));

		btnConfirm = new Button(COMBAT_UI_TEXT_PATH[(UINT)COMBAT_UI_TEXT::CON_TEXT], A_BTN_BACK);
		btnConfirm->SetInner(true);
		btnConfirm->SetAlpha(true);
		btnConfirm->UseInnerAlpha(false);
		btnConfirm->SetPos(Vector2(textDeploy->GetPos().x, textDeploy->GetPos().y + textDeploy->GetSize().y + 10.f));
		btnConfirm->SetInnerPos(Vector2(btnConfirm->GetPos().x + 10.f, 10.f));
		btnConfirm->SetSize(Vector2(100.f, 50.f));
		btnConfirm->SetState(GameObject::STATE::Invisible);

		textTurn = new Button(COMBAT_UI_TEXT_PATH[(UINT)COMBAT_UI_TEXT::TURN_TEXT], A_BTN_BACK);
		textTurn->SetInner(true);
		textTurn->SetAlpha(true);
		textTurn->UseInnerAlpha(false);
		textTurn->SetSize(Vector2(300.f, 50.f));
		textTurn->SetPos(Vector2(application.GetResolutionWidth() - textTurn->GetSize().x, 10.f));
		textTurn->SetInnerPos(Vector2(textTurn->GetSize().x / 2 - 105.f / 2
			, textTurn->GetSize().y / 2 - 14.f / 2));

		textTurnNum = new Button(COMBAT_UI_TEXT_PATH[iTurn], NO_BACK);
		textTurnNum->SetInner(true);
		textTurnNum->UseInnerAlpha(false);
		textTurnNum->SetPos(Vector2(textTurn->GetPos()));
		textTurnNum->SetInnerMag(2);
		textTurnNum->SetInnerPos(Vector2(textTurn->GetInnerPos().x + 60.f, 0.f));

		gridPowerBox = new Button(L"..\\Resources\\texture\\ui\\combat\\grid_def_box_off.bmp", A_BTN_BACK);
		gridPowerBox->SetInner(true);
		gridPowerBox->UseInnerAlpha(false);
		gridPowerBox->SetSize(Vector2(380.f, 38.f));
		gridPowerBox->SetPos(Vector2(10.f, 10.f));
		gridPowerBox->SetInnerPos(Vector2(gridPowerBox->GetSize().x / 2 - 291 / 2, gridPowerBox->GetSize().y / 2 - 33 / 2));
		gridPowerBox->SetState(GameObject::STATE::Invisible);
		AddGameObject(gridPowerBox, LAYER_TYPE::UI);

		for (int i = 0; i < MAX_GRID_POWER; i++)
		{
			wstring gridImageStr = L"";
			if (i < PlayerInfo::gridPower - 1) gridImageStr = L"..\\Resources\\texture\\ui\\combat\\grid_power_on.bmp";
			if (i == PlayerInfo::gridPower - 1) gridImageStr = L"..\\Resources\\texture\\ui\\combat\\grid_power_on_front.bmp";
			if (i > PlayerInfo::gridPower - 1) gridImageStr = L"..\\Resources\\texture\\ui\\combat\\grid_power_off.bmp";

			Button* gridPower = new Button(gridImageStr, NO_BACK);
			gridPower->SetInner(true);
			gridPower->UseInnerAlpha(false);
			gridPower->SetPos(Vector2(gridPowerBox->GetInnerPos().x + 95 + (i * 20 + gridPower->GetInnerImage()->GetWidth())
				, 10 + gridPowerBox->GetSize().y / 2 - 30 / 2));
			gridPower->SetState(GameObject::STATE::Invisible);
			AddGameObject(gridPower, LAYER_TYPE::UI);
			gridPowers.push_back(gridPower);
		}

		btnTurnEnd = new Button(L"..\\Resources\\texture\\ui\\combat\\turn_end_text.bmp", A_BTN_BACK);
		btnTurnEnd->SetInner(true);
		btnTurnEnd->UseInnerAlpha(false);
		btnTurnEnd->SetSize(Vector2(210, 65));
		btnTurnEnd->SetPos(Vector2(gridPowerBox->GetPos().x, gridPowerBox->GetPos().y + gridPowerBox->GetSize().y + 5));
		btnTurnEnd->SetInnerPos(Vector2(btnTurnEnd->GetSize().x / 2 - 90 / 2, btnTurnEnd->GetSize().y / 2 - 28 / 2));

		btnUndoMove = new Button(L"..\\Resources\\texture\\ui\\combat\\cancel_move_text.bmp", A_BTN_BACK);
		btnUndoMove->SetInner(true);
		btnUndoMove->UseInnerAlpha(false);
		btnUndoMove->SetSize(Vector2(90, 65));
		btnUndoMove->SetPos(Vector2(btnTurnEnd->GetPos().x + btnTurnEnd->GetSize().x + 5, btnTurnEnd->GetPos().y));
		btnUndoMove->SetInnerPos(Vector2(btnUndoMove->GetSize().x / 2 - 27 / 2, btnUndoMove->GetSize().y / 2 - 33 / 2));

		btnInitTurn = new Button(L"..\\Resources\\texture\\ui\\combat\\turn_init_text.bmp", A_BTN_BACK);
		btnInitTurn->SetInner(true);
		btnInitTurn->UseInnerAlpha(false);
		btnInitTurn->SetSize(Vector2(90, 38));
		btnInitTurn->SetPos(Vector2(15 + gridPowerBox->GetSize().x, 10));
		btnInitTurn->SetInnerPos(Vector2(btnInitTurn->GetSize().x / 2 - 63 / 2, btnInitTurn->GetSize().y / 2 - 13 / 2));

		playerTurnBox = new Button(L"..\\Resources\\texture\\ui\\combat\\player_turn_noti.bmp", TURN_BACK);
		playerTurnBox->SetInner(true);
		playerTurnBox->UseInnerAlpha(true);
		playerTurnBox->SetInnerConstant(0);
		playerTurnBox->SetAlpha(true);
		playerTurnBox->SetConstant(0);
		playerTurnBox->SetSize(Vector2((float)application.GetResolutionWidth(), 80.f));
		playerTurnBox->SetPos(Vector2(0, (float)application.GetResolutionHeight() / 2));
		playerTurnBox->SetInnerPos(Vector2(playerTurnBox->GetSize().x / 2 - 147 / 2, playerTurnBox->GetSize().y / 2 - 55 / 2));
		playerTurnBox->SetIdVar(5);
		playerTurnBox->SetState(GameObject::STATE::Invisible);

		alienTurnBox = new Button(L"..\\Resources\\texture\\ui\\combat\\start_mission_text.bmp", TURN_BACK);
		alienTurnBox->SetInner(true);
		alienTurnBox->UseInnerAlpha(true);
		alienTurnBox->SetInnerConstant(0);
		alienTurnBox->SetAlpha(true);
		alienTurnBox->SetConstant(0);
		alienTurnBox->SetSize(Vector2((float)application.GetResolutionWidth(), 80.f));
		alienTurnBox->SetPos(Vector2(0, (float)application.GetResolutionHeight() / 2));
		alienTurnBox->SetInnerPos(Vector2(alienTurnBox->GetSize().x / 2 - 133 / 2, alienTurnBox->GetSize().y / 2 - 27 / 2));
		alienTurnBox->SetIdVar(5);
		alienTurnBox->SetState(GameObject::STATE::Invisible);

		endMissionBox = new Button(L"..\\Resources\\texture\\ui\\combat\\end_mission_text.bmp", TURN_BACK);
		endMissionBox->SetInner(true);
		endMissionBox->UseInnerAlpha(true);
		endMissionBox->SetAlpha(true);
		endMissionBox->SetInnerConstant(0);
		endMissionBox->SetConstant(0);
		endMissionBox->SetSize(Vector2((float)application.GetResolutionWidth(), 80.f));
		endMissionBox->SetPos(Vector2(0, (float)application.GetResolutionHeight() / 2));
		endMissionBox->SetInnerPos(Vector2((float)endMissionBox->GetSize().x / 2 - 133 / 2, (float)endMissionBox->GetSize().y / 2 - 27 / 2));
		endMissionBox->SetIdVar(5);

		endMissionBox->SetState(GameObject::STATE::Invisible);
		btnTurnEnd->SetState(GameObject::STATE::Invisible);
		btnUndoMove->SetState(GameObject::STATE::Invisible);
		btnInitTurn->SetState(GameObject::STATE::Invisible);

		playerUnitInfo = new Button(L"..\\Resources\\texture\\ui\\combat\\player_unit_info.bmp", TURN_BACK);
		playerUnitInfo->SetInner(true);
		playerUnitInfo->SetSize(Vector2((float)playerUnitInfo->GetInnerImage()->GetWidth(), (float)playerUnitInfo->GetInnerImage()->GetHeight()));
		playerUnitInfo->SetPos(Vector2(10.f, (float)btnTurnEnd->GetPos().y + btnTurnEnd->GetSize().y + 5));
		playerUnitInfo->SetInnerPos(Vector2((float)playerUnitInfo->GetSize().x / 2 - 57 / 2, (float)playerUnitInfo->GetSize().y / 2 - 195 / 2));
		playerUnitInfo->SetState(GameObject::STATE::Invisible);
		
		selectUnitBox = new Button(L"..\\Resources\\texture\\ui\\combat\\select_player_unit.bmp", NO_BACK);
		selectUnitBox->SetInner(true);
		//selectUnitBox->SetPos(Vector2(10.f, btnTurnEnd->GetPos().y + btnTurnEnd->GetSize().y + 5));
		selectUnitBox->SetPos(Vector2(10.f, btnTurnEnd->GetPos().y + btnTurnEnd->GetSize().y + 5
		 + ((selectUnitBox->GetInnerImage()->GetHeight() + 3) * 2)));
		selectUnitBox->SetSize(Vector2((float)selectUnitBox->GetInnerImage()->GetWidth(),
			(float)selectUnitBox->GetInnerImage()->GetHeight()));
		//selectUnitBox->SetInnerPos(Vector2();
		selectUnitBox->SetState(GameObject::STATE::Invisible);

		//textTurnNum->SetSize(Vector2(300.f, 50.f));
		//textTurn->SetState(GameObject::STATE::Invisible);
		//textTurnInfo = new Button();
		//textDefence1 = new Button(L"..\\Resources\\texture\\ui\\combat\\grid_def_box.bmp", A_BTN_BACK);
		//textDefence1->SetText(true);
		//textDefence1->UseTextAlpha(false);
		//textDefence1->SetPos(Vector2(textTurn->GetPos()));
		//textDefence1->SetTextMag(2);
		//textDefence1->SetTextPos(Vector2(textTurn->GetTextPos().x + 60.f, 0.f));
		AddGameObject(textDeploy, LAYER_TYPE::UI);
		AddGameObject(btnConfirm, LAYER_TYPE::UI);
		AddGameObject(textTurn, LAYER_TYPE::UI);
		AddGameObject(textTurnNum, LAYER_TYPE::UI);

		AddGameObject(btnTurnEnd, LAYER_TYPE::UI);
		AddGameObject(btnUndoMove, LAYER_TYPE::UI);
		AddGameObject(btnInitTurn, LAYER_TYPE::UI);
		AddGameObject(playerUnitInfo, LAYER_TYPE::UI);
		AddGameObject(playerTurnBox, LAYER_TYPE::UI);
		AddGameObject(endMissionBox, LAYER_TYPE::UI);
		AddGameObject(alienTurnBox, LAYER_TYPE::UI);
		AddGameObject(selectUnitBox, LAYER_TYPE::UI);

		// 임시로 메카위치 설정
		// 마우스로 클릭한 땅에 메카가 떨어지게 설정해야됨
		//object::Instantiate(Vector2(0, 0), LAYER_TYPE::STRUCT, STRUCTURES::airfield);
		//object::Instantiate(Vector2(1, 0), LAYER_TYPE::STRUCT, STRUCTURES::bar);
		//object::Instantiate(Vector2(2, 0), LAYER_TYPE::STRUCT, STRUCTURES::battry);
		//object::Instantiate(Vector2(2, 0), LAYER_TYPE::STRUCT, STRUCTURES::energy);
		//object::Instantiate(Vector2(3, 0), LAYER_TYPE::STRUCT, STRUCTURES::factory);
		//object::Instantiate(Vector2(4, 0), LAYER_TYPE::STRUCT, STRUCTURES::hospital);
		//object::Instantiate(Vector2(5, 0), LAYER_TYPE::STRUCT, STRUCTURES::military);
		//object::Instantiate(Vector2(6, 0), LAYER_TYPE::STRUCT, STRUCTURES::power);
		//object::Instantiate(Vector2(7, 0), LAYER_TYPE::STRUCT, STRUCTURES::radar);
		//object::Instantiate(Vector2(0, 1), LAYER_TYPE::STRUCT, STRUCTURES::recycle);
		//object::Instantiate(Vector2(1, 1), LAYER_TYPE::STRUCT, STRUCTURES::research);
		//object::Instantiate(Vector2(2, 1), LAYER_TYPE::STRUCT, STRUCTURES::shield);
		//object::Instantiate(Vector2(3, 1), LAYER_TYPE::STRUCT, STRUCTURES::supply);
		//object::Instantiate(Vector2(2, 1), LAYER_TYPE::STRUCT, STRUCTURES::timelab);
		//object::Instantiate(Vector2(4, 1), LAYER_TYPE::STRUCT, STRUCTURES::wind);
		//object::Instantiate(Vector2::Minus, LAYER_TYPE::PLAYER, UNITS[(UINT)MECHS::artillery]);
		//object::Instantiate(Vector2::Minus, LAYER_TYPE::PLAYER, UNITS[(UINT)MECHS::tank]);
		//object::Instantiate(Vector2::Minus, LAYER_TYPE::PLAYER, UNITS[(UINT)MECHS::punch]);

		for (int i = 0; i < PlayerInfo::mMechs.size(); i++)
		{
			Mech* mech = new Mech(
				PlayerInfo::mMechs[i]->GetUnitName()
				, Vector2::Minus
				, 0
				, PlayerInfo::mMechs[i]->GetFullHp()
				, 99
			);
			mech->SetState(GameObject::STATE::NoMove);
			Image* img = mech->GetCurImage(COMBAT_CONDITION_T::NO_SHADOW);
			//Image* img = mech->GetCurImage(COMBAT_CONDITION_T::BROKEN);
			mech->SetHpCOffset(false);
			mech->SetHpBackOffset(Vector2(8, -35));
			mech->SetHpOffset(Vector2(3, -41));
			Vector2 offset = img->GetOffset();
			mech->SetPos(Vector2(playerUnitInfo->GetPos().x - offset.x + playerUnitInfo->GetSize().x / 2 + (img->GetWidth()) / 2
				,playerUnitInfo->GetPos().y - offset.y + 70 * (i + 1) - 30));
			mech->SetVisibleHp(true);
			mech->SetImageMag(1);
			mech->SetState(GameObject::STATE::Invisible);
			AddGameObject(mech, LAYER_TYPE::UI);
			infoUnits.push_back(mech);
		}

		//RandSpawnAlien(10);

		object::Instantiate(Vector2(0, 0), LAYER_TYPE::STRUCT, STRUCTURES::mountain, TILE_T::GREEN);
		object::Instantiate(Vector2(0, 1), LAYER_TYPE::STRUCT, STRUCTURES::mountain, TILE_T::GREEN);
		object::Instantiate(Vector2(0, 2), LAYER_TYPE::STRUCT, STRUCTURES::mountain, TILE_T::GREEN);

		object::Instantiate(Vector2(1, 0), LAYER_TYPE::STRUCT, STRUCTURES::mountain, TILE_T::GREEN);
		object::Instantiate(Vector2(2, 0), LAYER_TYPE::STRUCT, STRUCTURES::mountain, TILE_T::GREEN);
		object::Instantiate(Vector2(3, 0), LAYER_TYPE::STRUCT, STRUCTURES::mountain, TILE_T::GREEN);
		object::Instantiate(Vector2(4, 0), LAYER_TYPE::STRUCT, STRUCTURES::mountain, TILE_T::GREEN);

		object::Instantiate(Vector2(4, 5), LAYER_TYPE::STRUCT, STRUCTURES::mountain, TILE_T::GREEN);
		object::Instantiate(Vector2(4, 6), LAYER_TYPE::STRUCT, STRUCTURES::mountain, TILE_T::GREEN);
		object::Instantiate(Vector2(4, 7), LAYER_TYPE::STRUCT, STRUCTURES::mountain, TILE_T::GREEN);

		object::Instantiate(Vector2(4, 1), LAYER_TYPE::STRUCT, STRUCTURES::mountain, TILE_T::GREEN);
		object::Instantiate(Vector2(4, 2), LAYER_TYPE::STRUCT, STRUCTURES::mountain, TILE_T::GREEN);
		//object::Instantiate(Vector2(4, 3), LAYER_TYPE::STRUCT, STRUCTURES::mountain, TILE_T::GREEN);
		//object::Instantiate(Vector2(4, 4), LAYER_TYPE::STRUCT, STRUCTURES::mountain, TILE_T::GREEN);

		//object::Instantiate(Vector2(7, 7), LAYER_TYPE::STRUCT, STRUCTURES::mountain);

		//object::Instantiate(Vector2(5, 3), LAYER_TYPE::STRUCT, STRUCTURES::mountain);
		//object::Instantiate(Vector2(5, 4), LAYER_TYPE::STRUCT, STRUCTURES::mountain);
		//object::Instantiate(Vector2(5, 5), LAYER_TYPE::STRUCT, STRUCTURES::mountain);

		object::Instantiate(Vector2(0, 7), LAYER_TYPE::STRUCT, STRUCTURES::tower, TILE_T::GREEN);
		object::Instantiate(Vector2(1, 5), LAYER_TYPE::STRUCT, STRUCTURES::airfield, TILE_T::GREEN);
	}
	void CombatScene::RandSpawnAlien(int number)
	{
		size_t maxNum = GetAliens().size();
		while (GetAliens().size() != number + maxNum)
		{
			srand((unsigned int)time(NULL));
			//int randNum = rand();
			float randY = (float)(rand() % 7);
			float randX = (float)(rand() % 3);
			//int randNum2 = rand();

			randY += 1.f;
			randX += 5.f;
			int randAlien[2] = { 6,7 };
			int randUnit = rand() % 2;
			if (GetAliens().size() == 0)
				object::Instantiate(Vector2(6, 5), LAYER_TYPE::MONSTER, UNITS[/*randAlien[randUnit]*/6]);
			else
			{
				bool f = false;
				vector<Alien*>::iterator iter = GetAliens().begin();
				while (iter != GetAliens().end())
				{
					if ((*iter)->GetCoord() == Vector2(randX, randY))
					{
						f = true;
						break;
					}
					else iter++;
				}

				vector<Building*>::iterator iter2 = GetStructures().begin();
				while (iter2 != GetStructures().end())
				{
					if ((*iter2)->GetCoord() == Vector2(randX, randY))
					{
						f = true;
						break;
					}
					else iter2++;
				}
				//for (int i = 0; i < GetStructuresTiles().size(); i++)
				//{
				//	if (f) break;
				//	if (GetStructuresTiles()[i]->GetCoord() == Vector2(randX, randY))
				//	{
				//		f = true;
				//		break;
				//	}
				//}
				if (!f)
				{
					object::Instantiate(Vector2(randX, randY), LAYER_TYPE::MONSTER, UNITS[/*randAlien[randUnit]*/6]);
				}
			}
		}
	}
	void CombatScene::PlayerTurnBackground()
	{
		if (alienTurnBox->GetApDAp())
			alienTurnBox->SetApDAp(false);

		playerTurnBox->SetState(GameObject::STATE::Visible);
		playerTurnBox->SetApDAp(true);

		for (int i = 0; i < combatBack.size(); i++)
		{
			if (!combatBack[i]->GetSmoothAppear())
				combatBack[i]->SmoothDisappear(true);
		}
		Scene::SetCurTurnEnd(false);
	}
	void CombatScene::AlienTurnBackground()
	{
		if(playerTurnBox->GetApDAp())
			playerTurnBox->SetApDAp(false);

		alienTurnBox->SetState(GameObject::STATE::Visible);
		alienTurnBox->SetApDAp(true);

		for (int i = 0; i < combatBack.size(); i++)
		{
			if (!combatBack[i]->GetSmoothDisappear())
				combatBack[i]->SmoothAppear(true);
		}
		Scene::SetCurTurnEnd(false);
	}
	void CombatScene::PutUnitBeforeCombat()
	{
		for (int y = 1; y < 7; y++)
		{
			for (int x = 1; x < 4; x++)
			{
				SetPosTiles(y, x, TILE_T::MOVE_RANGE, MOVE_TILE_T::square_y);
			}
		}
		bool bConfirm = true;
		for (int i = 0; i < PlayerInfo::mMechs.size(); i++)
		{
			PlayerInfo::mMechs[i]->SetDeploy(true);
			if (!PlayerInfo::mMechs[i]->GetDeployed())
			{
				bConfirm = false;
			}
		}

		if (bConfirm)
		{
			textDeploy->ChangeInner(COMBAT_UI_TEXT_PATH[(UINT)COMBAT_UI_TEXT::DEPLOY_TEXT]);
			btnConfirm->SetState(GameObject::STATE::Visible);
			if (btnConfirm->GetClicked())
			{
				//SetTextTurnNumber(GetTextTurnNumber() + 1);
				Scene::ClearMTiles(TILE_T::GREEN, TILE_HEAD_T::ground);
				bSetPosition = true;
				SetMouseFollower(nullptr);
				for (int i = 0; i < PlayerInfo::mMechs.size(); i++)
				{
					PlayerInfo::mMechs[i]->SetState(GameObject::STATE::Idle);
					PlayerInfo::mMechs[i]->EndDeploy();
					PlayerInfo::mMechs[i]->SetFinalCoord(PlayerInfo::mMechs[i]->GetCoord());
					PlayerInfo::mMechs[i]->SetVisibleHp(true);
					MoveAffectUnit(PlayerInfo::mMechs[i]);
				}
				for (int i = 0; i < GetAliens().size(); i++)
				{
					GetAliens()[i]->SetState(GameObject::STATE::Emerge);
				}
				textDeploy->SetState(GameObject::STATE::Invisible);
				btnConfirm->SetState(GameObject::STATE::Invisible);
				btnConfirm->SetClicked(false);
				return;
			}
		}
		else
		{
			if (nullptr == GetMouseFollower())
			{
				for (int i = 0; i < PlayerInfo::mMechs.size(); i++)
				{
					if (!PlayerInfo::mMechs[i]->GetDeployed())
					{
						mechIdx = i;
						break;
					}
				}
				PlayerInfo::mMechs[mechIdx]->SetState(GameObject::STATE::NoMove);
				ObjectGoFront(PlayerInfo::mMechs[mechIdx], PlayerInfo::mMechs[mechIdx]->GetLayerType());
				SetMouseFollower(PlayerInfo::mMechs[mechIdx]);
			}
		}
		// MouseFollower 범위 벗어나는거 체크
		if (nullptr != GetMouseFollower()
			&& !CheckMouseOutRange())
		{
			// MouseFollower 범위 벗어나면 Cancel로 바꾸기
			GetMouseFollower()->SetCancelDeploy(true);
		}
		for (int y = 0; y < TILE_Y; y++)
		{
			for (int x = 0; x < TILE_X; x++)
			{
				Tile* p = GetPosTiles()[y][x];
				// MOUSE_POS가 있는 타일 찾기.
				if (math::CheckRhombusPos(p->GetPos(), p->GetScale(), MOUSE_POS))
				{
					if (nullptr != GetMouseFollower())
					{

						GetMouseFollower()->SetCoord(GetPosTile(y, x)->GetCoord());
						GetMouseFollower()->SetPos(GetPosTile(y, x)->GetCenterPos());
						//if (GetMouseFollower()->GetMakeDeployAlpha())
						//{
						//	SetAlphaFollower((Mech*)object::Instantiate(GetMouseFollower()->GetFinalCoord()
						//		, LAYER_TYPE::CLONE, GetMouseFollower()->GetUnitName(), GetMouseFollower()));
						//	GetAlphaFollower()->SetState(GameObject::STATE::NoMove);
						//	GetAlphaFollower()->SetDeployConstant(100);
						//	GetAlphaFollower()->SetUnitConstant(100);
						//	GetMouseFollower()->SetMakeDeployAlpha(false);
						//}
					}
					Mech* mech = nullptr;
					for (int i = 0; i < PlayerInfo::mMechs.size(); i++)
					{
						if (p->GetCoord() == PlayerInfo::mMechs[i]->GetCoord()
							&& i != mechIdx)
						{
							mech = PlayerInfo::mMechs[i];
							break;
						}
					}
					if (nullptr != GetMouseFollower()
						&& !((y > 0 && y < 7) && (x > 0 && x < 4)))
					{
						GetMouseFollower()->SetCancelDeploy(true);
					}
					if (nullptr != GetMouseFollower()
						&& mech)
					{
						GetMouseFollower()->SetSwap(true);
						mech->SetSwap(true);
						//if (mech->GetMakeDeployAlpha())
						//{
						//	Mech* mechAlpha = (Mech*)object::Instantiate(mech->GetFinalCoord()
						//		, LAYER_TYPE::CLONE, mech->GetUnitName(), mech);
						//	mechAlpha->SetState(GameObject::STATE::NoMove);
						//	mechAlpha->SetDeployConstant(100);
						//	mechAlpha->SetUnitConstant(100);
						//	mech->SetMakeDeployAlpha(false);
						//}
					}
					if (KEY_UP(KEYCODE_TYPE::LBTN))
					{

						if (nullptr != GetMouseFollower()
							&& GetMouseFollower()->GetCancelDeploy())
							return;

						if (nullptr != GetMouseFollower())
						{
							GetMouseFollower()->SetDeployed(true);

							if (mech) // 교환
							{
								ObjectGoFront(mech, mech->GetLayerType());
								SetMouseFollower(mech);
								//mech->SetDeployed(true);
								mechIdx = (int)mech->GetMIdx();
							}
							else // 배치
							{

								GetMouseFollower()->SetFinalPos(GetMouseFollower()->GetPos());
								GetMouseFollower()->SetFinalCoord(GetMouseFollower()->GetCoord());
								SetMouseFollower(nullptr);
								mechIdx = -1;
							}
						}
						else // 새로 이동
						{
							if (mech)
							{
								ObjectGoFront(mech, mech->GetLayerType());
								SetMouseFollower(mech);
								mechIdx = (int)mech->GetMIdx();
							}
						}
					}
					//bool bExMech = false;
					//Mech* mech = nullptr;
					//for (int i = 0; i < PlayerInfo::mMechs.size(); i++)
					//{
					//	// 타일의 위치에 있는 메크가 MouseFollower가 아니라면.
					//	// 메크를 받아오고
					//	// 교환 bool값 true로
					//	if (nullptr != GetMouseFollower()
					//		&& p->GetCoord() == PlayerInfo::mMechs[i]->GetCoord()
					//		&& i != GetMouseFollower()->GetMIdx())
					//	{
					//		mech = PlayerInfo::mMechs[i];
					//		bExMech = true;
					//		break;
					//	}
					//}
					//// 교환이면 MouseFollower Swap true, 교환 mech Swap true
					//if (nullptr != GetMouseFollower()
					//	&& bExMech)
					//{
					//	GetMouseFollower()->SetSwap(true);
					//	mech->SetSwap(true);
					//	//GetMouseFollower()->SetDeploy(false);
					//	//mech->SetDeploy(false);
					//	//mech->SetPos(GetMouseFollower()->GetPos());
					//	//mech->SetCoord(GetMouseFollower()->GetCoord());
					//}
					////else
					////{
					////	//배치
					////}
					//// 메크가 Deploy인 범위 외에 Cancel값 true
					//if (nullptr != GetMouseFollower()
					//	&& !((y > 0 && y < 7) && (x > 0 && x < 4)))
					//{
					//	GetMouseFollower()->SetCancelDeploy(true);
					//}
					//// MouseFollower 비어있지않고, MouseFollower 첫 배정된 메크가 아니라면
					//// 전체 메크가 Deploy 였던지 확인.
					//// MouseFollower FinalCoord에 알파생성.
					//if(nullptr != GetMouseFollower()
					//	&& GetMouseFollower()->GetMakeDeployAlpha()
					//	&& bConfirm)
					//{
					//	//SetAlphaState(GameObject::STATE::NoMove);
					//	SetAlphaFollower((Mech*)object::Instantiate(PlayerInfo::mMechs[mechIdx]->GetFinalCoord()
					//		, LAYER_TYPE::CLONE, PlayerInfo::mMechs[mechIdx]->GetUnitName(), PlayerInfo::mMechs[mechIdx]));
					//	GetAlphaFollower()->SetState(GameObject::STATE::NoMove);
					//	GetAlphaFollower()->SetDeployConstant(100);
					//	GetAlphaFollower()->SetUnitConstant(100);
					//	GetMouseFollower()->SetMakeDeployAlpha(false);
					//}
					//if (KEY_UP(KEYCODE_TYPE::LBTN))
					//{
					//	// MouseFollower Cancel 상태라면 클릭 return
					//	if (nullptr != GetMouseFollower()
					//		&& GetMouseFollower()->GetCancelDeploy())
					//		return;
					//	// MouseFollower 비어있지 않다면 
					//	// MouseFollower FinalCoord 에 현재 마우스의 위치값을 받아옴
					//	// MouseFollower 의 알파 생성 bool 값 true
					//	if (nullptr != GetMouseFollower())
					//	{
					//		GetMouseFollower()->SetFinalPos(GetMouseFollower()->GetPos());
					//		GetMouseFollower()->SetFinalCoord(GetMouseFollower()->GetCoord());
					//		GetMouseFollower()->SetMakeDeployAlpha(true);
					//	}
					//	// MouseFollower 비어있지 않다면
					//	// MouseFollower Deploy 설정
					//	if (nullptr != GetMouseFollower())
					//	{
					//		GetMouseFollower()->SetDeployed(true);
					//	}
					//	bExMech = false;
					//	for (int i = 0; i < PlayerInfo::mMechs.size(); i++)
					//	{
					//		// MouseFollower가 비어있지 않은 상태
					//		// 타일의 위치에 있는 메크가 MouseFollower가 아니라면.
					//		if (nullptr != GetMouseFollower()
					//			&& p->GetCoord() == PlayerInfo::mMechs[i]->GetCoord()
					//			&& i != GetMouseFollower()->GetMIdx())
					//		{
					//			bExMech = true;
					//			mech = PlayerInfo::mMechs[i];
					//			break;
					//		}
					//	}
					//	if (nullptr == GetMouseFollower() && nullptr != mech)
					//	{
					//		ObjectGoFront(mech, mech->GetLayerType());
					//		SetMouseFollower(mech);
					//	}
					//	// 배치
					//	if (!bExMech)
					//	{
					//		//if (mechIdx + 1 < PlayerInfo::mMechs.size()
					//		//	&& PlayerInfo::mMechs[mechIdx + 1]->GetState() == GameObject::STATE::NoMove)
					//		//{
					//		//	SetMouseFollower(nullptr);
					//		//	return;
					//		//}
					//		if (bConfirm)
					//		{
					//		}
					//		else
					//		{
					//			// 전체 메크중에 Deploy되지 않은 mech의 index받기.
					//			//mechIdx++;
					//			// MouseFollower를 nullptr로 바꿈
					//			SetMouseFollower(nullptr);
					//		}
					//	}
					//	// 교환
					//	else
					//	{
					//		if (bConfirm)
					//		{
					//			ObjectGoFront(mech, mech->GetLayerType());
					//			Vector2 tCoord = GetMouseFollower()->GetCoord();
					//			Vector2 tPos = GetMouseFollower()->GetPos();
					//			GetMouseFollower()->SetCoord(mech->GetCoord());
					//			GetMouseFollower()->SetPos(mech->GetPos());
					//			mech->SetCoord(tCoord);
					//			mech->SetPos(tPos);
					//			
					//			//SetMouseFollower(mech);
					//			//mechIdx = mech->GetMIdx();
					//		}
					//		else
					//		{
					//			ObjectGoFront(mech, mech->GetLayerType());
					//			SetMouseFollower(mech);
					//			mechIdx = mech->GetMIdx();
					//		}
					//	}
						//if (nullptr != GetMouseFollower()
						//	&& GetMouseFollower()->GetFinalPos() != Vector2::One)
						//{
						//	// AlphaBlender.
						//	GetMouseFollower()->SetFinalPos(GetMouseFollower()->GetPos());
						//	SetAlphaFollower((Mech*)object::Instantiate(GetMouseFollower()->GetFinalCoord(), LAYER_TYPE::CLONE, GetMouseFollower()->GetUnitName()));
						//}
					//}
				}
			}
		}
	}
	void CombatScene::SetTextTurnNumber(int _turn)
	{
		if (_turn < (int)COMBAT_UI_TEXT::END)
			textTurnNum->ChangeInner(COMBAT_UI_TEXT_PATH[_turn]);
		iTurn = _turn;
	}
	void CombatScene::AlienIndexReSort()
	{
		vector<Alien*>::iterator iter = GetAliens().begin();
		int idx = 0;
		//while (iter != GetAliens().end())
		//{
		//	(*iter)->SetMIdx(i);
		//	i++;
		//	iter++;
		//}
		for (int i = 0; i < GetAliens().size(); i++)
		{
			GetAliens()[i]->SetMIdx(idx);
			idx++;
		}
		int a = 0;

	}
	void CombatScene::ButtonActivationCondition()
	{
		if (gridPowerBox->GetHover())
		{
			for (int i = 0; i < gridPowers.size(); i++)
			{
				wstring gridImageStr = L"";
				if (i <= PlayerInfo::gridPower - 1) gridImageStr = L"..\\Resources\\texture\\ui\\combat\\grid_power_on_hover.bmp";
				if (i > PlayerInfo::gridPower - 1) gridImageStr = L"..\\Resources\\texture\\ui\\combat\\grid_power_off_hover.bmp";
				gridPowers[i]->ChangeInner(gridImageStr);
				gridPowers[i]->SetState(GameObject::STATE::Visible);
			}
			gridPowerBox->ChangeInner(L"..\\Resources\\texture\\ui\\combat\\grid_def_box_on.bmp");
		}
		else
		{

			for (int i = 0; i < gridPowers.size(); i++)
			{
				wstring gridImageStr = L"";
				if (i < PlayerInfo::gridPower - 1) gridImageStr = L"..\\Resources\\texture\\ui\\combat\\grid_power_on.bmp";
				if (i == PlayerInfo::gridPower - 1) gridImageStr = L"..\\Resources\\texture\\ui\\combat\\grid_power_on_front.bmp";
				if (i > PlayerInfo::gridPower - 1) gridImageStr = L"..\\Resources\\texture\\ui\\combat\\grid_power_off.bmp";
				gridPowers[i]->ChangeInner(gridImageStr);
				gridPowers[i]->SetState(GameObject::STATE::Visible);
			}
			gridPowerBox->ChangeInner(L"..\\Resources\\texture\\ui\\combat\\grid_def_box_off.bmp");
		}

		if (btnInitTurn->GetClicked())
		{
			Scene::ResetTurn();
			btnInitTurn->SetAlpha(true);
			btnInitTurn->UseInnerAlpha(true);
			btnInitTurn->SetInnerConstant(100);
			btnInitTurn->SetConstant(100);
			btnInitTurn->SetClicked(false);
		}
		if (btnUndoMove->GetClicked())
		{
			Scene::UndoMove();
			btnUndoMove->SetClicked(false);
		}
		if (GetMoveSave().size() == 0)
		{
			btnUndoMove->SetAlpha(true);
			btnUndoMove->UseInnerAlpha(true);
			btnUndoMove->SetInnerConstant(100);
			btnUndoMove->SetConstant(100);
		}
		else
		{
			btnUndoMove->UseInnerAlpha(false);
			btnUndoMove->SetAlpha(false);
		}
		//btnTurnEnd->SetState(GameObject::STATE::Visible);
		//btnUndoMove->SetState(GameObject::STATE::Visible);
		//btnInitTurn->SetState(GameObject::STATE::Visible);
	}
	void CombatScene::Update()
	{
		Scene::Update();
		if (!endGame)
		{
			if (!bSetPosition)
			{
				PutUnitBeforeCombat();
			}
			else
			{
				gridPowerBox->SetState(GameObject::STATE::Visible);
				btnTurnEnd->SetState(GameObject::STATE::Visible);
				btnUndoMove->SetState(GameObject::STATE::Visible);
				btnInitTurn->SetState(GameObject::STATE::Visible);
				playerUnitInfo->SetState(GameObject::STATE::Visible);
				for (int i = 0; i < infoUnits.size(); i++)
				{
					infoUnits[i]->SetState(GameObject::STATE::NoMove);
				}
				if (Scene::GetCurTurnEnd())
				{
					if (Scene::GetPlayerTurn())
						PlayerTurnBackground();
					if (!Scene::GetPlayerTurn())
						AlienTurnBackground();
				}
				else
				{
					if (Scene::GetPlayerTurn() && !playerTurnBox->GetApDAp()
						|| !Scene::GetPlayerTurn() && !alienTurnBox->GetApDAp())
					{
						alienTurnBox->ChangeInner(L"..\\Resources\\texture\\ui\\combat\\ey_turn_noti.bmp");
						alienTurnBox->SetInnerPos(Vector2(alienTurnBox->GetSize().x / 2 - 62 / 2, alienTurnBox->GetSize().y / 2 - 29 / 2));
						Scene::MoveMech();
						Scene::MoveSkill();
						Scene::AlienAlgorithm();
					}
				}
				for (int i = 0; i < infoUnits.size(); i++)
				{
					if (nullptr == GetMouseFollower())selectUnitBox->SetState(GameObject::STATE::Invisible);
					if (PlayerInfo::mMechs[i]->GetSelected())
					{
						selectUnitBox->SetPos(Vector2(10.f, btnTurnEnd->GetPos().y + btnTurnEnd->GetSize().y + 5
							+ ((selectUnitBox->GetInnerImage()->GetHeight() + 3) * i)));
						selectUnitBox->SetState(GameObject::STATE::Visible);
					}
					infoUnits[i]->SetCurHp(PlayerInfo::mMechs[i]->GetCurHp());
				}
				AlienIndexReSort();
				ButtonActivationCondition();
			}
			if (iTurn == (int)COMBAT_UI_TEXT::TURN_NUM_1 + 1)
			{
				showEnd = true;
			}
		}
		if (showEnd)
		{
			for (int i = 0; i < combatBack.size(); i++)
			{
				if (!combatBack[i]->GetSmoothAppear())
					combatBack[i]->SmoothDisappear(true);
			}

			gridPowerBox->SetState(GameObject::STATE::Invisible);
			btnTurnEnd->SetState(GameObject::STATE::Invisible);
			btnUndoMove->SetState(GameObject::STATE::Invisible);
			btnInitTurn->SetState(GameObject::STATE::Invisible);
			playerUnitInfo->SetState(GameObject::STATE::Invisible);
			for (int i = 0; i < infoUnits.size(); i++)
				infoUnits[i]->SetState(GameObject::STATE::Death);
			for (int i = 0; i < gridPowers.size(); i++)
				gridPowers[i]->SetState(GameObject::STATE::Invisible);
			for (int i = 0; i < GetAliens().size(); i++)
				GetAliens()[i]->SetState(GameObject::STATE::Retreat);

			textTurnNum->SetState(GameObject::STATE::Invisible);
			textTurn->SetState(GameObject::STATE::Invisible);

			endMissionBox->SetState(GameObject::STATE::Visible);
			endMissionBox->SetApDAp(true);
			
			endGame = true;
			showEnd = false;
		}
		if (!endMissionBox->GetApDAp() && endGame && !showEnd)
		{
			Camera::PushEffect(CAMERA_EFFECT_TYPE::Fade_Out, 1.f);
			SceneManager::LoadScene(SceneManager::GetSelectLand());
		}
	}
	void CombatScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void CombatScene::Release()
	{
		Scene::Release();
	}
	void CombatScene::OnEnter()
	{}
	void CombatScene::OnExit()
	{}

}