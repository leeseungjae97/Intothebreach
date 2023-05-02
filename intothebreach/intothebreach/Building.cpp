#include "Building.h"
#include "mTransform.h"
#include "mResources.h"
#include "mSceneManager.h"
#include "mPlayerInfo.h"
#include "mComponent.h"
#include "mAnimator.h"
#include "mScene.h"
#include "mTile.h"
#include "mImage.h"
namespace m {
	Building::Building(STRUCTURES _type, Vector2 _coord, int idx, TILE_T _mapType, int hp)
		: Unit(_coord, 0, hp, WEAPON_T::NONE, idx, 0)
		, mType(_type)
		, mapType(_mapType)
		, iBlinkCnt(0)
		, iDVar(1)
		, iDir(1)
		, iConstant(1)
		, bBlink(false)
	{
		
		if (mType == STRUCTURES::bomb)
		{
			Image* imn = Resources::Load<Image>(L"..\\Resources\\texture\\units\\mission\\bomb.bmp"
				, L"..\\Resources\\texture\\units\\mission\\bomb.bmp");
			SetCurImage(imn);
			//imn->SetOffset();
			SetState(STATE::Idle);
			SetVisibleHp(true);
			GameComp::bomb = this;
		}
		else if (mType == STRUCTURES::mountain)
		{
			gridIcon = nullptr;
			Image* imn = Resources::Load<Image>(MAKE_TILE_KEY(mapType, TILE_HEAD_T::mountain)
				, MAKE_TILE_PATH(mapType, TILE_HEAD_T::mountain));
			SetCurImage(imn);
			imn->SetOffset(Vector2(10.f, -35.f));
			SetState(STATE::Idle);

			Image* im = Resources::Load<Image>(MAKE_TILE_KEY(mapType, TILE_HEAD_T::mountain_explode)
				, MAKE_TILE_PATH(mapType, TILE_HEAD_T::mountain_explode));
			im->SetOffset(Vector2(-6.f, -19.f));

			if (nullptr == GetAnimator()->FindAnimation(MAKE_TILE_KEY(mapType, TILE_HEAD_T::mountain_explode)))
			{
				GetAnimator()->CreateAnimation(
					MAKE_TILE_KEY(mapType, TILE_HEAD_T::mountain_explode)
					, im
					, Vector2::Zero
					, Vector2((im->GetWidth() / 13.f), (float)im->GetHeight())
					, im->GetOffset()
					, 13
					, 0.1f
					, (UINT)AC_SRC_OVER
				);
			}
		}
		else
		{
			gridIcon = Resources::Load<Image>(L"gridPowerIcon", L"..\\Resources\\texture\\combat\\icons\\icon_gridpower_glow_y.bmp");
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
		
		switch (GetState())
		{
		case m::GameObject::STATE::Idle:
		{
			idle();
		}
			break;
		case m::GameObject::STATE::Broken:
		{
			broken();
		}
			break;
		case m::GameObject::STATE::Explo:
		{
			explo();
		}
			break;
		case m::GameObject::STATE::Water:
		{
			water();
		}
			break;
		default:
			break;
		}
	}
	void Building::Render(HDC hdc) {
		Unit::Render(hdc);
		//Vector2 mPos = GetPos();
		Vector2 mPos = GetPos();
		if (mType == STRUCTURES::bomb)
		{
			if (bBlink)
			{
				iConstant += iDVar * iDir;
				if (iConstant + iDVar >= 255 || iConstant - iDVar <= 0)
				{
					iDir *= -1;
					iBlinkCnt++;
				}
			}
			

			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			func.SourceConstantAlpha = iConstant;
			Image* im1 = Resources::Load<Image>(L"bombGlow", L"..\\Resources\\texture\\units\\mission\\bomb_glow.bmp");
			Image* im2 = Resources::Load<Image>(L"bombLight", L"..\\Resources\\texture\\units\\mission\\bomb_lights2.bmp");

			AlphaBlend(
				hdc
				, (int)(mPos.x - im1->GetWidth() / 2)
				, (int)(mPos.y - im1->GetHeight() / 2)
				, (int)im1->GetWidth() * 2
				, (int)im1->GetHeight() * 2
				, im1->GetHdc()
				, 0
				, 0
				, (int)im1->GetWidth()
				, (int)im1->GetHeight()
				, func);

			AlphaBlend(
				hdc
				, (int)(mPos.x - im2->GetWidth() / 2)
				, (int)(mPos.y - im2->GetHeight() / 2)
				, (int)im2->GetWidth() * 2
				, (int)im2->GetHeight() * 2
				, im2->GetHdc()
				, 0
				, 0
				, (int)im2->GetWidth()
				, (int)im2->GetHeight()
				, func);

		}
		//mPos.x += GetCurImage()->GetWidth() / 2;
		if (gridIcon)
		{
			Vector2 mCenterPos = SceneManager::GetActiveScene()->GetPosTile((int)GetCoord().y, (int)GetCoord().x)->GetCenterPos();
			mCenterPos.y -= GetCurImage()->GetHeight();
			//mCenterPos.x += gridIcon->GetWidth();
			TransparentBlt(hdc
				, (int)(mCenterPos.x + gridIcon->GetWidth() / 2.f)
				, (int)(mCenterPos.y - gridIcon->GetHeight() / 2.f)
				, (int)(gridIcon->GetWidth() * 2)
				, (int)(gridIcon->GetHeight() * 2)
				, gridIcon->GetHdc()
				, 0
				, 0
				, (int)(gridIcon->GetWidth())
				, (int)(gridIcon->GetHeight())
				, RGB(255, 0, 255));
		}
	}
	void Building::Hit(int damage)
	{
		if (mType == STRUCTURES::bomb)
		{
			if (GetCurHp() < damage) SetCurHp(0);
			else SetCurHp(GetCurHp() - damage);
			if (GetCurHp() == 0) SetState(STATE::Broken);
		}
		else
		{
			if (GetState() == STATE::Broken)
			{
				if (mType == STRUCTURES::mountain)
				{
					SetState(STATE::Explo);
				}
			}
			else
			{
				if (mType != STRUCTURES::mountain)
				{
					GameComp::gridPower -= 1;
					gridIcon = nullptr;
				}
				SetState(STATE::Broken);
			}
		}
		
		
	}
	void Building::idle()
	{
		if (mType == STRUCTURES::bomb)
		{
			Image* imn = Resources::Load<Image>(L"..\\Resources\\texture\\units\\mission\\bomb.bmp"
				, L"..\\Resources\\texture\\units\\mission\\bomb.bmp");
			SetCurImage(imn);
		}
		else if (mType != STRUCTURES::mountain)
		{
			SetCurImage(GetMImages()[(UINT)STRUCTURES_CONDITION_T::On]);
			if (nullptr == gridIcon)
				gridIcon = Resources::Load<Image>(L"gridPowerIcon", L"..\\Resources\\texture\\combat\\icons\\icon_gridpower_glow_y.bmp");
		}
		else
		{
			Image* imn = Resources::Load<Image>(MAKE_TILE_KEY(mapType, TILE_HEAD_T::mountain)
				, MAKE_TILE_PATH(mapType, TILE_HEAD_T::mountain));
			imn->SetOffset(Vector2(10.f, -35.f));
			SetCurImage(imn);
		}
	}
	void Building::broken()
	{
		if (mType == STRUCTURES::bomb)
		{
			bBombExplosive = true;
			Image* imn = Resources::Load<Image>(L"bomb_death", L"..\\Resources\\texture\\units\\mission\\bomb_death.bmp");
			GetAnimator()->Stop();
			if (nullptr == GetAnimator()->FindAnimation(L"bomb_death"))
			{
				GetAnimator()->CreateAnimation(
					L"bomb_death",
					imn,
					Vector2::Zero,
					Vector2(45.f, 35.f),
					Vector2::Zero,
					11,
					0.2f
				);
			}
			if (GetAnimator()->GetStopAnimator())
				GetAnimator()->Play(L"bomb_death", false);
		}
		else if (mType == STRUCTURES::mountain)
		{
			Image* im = Resources::Load<Image>(MAKE_TILE_KEY(mapType, TILE_HEAD_T::mountain_broken)
				, MAKE_TILE_PATH(mapType, TILE_HEAD_T::mountain_broken));
			SetCurImage(im);
			im->SetOffset(Vector2(10.f, -35.f));
		}
		else
		{
			SetCurImage(GetMImages()[(UINT)STRUCTURES_CONDITION_T::Broken]);
		}
		
	}
	void Building::water()
	{
		//SetCurImage(GetMImages()[(UINT)STRUCTURES_CONDITION_T::Off]);
	}
	void Building::explo()
	{
		GetAnimator()->Stop();
		GetAnimator()->Play(MAKE_TILE_KEY(mapType, TILE_HEAD_T::mountain_explode), false);
		SetCurImage(nullptr);
	}

}