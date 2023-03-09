#include "mUnit.h"
#include "mAnimator.h"
#include "mTransform.h"
#include "mCamera.h"
namespace m {
	Unit::Unit(Vector2 _coord, int _range)
		: mPilot(nullptr)
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
		mAnimator = GetComponent<Animator>();

	}
	Unit::Unit(Unit& _origin) 
		: GameObject(_origin)
		, curImage(_origin.curImage)
		, mCoord(_origin.mCoord)
		, mFinalCoord(_origin.mFinalCoord)
		, mFinalPos(_origin.mFinalPos)
		, moveRange(_origin.moveRange)
		, mState(_origin.mState)
	{
		mAnimator = GetComponent<Animator>();
	}
	Unit::Unit() {
	}
	Unit::~Unit() {
	}
	void Unit::Initialize() {
		GameObject::Initialize();
	}
	void Unit::Update() {
		GameObject::Update();
	}
	void Unit::Render(HDC hdc) {
		GameObject::Render(hdc);
		Image* curImage = GetCurImage();
		if (nullptr != GetCurImage()) {
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
	void Unit::Release() {
		GameObject::Release();
	}
	void Unit::SetSkill() {
	}
	void Unit::ChangePilotSlot() {
	}
	Weapon* Unit::ChangeWeaponSlot(int index) {
		return nullptr;
	}
}