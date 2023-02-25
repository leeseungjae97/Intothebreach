#pragma once
#include "yaResource.h"
namespace ya {
	class Resource;
	class Image :public Resource{
		friend Resource;
	public:
		static Image* Create(const std::wstring& key, UINT width, UINT height);

		Image();
		virtual ~Image() override;
		virtual HRESULT Load(const wstring& path) override;

		Pixel GetPixel(int x, int y);
		void SetPixel(int x, int y, Pixel pixel);

		HDC GetHdc() { return mHdc; }
		HBITMAP GetBitmap() { return mHBitmap; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }
	private:
		HBITMAP mHBitmap;
		void* mBitmap;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;
	};

}

