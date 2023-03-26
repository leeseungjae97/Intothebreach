#pragma once
#include "mGameObject.h"
namespace m
{
	class Weapon;
	class Image;
	class Pilot;
	class Skill;
	class Animator;
	class Unit :
		public GameObject
	{
	public:
		Unit(Vector2 _coord, int _range, int hp, int type);
		Unit(Unit& _origin);
		Unit();
		~Unit();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetSkill();
		void SetSkill(int type);
		void SetSkill(int idx, SKILL_T type);

		//SKILL_T GetSkill(int idx);
		Skill* GetSkill(int idx);

		void ChangePilotSlot();
		Weapon* ChangeWeaponSlot(int index);

		void SetCoord(Vector2 _coord) { mCoord = _coord; }
		void SetFinalPos(Vector2 _pos) { mFinalPos = _pos; }
		void SetFinalCoord(Vector2 _coord) { mFinalCoord = _coord; }
		void SetCurAttackSkill(Skill* weapon) { curAttactSkill = weapon; }
		void SetCurImage(Image* m) { curImage = m; }
		void SetLayerType(LAYER_TYPE _type) { lType = _type; }
		void SetMIdx(int _idx) { mIdx = _idx; }
		void SetMove(int _move) { moveRange = _move; }

		void Hit(int damage)
		{
			if (curHp < damage) curHp = 0;
			else curHp -= damage;
		}
		void Repair(int repair)
		{
			if (curHp + repair < mHp) curHp = mHp;
			else curHp += repair;
		}
		void DrawSkill(Vector2 pos, int idx);
		void SetHp(int _hp) { mHp = curHp = _hp; }
		int GetFullHp() { return mHp; }
		int GetCurHp() { return curHp; }
		int GetMIdx() { return mIdx; }
		int GetMove() { return moveRange; }
		
		vector<Image*>& GetMImages() { return mImages; }
		Animator* GetAnimator() { return mAnimator; }

		Image* GetCurImage() { return curImage; }
		
		LAYER_TYPE GetLayerType() { return lType; }

		Skill* GetCurAttackSkill() { return curAttactSkill; }
		Vector2 GetFinalPos() { 
			if (nullptr == this) return Vector2::Zero;
			return mFinalPos; 
		}
		Vector2 GetCoord() { 
			if (nullptr == this) return Vector2::Zero;
			return mCoord; 
		}
		Vector2 GetFinalCoord() { 
			if(nullptr == this) return Vector2::Zero; 
			return mFinalCoord; 
		}
		virtual void idle() = 0;
		virtual void broken() = 0;
		virtual void water() = 0;
		virtual void emerge() = 0;

	private:
		Animator* mAnimator;
		Image* curImage;
		Image* hpImage;
		Image* hpBack;
		vector<Image*> hpBar;
		LAYER_TYPE lType;

		Vector2 mCoord;

		Vector2 mFinalCoord;
		Vector2 mFinalPos;

		int mHp;
		int curHp;
		int moveRange;
		int mIdx;

		bool endMove;
		bool endAttack;

		Weapon* mWeapon;
		Pilot* mPilot;
		//vector<SKILL_T> mSkills;
		vector<Skill*> mSkills;
		Skill* curAttactSkill;
		vector<Image*> mImages;
	};
}


