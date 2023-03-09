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
namespace m
{
	Mech::Mech(MECHS _mech, Vector2 _coord, int _range)
		: Unit(_coord, _range)
		, mMechType(_mech)
	{
		GetMImages().resize((UINT)COMBAT_CONDITION_T::END);

		for (UINT i = 0; i < (UINT)COMBAT_CONDITION_T::END; i++) {
			GetMImages()[i] = Resources::Load<Image>(
				MAKE_COMBAT_MECH_KEY(mMechType, (COMBAT_CONDITION_T)i)
				, MAKE_COMBAT_MECH_PATH(mMechType, (COMBAT_CONDITION_T)i));
			if (nullptr == GetMImages()[i]) continue;
			GetMImages()[i]->SetOffset(MECHS_OFFSET[(UINT)mMechType]);
		}

		
		//float fWid = mImages[(UINT)COMBAT_CONDITION_T::S_SIZE]->GetWidth() - MECHS_IMAGE_SIZE[(UINT)mMechType].x;
		UINT len = UINT(GetMImages()[(UINT)COMBAT_CONDITION_T::IDLE]->GetWidth() / (GetMImages()[(UINT)COMBAT_CONDITION_T::S_SIZE]->GetWidth() + MECHS_IMAGE_SIZE[(UINT)mMechType].x));
		float fHei = GetMImages()[(UINT)COMBAT_CONDITION_T::S_SIZE]->GetHeight() + MECHS_IMAGE_SIZE[(UINT)mMechType].y;
		float fWid = (float)(GetMImages()[(UINT)COMBAT_CONDITION_T::IDLE]->GetWidth() / len);

		GetAnimator()->CreateAnimation(
			MAKE_COMBAT_MECH_KEY(mMechType, COMBAT_CONDITION_T::IDLE)
			, GetMImages()[(UINT)COMBAT_CONDITION_T::IDLE]
			, Vector2(Vector2::Zero)
			, Vector2(fWid, fHei)
			, GetMImages()[(UINT)COMBAT_CONDITION_T::IDLE]->GetOffset()
			, len
			, 0.5f
			, AC_SRC_OVER
		);
		GetAnimator()->Play(MAKE_COMBAT_MECH_KEY(mMechType, COMBAT_CONDITION_T::IDLE), true);
		SetMState(STATE::Idle);
	}
	Mech::Mech(Mech& _origin) 
		: mMechType(_origin.mMechType)
	{

	}
	Mech::~Mech()
	{
	}
	void Mech::Initialize() {
	}
	void Mech::Update()
	{
		Unit::Update();
		if (KEY_PRESSED(KEYCODE_TYPE::Q)) {
			SetMState(STATE::Broken);
		}
		if (KEY_PRESSED(KEYCODE_TYPE::E)) {
			SetMState(STATE::Idle);
		}
		switch (GetMState()) {
		case m::Mech::STATE::Idle:
			idle();
			break;
		case m::Mech::STATE::Broken:
			broken();
			break;
		case m::Mech::STATE::Water:
			water();
			break;
		case m::Mech::STATE::End:

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
	void Mech::idle() {
		GetAnimator()->Play(MAKE_COMBAT_MECH_KEY(mMechType, COMBAT_CONDITION_T::IDLE), true);
		 SetCurImage(nullptr);
	}
	void Mech::broken() {
		GetAnimator()->Stop();
		SetCurImage(GetMImages()[(UINT)COMBAT_CONDITION_T::BROKEN]);
	}
	void Mech::water() {
		GetAnimator()->Stop();
		SetCurImage(GetMImages()[(UINT)COMBAT_CONDITION_T::WATER]);
	}
}
