#include "yaApplication.h"
#include "yaSceneManager.h"
#include "yaTime.h"
#include "yaInput.h"

namespace ya
{
	Application::Application()
		: mHwnd(NULL)
		, mHdc(NULL)
	{
	}

	Application::~Application()
	{
		SceneManager::Release();
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

;		Time::Initiailize();
		Input::Initialize();
		SceneManager::Initialize();
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
	}

	void Application::Render()
	{
		Rectangle(mBackHdc
			, -1
			, -1
			, 1602
			, 902
		);

		Time::Render(mBackHdc);
		Input::Render(mBackHdc);
		SceneManager::Render(mBackHdc);

		BitBlt(mHdc, 0, 0, mWidth, mHeight
			, mBackHdc, 0, 0, SRCCOPY);

	}
}
