#include "mButton.h"
#include "mInput.h"
#include "mMath.h"
#include "mCamera.h"
#include "mImage.h"
m::Button::Button(const wstring& key
	, const wstring& path
	, int _sizeUp
	, bool _full
	, int _direction
	, bool _alphaCheck)
	: UI(key
		, path
		, _sizeUp
		, _full
		, _direction
		, _alphaCheck)
{
	SetCutPos(true);
	SetEC(false);
}

m::Button::~Button()
{}

void m::Button::Initialize()
{
	
}

void m::Button::Update()
{
	GameObject::Update();
	if (math::CheckRectPos(GetPos(), GetSize(), MOUSE_POS))
	{

	}
}

void m::Button::Render(HDC hdc)
{
	Vector2 mPos = GetPos();

	if (mAlpha)
	{
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_OVER;
		func.SourceConstantAlpha = 125;

		HFONT font, old;
		font = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
			VARIABLE_PITCH | FF_ROMAN, L"궁서");
		old =(HFONT)SelectObject(hdc, font);
		TextOut(hdc, 50, 50, L"게임시작", lstrlen(L"게임시작"));
		SetBkColor(hdc, RGB(255, 0, 255));
		SetBkMode(hdc, TRANSPARENT);
		SelectObject(hdc, old);
		DeleteObject(font);

		AlphaBlend(hdc
			, (int)(mPos.x)
			, (int)(mPos.y)
			, (int)(300.f)
			, (int)(mImage->GetHeight() / 2)
			, mImage->GetHdc()
			, 0
			, 0
			, (int)(mImage->GetWidth())
			, (int)(mImage->GetHeight())
			, func);
	}
	else
	{
		TransparentBlt(hdc
			, (int)(mPos.x)
			, (int)(mPos.y)
			, (int)(mImage->GetWidth())
			, (int)(mImage->GetHeight())
			, mImage->GetHdc()
			, 0
			, 0
			, (int)(mImage->GetWidth())
			, (int)(mImage->GetHeight())
			, RGB(255, 0, 255));
	}
}

void m::Button::Release()
{}
