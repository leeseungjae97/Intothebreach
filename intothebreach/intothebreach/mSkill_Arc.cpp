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

		fHeight = mStPos.y;
		fHeight -= 100.f;
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
	}
	void Skill_Arc::Update()
	{
		if (mOnwer->GetState() == GameObject::STATE::Death
			||
			mOnwer->GetState() == GameObject::STATE::Invisible
			||
			mOnwer->GetState() == GameObject::STATE::Broken) return;
		Skill::Update();
		Vector2 mPos = GetPos();
		
		if (startFire)
		{
			fTime += Time::fDeltaTime();
			Vector2 prevMPos = mPos;
			mPos.x = (mStPos.x - velocityX * fTime);
			mPos.y = (mStPos.y - velocityY * fTime - (0.5f * gravityAccel * fTime * fTime));
			Vector2 diff = prevMPos - mPos;
			arcTheta = atan2(diff.y, diff.x);
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
		if (mOnwer->GetState() == GameObject::STATE::Death
			||
			mOnwer->GetState() == GameObject::STATE::Invisible
			||
			mOnwer->GetState() == GameObject::STATE::Broken) return;
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
	void Skill_Arc::ReInit(Vector2 stPos, Vector2 enPos, Vector2 glp, SKILL_T type)
	{
		if (mOnwer->GetState() == GameObject::STATE::Death
			||
			mOnwer->GetState() == GameObject::STATE::Invisible
			||
			mOnwer->GetState() == GameObject::STATE::Broken) return;
		Skill::ReInit(stPos, enPos, glp, type);
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

		int direct[4][2] = { {0, 1},{-1, 0} ,{1, 0},{0, -1} };
		ARROW_TILE_T arrows[4] = {ARROW_TILE_T::arrow_right, ARROW_TILE_T::arrow_down
			, ARROW_TILE_T::arrow_up, ARROW_TILE_T::arrow_left};
		//Skill::DrawPushTile(direct, 4);
		Skill::DrawPushTile(arrows, 4);
	}
	void Skill_Arc::CheckDirection()
	{
		Vector2 pos = GetPos();
		Scene* scene = SceneManager::GetActiveScene();
		// right, up, down, left
		//int direct[4][2] = { {0, 1},{-1, 0} ,{1, 0},{0, -1} };
		ARROW_TILE_T arrows[4] = { ARROW_TILE_T::arrow_right, ARROW_TILE_T::arrow_down
			, ARROW_TILE_T::arrow_up, ARROW_TILE_T::arrow_left };
		if (endFire && scene->GetEffectUnit((int)GetEndCoord().y, (int)GetEndCoord().x) != nullptr)
		{
			//for (int i = 0; i < scene->GetEffectUnit((int)GetEndCoord().y, (int)GetEndCoord().x).size(); i++)
			//{
			//	scene->GetEffectUnit((int)GetEndCoord().y, (int)GetEndCoord().x)[i]->Hit(1);
			//}
			scene->GetEffectUnit((int)GetEndCoord().y, (int)GetEndCoord().x)->Hit(1);
			
			SetEndFire(false);
			SetStartFire(false);
			PushUnit(arrows, 4);
		}
		else if (endFire)
		{
			SetEndFire(false);
			SetStartFire(false);
			PushUnit(arrows, 4);
		}
	}
}