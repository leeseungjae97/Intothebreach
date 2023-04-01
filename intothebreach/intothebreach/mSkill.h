#pragma once
#include "mGameObject.h"
namespace m
{
	class Skill :
		public GameObject
	{
	public:
		Skill(SKILL_T _type, Unit* onwer);
		Skill(Skill& _origin);
		~Skill();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void ReInit(Vector2 stPos, Vector2 enPos);
		virtual void Active(HDC hdc);
		virtual void GuideWire(HDC hdc);
		virtual void PushUnit(int(*direct)[2], int size);
		virtual void CheckDirection();
		
		void DrawPushTile(int (*direct)[2], int size);
		void ClearPushTile();
		Vector2 GetEndCoord() { return endCoord; }
		void SetEndCoord(Vector2 _coord) { endCoord = _coord; }
		void CalEndFire();
		Unit* GetOwner() { return mOnwer; }

		LAYER_TYPE GetLayerType() { return mLayerType; }
		SKILL_T GetSkillType() { return mType; }
		Vector2 GetEndPos() { return mFinalEdPos; }
		bool GetEndFire()
		{
			return endFire;
		}
		bool GetStartFire()
		{
			return startFire;
		}
		bool GetStartRender() { 
			return startRender; 
		}
		bool CheckSkillFiring();
		void SetLayerType(LAYER_TYPE _type) { mLayerType = _type; }
		void SetSkillType(SKILL_T _type) { mType = _type; }
		void SetRealPos(Vector2 _pos) { ; }
		void SetEndPos(Vector2 _pos) { mFinalEdPos = _pos; }
		void SetStPos(Vector2 _pos) { mStPos = _pos; }
		void SetEndFire(bool _endFire) { endFire = _endFire; }
		void SetStartFire(bool _stFire) { 
			startFire = _stFire; 
		}
		void SetStartRender(bool _sR) { 
			if (!_sR) ClearPushTile();
			startRender = _sR; 
		}


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

		LAYER_TYPE mLayerType;
		SKILL_T mType;
		Unit* mOnwer;
		Vector2 Missile_vec;
		Vector2 Missile_vec2;
		Vector2 endCoord;
		Vector2 mStPos;
		Vector2 mFinalEdPos;
	};
}

