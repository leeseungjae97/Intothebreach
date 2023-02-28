#include "Mech.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaAnimator.h"
namespace ya
{
	Mech::Mech(MECHS _mech)
		: mMechType(_mech)
		, mWeapon(nullptr)
	{
		AddComponent(new Animator());
		AddComponent(new Transform());

		for (UINT i = 0; i < (UINT)COMBAT_CONDITION_T::End; i++) {
			mImages[i] = Resources::Load<Image>(
				MAKE_COMBAT_MECH_KEY(mMechType, (COMBAT_CONDITION_T)i)
				, MAKE_COMBAT_MECH_PATH(mMechType, (COMBAT_CONDITION_T)i));
		}

		mAnimator = GetComponent<Animator>();

		mAnimator->CreateAnimation(
			MAKE_COMBAT_MECH_KEY(mMechType, COMBAT_CONDITION_T::IDLE)
			, mImages[(UINT)COMBAT_CONDITION_T::IDLE]
			, Vector2(0.f, 0.f)
			, Vector2(44.f, 34.f)
			, Vector2(44.f, 0.f)
			, 44.f
			, 4
			, 0.1f
			, 0x01
		);
		mAnimator->Play(MAKE_COMBAT_MECH_KEY(mMechType, COMBAT_CONDITION_T::IDLE), true);
	}
	Mech::~Mech()
	{
	}
	void Mech::Initialize() {
	}
	void Mech::Update()
	{

		GameObject::Update();
		switch (mState) {
		case ya::Mech::eMechState::Idle:
			idle();
			break;
		case ya::Mech::eMechState::Broken:
			broken();
			break;
		case ya::Mech::eMechState::Water:
			water();
			break;
		case ya::Mech::eMechState::End:

			break;
		default:
			break;
		}
		
	}
	void Mech::Render(HDC hdc)
	{
		GameObject::Render(hdc);
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
	}
	void Mech::broken() {
		//mAnimator;
	}
	void Mech::water() {
		
	}
}
