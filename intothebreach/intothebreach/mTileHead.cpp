#include "mTileHead.h"
#include "mImage.h"
namespace m {
	TileHead::TileHead() 
		: mTileHeadTex(nullptr)
	{
	}
	TileHead::~TileHead() {
	}
	void TileHead::Update() {

	}
	void TileHead::Render(HDC hdc) {
		assert(mTileHeadTex);

		UINT tile_head_iWidth = mTileHeadTex->GetWidth();
		UINT tile_head_iHeight = mTileHeadTex->GetHeight();

		TransparentBlt(hdc
			, (int)(mPos.x)
			, (int)(mPos.y)
			, (int)(tile_head_iWidth * 2)
			, (int)(tile_head_iHeight * 2)
			, mTileHeadTex->GetHdc()
			, 0
			, 0
			, tile_head_iWidth
			, tile_head_iHeight
			, RGB(255, 0, 255));
	}
	
}
