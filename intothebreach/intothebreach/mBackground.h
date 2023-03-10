#pragma once
#include "mGameObject.h"
#include "mResources.h"
#include "mImage.h"
namespace m {
    class Background :
        public GameObject {
    public:
        Background(const wstring& key, const wstring& path
            , int _sizeUp = 0, bool _full = false
            , bool _isCenter = false, bool _alphaCheck = false);
        ~Background();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);
        virtual void Release();

        Vector2 GetSize() { return Vector2((float)mImage->GetWidth(), (float)mImage->GetHeight()); }
        void SetTex(const wstring& key, const wstring& path, ISLAND_T type) {
            mImage = Resources::Load<Image>(key, path);
            mImage->SetOffset(Vector2(ISLAND_OUTLINE_OFFSET[(UINT)type].x, ISLAND_OUTLINE_OFFSET[(UINT)type].y));
        }
        void Clear() {
            mImage = Resources::Load<Image>(mKey, mPath);
        }
    private :
        Image* mImage;
        wstring mPath;
        wstring mKey;

        bool mIsFull;
        bool mIsCenter;
        bool mAlpha;
        int mSizeUp;
    };

}

