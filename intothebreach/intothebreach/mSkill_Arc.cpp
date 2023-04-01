#include "mSkill_Arc.h"
#include "mTime.h"
#include "mResources.h"
#include "mUnit.h"
#include "mImage.h"
#include "func.h"
namespace m
{
	Skill_Arc::Skill_Arc(SKILL_T _type, Unit* onwer)
		: Skill(_type, onwer)
	{
	}
	Skill_Arc::~Skill_Arc()
	{
	}
	void Skill_Arc::Initialize()
	{
		object::Visible(this);
		fTime = 0.f;
		fMaxTime = 0.4f;
		fDistance = (mFinalEdPos - mStPos).Length();
		//fDistance = (mStPos - mFinalEdPos).Length();
		offsetHeight = mFinalEdPos.y - mStPos.y;
		//fHeight = max(mStPos.y, mFinalEdPos.y) - min(mStPos.y, mFinalEdPos.y);

		fHeight = 100.f - mStPos.y;
		gravityAccel = 2 * fHeight / (fMaxTime * fMaxTime);
		velocityY = sqrtf(2.f * fHeight * gravityAccel);

		float a = gravityAccel;
		float b = -2 * velocityY;
		float c = offsetHeight;

		maxTheta = (-b + sqrtf(b * b - 4 * a * c)) / (2 * a);
		minTheta = (-b - sqrtf(b * b - 4 * a * c)) / (2 * a);

		velocityX = -(mStPos.x - mFinalEdPos.x) / maxTheta;

		Missile_vec = mFinalEdPos - mStPos;

		m_fMissile_distance = Missile_vec.Length();
		Missile_vec.Normalize();

		curPos = mStPos;

		arcXMaxTime = 0.5f;
		arcYMaxTime = 1.f;
		maxHeight = 25.f;
	}
	void Skill_Arc::Update()
	{
		Skill::Update();
		Vector2 mPos = GetPos();
		Vector2 mPos2 = curPos;
		if (startFire)
		{
			fTime += Time::fDeltaTime();
			Vector2 prevMPos = mPos2;
			mPos2.x = mStPos.x - (velocityX * fTime);
			mPos2.y = mStPos.y - (velocityY * fTime) - (0.5f * gravityAccel * fTime * fTime);
			Vector2 diff = prevMPos - mPos2;
			arcTheta = atan2(diff.y, diff.x);

			float d = m_fMissile_distance;
			float vX = (d / arcXMaxTime);
			float vY = (d / arcYMaxTime);
			mPos.x += vX * Missile_vec.x * Time::fDeltaTime();
			mPos.y += vX * Missile_vec.y * Time::fDeltaTime();
		}
		CalEndFire();
		SetPos(mPos);

		if (endFire)
		{
			object::Invisible(this);
		}
	}
	void Skill_Arc::Render(HDC hdc)
	{
		if (!startRender) return;
		if (endFire) startFire = false;
		if (startFire)
		{
			Active(hdc);
		}
		else
		{
			GuideWire(hdc);
		}
	}
	void Skill_Arc::Release()
	{
	}
	void Skill_Arc::ReInit(Vector2 stPos, Vector2 enPos)
	{
		Skill::ReInit(stPos, enPos);
		this->Initialize();
	}
	void Skill_Arc::Active(HDC hdc)
	{
		Vector2 mPos = GetPos();
		Image* im = Resources::Load<Image>(L"missile", L"..\\Resources\\texture\\effect\\shotup_tribomb_missile_L.bmp");

		bitmap::RotateBitmap(hdc, mPos, im->GetBitmap(),
			arcTheta, im->GetHdc());
	}
	void Skill_Arc::GuideWire(HDC hdc)
	{
		Vector2 mPos = GetPos();
		Image* im = Resources::Load<Image>(L"line", L"..\\Resources\\texture\\combat\\artillery_dot.bmp");

		int len = (int)(mFinalEdPos - mStPos).Length() / im->GetWidth() / 2;
		float t = 0;
		for (int i = 0; i < len; i++)
		{
			mPos.x = mStPos.x - (velocityX * t);
			mPos.y = mStPos.y - (velocityY * t) - (0.5f * gravityAccel * t * t);

			t += 0.04f;

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


		//Vector2 vv = mStPos - mFinalEdPos;
		//vv.Normalize();
		//theta = atan2(vv.y, vv.x);

		//Vector2 vec = mStPos;
		//float absD = abs(mFinalEdPos.x - mStPos.x);
		//float absMD = abs(vec.x - mStPos.x);
		//float diff = absD - absMD;

		//float t = 0.f;
		//while (diff > 0)
		//{
		//	t += 0.01f;
		//	//mPos.x = mStPos.x - (velocityX * t);
		//	//mPos.y = mStPos.y - (velocityY * t) - (0.5f * gravityAccel * t * t);
		//	mPos.x -= 500.f * cosf(theta) * t;
		//	mPos.y -= 500.f * sinf(theta) * t;

		//	TransparentBlt(hdc,
		//		(int)(mPos.x),
		//		(int)(mPos.y),
		//		(int)(im->GetWidth() * 2),
		//		(int)(im->GetHeight() * 2),
		//		im->GetHdc(),
		//		0, 0,
		//		im->GetWidth(),
		//		im->GetHeight(),
		//		RGB(255, 0, 255));

		//	vec = Vector2(mPos.x, mPos.y);
		//	absD = abs(mFinalEdPos.x - mStPos.x);
		//	absMD = abs(vec.x - mStPos.x);
		//	diff = absD - absMD;
		//}
		int direct[4][2] = { {0, 1},{-1, 0} ,{1, 0},{0, -1} };
		Skill::DrawPushTile(direct, 4);
	}
	void Skill_Arc::CheckDirection()
	{
		Vector2 pos = GetPos();
		Scene* scene = SceneManager::GetActiveScene();
		// right, up, down, left
		int direct[4][2] = { {0, 1},{-1, 0} ,{1, 0},{0, -1} };
		if (endFire && scene->GetEffectUnit((int)GetEndCoord().y, (int)GetEndCoord().x).size() != 0)
		{
			for (int i = 0; i < scene->GetEffectUnit((int)GetEndCoord().y, (int)GetEndCoord().x).size(); i++)
			{
				scene->GetEffectUnit((int)GetEndCoord().y, (int)GetEndCoord().x)[i]->Hit(1);
			}
			
			SetEndFire(false);
			SetStartFire(false);
			PushUnit(direct, 4);
		}
		else if (endFire)
		{
			SetEndFire(false);
			SetStartFire(false);
			PushUnit(direct, 4);
		}
	}
}