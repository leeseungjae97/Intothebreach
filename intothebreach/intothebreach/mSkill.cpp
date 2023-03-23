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
		, endFire(false)
		, fTime(0)
	{
		AddComponent(new Transform);
		AddComponent(new Animator);
	}
	Skill::Skill(Skill& _origin) {
	}
	Skill::Skill() 
		: endFire(false)
	{
		AddComponent(new Transform);
		AddComponent(new Animator);
	}
	Skill::~Skill() {
	}
	void Skill::Initialize() {
		
	}
	void Skill::CalEndFire() {
		Vector2 vec = GetPos();
		float absD = abs(mFinalEdPos.x - mStPos.x);
		float absMD = abs(vec.x - mStPos.x);
		float diff = absD - absMD;

		absD - absMD <= 0.f ? endFire = true : endFire = false;
	}
	void Skill::PreCal() {
		//object::Restore(this);

		Missile_vec = mFinalEdPos - mStPos;

		m_fMissile_distance = Missile_vec.Length();

		fMaxTime = 0.5f;

		offsetHeight = mFinalEdPos.y - mStPos.y;
		fHeight = 100.f - min(mStPos.y, mFinalEdPos.y);


		// ���Ͽ� �ɸ��� �ð�
		// ������ �߷°��ӵ� = 2 * �Ÿ� / �ð�^2
		gravityAccel = 3.5f * fHeight / (fMaxTime * fMaxTime);

		// ���� ���� �ð� == �ӵ�
		velocityY =sqrtf(2.f * fHeight * gravityAccel);

		float a = gravityAccel;

		// �ӵ� == �ְ� ���̿��� �������� ��.
		// ����¥�� �� 2�� ����.
		float b = -2 * velocityY;
		float c = 2 * offsetHeight;

		// ����
		// ���� ���Ŀ� ���� �ΰ��� (-, +)x�� ����.
		maxTheta = (-b + sqrtf(b * b - 4.f * a * c)) / (2.f * a);
		minTheta = (-b - sqrtf(b * b - 4.f * a * c)) / (2.f * a);

		// x�� �ӵ�
		// �ӵ� = �Ÿ� / ����.
		velocityX = -(mStPos.x - mFinalEdPos.x) / maxTheta;
	}
	void Skill::Update() {
		GameObject::Update();
		Vector2 mPos = GetPos();
		switch (mType) {
		case SKILL_T::ARC:
		{
			fTime += Time::fDeltaTime();
			prevMPos = mPos;
			mPos.x = ( mStPos.x - velocityX * fTime) /** Time::fDeltaTime()*/;
			mPos.y = ( mStPos.y - velocityY * fTime - (0.5f * gravityAccel * fTime * fTime)) /** Time::fDeltaTime()*/;
			Vector2 diff = prevMPos - mPos;
			arcTheta = atan2(diff.y, diff.x);
		}
			break;
		case SKILL_T::ST:
		{
			float _theta = atan2(Missile_vec.y, Missile_vec.x);
			mPos.x += 500.f * cosf(_theta) * Time::fDeltaTime();
			mPos.y += 500.f * sinf(_theta) * Time::fDeltaTime();
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
		CalEndFire();
		SetPos(mPos);

		if (endFire) {
			object::Destory(this);
		}
	}
	void Skill::Render(HDC hdc) {
		switch (mType) {
		case SKILL_T::ARC:
		{
			Vector2 mPos = GetPos();
			Image* im = Resources::Load<Image>(L"missile", L"..\\Resources\\texture\\effect\\shotup_tribomb_missile_L.bmp");

			//float Dir;
			//if (Missile_vec.x > 0)	{Dir = 1;}
			//else					{Dir = -1;}
			
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
	void Skill::Release() {
	}
}