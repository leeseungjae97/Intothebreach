#include "mUnit.h"
#include "mAnimator.h"
#include "mTransform.h"
#include "mCamera.h"
#include "mResources.h"
#include "mSelectGDI.h"
#include "mSkill.h"
namespace m {
	Unit::Unit(Vector2 _coord, int _range, int hp, int _type)
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
		, mHp(hp)
		, curHp(hp)
	{
		SetSkill(_type);
		AddComponent(new Animator());
		AddComponent(new Transform());
		mAnimator = GetComponent<Animator>();

		hpImage = Resources::Load<Image>(HP_BAR, HP_BAR);
		hpImage->SetOffset(Vector2(10.f, -45.f));

		hpBack = Resources::Load<Image>(HP_BAR_BACK, HP_BAR_BACK);
		hpBack->SetOffset(Vector2(16.f, -39.f));

		mSkills.resize(MAX_WEAPONS);
	}
	Unit::Unit(Unit& _origin) 
		: GameObject(_origin)
		, curImage(_origin.curImage)
		, mCoord(_origin.mCoord)
		, mFinalCoord(_origin.mFinalCoord)
		, mFinalPos(_origin.mFinalPos)
		, moveRange(_origin.moveRange)
	{
		SetState(_origin.GetState());
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
		
		Vector2 mPos = GetPos();
		
		if (nullptr != GetCurImage()) {
			Image* curImage = GetCurImage();
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
		if (lType == LAYER_TYPE::CLONE) return;


		mPos = GetComponent<Transform>()->GetPos();
		if (nullptr != hpImage) {
			mPos += hpImage->GetOffset();
			mPos = Camera::CalculatePos(mPos);
			TransparentBlt(hdc
				, (int)(mPos.x - hpImage->GetWidth() / 2.f)
				, (int)(mPos.y - hpImage->GetHeight() / 2.f)
				, (int)(hpImage->GetWidth() * 2)
				, (int)(hpImage->GetHeight() * 2)
				, hpImage->GetHdc()
				, 0
				, 0
				, (int)(hpImage->GetWidth())
				, (int)(hpImage->GetHeight())
				, RGB(255, 0, 255));
		}
		mPos = GetComponent<Transform>()->GetPos();
		if (nullptr != hpBack) {
			mPos += hpBack->GetOffset();
			mPos = Camera::CalculatePos(mPos);
			
			int px = (int)(mPos.x - hpBack->GetWidth() / 2.f);
			int py = (int)(mPos.y - hpBack->GetHeight() / 2.f);
			if (mHp == 0) return;
			int hpWidth = (hpBack->GetWidth() * 2) / mHp;
			int hpHeight = hpBack->GetHeight() * 2;
			for (int i = 0; i < mHp; i++) {
				SelectGDI p(hdc, BRUSH_TYPE::GREEN);
				Rectangle(hdc
					, (int)(px + hpWidth * i)
					, (int)(py)
					, (int)(px + hpWidth * (i + 1))
					, (int)(py + hpHeight));
			}
		}
		
		
	}
	void Unit::Release() {
		GameObject::Release();
	}
	void Unit::SetSkill() {

	}
	void Unit::SetSkill(int type) {
		mSkills.push_back(new Skill((SKILL_T)type));
	}
	void Unit::SetSkill(int idx, SKILL_T type) {
		mSkills[idx] = new Skill(type);
	}
	SKILL_T Unit::GetSkill(int idx) {
		return mSkills[idx]->GetSkillType();
	}
	void Unit::ChangePilotSlot() {
	}
	Weapon* Unit::ChangeWeaponSlot(int index) {
		return nullptr;
	}
}