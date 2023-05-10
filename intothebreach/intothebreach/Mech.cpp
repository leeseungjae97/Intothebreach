#include "Mech.h"
#include "mTime.h"
#include "func.h"
#include "mSceneManager.h"
#include "mCombatScene.h"
#include "mResources.h"
#include "mAnimator.h"
#include "mBackground.h"
#include "mTransform.h"
#include "mImage.h"
#include "mInput.h"
#include "mCamera.h"
#include "mCollider.h"
#include "mSkill.h"
#include "mSound.h"
namespace m
{
	Mech::Mech(int unitName, Vector2 _coord, int _range, int _hp, size_t idx)
		: Unit(_coord, _range, _hp, BASIC_WEAPON_TYPE[(UINT)unitName], idx, unitName)
		, moveCnt(GetMoveRange())
		, fDeployConstant(255)
		, bMakeDeployAlpha(false)
		, bDeploy(false)
		, bSwap(false)
		, bCancelDeploy(false)
		, bDeployed(false)

	{
		int a = unitName;
		WEAPON_T bt = BASIC_WEAPON_TYPE[(UINT)unitName];
		int b = GetUnitName();
		int c = GET_UNIT_NUM(unitName);

		GetMImages().resize((UINT)COMBAT_CONDITION_T::END);

		for (UINT i = 0; i < (UINT)COMBAT_CONDITION_T::END; i++)
		{
			GetMImages()[i] = Resources::Load<Image>(
				MAKE_UNIT_KEY((MECHS)unitName, (COMBAT_CONDITION_T)i)
				, MAKE_UNIT_PATH((MECHS)unitName, (COMBAT_CONDITION_T)i));
			if (nullptr == GetMImages()[i]) continue;
			GetMImages()[i]->SetOffset(MECHS_OFFSET[(UINT)unitName][i]);
		}

		UINT len = UINT(GetMImages()[(UINT)COMBAT_CONDITION_T::IDLE]->GetWidth() / (GetMImages()[(UINT)COMBAT_CONDITION_T::S_SIZE]->GetWidth() + MECHS_IMAGE_SIZE[(UINT)unitName].x));
		float fHei = GetMImages()[(UINT)COMBAT_CONDITION_T::S_SIZE]->GetHeight() + MECHS_IMAGE_SIZE[(UINT)unitName].y;
		float fWid = (float)(GetMImages()[(UINT)COMBAT_CONDITION_T::IDLE]->GetWidth() / len);

		GetAnimator()->CreateAnimation(
			MAKE_UNIT_KEY((MECHS)unitName, COMBAT_CONDITION_T::IDLE)
			, GetMImages()[(UINT)COMBAT_CONDITION_T::IDLE]
			, Vector2(Vector2::Zero)
			, Vector2(fWid, fHei)
			, GetMImages()[(UINT)COMBAT_CONDITION_T::IDLE]->GetOffset()
			, len
			, 0.2f
			, (UINT)AC_SRC_ALPHA
		);

		GetAnimator()->SetConstant(255);
		GetAnimator()->Play(MAKE_UNIT_KEY((MECHS)unitName, COMBAT_CONDITION_T::IDLE), true);

		SetState(STATE::Idle);
	}
	Mech::Mech(Mech& _origin)
	{
	}
	Mech::~Mech()
	{
	}
	void Mech::Initialize()
	{}
	void Mech::Update()
	{
		Unit::Update();
		CheckInput();

		if (GetEndMove())
		{
			SceneManager::GetActiveScene()->SetMouseFollower(nullptr);
			MechMove();
		}
		//else object::DestoryUnitVector<Background*>(GetMoveDusts());
		//if (KEY_PRESSED(KEYCODE_TYPE::Q))
		//{
		//	SetState(STATE::Broken);
		//}
		//if (KEY_PRESSED(KEYCODE_TYPE::E))
		//{
		//	SetState(STATE::Idle);
		//}
		if (Unit::GetCurHp() == 0 && GetButtonType() == LAYER_TYPE::PLAYER)
		{
			SetState(STATE::Broken);
		}
		//else
		//{
		//	SetState(STATE::Idle);
		//}
		switch (GetState())
		{
		case STATE::Idle:
			idle();
			break;
		case STATE::Broken:
			broken();
			break;
		case STATE::Water:
			water();
			break;
		case STATE::NoMove:
			noMove();
			break;
		default:
			break;
		}
	}
	void Mech::Render(HDC hdc)
	{
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = (BYTE)fDeployConstant;
		if (bCancelDeploy && nullptr != GetCurImage())
		{
			deployArrow = Resources::Load<Image>(L"deploy_x", L"..\\Resources\\texture\\combat\\deployment_x.bmp");
			Vector2 mPos = GetPos();
			mPos.y -= deployArrow->GetHeight();
			AlphaBlend(hdc
				, (int)(mPos.x)
				, (int)(mPos.y)
				, (int)(deployArrow->GetWidth() * 2)
				, (int)(deployArrow->GetHeight() * 2)
				, deployArrow->GetHdc()
				, 0
				, 0
				, (int)(deployArrow->GetWidth())
				, (int)(deployArrow->GetHeight())
				, func);
		}
		if (bSwap && nullptr != GetCurImage())
		{
			deployArrow = Resources::Load<Image>(L"deploy_swap", L"..\\Resources\\texture\\combat\\deployment_swap.bmp");
			Vector2 mPos = GetPos();
			mPos.y -= deployArrow->GetHeight();
			AlphaBlend(hdc
				, (int)(mPos.x)
				, (int)(mPos.y)
				, (int)(deployArrow->GetWidth() * 2)
				, (int)(deployArrow->GetHeight() * 2)
				, deployArrow->GetHdc()
				, 0
				, 0
				, (int)(deployArrow->GetWidth())
				, (int)(deployArrow->GetHeight())
				, func);
		}
		if (bDeploy && nullptr != GetCurImage())
		{
			deployArrow = Resources::Load<Image>(L"deploy_arrow", L"..\\Resources\\texture\\combat\\deployment_arrow.bmp");
			Vector2 mPos = GetPos();
			mPos.y -= deployArrow->GetHeight();
			AlphaBlend(hdc
				, (int)(mPos.x)
				, (int)(mPos.y)
				, (int)(deployArrow->GetWidth() * 2)
				, (int)(deployArrow->GetHeight() * 2)
				, deployArrow->GetHdc()
				, 0
				, 0
				, (int)(deployArrow->GetWidth())
				, (int)(deployArrow->GetHeight())
				, func);
			//TransparentBlt(hdc
			//	, (int)(mPos.x)
			//	, (int)(mPos.y)
			//	, (int)(deployArrow->GetWidth() * 2)
			//	, (int)(deployArrow->GetHeight() * 2)
			//	, deployArrow->GetHdc()
			//	, 0
			//	, 0
			//	, (int)(deployArrow->GetWidth())
			//	, (int)(deployArrow->GetHeight())
			//	, RGB(255, 0, 255));
		}
		Unit::Render(hdc);

		if (bOverlayRepair)
		{
			repairImage = Resources::Load<Image>(L"repairImage"
				, L"..\\Resources\\texture\\combat\\overlay\\icon_heal_glow.bmp");
			Vector2 mPos = GetPos();
			TransparentBlt(hdc
				, (int)(mPos.x) + 10
				, (int)(mPos.y)
				, (int)(repairImage->GetWidth() * 2)
				, (int)(repairImage->GetHeight() * 2)
				, repairImage->GetHdc()
				, 0
				, 0
				, (int)(repairImage->GetWidth())
				, (int)(repairImage->GetHeight())
				, RGB(255, 0, 255)
			);
		}
		else
		{
			repairImage = nullptr;
		}
	}
	void Mech::Release()
	{
		Unit::Release();
	}
	void Mech::CheckInput()
	{
		Scene* scene = SceneManager::GetActiveScene();
		if (nullptr == scene->GetMouseFollower()) return;
		if (scene->GetMouseFollower()->GetMIdx() != GetMIdx()) return;
		
		if (bOverlayRepair)
		{
			bOverlayRepair = false;
			Repair(1);
		}

		if (KEY_UP(KEYCODE_TYPE::R))
		{
			if (bOverlayRepair)
			{
				bOverlayRepair = false;
				((CombatScene*)SceneManager::GetActiveScene())->SetWPBow(2);
			}
			else
			{
				bOverlayRepair = true;
				((CombatScene*)SceneManager::GetActiveScene())->SetWPBow(0);
			}
			
		}
		if (KEY_DOWN(KEYCODE_TYPE::NUM_1)) { SetSkillIdx(0); }
		if (KEY_DOWN(KEYCODE_TYPE::NUM_2)) { SetSkillIdx(1); }
		if (KEY_DOWN(KEYCODE_TYPE::NUM_3)) { SetSkillIdx(2); }
		if (KEY_DOWN(KEYCODE_TYPE::NUM_1)
			|| KEY_DOWN(KEYCODE_TYPE::NUM_2)
			|| KEY_DOWN(KEYCODE_TYPE::NUM_3))
		{
			SetPos(GetFinalPos());
			SetCoord(GetFinalCoord());

			if (!GetMove()) // ������ ��ҵǰ� �̵����ɻ��·�
			{
				((CombatScene*)SceneManager::GetActiveScene())->SetWPBow(2);
				SetMove(true);
				if(GetCurAttackSkill())
					GetCurAttackSkill()->SetStartRender(false);

				SetSkillIdx(-1);
			}
			else // �̵��� ��ҵǰ� ���ݰ��ɻ��·�
			{
				((CombatScene*)SceneManager::GetActiveScene())->SetWPBow(1);

				if(scene->GetAlphaFollower())
					//scene->GetAlphaFollower()->SetState(GameObject::STATE::Death);

				SetCurAttackSkill();
				SetMove(false);
			}
		}
	}
	void Mech::MechMove()
	{
		if (directQueue.size() == 0)
		{
			SetEndMove(false);
			return;
		}
		moveDelay += Time::fDeltaTime();
		if (moveDelay >= 0.1f)
		{
			moveDelay = 0.f;
		}
		else return;
		Scene* scene = SceneManager::GetActiveScene();

		//SetFinalCoord(directQueue[moveCnt - 1].coord);
		//SetFinalPos();
		if (directQueue.size() <= moveCnt)
			moveCnt = (int)directQueue.size() - 1;
		scene->MoveAffectUnit(this, directQueue[moveCnt].coord);
		
		int i = 0;
		wstring randMove = L"";
		while (randMove == L"")
		{
			i = rand() % 3;
			randMove = MECH_MOVE_SOUNDS[GetUnitName()][i];
		}
		randMoveSound = Resources::Load<Sound>(randMove, randMove);
		if (!randMoveSoundPlayed)
		{
			randMoveSound->SetVolume(10.f);
			randMoveSound->Play(false);
			randMoveSoundPlayed = true;
		}
		moveCnt--;
		DrawMoveDust();
		//if (GetCoord() == GetFinalCoord())
		//{
		//	scene->GetMoveSave().push_back(Vector2_2(GetFinalCoord(), GetFinalPos(), GetMIdx()));
		//	directQueue.clear();
		//	moveCnt = GetMoveRange();;
		//	SetEndMove(false);
		//	SceneManager::GetActiveScene()->SetMouseFollower(nullptr);
		//}
		if (moveCnt == -1)
		{
			//scene->GetMoveSave().push_back(Vector2_2(GetFinalCoord(), GetFinalPos(), GetMIdx()));
			directQueue.clear();
			moveCnt = GetMoveRange();
			SetEndMove(false);
			randMoveSoundPlayed = false;
		}
	}
	void Mech::idle()
	{
		GetAnimator()->Play(MAKE_UNIT_KEY((MECHS)GetUnitName(), COMBAT_CONDITION_T::IDLE), true);
		SetCurImage(nullptr);
	}
	void Mech::broken()
	{
		GetAnimator()->Stop();
		SetCurImage(GetMImages()[(UINT)COMBAT_CONDITION_T::BROKEN]);
	}
	void Mech::water()
	{
		GetAnimator()->Stop();
		SetCurImage(GetMImages()[(UINT)COMBAT_CONDITION_T::WATER]);
	}
	void Mech::noMove()
	{
		GetAnimator()->Stop();
		SetCurImage(GetMImages()[(UINT)COMBAT_CONDITION_T::NO_SHADOW]);
	}
}
