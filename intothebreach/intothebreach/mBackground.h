#pragma once
#include "mGameObject.h"
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

        Vector2 GetSize();
        void SetTex(const wstring& key, const wstring& path, ISLAND_T type);
        void Clear();
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

