#include "mSkill.h"
#include "mSelectGDI.h"
#include "mTime.h"
#include "mTransform.h"
#include "mAnimator.h"
#include "func.h"
#include "mApplication.h"
#include "mImage.h"
#include "mSceneManager.h"
extern m::Application application;
namespace m {
	Skill::Skill(SKILL_T _type)
		: mType(_type) 
	{
		AddComponent(new Transform);
		AddComponent(new Animator);
		endFire = false;
	}
	Skill::Skill(Skill& _origin) {
	}
	Skill::Skill() 
	{
		AddComponent(new Transform);
		AddComponent(new Animator);
	}
	Skill::~Skill() {
	}
	void Skill::Initialize() {
		
	}
	void Skill::PreCal() {
		Missile_vec = mFinalEdPos - mStPos;
		Vector2 maxDistance = max(mFinalEdPos, mStPos) - min(mFinalEdPos, mStPos);

		m_fMissile_distance = Missile_vec.Length();
		Missile_vec.Normalize();

		curPos = mStPos;
	}
	void Skill::Update() {
		GameObject::Update();
		Vector2 mPos = GetPos();
		switch (mType) {
		case SKILL_T::ARC: 
		{
			mPos.x += 500.f * Missile_vec.x * Time::fDeltaTime();
			mPos.y += 500.f * Missile_vec.y * Time::fDeltaTime();
			curPos = mPos;
		}
			break;
		case SKILL_T::ST:
		{
			mPos.x += 500.f * Missile_vec.x * Time::fDeltaTime();
			mPos.y += 500.f * Missile_vec.y * Time::fDeltaTime();
			curPos = mPos;
		}
			break;
		case SKILL_T::END:
		{

		}
			break;
		default:
			break;
		}
		if (m_fZ < 0) {
			object::Destory(this);
			endFire = true;
		}
		SetPos(mPos);
	}
	void Skill::Render(HDC hdc) {
		//Vector2 mPos = GetPos();

		//Image* im;
		//SKILL_DIR dir = SKILL_DIR::D;
		//if (mStPos < mFinalEdPos)
		//	dir = SKILL_DIR::R;
		//if (mStPos > mFinalEdPos)
		//	dir = SKILL_DIR::L;
		//if (mStPos.x < mFinalEdPos.x
		//	&& mStPos.y > mFinalEdPos.y)
		//	dir = SKILL_DIR::U;
		//if (mStPos.x > mFinalEdPos.x
		//	&& mStPos.y < mFinalEdPos.y)
		//	dir = SKILL_DIR::D;
		//im = Resources::Load<Image>(MAKE_SKILL_KEY(SKILL_T::ST, dir), MAKE_SKILL_PATH(SKILL_T::ST, dir));
		//TransparentBlt(hdc,
		//	(int)(mPos.x),
		//	(int)(mPos.y),
		//	(int)(im->GetWidth() * 2),
		//	(int)(im->GetHeight() * 2),
		//	im->GetHdc(),
		//	0, 0,
		//	im->GetWidth(),
		//	im->GetHeight(),
		//	RGB(255, 0, 255));

		time += 500.f * abs(Missile_vec.Length()) * Time::fDeltaTime();
		time2 = time * 2;

		float d = abs(m_fMissile_distance);
		m_fZ = (-time * time +d * time);
		m_Z = (-time2 * time2 + d * time2);

		switch (mType) {
		case SKILL_T::ARC:
		{
			//if (m_fZ < 0) {
			//	time = 0;
			//	time2 = 0;
			//	m_fZ = 0;
			//	return;
			//}
			Vector2 mPos = curPos;

			Image* im = Resources::Load<Image>(L"missile", L"..\\Resources\\texture\\effect\\shotup_tribomb_missile.bmp");
			
			float Dir;
			float _theta = 0;
			_theta = atan2((time2 - time), ((m_Z - m_fZ) / d));
			mPos.y -= (m_fZ / d);

			if (Missile_vec.x > 0) {
				Dir = 1;
			}
			else {
				Dir = -1;
			}
			_theta *= Dir;

			wchar_t szFloat[500] = {};
			swprintf_s(szFloat, 500, L"time: %f time2: %f", time, time2);
			size_t iLen = wcsnlen_s(szFloat, 500);
			RECT rt = { 50, 140, 400, 160 };
			DrawText(hdc, szFloat, iLen, &rt, DT_LEFT | DT_WORDBREAK);
			
			curPos = mPos;

			bitmap::RotateBitmap(hdc, mPos,
				im->GetBitmap(), _theta, im->GetHdc());
		}
			break;
		case SKILL_T::ST:
		{
			Vector2 mPos = GetPos();

			Image* im;
			SKILL_DIR dir = SKILL_DIR::D;
			if (mStPos < mFinalEdPos) 
				dir = SKILL_DIR::R;
			if (mStPos > mFinalEdPos) 
				dir = SKILL_DIR::L;
			if (mStPos.x < mFinalEdPos.x
				&& mStPos.y > mFinalEdPos.y)
				dir = SKILL_DIR::U;
			if (mStPos.x > mFinalEdPos.x
				&& mStPos.y < mFinalEdPos.y)
				dir = SKILL_DIR::D;
			im = Resources::Load<Image>(MAKE_SKILL_KEY(mType, dir), MAKE_SKILL_PATH(mType, dir));
			TransparentBlt(hdc,
				(int)(mPos.x),
				(int)(mPos.y),
				(int)(im->GetWidth() * 2),
				(int)(im->GetHeight() * 2),
				im->GetHdc(),
				0, 0,
				im->GetWidth(),
				im->GetHeight(),
				RGB(255, 0, 255));
			
		}
			break;
		case SKILL_T::END:
			break;
		default:
			break;
		}
	}
	void Skill::Release() {
	}
}