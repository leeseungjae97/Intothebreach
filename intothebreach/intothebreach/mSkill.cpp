#include "mSkill.h"
#include "mSelectGDI.h"
#include "mTime.h"
#include "mTransform.h"
#include "mAnimator.h"
#include "func.h"
namespace m {
	Skill::Skill(SKILL_T _type)
		: mType(_type)
	{
		AddComponent(new Transform);
		AddComponent(new Animator);

		mTheta = -PI / 2.f;
	}
	Skill::Skill(Skill& _origin) {
	}
	Skill::Skill() 
	{
		AddComponent(new Transform);
		AddComponent(new Animator);

		mTheta = -PI / 2.f;
	}
	Skill::~Skill() {
	}
	void Skill::Initialize() {
		
	}
	void Skill::Update() {
		Vector2 mS = GetPos();
		
		switch (mType) {
		case SKILL_T::ARC:
		{
			mEdPos = math::Rotate(mEdPos, 5.0f);
			mS.x += 500.f * mEdPos.x * cosf(mTheta) * Time::fDeltaTime();
			mS.y += 500.f * mEdPos.y * sinf(mTheta) * Time::fDeltaTime();
		}
		break;
		case SKILL_T::ST:
		{
			mS.x += 500.f * mEdPos.x * Time::fDeltaTime();
			mS.y += 500.f * mEdPos.y * Time::fDeltaTime();
		}
		break;
		case SKILL_T::END:
		{

		}
		break;
		default:
			break;
		}

		if (mFinalEdPos <= mS) {
			object::Destory(this);
		}
		SetPos(mS);
	}
	void Skill::Render(HDC hdc) {
		Vector2 mPos = GetPos();
		SelectGDI p(hdc, BRUSH_TYPE::GREEN);

		Rectangle(hdc,
			(int)(mPos.x),
			(int)(mPos.y),
			(int)(mPos.x + 50),
			(int)(mPos.y + 50)
			);
	}
	void Skill::Release() {
	}
}