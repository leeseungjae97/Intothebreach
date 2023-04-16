#include "Mech.h"
#include "mTime.h"
#include "func.h"
#include "mSceneManager.h"
#include "mResources.h"
#include "mAnimator.h"
#include "mBackground.h"
#include "mTransform.h"
#include "mImage.h"
#include "mInput.h"
#include "mCamera.h"
#include "mCollider.h"
#include "mSkill.h"
namespace m
{
	Mech::Mech(int unitName, Vector2 _coord, int _range, int _hp, size_t idx)
		: Unit(_coord, _range, _hp, BASIC_SKILL[(UINT)unitName], idx, unitName)
		, moveCnt(GetMoveRange())
		, fDeployConstant(255)
		, bMakeDeployAlpha(false)
		, bDeploy(false)
		, bSwap(false)
		, bCancelDeploy(false)
		, bDeployed(false)

	{
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
			, AC_SRC_ALPHA
		);
		if (GetLayerType() == LAYER_TYPE::CLONE)
		{
			return;
		}
		GetAnimator()->SetConstant(255);
		GetAnimator()->Play(MAKE_UNIT_KEY((MECHS)unitName, COMBAT_CONDITION_T::IDLE), true);

		SetState(STATE::Idle);
	}
	Mech::Mech(Mech& _origin)
		: Unit(_origin.GetCoord()
			, _origin.GetMoveRange()
			, 0
			, 0
			, _origin.GetMIdx()
			, _origin.GetUnitName())
	{
		SetState(_origin.GetState());
		SetDeploy(_origin.GetDeploy());
		SetCancelDeploy(_origin.GetCancelDeploy());
		SetSwap(_origin.GetSwap());
	}
	Mech::~Mech()
	{
	}
	void Mech::Initialize()
	{}
	void Mech::Update()
	{
		Unit::Update();
		CheckNumInput();

		if (GetEndMove())
		{
			SceneManager::GetActiveScene()->SetMouseFollower(nullptr);
			MechMove();
		}
		//else object::DestoryUnitVector<Background*>(GetMoveDusts());
		if (KEY_PRESSED(KEYCODE_TYPE::Q))
		{
			SetState(STATE::Broken);
		}
		if (KEY_PRESSED(KEYCODE_TYPE::E))
		{
			SetState(STATE::Idle);
		}
		if (Unit::GetCurHp() == 0)
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
		func.SourceConstantAlpha = fDeployConstant;

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
	}
	void Mech::Release()
	{
		Unit::Release();
	}
	void Mech::CheckNumInput()
	{
		Scene* scene = SceneManager::GetActiveScene();
		if (nullptr == scene->GetMouseFollower()) return;
		if (scene->GetMouseFollower()->GetMIdx() != GetMIdx()) return;
		if (KEY_DOWN(KEYCODE_TYPE::NUM_1)) { SetSkillIdx(0); }
		if (KEY_DOWN(KEYCODE_TYPE::NUM_2)) { SetSkillIdx(1); }
		if (KEY_DOWN(KEYCODE_TYPE::NUM_3)) { SetSkillIdx(2); }
		if (KEY_DOWN(KEYCODE_TYPE::NUM_1)
			|| KEY_DOWN(KEYCODE_TYPE::NUM_2)
			|| KEY_DOWN(KEYCODE_TYPE::NUM_3))
		{
			SetPos(GetFinalPos());
			SetCoord(GetFinalCoord());

			if (!GetMove()) // 공격이 취소되고 이동가능상태로
			{
				SetMove(true);
				GetCurAttackSkill()->SetStartRender(false);

				SetSkillIdx(-1);
			}
			else // 이동이 취소되고 공격가능상태로
			{
				if(scene->GetAlphaFollower())
					scene->GetAlphaFollower()->SetState(GameObject::STATE::Death);

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
			moveCnt = directQueue.size() - 1;
		scene->MoveEffectUnit(this, directQueue[moveCnt].coord);
		
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
			scene->GetMoveSave().push_back(Vector2_2(GetFinalCoord(), GetFinalPos(), GetMIdx()));
			directQueue.clear();
			moveCnt = GetMoveRange();
			SetEndMove(false);
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
