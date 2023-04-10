#pragma once
#include "mGameObject.h"
namespace m
{
	class Image;
	class Tile :
		public GameObject
	{
	public:
		Tile(Vector2 _coord);
		Tile();
		~Tile();


	public:
		void SetTileTexture(const wstring& key, const wstring& path);
		void SetTileTexture(const wstring& key, const wstring& path, Vector2 offset);
		void SetTileAnimator(COMBAT_ANIM_TILE_T _type, BYTE fConstant = 0, bool alpha = false);
		void SetTileAnimator(DIR_EFFECT_T _type, BYTE fConstant = 0, bool alpha = false);
		void SetTileAnimator(IMMO_EFFECT_T _type, BYTE fConstant = 0, bool alpha = false);
		void SetTileType(TILE_T _type) { mTileType = _type; }
		TILE_T GetTileType() { return mTileType; }
		void InitETCTiles(int _size) { mETCTexs.resize(_size); }
		void ClearAddETCTiles();
		void SetETCTiles(const wstring& key, const wstring& path);
		void SetSourceConstantAlpha(BYTE _constant) { mConstant = _constant; }
		Vector2 GetCoord() { return mCoord; }
		Vector2 GetCenterPos()
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
	private:
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Initialize() override;

	private:
		vector<Image*> mETCTexs;
		Image* mTileTex;
		Animator* mAnimator;
		TILE_T      mTileType;
		Vector2     mCoord;

		BYTE mConstant;
		int eTCTexsIdx;
	};
}

