#include "yaBackground.h"
#include "yaResources.h"
#include "yaTransform.h"
#include "yaApplication.h"
#include "yaSelectGDI.h"
extern ya::Application application;
namespace ya {
	Background::Background(const wstring& key
		, const wstring& path
		, int _sizeUp
		, bool _full
		, bool _isCenter
		
	)
		: mImage(nullptr)
		, mPath(path)
		, mKey(key)
		, mSizeUp(_sizeUp)
		, mIsFull(_full)
		, mIsCenter(_isCenter)
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
	}

	void Background::Render(HDC hdc) {
		Transform* tr = GetComponent<Transform>();
		Vector2 mPos = tr->GetPos();
		float _x = mPos.x;
		float _y = mPos.y;
		UINT iWidth;
		UINT iHeight;
		if (mImage == nullptr) {
			SelectGDI tmp(hdc, BRUSH_TYPE::CUSTOM_BLACK);
			Rectangle(hdc, 0, 0, application.GetResolutionWidth() - 1
				, application.GetResolutionHeight() - 1);
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
				_x = (float)application.GetResolutionWidth() / 2;
				_y = (float)application.GetResolutionHeight() / 2;
				_x -= iWidth / 2;
				_y -= iHeight / 2;
			}
			TransparentBlt(hdc
				, (int)(_x)
				, (int)(_y)
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
	void Background::Release() {
		GameObject::Release();
	}

}