#include "mButton.h"
#include "mInput.h"
#include "mMath.h"
#include "mCamera.h"
#include "mImage.h"
#include "mResources.h"
#include "mSceneManager.h"
m::Button::Button(const wstring& inner
	, const wstring& background
	, int _sizeUp
	, bool _full
	, int _direction
	, bool _alphaCheck)
	: UI(background
		, background
		, _sizeUp
		, _full
		, _direction
		, _alphaCheck)
	, btnName(inner)
{
	SetCutPos(true);
	SetEC(false);
	textAlpha = 0;
	iTextMag = 1;
	textPos = Vector2::Minus;
	bReSzieable = false;
	bClicked = false;
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
		if (KEY_UP(KEYCODE_TYPE::LBTN))
		{
			bClicked = true;
		}
		if (bReSzieable)
		{
			if (mSize.x <= 400.f) mSize.x += 50.f;
		}
			
	}
	else
	{
		if (bReSzieable)
		{
			if (mSize.x > 300.f) mSize.x -= 50.f;
		}
		
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

		AlphaBlend(hdc
			, (int)(mPos.x)
			, (int)(mPos.y)
			, (int)(mSize.x)
			, (int)(mSize.y)
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
	
	if (bText)
	{
		Image* im = Resources::Load<Image>(btnName, btnName);
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = textAlpha;
		if (textPos != Vector2::Minus) mPos += textPos;
		if (bTextAlpha)
		{
			AlphaBlend(hdc
				, (int)(mPos.x)
				, (int)(mPos.y)
				, (int)(im->GetWidth() * iTextMag)
				, (int)(im->GetHeight() * iTextMag)
				, im->GetHdc()
				, 0
				, 0
				, (int)(im->GetWidth())
				, (int)(im->GetHeight())
				, func);
		}
		else
		{
			TransparentBlt(hdc
				, (int)(mPos.x)
				, (int)(mPos.y)
				, (int)(im->GetWidth() * iTextMag)
				, (int)(im->GetHeight() * iTextMag)
				, im->GetHdc()
				, 0
				, 0
				, (int)(im->GetWidth())
				, (int)(im->GetHeight())
				, RGB(255, 0, 255));
		}
	}
}

void m::Button::Release()
{}
