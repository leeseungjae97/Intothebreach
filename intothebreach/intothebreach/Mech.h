#pragma once
#include "mGameObject.h"
#include "mImage.h"
namespace m
{
	class Weapon;
	class Pilot;
	class Skill;
	class Animator;
	class Mech : public GameObject
	{
	public:
		enum class MECH_STATE {
			Idle,
			Broken,
			Water,
			End,
		};
		Mech(MECHS _mech);
		~Mech();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		//TODO : ¹«±â, ÆÄÀÏ·µ

		void SetSkill();
		void ChangePilotSlot();
		Weapon* ChangeWeaponSlot(int index);

		void SetCoord(Vector2 _coord) { mCoord = _coord; }
		void SetFinalPos(Vector2 _pos) { mFinalPos = _pos; }
		void SetFinalCoord(Vector2 _coord) { mFinalCoord = _coord; }

		Vector2 GetFinalPos() { return mFinalPos; }
		Vector2 GetCoord() { return mCoord; }
		Vector2 GetFinalCoord() { return mFinalCoord; }

		CLONE(Mech);

	private:
		void idle();
		void broken();
		void water();

	private:
		MECHS mMechType;
		Animator* mAnimator;
		MECH_STATE mState;
		Image* curImage;

		Vector2 mCoord;

		Vector2 mFinalCoord;
		Vector2 mFinalPos;

		Weapon* mWeapon;
		Pilot* mPilot;
		vector<Skill*> mSkills;
		vector<Image*> mImages;
	};
}
