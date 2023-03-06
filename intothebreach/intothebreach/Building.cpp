#include "Building.h"
#include "mTransform.h"
#include "mResources.h"
#include "mImage.h"
namespace m {
	Building::Building(STRUCTURES_T _type, Vector2 _coord)
		: mCoord(_coord)
		, mFinalCoord(_coord)
		, mFinalPos(Vector2::One)
		, mType(_type)
	{
		AddComponent(new Transform());

		mImage =Resources::Load<Image>(L"testMoutain", L"..\\Resources\\texture\\terrain\\green\\mountain_0.bmp");
		mImage->SetOffset(Vector2(20.f, 40.f));
		SetScale(Vector2((float)(mImage->GetWidth() * 2), (float)(mImage->GetHeight() * 2)));
	}
	Building::~Building() {

	}
	void Building::Update() {

	}
	void Building::Render(HDC hdc) {
		Vector2 mPos = GetPos();
		mPos += mImage->GetOffset();
		Vector2 mScale = GetScale();
		TransparentBlt(hdc
			, (int)(mPos.x - mScale.x / 2.f)
			, (int)(mPos.y - mScale.y / 2.f)
			, (int)(mScale.x)
			, (int)(mScale.y)
			, mImage->GetHdc()
			, 0
			, 0
			, (int)(mImage->GetWidth())
			, (int)(mImage->GetHeight())
			, RGB(255, 0, 255));
	}
}