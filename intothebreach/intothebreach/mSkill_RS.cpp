#include "mSkill_RS.h"
#include "mUnit.h"
#include "mResources.h"
#include "mAnimator.h"
#include "Mech.h"
#include "Alien.h"
#include "mSceneManager.h"
#include "mScene.h"
#include "mTime.h"

namespace m
{
	Skill_RS::Skill_RS(WEAPON_T _type, Unit* owner)
		:Skill(_type, owner)
	{
	}
	Skill_RS::~Skill_RS()
	{}
	void Skill_RS::Initialize()
	{
		Vector2 diff = mFinalEdPos - mStPos;
		fDistance = diff.Length();
		Missile_vec = mFinalEdPos - mStPos;
		Missile_vec.Normalize();
	}
	void Skill_RS::Update()
	{
		Skill::Update();
		Vector2 mPos = GetPos();
		CalEndFire();

		if (startFire)
		{
			mPos.x += 500.f * Missile_vec.x * Time::fDeltaTime();
			mPos.y += 500.f * Missile_vec.y * Time::fDeltaTime();
		}
		SetPos(mPos);
	}
	void Skill_RS::Render(HDC hdc)
	{
		Skill::Render(hdc);
		if (endFire)
		{
			startFire = false;
			//endFire = false;
			//startRender = false;
			//object::Invisible(this);
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
	void Skill_RS::Release()
	{}
	void Skill_RS::ReInit(Vector2 stPos, Vector2 enPos, Vector2 glp, SKILL_T type)
	{
		Skill::ReInit(stPos, enPos, glp, type);
		this->Initialize();
	}
	void Skill_RS::Active(HDC hdc)
	{
		Vector2 mPos = GetPos();

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

		//WEAPON_T nn = mWeaponType;

		//if (nullptr == GetAnimator()->FindAnimation(MAKE_SKILL_KEY(WEAPON_T::titan_fist, dir)))
		//{
		//	Image* im = Resources::Load<Image>(MAKE_SKILL_KEY(WEAPON_T::titan_fist, dir), MAKE_SKILL_PATH(WEAPON_T::titan_fist, dir));
		//	float fWid = (float)(im->GetWidth() / WEAPON_LEN[(UINT)WEAPON_T::titan_fist]);

		//	GetAnimator()->CreateAnimation(
		//		MAKE_SKILL_KEY(WEAPON_T::titan_fist, dir),
		//		im,
		//		Vector2::Zero,
		//		Vector2(fWid, (float)im->GetHeight()),
		//		Vector2::Zero,
		//		WEAPON_LEN[(UINT)mType],
		//		0.5f,
		//		AC_SRC_OVER
		//	);
		//}
		//if(GetAnimator()->GetStopAnimator())
		//	GetAnimator()->Play(MAKE_SKILL_KEY(WEAPON_T::titan_fist, dir), false);
		//GetAnimator()->SetConstant(255);
		//if (nullptr == GetAnimator()->FindAnimation(MAKE_SKILL_KEY(WEAPON_T::titan_fist, dir)))
		//{
		//	UINT len = WEAPON_LEN[(UINT)WEAPON_T::titan_fist];

		//	Image* im = Resources::Load<Image>(MAKE_SKILL_KEY(WEAPON_T::titan_fist, dir)
		//		, MAKE_SKILL_PATH(WEAPON_T::titan_fist, dir));

		//	float fWid = (float)im->GetWidth() / len;
		//	float fHei = (float)im->GetHeight();

		//	GetAnimator()->CreateAnimation(
		//		MAKE_SKILL_KEY(WEAPON_T::titan_fist, dir)
		//		, im
		//		, Vector2::Zero
		//		, Vector2(fWid, fHei)
		//		, Vector2::Zero
		//		, len
		//		, 0.1f
		//		, AC_SRC_OVER
		//	);
		//}
		//if (GetAnimator()->GetStopAnimator())
		//	GetAnimator()->Play(MAKE_SKILL_KEY(WEAPON_T::titan_fist, dir), true);
	}
	void Skill_RS::GuideWire(HDC hdc)
	{
		Scene* scene = SceneManager::GetActiveScene();

		ARROW_TILE_T arrow[1];
		if (mOwner->GetCoord().y < guideLineCoord.y)arrow[0] = ARROW_TILE_T::arrow_down;
		if (mOwner->GetCoord().y > guideLineCoord.y)arrow[0] = ARROW_TILE_T::arrow_up;
		if (mOwner->GetCoord().x < guideLineCoord.x)arrow[0] = ARROW_TILE_T::arrow_right;
		if (mOwner->GetCoord().x > guideLineCoord.x)arrow[0] = ARROW_TILE_T::arrow_left;

		Skill::DrawPushTile(arrow, WEAPON_PUSH_DIR[(UINT)mOwner->GetWeaponType()]);
	}
	void Skill_RS::CheckDirection()
	{
		HitEffectDir();
		Scene* scene = SceneManager::GetActiveScene();

		scene->HitAffectUnit((int)guideLineCoord.y, (int)guideLineCoord.x, 1);

		SetEndFire(false);
		SetStartFire(false);
		SetStartRender(false);


		ARROW_TILE_T arrow[1] = { (ARROW_TILE_T)iDir };
		PushUnit(arrow, WEAPON_PUSH_DIR[(UINT)mOwner->GetWeaponType()]);

		//if (WEAPON_PUSH_DIR[(UINT)mOwner->GetWeaponType()] != 0)
		//{

		//}else 
			
		return;
	}
}