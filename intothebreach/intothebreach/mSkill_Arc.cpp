#include "mSkill_Arc.h"
#include "mTime.h"
#include "mResources.h"
#include "mBackground.h"
#include "mUnit.h"
#include "mImage.h"
#include "func.h"
#include "mApplication.h"
extern m::Application application;
namespace m
{
	Skill_Arc::Skill_Arc(WEAPON_T _type, Unit* onwer)
		: Skill(_type, onwer)
	{
	}
	Skill_Arc::~Skill_Arc()
	{
	}
	void Skill_Arc::Initialize()
	{
		object::DestoryUnitVector<Background*>(smokeVector);
		//object::Visible(this);
		fTime = 0.f;
		fMaxTime = 0.4f;
		fDistance = (mFinalEdPos - mStPos).Length();
		//fDistance = (mStPos - mFinalEdPos).Length();
		offsetHeight = mFinalEdPos.y - mStPos.y;
		//fHeight = max(mStPos.y, mFinalEdPos.y) - min(mStPos.y, mFinalEdPos.y);
		//fHeight = mStPos.y;
		//fHeight -= 100.f;

		//if(mStPos.y )
		fHeight = 100.f - mStPos.y;

		if (fHeight > 0) fHeight *= -1;
		/*if (fHeight > 0) */
		//else fHeight += 100.f;
		//fHeight *= -1;
 			gravityAccel = 2 * fHeight / (fMaxTime * fMaxTime);
		velocityY = sqrtf(2.f * fHeight * gravityAccel);
		float a = gravityAccel;
		float b = -2 * velocityY;
		float c = 2 * offsetHeight;
		maxTheta = (-b + sqrtf(b * b - 4 * a * c)) / (2 * a);
		minTheta = (-b - sqrtf(b * b - 4 * a * c)) / (2 * a);
		velocityX = -(mStPos.x - mFinalEdPos.x) / maxTheta;

		//Vector2 diff = mFinalEdPos - mStPos;
		//fDistance = diff.Length();
		//Missile_vec = mFinalEdPos - mStPos;
		//Missile_vec.Normalize();

	}
	void Skill_Arc::Update()
	{
		Skill::Update();
		Vector2 mPos = GetPos();
		
		if (startFire)
		{
			fTime += Time::fDeltaTime();
			Vector2 prevMPos = mPos;
			mPos.x = (mStPos.x - velocityX * fTime);
			mPos.y = (mStPos.y - velocityY * fTime - (0.5f * gravityAccel * fTime * fTime));
			Vector2 diff = prevMPos - mPos;
			DrawSmoke();
			arcTheta = atan2(diff.y, diff.x);
			//mPos.x += 500.f * Missile_vec.x * Time::fDeltaTime();
			//mPos.y += 500.f * Missile_vec.y * Time::fDeltaTime();
		}
		CalEndFire();
		SetPos(mPos);

		if (endFire)
		{
			//object::Invisible(this);
		}
	}
	void Skill_Arc::Render(HDC hdc)
	{
		Skill::Render(hdc);
		if (endFire)
		{
			startFire = false;
			endFire = false;
			startRender = false;
		}
		if (!startRender) return;
		if (startFire)
		{
			Active(hdc);
		}
		else
		{
			GuideWire(hdc);
		}
	}
	void Skill_Arc::DrawSmoke()
	{
		//Image* im = Resources::Load<Image>(MAKE_EFFECT_KEY(SINGLE_EFFECT_T::ar_s), MAKE_EFFECT_PATH(SINGLE_EFFECT_T::ar_s));
		//smokeVector.push_back(im);
		int c = rand() % 4;
		Background* smoke = new Background(
			MAKE_EFFECT_KEY(SINGLE_EFFECT_T::ar_s, c),
			MAKE_EFFECT_PATH(SINGLE_EFFECT_T::ar_s, c),
		2);

		smoke->SetCutPos(true);
		smoke->SetAlpha(true);
		float randConstant = (float)(rand() % 255) + 125;
		smoke->SetAlphaConstant((int)randConstant);
		float randX = GetPos().x - (rand() % 50);
		float randY = GetPos().y - (rand() % 50);
		
		smoke->SetPos(Vector2(randX, randY));
		int randDegree = rand() % 360;
		int randTheta = (int)(randDegree * PI / 180.f);
		//bitmap::RotateBitmap(application.GetHdc(), smoke->GetPos(), smoke->GetImage()->GetBitmap(), randTheta, smoke->GetImage()->GetHdc());

		float randDirX = (float)(rand() % 255);
		float randDirY = (float)(rand() % 255);
		Vector2 dir = Vector2(randDirX, randDirY);

		smoke->SetMovement(dir);
		
		smokeVector.push_back(smoke);
		SceneManager::GetActiveScene()->AddGameObject(smoke, LAYER_TYPE::UI);
	}
	void Skill_Arc::Release()
	{
	}
	void Skill_Arc::ReInit(Vector2 stPos, Vector2 enPos, Vector2 glp, SKILL_T type)
	{
		Skill::ReInit(stPos, enPos, glp, type);
		this->Initialize();
	}
	void Skill_Arc::Active(HDC hdc)
	{
		Vector2 mPos = GetPos();
		Image* im = Resources::Load<Image>(MAKE_SKILL_KEY(mWeaponType, SKILL_DIR::NONE), MAKE_SKILL_PATH(mWeaponType, SKILL_DIR::NONE));
		//Image* im = Resources::Load<Image>(L"missile", L"..\\Resources\\texture\\effect\\shotup_tribomb_missile_L.bmp");

		bitmap::RotateBitmap(hdc, mPos, im->GetBitmap(),
			arcTheta, im->GetHdc());
	}
	void Skill_Arc::GuideWire(HDC hdc)
	{
		Vector2 mPos = mStPos;
		Image* im = Resources::Load<Image>(L"dot", L"..\\Resources\\texture\\combat\\artillery_dot.bmp");

		Vector2 vec = mStPos;
		float absD = abs(mFinalEdPos.x - mStPos.x);
		float absMD = abs(vec.x - mStPos.x);
		float diff = absD - absMD;
		float len = (mFinalEdPos - mStPos).Length() / im->GetWidth() / 2.f;
		float t = fMaxTime / len;
		while (diff > 0)
		{
			mPos.x = (mStPos.x - velocityX * t);
			mPos.y = (mStPos.y - velocityY * t - (0.5f * gravityAccel * t * t));
			t += fMaxTime / len;
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
			vec = Vector2(mPos.x, mPos.y);
			absD = abs(mFinalEdPos.x - mStPos.x);
			absMD = abs(vec.x - mStPos.x);
			diff = absD - absMD;
		}

		//float diff = (mFinalEdPos - mStPos).Length();
		//float len = diff / im->GetWidth() / 2.f;
		////m_curTime += sqrt(Missile_vec.x * Missile_vec.x + Missile_vec.y * Missile_vec.y)
		////	* 500.f * im->GetWidth() * 2.f;
		//m_curTime = 0;
		////if (endCoord == guideLineCoord) (int)len == 3 ? len = 2 : 0;
		//for (int i = 0; i < (int)len; i++)
		//{
		//	m_curTime += fDistance / im->GetWidth() * 2.f;
		//	m_curZ = (-m_curTime * m_curTime + fDistance * m_curTime);
		//	mPos.x += Missile_vec.x * im->GetWidth() * 2.f;
		//	//mPos.y = m_curZ / fDistance;
		//	mPos.y += Missile_vec.y * im->GetHeight() * 2.f;
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
		//}


		//int direct[4][2] = { {0, 1},{-1, 0} ,{1, 0},{0, -1} };
		ARROW_TILE_T arrows[4] = {ARROW_TILE_T::arrow_right, ARROW_TILE_T::arrow_up,
			ARROW_TILE_T::arrow_down, ARROW_TILE_T::arrow_left};
		//Skill::DrawPushTile(direct, 4);
		Skill::DrawPushTile(arrows, 4);
	}
	void Skill_Arc::CheckDirection()
	{
		Skill::CheckDirection();
		Vector2 pos = GetPos();
		Scene* scene = SceneManager::GetActiveScene();
		//int direct[4][2] = { {0, 1},{-1, 0} ,{1, 0},{0, -1} };
		if (endFire && scene->SearchAffectUnit((int)GetEndCoord().y, (int)GetEndCoord().x))
		{
			//for (int i = 0; i < scene->GetEffectUnit((int)GetEndCoord().y, (int)GetEndCoord().x).size(); i++)
			//{
			//	scene->GetEffectUnit((int)GetEndCoord().y, (int)GetEndCoord().x)[i]->Hit(1);
			//}
			scene->HitAffectUnit((int)GetEndCoord().y, (int)GetEndCoord().x, 1);
			
			SetEndFire(false);
			SetStartFire(false);
			ImpactSound();
			if (WEAPON_PUSH_DIR[(UINT)mOwner->GetWeaponType()] != 0)
			{
				ARROW_TILE_T arrows[4] = { ARROW_TILE_T::arrow_right, ARROW_TILE_T::arrow_up,
				ARROW_TILE_T::arrow_down, ARROW_TILE_T::arrow_left };
				PushUnit(arrows, 4);
			}
		}
		else if (endFire)
		{
			SetEndFire(false);
			SetStartFire(false);
			ImpactSound();
			ARROW_TILE_T arrows[4] = { ARROW_TILE_T::arrow_right, ARROW_TILE_T::arrow_up,
			ARROW_TILE_T::arrow_down, ARROW_TILE_T::arrow_left };
			PushUnit(arrows, 4);
		}
	}
}