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
		Mech(MECHS _mech, Vector2 _coord, int _range);
		Mech(Mech& _origin);
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

		int GetFullHp() { return mHp; }
		int GetCurHp() { return curHp; }

		void Hit(int damage) { 
			if (curHp < damage) curHp = 0;
			else curHp -= damage;
		}
		void Repair(int repair) { 
			if (curHp + repair < mHp) curHp = mHp;
			else curHp += repair; 
		}
		int GetMove() { return moveRange; }
		void SetMove(int _move) { moveRange = _move; }


	private:
		void idle();
		void broken();
		void water();

	private:
		MECHS mMechType;
		Animator* mAnimator;
		Image* curImage; 
		STATE mState;
		vector<Image*> hpBar;

		Vector2 mCoord;

		Vector2 mFinalCoord;
		Vector2 mFinalPos;

		int mHp;
		int curHp;
		int moveRange;

		bool endMove;
		bool endAttack;

		Weapon* mWeapon;
		Pilot* mPilot;
		vector<Skill*> mSkills;
		vector<Image*> mImages;
	};
}
