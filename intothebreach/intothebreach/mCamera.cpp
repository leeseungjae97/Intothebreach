#include "mCamera.h"
#include "mApplication.h"
#include "mInput.h"
#include "mTime.h"
#include "mGameObject.h"
#include "mImage.h"
extern m::Application application;
namespace m
{
	Vector2 Camera::mResolution = {};
	Vector2 Camera::mLookPosition = {};
	Vector2 Camera::mPrevLookPosition = {};
	Vector2 Camera::mCurLookPosition = {};
	Vector2 Camera::mDistance = {};
	GameObject* Camera::mTarget = nullptr;

	queue<Camera::EffectInfo> Camera::mEffectQueue;
	Image* Camera::mCutton = nullptr;

	float Camera::mCuttonAlpha;
	float Camera::speed;
	float Camera::m_fAcctime;
	float Camera::m_fTime = 2.5f;

	void Camera::Initialize()
	{
		mResolution.y = (float)application.GetResolutionHeight();
		mResolution.x = (float)application.GetResolutionWidth();
		mLookPosition = (mResolution / 2.0f);
		mCurLookPosition = (mResolution / 2.0f);
		mPrevLookPosition = (mResolution / 2.0f);
		speed = 0.f;
		mCutton = Image::Create(L"Cutton", (UINT)mResolution.x, (UINT)mResolution.y);
	}
	void Camera::Update()
	{
		if (nullptr != mTarget)
		{
			if (mTarget->IsDead())
			{
				mTarget = nullptr;
			}
			else
			{
				mCurLookPosition = mTarget->GetPos();
			}
		}
		//Camera::PushEffect(CAMERA_EFFECT_TYPE::Fade_In, 2.0f);
		if (KEY_PRESSED(KEYCODE_TYPE::W))
		{
			mLookPosition.y -= Time::fDeltaTime() * 500.0f;
		}
		if (KEY_PRESSED(KEYCODE_TYPE::S))
		{
			mLookPosition.y += Time::fDeltaTime() * 500.0f;
		}
		if (KEY_PRESSED(KEYCODE_TYPE::A))
		{
			mLookPosition.x -= Time::fDeltaTime() * 500.0f;
		}
		if (KEY_PRESSED(KEYCODE_TYPE::D))
		{
			mLookPosition.x += Time::fDeltaTime() * 500.0f;
		}
		CalDiff();
		CheckEffectEnd();
	}
	void Camera::Render(HDC hdc)
	{
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
	void Camera::PushEffect(CAMERA_EFFECT_TYPE _effect, float _duration)
	{
		EffectInfo info = {};
		info.time = 0.0f;
		info.effect = _effect;
		info.duration = _duration;

		mEffectQueue.push(info);
	}
	void Camera::CalDiff()
	{
		m_fAcctime += Time::fDeltaTime();

		if (mTarget != nullptr)
			mLookPosition = mTarget->GetPos();

		if (m_fAcctime <= m_fTime)
		{
			Vector2 look = mLookPosition - mPrevLookPosition;
			if (look >= Vector2::Zero)
			{
				speed = look.Length() / (m_fTime - m_fAcctime);
				mCurLookPosition = mPrevLookPosition + look.Normalize() * speed * Time::fDeltaTime();
			}
		}
		else
		{
			mCurLookPosition = mLookPosition;
		}

		//if (!mEffectQueue.empty())
		//{
		//	EffectInfo& info = mEffectQueue.front();
		//	info.time += Time::fDeltaTime();
		//	float ratio = (info.time / info.duration);

		//	if (ratio >= 1.0f)
		//	{
		//		ratio = 1.0f;
		//		mEffectQueue.pop();
		//	}


		//	if (CAMERA_EFFECT_TYPE::Fade_In == info.effect)
		//		mCuttonAlpha = 1.0f - ratio;
		//	else if (CAMERA_EFFECT_TYPE::Fade_Out == info.effect)
		//		mCuttonAlpha = ratio;
		//	else
		//		mCuttonAlpha = 0.0f;
		//}
		mDistance = mCurLookPosition - (mResolution / 2.0f);
		mPrevLookPosition = mCurLookPosition;
	}
	void Camera::CheckEffectEnd()
	{
		if (!mEffectQueue.empty())
		{
			EffectInfo& info = mEffectQueue.front();
			info.time += Time::fDeltaTime();
			float ratio = (info.time / info.duration);

			if (ratio >= 1.0f)
			{
				ratio = 1.0f;
				mEffectQueue.pop();
			}

			if (CAMERA_EFFECT_TYPE::Fade_In == info.effect)
				mCuttonAlpha = 1.0f - ratio;
			else if (CAMERA_EFFECT_TYPE::Fade_Out == info.effect)
				mCuttonAlpha = ratio;
			else
			{
				mCuttonAlpha = 0.0f;
			}
		}
	}
	void Camera::Release()
	{
		if (nullptr != mTarget) delete mTarget;

	}
	bool Camera::SetLookAt(Vector2 pos)
	{
		if (mLookPosition != pos)
		{
			mLookPosition = pos;
			float fMoveDist = (mLookPosition - mPrevLookPosition).Length();
			speed = fMoveDist / m_fTime;
		}

		if (m_fAcctime > m_fTime) return true;
		else return false;
	}
}