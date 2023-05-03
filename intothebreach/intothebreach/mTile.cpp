#include "mTile.h"
#include "mImage.h"
#include "mCamera.h"
#include "mAnimator.h"
#include "mResources.h"
#include "mComponent.h"
namespace m {
	Tile::Tile(Vector2 _coord)
		: mTileTex(nullptr)
		, mCoord(_coord)
		, eTCTexsIdx(0)
		, mConstant(50)
	{
		AddComponent(new Transform());
		AddComponent(new Animator());
		mAnimator = GetComponent<Animator>();
	}
	Tile::Tile()
		: mTileTex(nullptr)
		, mCoord(Vector2::One)
		, eTCTexsIdx(0)
		, mConstant(50)
	{
		AddComponent(new Transform());
		AddComponent(new Animator());
		mAnimator = GetComponent<Animator>();
		SetScale(Vector2(TILE_SIZE_X * 2, TILE_SIZE_Y * 2));
	}
	Tile::~Tile() {
	}
	void Tile::Initialize()
	{
	}
	Vector2 Tile::GetCenterPos()
	{
		if (nullptr == mTileTex)
		{
			return Vector2(GetPos().x + 28.f, GetPos().y + 22.f);
		}
		else
		{
			return Vector2(GetPos().x + (mTileTex->GetWidth() / 2), GetPos().y + (mTileTex->GetHeight() / 2));
		}
	}
	void Tile::Update() {
		GameObject::Update();
	}
	void Tile::SetTileTexture(const wstring& key, const wstring& path)
	{
		mAnimator->Stop();
		mTileTex = Resources::Load<Image>(key, path);
		//mTileTex->SetOffset();
		SetScale(Vector2((float)(mTileTex->GetWidth() * 2), (float)(mTileTex->GetHeight() * 2)));
	}
	void Tile::SetTileTexture(const wstring& key, const wstring& path, Vector2 offset)
	{
		mAnimator->Stop();
		mTileTex = Resources::Load<Image>(key, path);
		mTileTex->SetOffset(offset);
		SetScale(Vector2((float)(mTileTex->GetWidth() * 2), (float)(mTileTex->GetHeight() * 2)));
	}
	void Tile::SetTileAnimator(COMBAT_ANIM_TILE_T _type, BYTE fConstant, bool alpha)
	{
		mTileTex = nullptr;
		if (alpha) mAnimator->SetConstant(fConstant);
		
		if (nullptr == mAnimator->FindAnimation(MAKE_TILE_KEY(_type)))
		{
			UINT len = COMBAT_ANIM_TILE_LEN[(UINT)_type];

			Image* im = Resources::Load<Image>(MAKE_TILE_KEY(_type)
				, MAKE_TILE_PATH(_type));

			float fWid = (float)im->GetWidth() / len;
			float fHei = (float)im->GetHeight();

			mAnimator->CreateAnimation(
				MAKE_TILE_KEY(_type)
				, im
				, Vector2::Zero
				, Vector2(fWid, fHei)
				, COMBAT_ANIM_TIME_OFFSET[(UINT)_type]
				, len
				, 0.2f
				, (UINT)AC_SRC_ALPHA
			);
		}
		mAnimator->Play(MAKE_TILE_KEY(_type), true);
	}
	void Tile::SetTileAnimator(DIR_EFFECT_T _type, BYTE fConstant, bool alpha)
	{
		mTileTex = nullptr;
		if (alpha) mAnimator->SetConstant(fConstant);

		if (nullptr == mAnimator->FindAnimation(MAKE_EFFECT_KEY(_type)))
		{
			UINT len = GET_LEN(_type);

			Image* im = Resources::Load<Image>(MAKE_EFFECT_KEY(_type)
				, MAKE_EFFECT_PATH(_type));

			float fWid = (float)im->GetWidth() / len;
			float fHei = (float)im->GetHeight();

			mAnimator->CreateAnimation(
				MAKE_EFFECT_KEY(_type)
				, im
				, Vector2::Zero
				, Vector2(fWid, fHei)
				, DIR_EFFECT_T_OFFSET[(UINT)_type]
				, len
				, 0.05f
				, (UINT)AC_SRC_OVER
			);
		}
		if(mAnimator->GetStopAnimator())
			mAnimator->Play(MAKE_EFFECT_KEY(_type), false);
	}
	void Tile::SetTileAnimator(IMMO_EFFECT_T _type, BYTE fConstant, bool alpha)
	{
		mTileTex = nullptr;
		if (alpha) mAnimator->SetConstant(fConstant);

		if (nullptr == mAnimator->FindAnimation(MAKE_EFFECT_KEY(_type)))
		{
			UINT len = GET_LEN(_type);

			Image* im = Resources::Load<Image>(MAKE_EFFECT_KEY(_type)
				, MAKE_EFFECT_PATH(_type));

			float fWid = (float)im->GetWidth() / len;
			float fHei = (float)im->GetHeight();

			mAnimator->CreateAnimation(
				MAKE_EFFECT_KEY(_type)
				, im
				, Vector2::Zero
				, Vector2(fWid, fHei)
				, IMMO_EFFECT_T_OFFSET[(UINT)_type]
				, len
				, 0.05f
				, (UINT)AC_SRC_OVER
			);
		}
		if (mAnimator->GetStopAnimator())
			mAnimator->Play(MAKE_EFFECT_KEY(_type), false);
	}
	void Tile::ClearAddETCTiles()
	{
		for (int i = 0; i < mETCTexs.size(); i++)
			mETCTexs[i] = Resources::Load<Image>(SQUARE__KEY, SQUARE__PATH);
	}
	void Tile::SetETCTiles(const wstring& key, const wstring& path)
	{
		++eTCTexsIdx %= mETCTexs.size();
		mETCTexs[eTCTexsIdx] = Resources::Load<Image>(key, path);
		SetScale(Vector2((float)(mETCTexs[eTCTexsIdx]->GetWidth() * 2), (float)(mETCTexs[eTCTexsIdx]->GetHeight() * 2)));
	}
	void Tile::Render(HDC hdc) {
		GameObject::Render(hdc);
		if(nullptr != mTileTex) {
			UINT tile_iWidth = mTileTex->GetWidth();
			UINT tile_iHeight = mTileTex->GetHeight();


			Vector2 vRenderPos = Camera::CalculatePos(GetPos());
			Vector2 vScale = GetScale();
			vRenderPos += mTileTex->GetOffset();
			if (TILE_T::MOVE_RANGE == mTileType) {
				BLENDFUNCTION func = {};
				func.BlendOp = AC_SRC_OVER;
				func.BlendFlags = 0;
				func.AlphaFormat = AC_SRC_ALPHA;
				func.SourceConstantAlpha = mConstant;

				AlphaBlend(hdc
					, (int)(vRenderPos.x)
					, (int)(vRenderPos.y)
					, (int)(vScale.x)
					, (int)(vScale.y)
					, mTileTex->GetHdc()
					, 0
					, 0
					, tile_iWidth
					, tile_iHeight
					, func);
			}
			else {
				TransparentBlt(hdc
					, (int)(vRenderPos.x)
					, (int)(vRenderPos.y)
					, (int)(vScale.x)
					, (int)(vScale.y)
					, mTileTex->GetHdc()
					, 0
					, 0
					, tile_iWidth
					, tile_iHeight
					, RGB(255, 0, 255));
			}
		}
		if (!mETCTexs.empty()) {
			for (int i = 0; i < mETCTexs.size(); i++) {
				if (nullptr == mETCTexs[i]) continue;
				UINT tile_iWidth = mETCTexs[i]->GetWidth();
				UINT tile_iHeight = mETCTexs[i]->GetHeight();

				Vector2 vRenderPos = Camera::CalculatePos(GetPos());
				Vector2 vScale = GetScale();
				TransparentBlt(hdc
					, (int)(vRenderPos.x)
					, (int)(vRenderPos.y)
					, (int)(vScale.x)
					, (int)(vScale.y)
					, mETCTexs[i]->GetHdc()
					, 0
					, 0
					, tile_iWidth
					, tile_iHeight
					, RGB(255, 0, 255));
			}
		}
	}
}