#include "Building.h"
#include "mTransform.h"
#include "mResources.h"
#include "mImage.h"
namespace m {
	Building::Building(STRUCTURES _type, Vector2 _coord, int idx)
		//: mCoord(_coord)
		//, mFinalCoord(_coord)
		//, mFinalPos(Vector2::One)
		: Unit(_coord, 0, 0, 0, idx, 0)
		//, mSkillType(_type)
	{
		AddComponent(new Transform());	
		
		if (_type == STRUCTURES::mountain)
		{
			Image* im = Resources::Load<Image>(L"testMoutain", L"..\\Resources\\texture\\terrain\\mountain_0.bmp");
			SetCurImage(im);
			im->SetOffset(Vector2(10.f, -35.f));
			SetState(STATE::Idle);
		}
		else
		{
			GetMImages().resize((UINT)STRUCTURES::END);
			for (UINT i = 0; i < (UINT)STRUCTURES_CONDITION_T::END; i++)
			{
				GetMImages()[i] = Resources::Load<Image>(
					MAKE_UNIT_KEY(_type, (STRUCTURES_CONDITION_T)i)
					, MAKE_UNIT_PATH(_type, (STRUCTURES_CONDITION_T)i)
				);

				if (nullptr == GetMImages()[i])continue;
				GetMImages()[i]->SetOffset(STRUCTURES_OFFSET[(UINT)_type]);
			}


			SetCurImage(GetMImages()[(UINT)STRUCTURES_CONDITION_T::On]);
			SetState(GameObject::STATE::Idle);
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
		Unit::Update();
	}
	void Building::Render(HDC hdc) {
		Unit::Render(hdc);
	}
	void Building::idle()
	{
		SetCurImage(GetMImages()[(UINT)STRUCTURES_CONDITION_T::On]);
	}
	void Building::broken()
	{
		SetCurImage(GetMImages()[(UINT)STRUCTURES_CONDITION_T::Broken]);
	}
	void Building::water()
	{
		SetCurImage(GetMImages()[(UINT)STRUCTURES_CONDITION_T::Off]);
	}
}