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

		static void Release();
	private:
		static void CalDiff();
	private:
		Camera() = delete;
		~Camera() = delete;

	private:
		static Size mResolution;
		static Vector2 mLookPosition;
		static Vector2 mDistance;
		static GameObject* mTarget;

		static queue<EffectInfo> mEffectQueue;
		static Image* mCutton;
		static float mCuttonAlpha;
	};
}

