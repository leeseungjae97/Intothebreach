#include "mSkill.h"
#include "mSelectGDI.h"
#include "mTime.h"
#include "mTransform.h"
#include "mAnimator.h"
#include "func.h"
#include "mApplication.h"
#include "mImage.h"
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
	}
	Skill::~Skill() {
	}
	void Skill::Initialize() {
		
	}
	void Skill::PreCal() {
		fEndHeight = mFinalEdPos.y - mStPos.y;
		fHeight = 50 - mStPos.y;

		fg = 2 * fHeight / (fMaxTime * fMaxTime);
		fy = sqrtf(fg * fHeight);

		float a = fg;
		float b = - 2 * fy;
		float c = 2 * fEndHeight;

		if (a == 0) {
			fEndTime = fMaxTime;
		}
		else {
			fEndTime = (-b + sqrtf(b * b - 4 * a * c)) / (2 * a);
		}

		fx = -(mStPos.x - mFinalEdPos.x) / fEndTime;
	}
	void Skill::Update() {
		Vector2 mPos = GetPos();
		
		switch (mType) {
		case SKILL_T::ARC:
		{
			fTime += Time::fDeltaTime();

			mPos.x = mStPos.x - fx * fTime;
			mPos.y = mStPos.y - (fy * fTime) - (0.5f * fg * fTime * fTime);
			/*Vector2 m = mFinalEdPos - mPos;
			float theta = atan2(m.y, m.x);

			wchar_t szFloat[500] = {};
			swprintf_s(szFloat, 500
				, L"fx : %f, fy : %f\n posx : %f, posy : %f\ntheta : %f, angle : %f"
				, fx , fy , m.x, m.y, theta , theta * 180 / PI);

			size_t iLen = wcsnlen_s(szFloat, 500);
			RECT rt = { 50, 100, 400, 200 };
			DrawText(application.GetHdc(), szFloat, iLen, &rt, DT_LEFT | DT_WORDBREAK);*/

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
		
		if (mStPos.x > mFinalEdPos.x){
			// 물체보다 오른쪽 위에 있을때.
			if (mStPos.y < mFinalEdPos.y) {
				if (mFinalEdPos.y <= mPos.y
					|| mFinalEdPos.x >= mPos.x) {
					object::Destory(this);
				}
			}
			// 물체보다 오른쪽 아래, 오른쪽 동일선 일때.
			else {
				if (mFinalEdPos.y >= mPos.y
					|| mFinalEdPos.x >= mPos.x) {
					object::Destory(this);
				}
			}
		}
		else {
			// 왼쪽 위
			if (mStPos.y < mFinalEdPos.y) {
				if (mFinalEdPos.y <= mPos.y
					|| mFinalEdPos.x <= mPos.x) {
					object::Destory(this);
				}
			}
			// 물체보다 왼쪽 아래, 왼쪽 동일선 일때.
			else {
				if (mFinalEdPos.y >= mPos.y
					|| mFinalEdPos.x <= mPos.x) {
					object::Destory(this);
				}
			}
		}
		SetPos(mPos);
	}
	void Skill::Render(HDC hdc) {
		Vector2 mPos = GetPos();
		switch (mType) {
		case SKILL_T::ARC:
		{
			Vector2 cm = max(mFinalEdPos, mStPos);
			Vector2 m = mFinalEdPos - mPos;
			m.Normalize();
			//if (prevPosy == mPos.y) mPos.y *= -1;
			float _theta = atan2(m.x , m.y);

			Image* im = Resources::Load<Image>(L"missile", L"..\\Resources\\texture\\effect\\shotup_tribomb_missile.bmp");

			wchar_t szFloat[500] = {};
			swprintf_s(szFloat, 500, L"fHeight : %f, fy : %f", fHeight, fy);
			size_t iLen = wcsnlen_s(szFloat, 500);
			RECT rt = { 50, 100, 400, 500 };
			DrawText(hdc, szFloat, iLen, &rt, DT_CENTER | DT_WORDBREAK);

			if (mFinalEdPos.x < mStPos.x) { _theta *= -1; }


			bitmap::RotateBitmap(hdc, mPos,
				im->GetBitmap(), im->GetWidth()
				, im->GetHeight(), _theta, im->GetHdc());
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