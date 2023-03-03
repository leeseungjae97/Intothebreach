#pragma once
#include "mGameObject.h"
namespace m {
	class Image;
	class TileHead :public GameObject{
	public:
		TileHead();
		~TileHead();

		virtual void Render(HDC hdc) override;
		virtual void Update() override;
	private:
		Image* mTileHeadTex;
		Vector2 mPos;
	};
}

