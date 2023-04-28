#include "mImage.h"
#include "mApplication.h"
#include "mResources.h"

extern m::Application application;
namespace m {
	Image* Image::Create(const wstring& key, UINT width, UINT height) {

		Image* image = Resources::Find<Image>(key);
		if (nullptr != image) {
			MessageBox(nullptr, L"중복 키 발생", L"이미지 생성 실패", MB_OK);
			return nullptr;
		}

		image = new Image();
		HDC mainHdc = application.GetHdc();

		image->mHBitmap = CreateCompatibleBitmap(mainHdc, width, height);
		image->mHdc = CreateCompatibleDC(mainHdc);

		if (0 == image->mHBitmap || 0 == image->mHdc)
			return nullptr;

		HBITMAP defaultBitmap = (HBITMAP)SelectObject(image->mHdc, image->mHBitmap);
		DeleteObject(defaultBitmap);

		// 비트맵 정보 확인
		BITMAP bitmap = {};
		GetObject(image->mHBitmap, sizeof(BITMAP), &bitmap);

		image->mWidth = bitmap.bmWidth;
		image->mHeight = bitmap.bmHeight;

		image->SetKey(key);
		Resources::Insert<Image>(key, image);

		return image;
	}
	Image::Image()
		: mHBitmap(NULL)
		, mHdc(NULL)
		, mWidth(0)
		, mHeight(0)
		, mOffset(Vector2::Zero)
	{

	}
	Image::~Image() {
		DeleteDC(mHdc);
		DeleteObject(mHBitmap);
	}
	HRESULT Image::Load(const wstring& path) {
		mHBitmap = (HBITMAP)LoadImageW(nullptr
			, path.c_str()
			, IMAGE_BITMAP
			, 0, 0
			, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (nullptr == mHBitmap) {
			return E_FAIL;
		}
		BITMAP bitInfo = {};
		GetObject(mHBitmap, sizeof(BITMAP), &bitInfo);

		mWidth = bitInfo.bmWidth;
		mHeight = bitInfo.bmHeight;
		mBitmap = bitInfo.bmBits;

		HDC mainDC = application.GetHdc();
		mHdc = CreateCompatibleDC(mainDC);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mHdc, mHBitmap);
		DeleteObject(oldBitmap);

		return S_OK;
	}
	COLORREF Image::GetPixel(int x, int y)
	{
		return ::GetPixel(mHdc, x, y);
	}
	void Image::SetPixel(int x, int y, COLORREF color)
	{
		::SetPixel(mHdc, x, y, color);
	}
}