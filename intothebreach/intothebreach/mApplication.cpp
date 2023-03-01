#include "mApplication.h"
#include "mSceneManager.h"
#include "mTime.h"
#include "mInput.h"
#include "mResources.h"
#include "mSelectGDI.h"
#include "mCamera.h"
namespace m
{
	Application::Application()
		: mHwnd(NULL)
		, mHdc(NULL)
		, mBackBuffer(NULL)
		, mBackHdc(NULL)
		, mHeight(0)
		, mWidth(0)
	{
	}

	Application::~Application()
	{
		SceneManager::Release();
		Resources::Release();
		//Time::Release();
	}

	void Application::Initialize(HWND hWnd)
	{
		mHwnd = hWnd;
		mHdc = GetDC(hWnd);
		mWidth = 1600;
		mHeight = 900;

		RECT rect = { 0, 0, (LONG)mWidth, (LONG)mHeight };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, true);

		SetWindowPos(mHwnd
			, nullptr
			, 100
			, 50
			, rect.right - rect.left
			, rect.bottom - rect.top
			, 0);

		ShowWindow(mHwnd, true);

		mBackBuffer = CreateCompatibleBitmap(mHdc, mWidth, mHeight);
		mBackHdc = CreateCompatibleDC(mHdc);

		HBITMAP hOldBit = (HBITMAP)SelectObject(mBackHdc, mBackBuffer);
		DeleteObject(hOldBit);
		CreateBrushPen();

;		Time::Initiailize();
		Input::Initialize();
		SceneManager::Initialize();
		Camera::Initialize();
	}

	void Application::Run()
	{
		Update();
		Render();
	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();
		SceneManager::Update();
		Camera::Update();
	}

	void Application::Render()
	{

		Clear();

		Time::Render(mBackHdc);
		Input::Render(mBackHdc);
		SceneManager::Render(mBackHdc);
		Camera::Render(mBackHdc);

		BitBlt(mHdc, 0, 0, mWidth, mHeight
			, mBackHdc, 0, 0, SRCCOPY);

	}
	void Application::Clear() {
		SelectGDI a(mHdc, BRUSH_TYPE::GRAY);

		Rectangle(mBackHdc
			, -1
			, -1
			, 1602
			, 902
		);
	}
	void Application::CreateBrushPen() {
		//hollow brush
		m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
		m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);
		m_arrBrush[(UINT)BRUSH_TYPE::CUSTOM_BLACK] = (HBRUSH)CreateSolidBrush(RGB(9,7,8));
		m_arrBrush[(UINT)BRUSH_TYPE::GRAY] = (HBRUSH)GetStockObject(GRAY_BRUSH);

		//red pen
		m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		//green pen
		m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		//blud pen
		m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	}
}
