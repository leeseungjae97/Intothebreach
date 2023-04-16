#include "mCombatScene.h"
#include "Mech.h"
#include "mSceneManager.h"
#include "mInput.h"
#include "mTransform.h"
#include "mBackground.h"
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
extern m::Application application;
namespace m {
	CombatScene::CombatScene() {
	}
	CombatScene::~CombatScene() {
	}
	void CombatScene::Initialize() {
		Scene::Initialize();
		Scene::MakeTile(TILE_X, TILE_Y, TILE_T::GREEN, TILE_HEAD_T::ground);
		mechIdx = 0;
		Background* b0 = new Background(L"combatBackground1"
			, L"..\\Resources\\texture\\ui\\combat\\bg.bmp", 0, false, DEFAULT);

		UINT _x = (UINT)(application.GetResolutionWidth() / b0->GetWidth());
		UINT _y = (UINT)(application.GetResolutionHeight() / b0->GetHeight());

		delete b0;

		

		for (UINT y = 0; y <= _y; y++) {
			for (UINT x = 0; x <= _x; x++) {
				Background* b_ = new Background(L"combatBackground1"
					, L"..\\Resources\\texture\\ui\\combat\\bg.bmp", 0, false, DEFAULT);
				b_->SetPos(Vector2(b_->GetWidth() * x, b_->GetHeight() * y));
				mBacks.push_back(b_);
				AddGameObject(b_, LAYER_TYPE::BACKGROUND);
			}
		}
		// �ӽ÷� ��ī��ġ ����
		// ���콺�� Ŭ���� ���� ��ī�� �������� �����ؾߵ�
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

		object::Instantiate(Vector2(5, 5), LAYER_TYPE::MONSTER, UNITS[(UINT)ALIENS::Hornet]);
		object::Instantiate(Vector2(5, 4), LAYER_TYPE::MONSTER, UNITS[(UINT)ALIENS::Leaper]);
		object::Instantiate(Vector2(5, 3), LAYER_TYPE::MONSTER, UNITS[(UINT)ALIENS::Firefly]);

		object::Instantiate(Vector2(3, 1), LAYER_TYPE::STRUCT, STRUCTURES::tower);
	}
	void CombatScene::RandSpawnAlien()
	{
		for (int y = 1; y < TILE_Y - 1; y++)
		{
			for (int x = 5; x < TILE_X; x++)
			{

			}
		}
	}
	void CombatScene::PutUnitBeforeCombat()
	{
		bool bConfirm = true;
		for (int i = 0; i < GetMechs().size(); i++)
		{
			GetMechs()[i]->SetDeploy(true);
			if (!GetMechs()[i]->GetDeployed())
			{
				bConfirm = false;
			}
		}

		if (bConfirm)
		{
			if (KEY_UP(KEYCODE_TYPE::SPACE))
			{
				bSetPosition = true;
				SetMouseFollower(nullptr);
				return;
			}
		}
		else
		{
			if (nullptr == GetMouseFollower() 
				&& GetMechs()[mechIdx]->GetState() != GameObject::STATE::NoMove)
			{
				for (int i = 0; i < GetMechs().size(); i++)
				{
					if (!GetMechs()[i]->GetDeployed())
					{
						mechIdx = i;
						break;
					}
				}
				GetMechs()[mechIdx]->SetState(GameObject::STATE::NoMove);
				SetMouseFollower(GetMechs()[mechIdx]);
			}
		}

		// MouseFollower ���� ����°� üũ
		if (nullptr != GetMouseFollower()
			&& !CheckMouseOutRange())
		{	
			// MouseFollower ���� ����� Cancel�� �ٲٱ�
			GetMouseFollower()->SetCancelDeploy(true);
		}
		for (int y = 0; y < TILE_Y; y++)
		{
			for (int x = 0; x < TILE_X; x++)
			{
				Tile* p = GetPosTiles()[y][x];
				// MOUSE_POS�� �ִ� Ÿ�� ã��.
				if (math::CheckRhombusPos(p->GetPos(), p->GetScale(), MOUSE_POS))
				{
					if (nullptr != GetMouseFollower())
					{
						GetMouseFollower()->SetCoord(GetPosTile(y, x)->GetCoord());
						GetMouseFollower()->SetPos(GetPosTile(y, x)->GetCenterPos());
					}
					if (KEY_UP(KEYCODE_TYPE::LBTN))
					{
						SetMouseFollower(nullptr);
					}


					//bool bExMech = false;
					//Mech* mech = nullptr;
					//for (int i = 0; i < GetMechs().size(); i++)
					//{
					//	// Ÿ���� ��ġ�� �ִ� ��ũ�� MouseFollower�� �ƴ϶��.
					//	// ��ũ�� �޾ƿ���
					//	// ��ȯ bool�� true��
					//	if (nullptr != GetMouseFollower()
					//		&& p->GetCoord() == GetMechs()[i]->GetCoord()
					//		&& i != GetMouseFollower()->GetMIdx())
					//	{
					//		mech = GetMechs()[i];
					//		bExMech = true;
					//		break;
					//	}
					//}
					//// ��ȯ�̸� MouseFollower Swap true, ��ȯ mech Swap true
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
					////	//��ġ
					////}
					//// ��ũ�� Deploy�� ���� �ܿ� Cancel�� true
					//if (nullptr != GetMouseFollower()
					//	&& !((y > 0 && y < 7) && (x > 0 && x < 4)))
					//{
					//	GetMouseFollower()->SetCancelDeploy(true);
					//}

					//// MouseFollower ��������ʰ�, MouseFollower ù ������ ��ũ�� �ƴ϶��
					//// ��ü ��ũ�� Deploy ������ Ȯ��.
					//// MouseFollower FinalCoord�� ���Ļ���.
					//if(nullptr != GetMouseFollower()
					//	&& GetMouseFollower()->GetMakeDeployAlpha()
					//	&& bConfirm)
					//{
					//	//SetAlphaState(GameObject::STATE::NoMove);
					//	SetAlphaFollower((Mech*)object::Instantiate(GetMechs()[mechIdx]->GetFinalCoord()
					//		, LAYER_TYPE::CLONE, GetMechs()[mechIdx]->GetUnitName(), GetMechs()[mechIdx]));
					//	GetAlphaFollower()->SetState(GameObject::STATE::NoMove);
					//	GetAlphaFollower()->SetDeployConstant(100);
					//	GetAlphaFollower()->SetUnitConstant(100);
					//	GetMouseFollower()->SetMakeDeployAlpha(false);
					//}

					//if (KEY_UP(KEYCODE_TYPE::LBTN))
					//{
					//	// MouseFollower Cancel ���¶�� Ŭ�� return
					//	if (nullptr != GetMouseFollower()
					//		&& GetMouseFollower()->GetCancelDeploy())
					//		return;
					//	// MouseFollower ������� �ʴٸ� 
					//	// MouseFollower FinalCoord �� ���� ���콺�� ��ġ���� �޾ƿ�
					//	// MouseFollower �� ���� ���� bool �� true
					//	if (nullptr != GetMouseFollower())
					//	{
					//		GetMouseFollower()->SetFinalPos(GetMouseFollower()->GetPos());
					//		GetMouseFollower()->SetFinalCoord(GetMouseFollower()->GetCoord());
					//		GetMouseFollower()->SetMakeDeployAlpha(true);
					//	}
					//	// MouseFollower ������� �ʴٸ�
					//	// MouseFollower Deploy ����
					//	if (nullptr != GetMouseFollower())
					//	{
					//		GetMouseFollower()->SetDeployed(true);
					//	}

					//	bExMech = false;
					//	for (int i = 0; i < GetMechs().size(); i++)
					//	{
					//		// MouseFollower�� ������� ���� ����
					//		// Ÿ���� ��ġ�� �ִ� ��ũ�� MouseFollower�� �ƴ϶��.
					//		if (nullptr != GetMouseFollower()
					//			&& p->GetCoord() == GetMechs()[i]->GetCoord()
					//			&& i != GetMouseFollower()->GetMIdx())
					//		{
					//			bExMech = true;
					//			mech = GetMechs()[i];
					//			break;
					//		}
					//	}
					//	if (nullptr == GetMouseFollower() && nullptr != mech)
					//	{
					//		ObjectGoFront(mech, mech->GetLayerType());
					//		SetMouseFollower(mech);
					//	}

					//	// ��ġ
					//	if (!bExMech)
					//	{
					//		//if (mechIdx + 1 < GetMechs().size()
					//		//	&& GetMechs()[mechIdx + 1]->GetState() == GameObject::STATE::NoMove)
					//		//{
					//		//	SetMouseFollower(nullptr);
					//		//	return;
					//		//}
					//		if (bConfirm)
					//		{

					//		}
					//		else
					//		{
					//			// ��ü ��ũ�߿� Deploy���� ���� mech�� index�ޱ�.
					//			//mechIdx++;
					//			// MouseFollower�� nullptr�� �ٲ�
					//			SetMouseFollower(nullptr);
					//		}
					//	}
					//	// ��ȯ
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
	void CombatScene::Update() {
		Scene::Update();

		if (!bSetPosition)
		{
			RandSpawnAlien();
			PutUnitBeforeCombat();
		}
		else
		{
			Scene::MoveMech();
			Scene::MoveSkill();
			Scene::AlienAlgorithm();
		}
		if (KEY_DOWN(KEYCODE_TYPE::N)) {
			SceneManager::LoadScene(SCENE_TYPE::TITLE);
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