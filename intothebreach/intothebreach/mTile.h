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
        }
        void SetTileType(TILE_T _type) {
            mTileType = _type;
        }
        Vector2 GetCoord() { return mCoord; }
    private:
        virtual void Update() override;
        virtual void Render(HDC hdc) override;

    private:
        Image*      mTileTex;
        TILE_T      mTileType;
        Vector2     mCoord;
    };
}

