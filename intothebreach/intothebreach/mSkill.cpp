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

		mTheta = -PI / 4.f;
	}
	Skill::Skill(Skill& _origin) {
	}
	Skill::Skill() 
	{
		AddComponent(new Transform);
		AddComponent(new Animator);

		mTheta = -PI / 4.f;
		a = 45 * PI / 180.f;
	}
	Skill::~Skill() {
	}
	void Skill::Initialize() {
		
	}
	void Skill::PreCal() {
		//Values["gravity"] = 3
		//Values["x_velocity"] = 0.7
		//Values["y_velocity"] = 18

		Missile_vec = mFinalEdPos - mStPos;
		Missile_vec2 = Missile_vec;

		m_fTarget_distance = Missile_vec.Length();

		Missile_vec.Normalize();
	}
	void Skill::Update() {
		PreCal();
		Vector2 mPos = GetPos();
		
		switch (mType) {
		case SKILL_T::ARC:
		{
			mPos.x += 500.f * Missile_vec2.x * Time::fDeltaTime();
			mPos.y += 500.f * Missile_vec2.y * Time::fDeltaTime();

			Missile_vec2.x = mPos.x;
		}
			break;
		case SKILL_T::ST:
		{
			mPos.x += 500.f * mEdPos.x * Time::fDeltaTime();
			mPos.y += 500.f * mEdPos.y * Time::fDeltaTime();
		}
			break;
		case SKILL_T::END:
		{

		}
			break;
		default:
			break;
		}
		tm  += Time::fDeltaTime();
		if (tm > 2.f) {
			object::Destory(this);
		}

		//if (mStPos.x > mFinalEdPos.x){
		//	// 물체보다 오른쪽 위에 있을때.
		//	if (mStPos.y < mFinalEdPos.y) {
		//		if (mFinalEdPos.y <= mPos.y
		//			&& mFinalEdPos.x >= mPos.x) {
		//			object::Destory(this);
		//		}
		//	}
		//	// 물체보다 오른쪽 아래, 오른쪽 동일선 일때.
		//	else {
		//		if (mFinalEdPos.y >= mPos.y
		//			&& mFinalEdPos.x >= mPos.x) {
		//			object::Destory(this);
		//		}
		//	}
		//}
		//else {
		//	// 왼쪽 위
		//	if (mStPos.y < mFinalEdPos.y) {
		//		if (mFinalEdPos <= mPos) {
		//			object::Destory(this);
		//		}
		//	}
		//	// 물체보다 왼쪽 아래, 왼쪽 동일선 일때.
		//	// mStPos.x <= mFinalEdPos.x
		//	// mStPos.y >= mFinalEdPos.y
		//	else {
		//		if (mFinalEdPos <= mPos) {
		//			object::Destory(this);
		//		}
		//	}
		//}

		SetPos(mPos);
	}
	void Skill::Render(HDC hdc) {
		Vector2 m = GetPos();
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

		Image* iml = Resources::Load<Image>(MAKE_SKILL_KEY(SKILL_T::ST, dir), MAKE_SKILL_PATH(SKILL_T::ST, dir));
		TransparentBlt(hdc,
			(int)(m.x),
			(int)(m.y),
			(int)(iml->GetWidth() * 2),
			(int)(iml->GetHeight() * 2),
			iml->GetHdc(),
			0, 0,
			iml->GetWidth(),
			iml->GetHeight(),
			RGB(255, 0, 255));


		Vector2 mPos = Missile_vec2;

		switch (mType) {
		case SKILL_T::ARC:
		{
			Image* im = Resources::Load<Image>(L"missile", L"..\\Resources\\texture\\effect\\shotup_tribomb_missile.bmp");
			
			m_Z = 0.f;
			if (m_fZ < 0) {
				time = 0.f;
				time2 = 0.f;
				m_fZ = 0;
			}
			else {
				time += Missile_vec2.Length() * 500.f * Time::DeltaTime();
				time2 = time + 0.001f;

				m_fZ = (-time * time + m_fTarget_distance * time);
				m_Z = (-time2 * time2 + m_fTarget_distance * time2);
				
				mPos.y = m_fZ / m_fTarget_distance * 1.3f;
			}

			wchar_t szFloat[500] = {};
			swprintf_s(szFloat, 500, L"mPos(x, y) : %f, %f"
				, mPos.x, mPos.y);
			size_t iLen = wcsnlen_s(szFloat, 500);
			RECT rt = { 50, 100, 400, 500 };
			DrawText(hdc, szFloat, iLen, &rt, DT_LEFT | DT_WORDBREAK);

			float Dir;

			if (mPos.x > 0) {
				Dir = -1;
			}
			else Dir = 1;

			float _theta = atan2((time2 - time) * Dir, (m_Z - m_fZ) / m_fTarget_distance * 1.3f);

			bitmap::RotateBitmap(hdc, mPos,
				im->GetBitmap(), im->GetWidth()
				, im->GetHeight(), _theta, im->GetHdc());

			Missile_vec2 = mPos;
		}
			break;
		case SKILL_T::ST:
		{
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


			//wchar_t szFloat[500] = {};
			//swprintf_s(szFloat, 500, MAKE_SKILL_PATH(mType, dir).c_str() );

			//size_t iLen = wcsnlen_s(szFloat, 500);
			//RECT rt = { 50, 100, 400, 200 };
			//DrawText(hdc, szFloat, iLen, &rt, DT_LEFT | DT_WORDBREAK);


			im = Resources::Load<Image>(MAKE_SKILL_KEY(mType, dir), MAKE_SKILL_PATH(mType, dir));
			TransparentBlt(hdc,
				(int)(mPos.x),
				(int)(mPos.y),
				(int)(im->GetWidth() * 2),
				(int)(im->GetHeight() * 2),
				im->GetHdc(),
				0,0,
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