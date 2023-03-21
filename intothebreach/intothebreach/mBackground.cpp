#include "mBackground.h"
#include "mResources.h"
#include "mTransform.h"
#include "mApplication.h"
#include "mSelectGDI.h"
#include "mCamera.h"
extern m::Application application;
namespace m {
	Background::Background(const wstring& key
		, const wstring& path
		, int _sizeUp
		, bool _full
		, bool _isCenter
		, bool _alphaCheck
		
	)
		: mImage(nullptr)
		, mPath(path)
		, mKey(key)
		, mSizeUp(_sizeUp)
		, mIsFull(_full)
		, mIsCenter(_isCenter)
		, mAlpha(_alphaCheck)
	{
		AddComponent(new Transform());
		if (mKey.empty() && mPath.empty()) return;
		mImage = Resources::Load<Image>(mKey, mPath);
	}
	Background::~Background() {
	}
	void Background::Initialize() {

		
	}
	void Background::Update() {
		GameObject::Update();
	}

	void Background::Render(HDC hdc) {
		GameObject::Render(hdc);
		Transform* tr = GetComponent<Transform>();
		Vector2 mPos = tr->GetPos();

		UINT iWidth;
		UINT iHeight;
		if (mImage == nullptr) {
			SelectGDI tmp(hdc, BRUSH_TYPE::CUSTOM_BLACK);
			Rectangle(hdc, 0, 0, application.GetResolutionWidth()
				, application.GetResolutionHeight());
		}
		else {
			if (mIsFull) {
				iWidth = application.GetResolutionWidth();
				iHeight = application.GetResolutionHeight();
			}
			else {
				iWidth = mImage->GetWidth();
				iHeight = mImage->GetHeight();
			}
			if (mSizeUp != 0) {
				iWidth *= mSizeUp;
				iHeight *= mSizeUp;
			}

			if (mIsCenter) {
				mPos.x = (float)application.GetResolutionWidth() / 2;
				mPos.y = (float)application.GetResolutionHeight() / 2;
				mPos.x -= iWidth / 2;
				mPos.y -= iHeight / 2;
			}
			mPos += mImage->GetOffset();
			SetScale(Vector2((float)iWidth, (float)iHeight));
			mPos = Camera::CalculatePos(mPos);
			if (mAlpha) {
				BLENDFUNCTION func = {};
				func.BlendOp = AC_SRC_OVER;
				func.BlendFlags = 0;
				func.AlphaFormat = mAlpha;
				func.SourceConstantAlpha = 125;

				mPos = Camera::CalculatePos(mPos);
				AlphaBlend(hdc
					, (int)(mPos.x)
					, (int)(mPos.y)
					, (int)(iWidth)
					, (int)(iHeight)
					, mImage->GetHdc()
					, 0
					, 0
					, (int)(mImage->GetWidth())
					, (int)(mImage->GetHeight())
					, func);
			}
			else {
				TransparentBlt(hdc
					, (int)(mPos.x)
					, (int)(mPos.y)
					, (int)(iWidth)
					, (int)(iHeight)
					, mImage->GetHdc()
					, 0
					, 0
					, (int)(mImage->GetWidth())
					, (int)(mImage->GetHeight())
					, RGB(255, 0, 255));
			}
			
		}
		
	}
	void Background::Release() {
		GameObject::Release();
	}

}