#pragma once
#include "mGameObject.h"
#include "mResources.h"
namespace m {
    class Image;
    class Tile :
        public GameObject {
    public:
        Tile(Vector2 _coord);
        Tile();
        Tile(int m);
        ~Tile();
   

    public:
        void SetTileTexture(const wstring& key, const wstring& path) {
            mTileTex = Resources::Load<Image>(key, path);
            SetScale(Vector2((float)(mTileTex->GetWidth() * 2), (float)(mTileTex->GetHeight() * 2)));
        }
        void SetTileType(TILE_T _type) {
            mTileType = _type;
        }
        TILE_T GetTileType() {
            return mTileType;
        }
        void InitETCTiles(int _size) {
            mETCTexs.resize(_size);
        }
        void ClearAddETCTiles() {
            for(int i = 0; i < mETCTexs.size(); i ++) 
                mETCTexs[i] = Resources::Load<Image>(SQUARE__KEY, SQUARE__PATH);
        }
        void SetETCTiles(const wstring& key, const wstring& path) {
            ++eTCTexsIdx %= mETCTexs.size();
            mETCTexs[eTCTexsIdx] = Resources::Load<Image>(key, path);
            SetScale(Vector2((float)(mETCTexs[eTCTexsIdx]->GetWidth() * 2), (float)(mETCTexs[eTCTexsIdx]->GetHeight() * 2)));
        }
        void SetSourceConstantAlpha(BYTE _constant) {
            mConstant = _constant;
        }
        Vector2 GetCoord() { return mCoord; }
        Vector2 GetCenterPos() 
        { 
            return Vector2(GetPos().x + mTileTex->GetWidth() / 2, GetPos().y + mTileTex->GetHeight() / 2);
        }
    private:
        virtual void Update() override;
        virtual void Render(HDC hdc) override;

    private:
        vector<Image*> mETCTexs;
        Image*      mTileTex;
        TILE_T      mTileType;
        Vector2     mCoord;

        BYTE mConstant;
        int eTCTexsIdx;
    };
}

