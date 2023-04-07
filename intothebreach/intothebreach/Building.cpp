#include "Building.h"
#include "mTransform.h"
#include "mResources.h"
#include "mImage.h"
namespace m {
	Building::Building(STRUCTURES _type, Vector2 _coord, int idx)
		//: mCoord(_coord)
		//, mFinalCoord(_coord)
		//, mFinalPos(Vector2::One)
		: Unit(_coord, 0, 0, 0, idx)
		, mType(_type)
	{
		AddComponent(new Transform());	
		GetMImages().resize((UINT)STRUCTURES::END);
		for (UINT i = 0; i < (UINT)STRUCTURES_CONDITION_T::END; i++)
		{
			GetMImages()[i] = Resource::Load<Image>(
				MAKE_UNIT_KEY(_type, (STRUCTURES_CONDITION_T)i)
				,MAKE_UNIT_PATH(_type, (STRUCTURES_CONDITION_T)i)
				);

			if (nullptr == GetMImages()[i])continue;
			//GetMImages()[i]->SetOffset();
		}


		//Image* im;
		//if (_type == STRUCTURES::Mountain) {
		//	im =Resources::Load<Image>(L"testMoutain", L"..\\Resources\\texture\\terrain\\green\\mountain_0.bmp");
		//}
		//else {
		//	im = Resources::Load<Image>(SQUARE__KEY, SQUARE__PATH);
		//}
		//im->SetOffset(Vector2(47.f, -18.f));
		//SetScale(Vector2((float)(im->GetWidth() * 2), (float)(im->GetHeight() * 2)));
		//SetCurImage(im);
	}
	Building::~Building() {

	}
	void Building::Update() {
		GameObject::Update();
	}
	void Building::Render(HDC hdc) {
		GameObject::Render(hdc);
		Vector2 mPos = GetPos();
		//mPos += GetCurImage()->GetOffset();
		Vector2 mScale = GetScale();
		//TransparentBlt(hdc
		//	, (int)(mPos.x - mScale.x / 2.f)
		//	, (int)(mPos.y - mScale.y / 2.f)
		//	, (int)(mScale.x)
		//	, (int)(mScale.y)
		//	, GetCurImage()->GetHdc()
		//	, 0
		//	, 0
		//	, (int)(GetCurImage()->GetWidth())
		//	, (int)(GetCurImage()->GetHeight())
		//	, RGB(255, 0, 255));
	}
	void Building::idle()
	{
		GetMImages()[(UINT)STRUCTURES_CONDITION_T::On];
	}
	void Building::broken()
	{
		GetMImages()[(UINT)STRUCTURES_CONDITION_T::Broken];
	}
	void Building::water()
	{
		GetMImages()[(UINT)STRUCTURES_CONDITION_T::Off];
	}
	void Building::emerge()
	{
		GetMImages()[(UINT)STRUCTURES_CONDITION_T::Off];
	}
}