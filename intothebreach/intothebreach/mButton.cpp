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
	, btConstant(0)
	, innerAlpha(0)
	, iInnerScale(1)
	, innerPos(Vector2::Minus)
	, bReSzieable(false)
	, bClicked(false)
{
	if(L"" != btnName) innerImage = Resources::Load<Image>(btnName, btnName);
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
		bHover = true;
		if (KEY_PRESSED(KEYCODE_TYPE::LBTN))
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
		bHover = false;
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
		if(btConstant != 0)func.SourceConstantAlpha = btConstant;
		else func.SourceConstantAlpha = 125;

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
			, (int)(mSize.x)
			, (int)(mSize.y)
			, mImage->GetHdc()
			, 0
			, 0
			, (int)(mImage->GetWidth())
			, (int)(mImage->GetHeight())
			, RGB(255, 0, 255));
	}
	
	if (bInner)
	{
		innerImage = Resources::Load<Image>(btnName, btnName);
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = innerAlpha;
		if (innerPos != Vector2::Minus) mPos += innerPos;
		if (bInnerAlpha)
		{
			AlphaBlend(hdc
				, (int)(mPos.x)
				, (int)(mPos.y)
				, (int)(innerImage->GetWidth() * iInnerScale)
				, (int)(innerImage->GetHeight() * iInnerScale)
				, innerImage->GetHdc()
				, 0
				, 0
				, (int)(innerImage->GetWidth())
				, (int)(innerImage->GetHeight())
				, func);
		}
		else
		{
			TransparentBlt(hdc
				, (int)(mPos.x)
				, (int)(mPos.y)
				, (int)(innerImage->GetWidth() * iInnerScale)
				, (int)(innerImage->GetHeight() * iInnerScale)
				, innerImage->GetHdc()
				, 0
				, 0
				, (int)(innerImage->GetWidth())
				, (int)(innerImage->GetHeight())
				, RGB(255, 0, 255));
		}
	}
}

void m::Button::Release()
{}
