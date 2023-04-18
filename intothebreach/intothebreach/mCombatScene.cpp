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
extern m::Application application;
namespace m
{
	CombatScene::CombatScene()
	{}
	CombatScene::~CombatScene()
	{}
	void CombatScene::Initialize()
	{
		Scene::Initialize();
		Scene::MakeTile(TILE_X, TILE_Y, TILE_T::GREEN, TILE_HEAD_T::ground);
		mechIdx = 0;
		iTurn = 4;
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
		textDeploy->SetText(true);
		textDeploy->SetAlpha(true);
		textDeploy->UseTextAlpha(false);
		textDeploy->SetTextPos(Vector2(10.f, 10.f));
		textDeploy->SetPos(Vector2(10.f, 10.f));
		textDeploy->SetSize(Vector2(300.f, 80.f));

		btnConfirm = new Button(COMBAT_UI_TEXT_PATH[(UINT)COMBAT_UI_TEXT::CON_TEXT], A_BTN_BACK);
		btnConfirm->SetText(true);
		btnConfirm->SetAlpha(true);
		btnConfirm->UseTextAlpha(false);
		btnConfirm->SetPos(Vector2(textDeploy->GetPos().x, textDeploy->GetPos().y + textDeploy->GetSize().y + 10.f));
		btnConfirm->SetTextPos(Vector2(btnConfirm->GetPos().x + 10.f, 10.f));
		btnConfirm->SetSize(Vector2(100.f, 50.f));
		btnConfirm->SetState(GameObject::STATE::Invisible);

		textTurn = new Button(COMBAT_UI_TEXT_PATH[(UINT)COMBAT_UI_TEXT::TURN_TEXT], A_BTN_BACK);
		textTurn->SetText(true);
		textTurn->SetAlpha(true);
		textTurn->UseTextAlpha(false);
		textTurn->SetSize(Vector2(300.f, 50.f));
		textTurn->SetPos(Vector2(application.GetResolutionWidth() - textTurn->GetSize().x, 10.f));
		textTurn->SetTextPos(Vector2(textTurn->GetSize().x / 2 - 105.f / 2
			, textTurn->GetSize().y / 2 - 14.f / 2));

		textTurnNum = new Button(COMBAT_UI_TEXT_PATH[iTurn], NO_BACK);
		textTurnNum->SetText(true);
		textTurnNum->UseTextAlpha(false);
		textTurnNum->SetPos(Vector2(textTurn->GetPos()));
		textTurnNum->SetTextMag(2);
		textTurnNum->SetTextPos(Vector2(textTurn->GetTextPos().x + 60.f, 0.f));

		gridPowerBox = new Button(L"..\\Resources\\texture\\ui\\combat\\grid_def_box.bmp", A_BTN_BACK);
		gridPowerBox->SetText(true);
		gridPowerBox->UseTextAlpha(false);
		gridPowerBox->SetSize(Vector2(380.f, 38.f));
		gridPowerBox->SetPos(Vector2(10.f, 10.f));
		gridPowerBox->SetTextPos(Vector2(gridPowerBox->GetSize().x / 2 - 291 / 2, gridPowerBox->GetSize().y / 2 - 33 / 2));

		btnTurnEnd = new Button(L"..\\Resources\\texture\\ui\\combat\\turn_end_text.bmp", A_BTN_BACK);
		btnTurnEnd->SetText(true);
		btnTurnEnd->UseTextAlpha(false);
		btnTurnEnd->SetSize(Vector2(210, 65));
		btnTurnEnd->SetPos(Vector2(gridPowerBox->GetPos().x, gridPowerBox->GetPos().y + gridPowerBox->GetSize().y + 5));
		btnTurnEnd->SetTextPos(Vector2(btnTurnEnd->GetSize().x / 2 - 90 / 2, btnTurnEnd->GetSize().y / 2 - 28 / 2));

		btnUndoMove = new Button(L"..\\Resources\\texture\\ui\\combat\\cancel_move_text.bmp", A_BTN_BACK);
		btnUndoMove->SetText(true);
		btnUndoMove->UseTextAlpha(false);
		btnUndoMove->SetSize(Vector2(90, 65));
		btnUndoMove->SetPos(Vector2(btnTurnEnd->GetPos().x + btnTurnEnd->GetSize().x + 5, btnTurnEnd->GetPos().y));
		btnUndoMove->SetTextPos(Vector2(btnUndoMove->GetSize().x / 2 - 27 / 2, btnUndoMove->GetSize().y / 2 - 33 / 2));

		btnInitTurn = new Button(L"..\\Resources\\texture\\ui\\combat\\turn_init_text.bmp", A_BTN_BACK);
		btnInitTurn->SetText(true);
		btnInitTurn->UseTextAlpha(false);
		btnInitTurn->SetSize(Vector2(90, 38));
		btnInitTurn->SetPos(Vector2(15 + gridPowerBox->GetSize().x, 10));
		btnInitTurn->SetTextPos(Vector2(btnInitTurn->GetSize().x /2 - 63/ 2 , btnInitTurn->GetSize().y / 2 - 13/2));

		textBattleEnd = new Button(L"..\\Resources\\texture\\ui\\combat\\turn_init_text.bmp", A_BTN_BACK);
		textBattleEnd->SetText(true);
		textBattleEnd->UseTextAlpha(false);
		textBattleEnd->SetSize(Vector2(90, 38));
		textBattleEnd->SetPos(Vector2(15 + gridPowerBox->GetSize().x, 10));
		textBattleEnd->SetTextPos(Vector2(textBattleEnd->GetSize().x / 2 - 63 / 2, textBattleEnd->GetSize().y / 2 - 13 / 2));

		gridPowerBox->SetState(GameObject::STATE::Invisible);
		btnTurnEnd->SetState(GameObject::STATE::Invisible);
		btnUndoMove->SetState(GameObject::STATE::Invisible);
		btnInitTurn->SetState(GameObject::STATE::Invisible);
		textBattleEnd->SetState(GameObject::STATE::Invisible);

		showPlayerInfo;
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
		AddGameObject(gridPowerBox, LAYER_TYPE::UI);
		AddGameObject(btnTurnEnd, LAYER_TYPE::UI);
		AddGameObject(btnUndoMove, LAYER_TYPE::UI);
		AddGameObject(btnInitTurn, LAYER_TYPE::UI);
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
		object::Instantiate(Vector2::Minus, LAYER_TYPE::PLAYER, UNITS[(UINT)MECHS::artillery]);
		object::Instantiate(Vector2::Minus, LAYER_TYPE::PLAYER, UNITS[(UINT)MECHS::tank]);
		object::Instantiate(Vector2::Minus, LAYER_TYPE::PLAYER, UNITS[(UINT)MECHS::punch]);

		RandSpawnAlien();

		object::Instantiate(Vector2(0, 2), LAYER_TYPE::STRUCT, STRUCTURES::mountain);
		object::Instantiate(Vector2(0, 1), LAYER_TYPE::STRUCT, STRUCTURES::mountain);

		object::Instantiate(Vector2(0, 0), LAYER_TYPE::STRUCT, STRUCTURES::mountain);
		object::Instantiate(Vector2(1, 0), LAYER_TYPE::STRUCT, STRUCTURES::mountain);
		object::Instantiate(Vector2(2, 0), LAYER_TYPE::STRUCT, STRUCTURES::mountain);
		object::Instantiate(Vector2(3, 0), LAYER_TYPE::STRUCT, STRUCTURES::mountain);
		object::Instantiate(Vector2(4, 0), LAYER_TYPE::STRUCT, STRUCTURES::mountain);
		object::Instantiate(Vector2(5, 0), LAYER_TYPE::STRUCT, STRUCTURES::mountain);

	

		object::Instantiate(Vector2(7, 7), LAYER_TYPE::STRUCT, STRUCTURES::mountain);

		object::Instantiate(Vector2(5, 3), LAYER_TYPE::STRUCT, STRUCTURES::mountain);
		object::Instantiate(Vector2(5, 4), LAYER_TYPE::STRUCT, STRUCTURES::mountain);
		object::Instantiate(Vector2(5, 5), LAYER_TYPE::STRUCT, STRUCTURES::mountain);

		object::Instantiate(Vector2(0, 7), LAYER_TYPE::STRUCT, STRUCTURES::tower);
		object::Instantiate(Vector2(5, 1), LAYER_TYPE::STRUCT, STRUCTURES::airfield);
	}
	void CombatScene::RandSpawnAlien()
	{
		while (GetAliens().size() != 2)
		{
			srand((unsigned int)time(NULL));
			//int randNum = rand();
			float randY = (float)(rand() % 7);
			float randX = (float)(rand() % 3);
			//int randNum2 = rand();

			randY += 1.f;
			randX += 5.f;
			int randAlien[3] = { 6,7,9 };
			int randUnit = rand() % 3;
			if (GetAliens().size() == 0)
				object::Instantiate(Vector2(randX, randY), LAYER_TYPE::MONSTER, UNITS[7]);
			else
			{
				bool f = false;
				vector<Alien*>::iterator iter = GetAliens().begin();
				while (iter != GetAliens().end())
				{
					if ((*iter)->GetCoord() == Vector2(randX, randY))
					{
						for (int i = 0; i < GetStructuresTiles().size(); i++)
						{
							if (GetStructuresTiles()[i]->GetCoord() == Vector2(randX, randY))
							{
								f = true;
								break;
							}
						}
						f = true;
						break;
					}else iter++;
				}
				if (!f)
					object::Instantiate(Vector2(randX, randY), LAYER_TYPE::MONSTER, UNITS[7]);
			}
		}
		
		//for (int i = 0; i < 3; i++)
		//{
		//	
		//}
	}
	void CombatScene::PlayerTurnBackground()
	{
		for (int i = 0; i < combatBack.size(); i++)
		{
			if(!combatBack[i]->GetSmoothAppear())
				combatBack[i]->SmoothDisappear(true);
		}
	}
	void CombatScene::AlienTurnBackground()
	{
		for (int i = 0; i < combatBack.size(); i++)
		{
			if (!combatBack[i]->GetSmoothDisappear())
				combatBack[i]->SmoothAppear(true);
		}
	}
	void CombatScene::PutUnitBeforeCombat()
	{
		//((y > 0 && y < 7) && (x > 0 && x < 4))
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
			textDeploy->ChangeText(COMBAT_UI_TEXT_PATH[(UINT)COMBAT_UI_TEXT::DEPLOY_TEXT]);
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
					PlayerInfo::mMechs[i]->SetVisibleHp(true);
					MoveEffectUnit(PlayerInfo::mMechs[i]);
				}
				for (int i = 0; i < GetAliens().size(); i++)
				{
					GetAliens()[i]->SetState(GameObject::STATE::Emerge);
				}
				textDeploy->SetState(GameObject::STATE::Invisible);
				btnConfirm->SetState(GameObject::STATE::Invisible);

