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
		fy = sqrtf(1 * fg * fHeight);

		float a = fg;
		float b = - 2 * fy;
		float c = 2 * fEndHeight;

		fEndTime = (-b + sqrtf(b * b - 4 * a * c)) / (2 * a);

		fx = -(mStPos.x - mFinalEdPos.x) / fEndTime;
	}
	void Skill::Update() {
		Vector2 mPos = GetPos();
		
		switch (mType) {
		case SKILL_T::ARC:
		{
			PreCal();
			fTime += Time::fDeltaTime();

			mPos.x = mStPos.x - fx * fTime;
			mPos.y = mStPos.y - (fy * fTime) - (0.5f * fg * fTime * fTime);


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
		if (mStPos.x > mFinalEdPos.x) {
			if (mFinalEdPos.y <= mPos.y) {
				object::Destory(this);
			}
		}
		if (mFinalEdPos <= mPos) {
			object::Destory(this);
		}
		SetPos(mPos);
	}
	void Skill::Render(HDC hdc) {
		Vector2 mPos = GetPos();
		SelectGDI p(hdc, BRUSH_TYPE::GREEN);
		
		float _theta = atan2(mPos.y, mPos.x);

	    Image* im = Resources::Load<Image>(L"missile", L"..\\Resources\\texture\\effect\\shotup_tribomb_missile.bmp");
		Image* output = Resources::Load<Image>(L"missile", L"..\\Resources\\texture\\effect\\shotup_tribomb_missile_square.bmp");;
		HBITMAP hbm = im->GetBitmap();
		BITMAP bm;
		GetObject(hbm, sizeof(bm), &bm);

		bitmap::RotatingImage(im, output, bm.bmWidth, bm.bmHeight, _theta);

		TransparentBlt(hdc, 
			(int)(mPos.x),
			(int)(mPos.y),
			(int)(output->GetWidth() * 2),
			(int)(output->GetHeight() * 2),
			output->GetHdc(),
			0,0,
			output->GetWidth(), output->GetHeight(),
			RGB(255,0,255));
		//PlgBlt(hdc, );

	/*	Rectangle(hdc,
			(int)(mPos.x),
			(int)(mPos.y),
			(int)(mPos.x + 50),
			(int)(mPos.y + 50)
			);*/

		/**RotateBitmap(bitmap, hdc, size x, size y,
		* angle(theta), dstX, dstY);
		*/
	}
	void Skill::Release() {
	}
}