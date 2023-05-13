#pragma once
#include "_Engine.h"
namespace m {
	enum class CAMERA_EFFECT_TYPE {
		Fade_In,
		Fade_Out,
		Shake,
		None,
	};

	class GameObject;
	class Image;
	class Camera {
	public:
		struct EffectInfo {
			CAMERA_EFFECT_TYPE effect;
			float duration;
			float time;
			float increase;
		};
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		static void PushEffect(CAMERA_EFFECT_TYPE _effect, float _duration, int increase = 20);
		static Vector2 CalculatePos(Vector2 _pos) { return _pos - mDistance; }
		static void SetTarget(GameObject* _obj) { mTarget = _obj; }
		static Vector2 GetRealPos(Vector2 _vRenderPos) { return _vRenderPos + mDistance; }
		static void MoveCamera(Vector2 pos) { mLookPosition = pos; }
		static void CheckEffectEnd();
		static void SetMoveTime(float _time) { 
			m_fAcctime = 0;
			m_fTime = _time; 
		}
		static bool CheckCurPos(Vector2 pos)
		{
			if (pos == mCurLookPosition) return true;
			else return false;
		}
		static Vector2 GetCurPos() { return mCurLookPosition; }
		static void Release();
		static float GetShakeTime(){return lmfT;}
		static int GetEffectSize() { return mEffectQueue.size(); }
		static bool SetLookAt(Vector2 pos);
	private:
		static void CalDiff();
	private:
		Camera() = delete;
		~Camera() = delete;

	private:
		static Vector2 mResolution;
		static Vector2 mLookPosition;
		static Vector2 mPrevLookPosition;
		static Vector2 mCurLookPosition;
		static Vector2 mDistance;
		static Vector2 mOriginPos;
		static GameObject* mTarget;

		static int idVar;
		static int increase;
		static queue<EffectInfo> mEffectQueue;
		static Image* mCutton;
		static float mCuttonAlpha;
		static float speed;
		static float lmfT;
		static float m_fTime;		// Ÿ���� ���󰡴µ� �ɸ��� �ð�.
		static float m_fAcctime;		// �����ð�
	};
}

