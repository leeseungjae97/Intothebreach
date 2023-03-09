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
		: mMechType(_mech)
		, mPilot(nullptr)
		, mWeapon(nullptr)
		, curImage(nullptr)
		, mAnimator(nullptr)
		, endMove(false)
		, endAttack(false)
		, mCoord(_coord)
		, mFinalCoord(_coord)
		, mFinalPos(Vector2::One)
		, moveRange(_range)
		, mHp(0)
		, curHp(0)
	{
		AddComponent(new Animator());
		AddComponent(new Transform());
		//AddComponent(new Collider());

		mImages.resize((UINT)COMBAT_CONDITION_T::END);

		for (UINT i = 0; i < (UINT)COMBAT_CONDITION_T::END; i++) {
			mImages[i] = Resources::Load<Image>(
				MAKE_COMBAT_MECH_KEY(mMechType, (COMBAT_CONDITION_T)i)
				, MAKE_COMBAT_MECH_PATH(mMechType, (COMBAT_CONDITION_T)i));
			if (nullptr == mImages[i]) continue;
			mImages[i]->SetOffset(MECHS_OFFSET[(UINT)mMechType]);
		}

		mAnimator = GetComponent<Animator>();
		//float fWid = mImages[(UINT)COMBAT_CONDITION_T::S_SIZE]->GetWidth() - MECHS_IMAGE_SIZE[(UINT)mMechType].x;
		UINT len = UINT(mImages[(UINT)COMBAT_CONDITION_T::IDLE]->GetWidth() / (mImages[(UINT)COMBAT_CONDITION_T::S_SIZE]->GetWidth() + MECHS_IMAGE_SIZE[(UINT)mMechType].x));
		float fHei = mImages[(UINT)COMBAT_CONDITION_T::S_SIZE]->GetHeight() + MECHS_IMAGE_SIZE[(UINT)mMechType].y;
		float fWid = (float)(mImages[(UINT)COMBAT_CONDITION_T::IDLE]->GetWidth() / len);

		mAnimator->CreateAnimation(
			MAKE_COMBAT_MECH_KEY(mMechType, COMBAT_CONDITION_T::IDLE)
			, mImages[(UINT)COMBAT_CONDITION_T::IDLE]
			, Vector2(Vector2::Zero)
			, Vector2(fWid, fHei)
			, mImages[(UINT)COMBAT_CONDITION_T::IDLE]->GetOffset()
			, len
			, 0.5f
			, AC_SRC_OVER
		);
		mAnimator->Play(MAKE_COMBAT_MECH_KEY(mMechType, COMBAT_CONDITION_T::IDLE), true);
		mState = STATE::Idle;
	}
	Mech::Mech(Mech& _origin) 
		: mMechType(_origin.mMechType)
		, GameObject(_origin)
		, curImage(_origin.curImage)
		, mCoord(_origin.mCoord)
		, mFinalCoord(_origin.mFinalCoord)
		, mFinalPos(_origin.mFinalPos)
		, moveRange(_origin.moveRange)
		, mState(_origin.mState)
	{
		mAnimator = GetComponent<Animator>();
	}
	Mech::~Mech()
	{
	}
	void Mech::Initialize() {
	}
	void Mech::Update()
	{

		GameObject::Update();
		if (KEY_PRESSED(KEYCODE_TYPE::Q)) {
			mState = STATE::Broken;
		}
		if (KEY_PRESSED(KEYCODE_TYPE::E)) {
			mState = STATE::Idle;
		}
		switch (mState) {
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
		GameObject::Render(hdc);
		
		if (nullptr != curImage) {
			Vector2 mPos = GetComponent<Transform>()->GetPos();
			mPos += curImage->GetOffset();
			mPos = Camera::CalculatePos(mPos);
			TransparentBlt(hdc
				, (int)(mPos.x - curImage->GetWidth() / 2.f)
				, (int)(mPos.y - curImage->GetHeight() / 2.f)
				, (int)(curImage->GetWidth() * 2)
				, (int)(curImage->GetHeight() * 2)
				, curImage->GetHdc()
				, 0
				, 0
				, (int)(curImage->GetWidth())
				, (int)(curImage->GetHeight())
				, RGB(255, 0, 255));
		}
	}
	void Mech::Release()
	{
		GameObject::Release();

	}
	void Mech::SetSkill() {
	}
	void Mech::ChangePilotSlot() {
	}
	Weapon* Mech::ChangeWeaponSlot(int index) {
		return nullptr;
	}
	void Mech::idle() {
		mAnimator->Play(MAKE_COMBAT_MECH_KEY(mMechType, COMBAT_CONDITION_T::IDLE), true);
		curImage = nullptr;
	}
	void Mech::broken() {
		mAnimator->Stop();
		curImage = mImages[(UINT)COMBAT_CONDITION_T::BROKEN];
	}
	void Mech::water() {
		mAnimator->Stop();
		curImage = mImages[(UINT)COMBAT_CONDITION_T::WATER];
	}
}
