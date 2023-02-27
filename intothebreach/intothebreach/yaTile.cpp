#include "yaTile.h"
namespace ya {
	Tile::Tile(Vector2 pos)
		: GameObject()
		, mImage(nullptr)
		, mPos{}
	{
	}
	Tile::Tile(Image* img, int index) 
	{
		Initialize(img, index);
	}
	Tile::~Tile() {
	}
	void Tile::Initialize(Image* img, int index) {
		mIndex = index;
		if (nullptr == img || index < 0) return;

		mImage = img;



	}
	void Tile::SetIndex(int index) {
	}
	void Tile::Update() {
	}
	void Tile::Render(HDC hdc) {
	}
}