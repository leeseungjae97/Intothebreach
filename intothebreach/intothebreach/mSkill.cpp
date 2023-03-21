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

		m_fMissile_distance = Missile_vec.Length();
		Missile_vec.Normalize();

		curPos = mStPos;

		arcXMaxTime = 0.5f;
		arcYMaxTime = 1.f;
		maxHeight = 25.f;
	}
	void Skill::Update() {
		GameObject::Update();
		Vector2 mPos = GetPos();
		switch (mType) {
		case SKILL_T::ARC: 
		{
			float d = m_fMissile_distance;
			float vX = (d / arcXMaxTime);
			float vY = (d / arcYMaxTime);
			mPos.x += vX * Missile_vec.x * Time::fDeltaTime();
			mPos.y += vX * Missile_vec.y * Time::fDeltaTime();
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

		float d = m_fMissile_distance;
		float vX = (d / arcXMaxTime);
		float vY = (d / arcYMaxTime);
		// X의 이동 시간을 토대로 속도계산
		// 이동거리가 달라도 같은 시간에 도달
		moveXtime += vX * abs(Missile_vec.Length()) * Time::fDeltaTime();
		//moveXtime += vY * abs(Missile_vec.Length()) * Time::fDeltaTime();

		m_fZ = (-moveXtime * moveXtime + d * moveXtime);	

		switch (mType) {
		case SKILL_T::ARC:
		{
			Vector2 mPos = GetPos();

			Image* im = Resources::Load<Image>(L"missile", L"..\\Resources\\texture\\effect\\shotup_tribomb_missile.bmp");
			mPos.y -= (m_fZ / d);
			curPos = mPos;

			TransparentBlt(hdc,
				(int)(mPos.x),
				(int)(mPos.y),
				(int)(im->GetWidth()* 2),
				(int)(im->GetHeight() * 2),
				im->GetHdc(),
				0, 0,
				im->GetWidth(), im->GetHeight(),
				RGB(255, 0, 255));
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