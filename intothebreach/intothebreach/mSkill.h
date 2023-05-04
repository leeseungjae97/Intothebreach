#pragma once
#include "mGameObject.h"
namespace m
{
	class Animator;
	class Sound;
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
		void DrawSkillEffect();
		void DrawPushTile(ARROW_TILE_T *arrows, int size);
		void ClearPushTile();
		void SetEndCoord(Vector2 _coord) { endCoord = _coord; }
		virtual void CalEndFire();

		Unit* GetOwner() { return mOwner; }
		LAYER_TYPE GetButtonType() { return mLayerType; }
		SKILL_T GetSkillType() { return mType; }
		WEAPON_T GetWeaponType() { return mWeaponType; }
		Vector2 GetEndPos() { return mFinalEdPos; }
		Vector2 GetGuideLinePos() { return guideLinePos; }
		Vector2 GetGuideLineCoord() { return guideLineCoord; }
		virtual Vector2 GetEndCoord() { return endCoord; }
		Animator* GetAnimator() { return mAnimator; }

		virtual bool GetStartFire(){return startFire;}
		virtual bool GetEndFire(){return endFire;}
		virtual bool GetStartRender() { return startRender; }
		bool CheckSkillFiring();
		int GetSkillDir() { return iDir; }

		void SetWeaponType(WEAPON_T _type) { mWeaponType = _type; }

		virtual void SetEndFire(bool _endFire) { endFire = _endFire; }
		virtual void SetStartFire(bool _stFire) { startFire = _stFire; }
		virtual void SetStartRender(bool _sR) { startRender = _sR; }

		void SetButtonType(LAYER_TYPE _type) { mLayerType = _type; }
		void SetSkillType(SKILL_T _type) { mType = _type; }
		void SetRealPos(Vector2 _pos) { ; }
		void SetEndPos(Vector2 _pos) { mFinalEdPos = _pos; }
		void SetStPos(Vector2 _pos) { mStPos = _pos; }
		void SetGuideLinePos(Vector2 _glp) { guideLinePos = _glp; }
		void SetGuideLineCoord(Vector2 _glc) { guideLineCoord = _glc; }
		void LaunchSound();
		void ImpactSound();
		//void SetOppsite(bool _b) { bOppsite = _b; }
		//void SetOppsiteDraw(Vector2 _coord, Vector2 guideCoord);
		void Clear();

	protected:
		float GRAVITY = 9.81f * 0.1f;

		bool endFire;
		bool startFire;
		bool startRender;
		bool bOppsite;

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
		int pIDir;

		Animator* mAnimator;
		LAYER_TYPE mLayerType;
		SKILL_T mType;
		WEAPON_T mWeaponType;
		Unit* mOwner;
		Vector2 guideLinePos;
		Vector2 guideLineCoord;
		Vector2 Missile_vec;
		Vector2 Missile_vec2;
		Vector2 endCoord;
		Vector2 mStPos;
		Vector2 mFinalEdPos;

		Vector2 opPos;
		Vector2 opEndCoord;
		Vector2 opEndPos;
		Vector2 opGuideEndCoord;
		Vector2 opMissile_vec;
		
		Sound* launchSound;
		bool launchSoundPlayed;
		Sound* impactSound;
		bool impactSoundPlayed;
	};
}

