#include "mCamera.h"
#include "mApplication.h"
#include "mInput.h"
#include "mTime.h"
#include "mGameObject.h"
#include "mImage.h"
extern m::Application application;
namespace m {
	Size Camera::mResolution = {};
	Vector2 Camera::mLookPosition = {};
	Vector2 Camera::mDistance = {};
	GameObject* Camera::mTarget = nullptr;

	queue<Camera::EffectInfo> Camera::mEffectQueue;
	Image* Camera::mCutton = nullptr;

	float Camera::mCuttonAlpha;

	void Camera::Initialize() {
		mResolution.y = (float)application.GetResolutionHeight();
		mResolution.x = (float)application.GetResolutionWidth();
		mLookPosition = (mResolution / 2.0f);

		mCutton = Image::Create(L"Cutton", (UINT)mResolution.x, (UINT)mResolution.y);
	}
	void Camera::Update() {
		if (KEY_PREESED(KEYCODE_TYPE::W)) {
			mLookPosition.y -= Time::fDeltaTime() * 500.0f;
		}
		if (KEY_PREESED(KEYCODE_TYPE::S)) {
			mLookPosition.y += Time::fDeltaTime() * 500.0f;
		}
		if (KEY_PREESED(KEYCODE_TYPE::A)) {
			mLookPosition.x -= Time::fDeltaTime() * 500.0f;
		}
		if (KEY_PREESED(KEYCODE_TYPE::D)) {
			mLookPosition.x += Time::fDeltaTime() * 500.0f;
		}
		

		CalDiff();
	}
	void Camera::Render(HDC hdc) {
		if (mEffectQueue.empty())
			return;

		BLENDFUNCTION tFunc = {};
		tFunc.BlendOp = AC_SRC_OVER;
		tFunc.BlendFlags = 0;
		tFunc.AlphaFormat = 0;
		tFunc.SourceConstantAlpha = (BYTE)(255.0f * mCuttonAlpha);

		AlphaBlend(hdc, 0, 0
			, mCutton->GetWidth(), mCutton->GetHeight()
			, mCutton->GetHdc()
			, 0, 0
			, mCutton->GetWidth(), mCutton->GetHeight()
			, tFunc);
	}
	void Camera::PushEffect(CAMERA_EFFECT_TYPE _effect, float _duration) {
		EffectInfo info = {};
		info.time = 0.0f;
		info.effect = _effect;
		info.duration = _duration;

		mEffectQueue.push(info);
	}
	void Camera::CalDiff() {
		if (mTarget != nullptr)
			mLookPosition = mTarget->GetPos();

		if (!mEffectQueue.empty()) {
			EffectInfo& info = mEffectQueue.front();
			info.time += Time::fDeltaTime();
			float ratio = (info.time / info.duration);

			if (ratio >= 1.0f) {
				ratio = 1.0f;
				mEffectQueue.pop();
			}

			if (CAMERA_EFFECT_TYPE::Fade_In == info.effect)
				mCuttonAlpha = 1.0f - ratio;
			else if (CAMERA_EFFECT_TYPE::Fade_Out == info.effect)
				mCuttonAlpha = ratio;
			else
				mCuttonAlpha = 0.0f;
		}
		mDistance = mLookPosition - (mResolution / 2.0f);
	}
	void Camera::Release() {
		if (nullptr != mTarget) delete mTarget;

	}
}