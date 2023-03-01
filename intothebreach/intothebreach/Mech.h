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
		enum class eMechState {
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

		void SetSkill();
		void ChangePilotSlot();
		Weapon* ChangeWeaponSlot(int index);

	private:
		void idle();
		void broken();
		void water();

	private:
		MECHS mMechType;
		Animator* mAnimator;
		eMechState mState;
		Weapon* mWeapon;
		Pilot* mPilot;
		vector<Skill*> mSkills;
		vector<Image*> mImages;
		Image* curImage;
	};
}
