#pragma once
#include "_Engine.h"
namespace m
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

		void SetMenuBar(bool power);
		
		UINT GetResolutionWidth() { return mWidth; }
		UINT GetResolutionHeight() { return mHeight; }

		HWND GetHwnd() { return mHwnd; }
		HDC GetHdc() { return mHdc; }

		HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
		HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
	private:
		void CreateBrushPen();
		void Clear();
	private:
		HWND mHwnd;
		HDC mHdc;
		HBITMAP mBackBuffer;
		HDC	mBackHdc;
		HMENU mMenuBar;

		UINT mWidth;
		UINT mHeight;

		Vector2 mPos;
		HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
		HPEN	m_arrPen[(UINT)PEN_TYPE::END];
		//Scene mScene[256];
	};
}