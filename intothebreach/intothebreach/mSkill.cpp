#include "mSkill.h"
#include "mSelectGDI.h"
#include "mTime.h"
#include "mTransform.h"
#include "mAnimator.h"
#include "func.h"
#include "mApplication.h"
#include "mImage.h"
#include "mResources.h"
#include "mSceneManager.h"
extern m::Application application;
namespace m {
	Skill::Skill(SKILL_T _type)
		: mType(_type) 
		, mLayerType(LAYER_TYPE::SKILL)
		, endFire(false)
		, stFire(false)
		, fTime(0)
		, offsetHeight(0)
		, maxTheta(0)
		, minTheta(0)
		, fHeight(0)
		, fMaxTime(0)
		, velocityY(0)
		, velocityX(0)
		, gravityAccel(0)
		, arcTheta(0)
		, Missile_vec(Vector2::One)
		, endCoord(Vector2::One)
		, mStPos(Vector2::Zero)
		, mFinalEdPos(Vector2::One)
	{
		AddComponent(new Transform);
		AddComponent(new Animator);
	}
	Skill::Skill(Skill& _origin) 
		: mType(_origin.mType)
		, mLayerType(LAYER_TYPE::SKILL)
		, endFire(false)
		, stFire(false)
		, fTime(_origin.fTime)
		, offsetHeight(_origin.offsetHeight)
		, maxTheta(_origin.maxTheta)
		, minTheta(_origin.minTheta)
		, fHeight(_origin.fHeight)
		, fMaxTime(_origin.fMaxTime)
		, velocityY(_origin.velocityY)
		, velocityX(_origin.velocityX)
		, gravityAccel(_origin.gravityAccel)
		, arcTheta(_origin.arcTheta)
		, Missile_vec(_origin.Missile_vec)
		, endCoord(_origin.endCoord)
		, mStPos(_origin.mStPos)
		, mFinalEdPos(_origin.mFinalEdPos)
	{
	}
	Skill::~Skill() {
	}
	void Skill::Initialize() {
		object::Visible(this);
		switch (mType)
		{
		case SKILL_T::ARC:
		{
			fTime = 0.f;
			fMaxTime = 0.5f;
			fDistance = (mFinalEdPos - mStPos).Length();
			offsetHeight = mFinalEdPos.y - mStPos.y;
			fHeight = 100.f - min(mStPos.y, mFinalEdPos.y);

			// 낙하에 걸리는 시간
			// 임의의 중력가속도 = 2 * 거리 / 시간^2
			gravityAccel = 3.5f * fHeight / (fMaxTime * fMaxTime);

			// 지면 도달 시간 == 속도
			velocityY = sqrtf(2.f * fHeight * gravityAccel);

			float a = gravityAccel;

			// 속도 == 최고 높이에서 떨어지는 값.
			// 반절짜리 라서 2를 곱함.
			float b = -2 * velocityY;
			float c = 2 * offsetHeight;

			// 고도각
			// 근의 공식에 따라 두개의 (-, +)x가 나옴.
			maxTheta = (-b + sqrtf(b * b - 4.f * a * c)) / (2.f * a);
			minTheta = (-b - sqrtf(b * b - 4.f * a * c)) / (2.f * a);

			// x의 속도
			// 속도 = 거리 / 고도각.
			velocityX = -(mStPos.x - mFinalEdPos.x) / maxTheta;
		}
		break;
		case SKILL_T::ST:
		{
			Vector2 diff = mFinalEdPos - mStPos;
			fDistance = diff.Length();
			Missile_vec = mFinalEdPos - mStPos;
			Missile_vec.Normalize();
		}
		break;
		default:
			break;
		}
	}
	void Skill::CalEndFire() {
		Vector2 vec = GetPos();
		float absD = abs(mFinalEdPos.x - mStPos.x);
		float absMD = abs(vec.x - mStPos.x);
		float diff = absD - absMD;

		absD - absMD <= 0.f ? endFire = true : endFire = false;
	}
	//void Skill::PreCal() {
	//	
	//}
	void Skill::Update() {
		GameObject::Update();
		Vector2 mPos = GetPos();
		if (stFire)
		{
			switch (mType)
			{
			case SKILL_T::ARC:
			{
				fTime += Time::fDeltaTime();
				Vector2 prevMPos = mPos;
				mPos.x = (mStPos.x - velocityX * fTime) /** Time::fDeltaTime()*/;
				mPos.y = (mStPos.y - velocityY * fTime - (0.5f * gravityAccel * fTime * fTime)) /** Time::fDeltaTime()*/;
				Vector2 diff = prevMPos - mPos;
				arcTheta = atan2(diff.y, diff.x);
			}
			break;
			case SKILL_T::ST:
			{
				mPos.x += 500.f * Missile_vec.x * Time::fDeltaTime();
				mPos.y += 500.f * Missile_vec.y * Time::fDeltaTime();
			}
			break;
			case SKILL_T::END:
			{

			}
			break;
			default:
				break;
			}
			CalEndFire();
			SetPos(mPos);

			if (endFire)
			{
				object::Invisible(this);
			}
		}
		
	}
	void Skill::ReInit(Vector2 stPos, Vector2 enPos)
	{
		Scene* scene = SceneManager::GetActiveScene();
		SetEndCoord(enPos);

		SetPos(scene->GetPosTiles()[(int)stPos.y][(int)stPos.x]->GetCenterPos());
		SetStPos(GetPos());
		SetEndPos(scene->GetPosTiles()[(int)enPos.y][(int)enPos.x]->GetCenterPos());

		this->Initialize();
	}
	void Skill::Active(HDC hdc)
	{
		switch (mType)
		{
		case SKILL_T::ARC:
		{
			Vector2 mPos = GetPos();
			Image* im = Resources::Load<Image>(L"missile", L"..\\Resources\\texture\\effect\\shotup_tribomb_missile_L.bmp");

			bitmap::RotateBitmap(hdc, mPos, im->GetBitmap(),
				arcTheta, im->GetHdc());
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
	void Skill::GuideWire(HDC hdc)
	{
		Vector2 mPos = mStPos;
		Image* im = Resources::Load<Image>(L"line", L"..\\Resources\\texture\\combat\\artillery_dot.bmp");
		
		switch (mType)
		{
		case SKILL_T::ARC:
		{
			float len = (mFinalEdPos - mStPos).Length() / im->GetWidth();
			float ft = 0;
			float mh = (100.f - min(mStPos.y, mFinalEdPos.y));
			float tg = 3.5f * mh * 1.f * 1.f;

			float _vy = sqrtf(2.f * mh * tg);
			float _fh = mFinalEdPos.y - mStPos.y;
			float a = tg;

			// 속도 == 최고 높이에서 떨어지는 값.
			// 반절짜리 라서 2를 곱함.
			float b = -2 * _vy;
			float c = 2 * _fh;

			// 고도각
			// 근의 공식에 따라 두개의 (-, +)x가 나옴.
			float _theta = (-b + sqrtf(b * b - 4.f * a * c)) / (2.f * a);

			float _vx = -(mStPos.x - mFinalEdPos.x) / maxTheta;
			for (; ft <= 1.f; ft += 0.1f)
			{
				//mPos.x = (mStPos.x - velocityX * fTime) /** Time::fDeltaTime()*/;
				//mPos.y = (mStPos.y - velocityY * fTime - (0.5f * gravityAccel * fTime * fTime)) /** Time::fDeltaTime()*/;

				mPos.x = mStPos.x - _vx * ft;
				mPos.y = mStPos.y - _vy * ft - (0.5f * tg * ft * ft);

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
			
		}
			break;
		case SKILL_T::ST:
		{
			int len = fDistance / im->GetWidth();
			for (int i = 0; i < len; i++)
			{
				mPos.x += Missile_vec.x * im->GetWidth() * 2;
				mPos.y += Missile_vec.y * im->GetHeight() * 2;

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
		}
			break;
		default:
			break;
		}
		

	}
	void Skill::Render(HDC hdc) {
		if (!startRender) return;
		if (endFire) stFire = false;
		if (stFire)
		{
			Active(hdc);
		}
		else
		{
			GuideWire(hdc);
		}
	}
	void Skill::Release() {
	}
}