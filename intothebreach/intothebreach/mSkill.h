#pragma once
#include "mGameObject.h"
namespace m
{
	class Skill :
		public GameObject
	{
	public:
		Skill(WEAPON_T _type, Unit* onwer);
		Skill(Skill& _origin);
		~Skill();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void ReInit(Vector2 stPos, Vector2 enPos, Vector2 glp, SKILL_T _type);
		virtual void Active(HDC hdc);
		virtual void GuideWire(HDC hdc);
		virtual void PushUnit(ARROW_TILE_T *arrows, int size);
		virtual void CheckDirection();
		virtual void HitEffectDir();

		//void DrawPushTile(int (*direct)[2], int size);
		void DrawPushTile(ARROW_TILE_T *arrows, int size);
		void ClearPushTile();
		void SetEndCoord(Vector2 _coord) { endCoord = _coord; }
		void CalEndFire();

		Unit* GetOwner() { return mOwner; }
		LAYER_TYPE GetLayerType() { return mLayerType; }
		SKILL_T GetSkillType() { return mSkillType; }
		Vector2 GetEndPos() { return mFinalEdPos; }
		Vector2 GetGuideLinePos() { return guideLinePos; }
		Vector2 GetGuideLineCoord() { return guideLineCoord; }
		Vector2 GetEndCoord() { return endCoord; }
		Animator* GetAnimator() { return mAnimator; }

		bool GetEndFire(){return endFire;}
		bool GetStartFire(){return startFire;}
		bool GetStartRender() { return startRender; }
		bool CheckSkillFiring();
		int GetSkillDir() { return iDir; }

		void SetLayerType(LAYER_TYPE _type) { mLayerType = _type; }
		void SetSkillType(SKILL_T _type) { mSkillType = _type; }
		void SetRealPos(Vector2 _pos) { ; }
		void SetEndPos(Vector2 _pos) { mFinalEdPos = _pos; }
		void SetStPos(Vector2 _pos) { mStPos = _pos; }
		void SetGuideLinePos(Vector2 _glp) { guideLinePos = _glp; }
		void SetGuideLineCoord(Vector2 _glc) { guideLineCoord = _glc; }
		void SetEndFire(bool _endFire) { endFire = _endFire; }
		void SetStartFire(bool _stFire) { startFire = _stFire; }
		void SetStartRender(bool _sR) { startRender = _sR; }


	protected:
		float GRAVITY = 9.81f * 0.1f;

		bool endFire;
		bool startFire;
		bool startRender;

		float offsetHeight;
		float maxTheta;
		float minTheta;
		float fHeight;
		float fMaxTime;
		float fTime;
		float velocityY;
		float velocityX;
		float gravityAccel;

		float fDistance;

		float arcTheta;
		float theta;

		int iDir;

		Animator* mAnimator;
		LAYER_TYPE mLayerType;
		SKILL_T mSkillType;
		WEAPON_T mWeaponType;
		Unit* mOwner;
		Vector2 guideLinePos;
		Vector2 guideLineCoord;
		Vector2 Missile_vec;
		Vector2 Missile_vec2;
		Vector2 endCoord;
		Vector2 mStPos;
		Vector2 mFinalEdPos;
	};
}

