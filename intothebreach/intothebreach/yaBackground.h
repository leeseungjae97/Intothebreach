#pragma once
#include "yaGameObject.h"
#include "yaImage.h"
namespace ya {
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

        void SetPos(Vector2 _pos);
    private :
        Image* mImage;
        wstring mPath;
        wstring mKey;
        bool mIsFull;
        bool mIsCenter;
        int mSizeUp;
    };

}

