#include "yImage.h"
#include "yaApplication.h"
extern ya::Application application;
namespace ya {
	Image::Image() 
		: mBitmap(NULL)
		, mHdc(NULL)
		, mWidth(0)
		, mHeight(0)
	{

	}
	Image::~Image() {

	}
	HRESULT Image::Load(const wstring& path) {
		mBitmap = (HBITMAP)LoadImageW(nullptr
			, path.c_str()
			, IMAGE_BITMAP
			, 0, 0
			, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (nullptr == mBitmap) {
			return E_FAIL;
		}
		BITMAP bitInfo = {};
		GetObject(mBitmap, sizeof(BITMAP), &bitInfo);

		mWidth = bitInfo.bmWidth;
		mHeight = bitInfo.bmHeight;

		HDC mainDC = application.GetHdc();
		mHdc = CreateCompatibleDC(mainDC);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
		DeleteObject(oldBitmap);
		return S_OK;
	}
}