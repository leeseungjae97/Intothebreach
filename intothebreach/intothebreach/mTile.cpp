#include "mTile.h"
#include "mImage.h"
#include "mCamera.h"
namespace m {
	//wstring tileTypeName[(UINT)TILE_T::END] = {
	//L"texture\\terrain\\green\\",
	//L"texture\\terrain\\acid\\",
	//L"texture\\terrain\\sand\\",
	//L"texture\\terrain\\snow\\",
	//L"texture\\terrain\\volcano\\",
	//L"texture\\terrain\\cave\\"
	//};


	Tile::Tile(Vector2 _coord)
		: mTileTex(nullptr)
		, mCoord(_coord)
		, eTCTexsIdx(0)
		, mConstant(50)
	{
		AddComponent(new Transform());
	}
	Tile::Tile()
		: mTileTex(nullptr)
		, mCoord(Vector2::One)
		, eTCTexsIdx(0)
		, mConstant(50)
	{
		AddComponent(new Transform());
		SetScale(Vector2(TILE_SIZE_X * 2, TILE_SIZE_Y * 2));
	}
	Tile::Tile(int m)
		: mTileTex(nullptr)
		, mCoord(Vector2::One) 
		, eTCTexsIdx(0)
		, mConstant(50)
	{
		AddComponent(new Transform());
	}
	Tile::~Tile() {
	}
	void Tile::Update() {
	}

	void Tile::Render(HDC hdc) {
		if (!mETCTexs.empty()) {
			for (int i = 0; i < mETCTexs.size(); i++) {
				assert(mETCTexs[i]);
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
		else {
			assert(mTileTex);
			UINT tile_iWidth = mTileTex->GetWidth();
			UINT tile_iHeight = mTileTex->GetHeight();


			Vector2 vRenderPos = Camera::CalculatePos(GetPos());
			Vector2 vScale = GetScale();

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
	}
}