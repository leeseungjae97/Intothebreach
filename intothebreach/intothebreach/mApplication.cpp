#include "Resource.h"
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
	}

	void Application::Initialize(HWND hWnd)
	{
		mHwnd = hWnd;
		mHdc = GetDC(hWnd);
		mWidth = 1280;
		mHeight = 720;

		RECT rect = { 0, 0, (LONG)mWidth, (LONG)mHeight };
		//AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, true);

		//SetWindowPos(mHwnd
		//	, nullptr
		//	, 0
		//	, 0
		//	, rect.right - rect.left
		//	, rect.bottom - rect.top
		//	, 0);

		//ShowWindow(mHwnd, true);

		mBackBuffer = CreateCompatibleBitmap(mHdc, mWidth, mHeight);
		mBackHdc = CreateCompatibleDC(mHdc);
		mMenuBar = LoadMenu(nullptr, MAKEINTRESOURCE(IDI_CLIENT));

		HBITMAP hOldBit = (HBITMAP)SelectObject(mBackHdc, mBackBuffer);
		DeleteObject(hOldBit);
		CreateBrushPen();

;		Time::Initiailize();
		Input::Initialize();
		SceneManager::Initialize();
		Camera::Initialize();

		SetMenuBar(false);
	}

	void Application::Run()
	{
		Update();
		Render();
		SceneManager::Destroy();
	}
	void Application::SetMenuBar(bool power)
	{
		SetMenu(mHwnd, mMenuBar);

		RECT rect = { 0, 0, mWidth , mHeight };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, power);

		// 윈도우 크기 변경및 출력 설정
		SetWindowPos(mHwnd
			, nullptr, 0, 0
			, rect.right - rect.left
			, rect.bottom - rect.top
			, 0);

		ShowWindow(mHwnd, true);
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
		SelectGDI a(mBackHdc, BRUSH_TYPE::BLACK);

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
		m_arrBrush[(UINT)BRUSH_TYPE::GREEN] = (HBRUSH)CreateSolidBrush(RGB(50, 255, 50));

		//red pen
		m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		//green pen
		m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		//blud pen
		m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	}
}
