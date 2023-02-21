#pragma once
#include "YamYamEngine.h"


namespace ya
{
	class Application
	{
	public:
		Application();
		~Application();

		void Initialize(HWND hWnd);
		void Run();
		void Update();
		void Render();

		HWND GetHwnd() { return mHwnd; }
		HDC GetHdc() { return mHdc; }
	private:
		HWND mHwnd;
		HDC mHdc;
		HBITMAP mBackBuffer;
		HDC	mBackHdc;

		UINT mWidth;
		UINT mHeight;

		Vector2 mPos;

		//Scene mScene[256];
	};
}