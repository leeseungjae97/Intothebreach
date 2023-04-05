#pragma once
#include "_Engine.h"
namespace m {
	enum class CAMERA_EFFECT_TYPE {
		Fade_In,
		Fade_Out,
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
		};
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		static void PushEffect(CAMERA_EFFECT_TYPE _effect, float _duration);
		static Vector2 CalculatePos(Vector2 _pos) { return _pos - mDistance; }
		static void SetTarget(GameObject* _obj) { mTarget = _obj; }
		static Vector2 GetRealPos(Vector2 _vRenderPos) { return _vRenderPos + mDistance; }
		static void MoveCamera(Vector2 pos) { mLookPosition = pos; }
		static void CheckEffectEnd();
		static void SetMoveTime(float _time) { 
			m_fAcctime = 0;
			m_fTime = _time; 
		}
		static Vector2 GetCurPos() { return mCurLookPosition; }
		static void Release();

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
		static GameObject* mTarget;

		static queue<EffectInfo> mEffectQueue;
		static Image* mCutton;
		static float mCuttonAlpha;
		static float speed;
		static float m_fTime;		// 타겟을 따라가는데 걸리는 시간.
		static float m_fAcctime;		// 누적시간
	};
}

