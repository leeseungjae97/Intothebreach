#pragma once
#include "mGameObject.h"
#include "mImage.h"
namespace m {
    class Background :
        public GameObject {
    public:
        Background(const wstring& key, const wstring& path
            , int _sizeUp = 0, bool _full = false, bool _isCenter = false);
        ~Background();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);
        virtual void Release();

    private :
        Image* mImage;
        wstring mPath;
        wstring mKey;
        bool mIsFull;
        bool mIsCenter;
        int mSizeUp;
    };

}

