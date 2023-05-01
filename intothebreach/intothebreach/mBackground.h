#pragma once
#include "mUI.h"
namespace m {
    class Animator;
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
        void SetOriginPos(Vector2 _pos) { originPos = _pos; }
        void SmoothDisappear(bool _b) { bSmoothDisappear = _b; }
        void SmoothAppear(bool _b) { bSmoothAppear = _b; }
        void SetIdVar(int _v) { idVar = _v; }
        void CreateAnimationBack(const wstring& key, const wstring& path, int len, float duration);
        void SetAnimation(bool _b) { bCreateAnimation = _b; }

        bool GetSmoothAppear() { return bSmoothAppear; }
        bool GetSmoothDisappear() { return bSmoothDisappear; }
        Vector2 GetOriginPos() { return originPos; }
    private :
        int iConstant;
        int idDir;
        int idVar;
        bool bBlink;
        bool bSmoothAppear;
        bool bSmoothDisappear;
        bool bCreateAnimation;

        Animator* mAnimator;
        Vector2 vMovement;
        Vector2 originPos;
    };

}

