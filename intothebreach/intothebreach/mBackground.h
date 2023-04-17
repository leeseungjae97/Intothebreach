#pragma once
#include "mUI.h"
namespace m {
    class Background :
        public UI {
    public:
        Background(const wstring& key, const wstring& path
            , int _sizeUp = 0, bool _full = false
            , int mDir = DEFAULT, bool _alphaCheck = false);
        ~Background();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);
        virtual void Release();

        void SetAlphaConstant(int _a) { iConstant = _a; }
        int GetAlphaConstant() { return iConstant; }

        void SetBlink(bool _b) { bBlink = _b; }
        void SetMovement(Vector2 _v) { vMovement = _v; }
        void SmoothDisappear(bool _b) { bSmoothDisappear = _b; }
        void SmoothAppear(bool _b) { bSmoothAppear = _b; }
        void SetIdVar(int _v) { idVar = _v; }

        bool GetSmoothAppear() { return bSmoothAppear; }
        bool GetSmoothDisappear() { return bSmoothDisappear; }
    private :
        int iConstant;
        int idDir;
        int idVar;
        bool bBlink;
        bool bSmoothAppear;
        bool bSmoothDisappear;

        Vector2 vMovement;
    };

}

