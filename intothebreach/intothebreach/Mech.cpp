#include "Mech.h"
#include "mTime.h"
#include "mSceneManager.h"
#include "mInput.h"
#include "mResources.h"
#include "mImage.h"
#include "mTransform.h"
#include "mTime.h"
#include "mAnimator.h"
#include "mCamera.h"
#include "mCollider.h"
#include "mSkill.h"
#include "func.h"
namespace m
{
	Mech::Mech(int unitName, Vector2 _coord, int _range, int _hp, size_t idx)
		: Unit(_coord, _range, _hp, BASIC_SKILL[(UINT)unitName], idx, unitName)
	{
		GetMImages().resize((UINT)COMBAT_CONDITION_T::END);

		for (UINT i = 0; i < (UINT)COMBAT_CONDITION_T::END; i++)
		{
			GetMImages()[i] = Resources::Load<Image>(
				MAKE_UNIT_KEY((MECHS)unitName, (COMBAT_CONDITION_T)i)
				, MAKE_UNIT_PATH((MECHS)unitName, (COMBAT_CONDITION_T)i));
			if (nullptr == GetMImages()[i]) continue;
			GetMImages()[i]->SetOffset(MECHS_OFFSET[(UINT)unitName]);
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
		CheckNumInput();
		Unit::Update();
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
		case STATE::Emerge:
			break;
		case STATE::End:
			break;
		default:
			break;
		}
	}
	void Mech::Render(HDC hdc)
	{
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
	void Mech::emerge()
	{}
}
