#pragma once
#include "yaGameObject.h"
namespace ya {
	class Image;
	class Tile :public GameObject{
	public:
		Tile(Vector2 pos);
		Tile(Image* img, int index);
		~Tile();

	public:
		void Initialize(Image* img, int index);
		void SetIndex(int index);
		int GetIndex() { return mIndex; }

		virtual void Update() override;
		virtual void Render(HDC hdc) override;
	private:
		Image* mImage;
		int mIndex;
		Vector2 mPos;
	};
}

