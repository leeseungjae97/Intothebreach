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
	, innerConstant(0)
	, iInnerScale(1)
	, iScale(1)
	, idVar(1)
	, idDir(1)
	, iItem(0)
	, invenIdx(-1)
	, bFromInven(false)
	, bBlink(false)
	, innerPos(Vector2::Minus)
	, bReSzieable(false)
	, bClicked(false)
	, bSmoothDisappear(false)
	, bSmoothAppear(false)
	, endApDAp(false)
{
	if (L"" != btnName) innerImage = Resources::Load<Image>(btnName, btnName);
	SetCutPos(true);
	SetEC(false);
}

m::Button::~Button()
{
	//if(nullptr != innerImage)
	//	delete innerImage;
}

void m::Button::Initialize()
{

}
void m::Button::Update()
{
	GameObject::Update();
	if (math::CheckRectPos(GetPos(), GetSize(), MOUSE_POS))
	{
		bHover = true;
		if (KEY_UP(KEYCODE_TYPE::LBTN))
		{
			bClicked = true;
		}
		if (bReSzieable)
		{
			if (mSize.x < resizeMax.x) mSize.x += resizeUnit.x;
			if (mSize.y < resizeMax.y) { mSize.y += resizeUnit.y; }
			if (mSize.x == resizeMax.x) mSize.x = resizeMax.x;
			if (mSize.y == resizeMax.y) mSize.y = resizeMax.y;
		}
	}
	else
	{
		//if (KEY_UP(KEYCODE_TYPE::LBTN))
		//{
		//	bClicked = false;
		//}
		bHover = false;
		if (bReSzieable)
		{
			if (mSize.x > originSize.x) mSize.x -= resizeUnit.x;
			if (mSize.y > originSize.y) mSize.y -= resizeUnit.y;
		}
	}
}
void m::Button::Render(HDC hdc)
{
	Vector2 mPos = GetPos();
	//if (bBlink)
	//{
	//	btConstant += idVar * idDir;
	//	innerAlpha += idVar * idDir;
	//	if (btConstant >= 255 || btConstant <= 0)
	//	{
	//		idDir *= -1;
	//	}
	//}
	if (bApDAp)
	{
		if (btConstant >= 255)
		{
			idDir *= -1;
		}
		if (btConstant - idVar <= 0 && idDir == -1)
		{
			idDir *= -1;
			bApDAp = false;
			btConstant = 0;
			innerConstant = 0;
			SetState(STATE::Invisible);
		}
		btConstant += idVar * idDir;
		innerConstant += idVar * idDir;
	}
	else idDir *= -1;

	if (bSmoothAppear)
	{
		idDir = 1;
		if (btConstant < 255 - idVar)
		{
			btConstant += idVar * idDir;
			innerConstant += idVar * idDir;
		}
	}
	if (bSmoothDisappear)
	{
		idDir = -1;
		if (btConstant - idVar > 0)
		{
			btConstant += idVar * idDir;
			innerConstant += idVar * idDir;
		}
	}

	if (mAlpha)
	{
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		if (btConstant != 0)func.SourceConstantAlpha = btConstant;
		else func.SourceConstantAlpha = 125;

		AlphaBlend(hdc
			, (int)(mPos.x)
			, (int)(mPos.y)
			, (int)(mSize.x * iScale)
			, (int)(mSize.y * iScale)
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
			, (int)(mSize.x * iScale)
			, (int)(mSize.y * iScale)
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
		func.SourceConstantAlpha = innerConstant;

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