				return;
			}
			//if (KEY_UP(KEYCODE_TYPE::SPACE))
			//{
			//	
			//}
		}
		else
		{
			//if (nullptr == GetMouseFollower() 
			//	&& PlayerInfo::mMechs[mechIdx]->GetState() != GameObject::STATE::NoMove)
			if (nullptr == GetMouseFollower())
			{
				for (int i = 0; i < PlayerInfo::mMechs.size(); i++)
				{
					if (!PlayerInfo::mMechs[i]->GetDeployed())
					{
						mechIdx = i;
						break;
					}
					//if (bConfirm)
					//	PlayerInfo::mMechs[i]->SetMakeDeployAlpha(true);
				}
				PlayerInfo::mMechs[mechIdx]->SetState(GameObject::STATE::NoMove);
				ObjectGoFront(PlayerInfo::mMechs[mechIdx], PlayerInfo::mMechs[mechIdx]->GetLayerType());
				SetMouseFollower(PlayerInfo::mMechs[mechIdx]);
			}
		}
		//if (nullptr != GetMouseFollower()
		//	&& bConfirm)
		//	GetMouseFollower()->SetMakeDeployAlpha(true);

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
		textTurnNum->ChangeText(COMBAT_UI_TEXT_PATH[_turn]);
		iTurn = _turn;
	}
	void CombatScene::Update()
	{
		Scene::Update();

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
			Scene::MoveMech();
			Scene::MoveSkill();
			Scene::AlienAlgorithm();
		}
		if (iTurn == (int)COMBAT_UI_TEXT::TURN_NUM_1 + 1)
		{
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