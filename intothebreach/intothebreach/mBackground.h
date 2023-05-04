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
        void SetBrush(BRUSH_TYPE _type) { mType = _type; }
        void SetSizeUp(bool _b) { bSizeUp = _b; }
        void SetSizeUpxUnit(float _sizeup) { sizeUpUnitx = _sizeup; }
        void SetSizeUpyUnit(float _sizeup) { sizeUpUnity = _sizeup; }
        float GetWid() { return iWid; }
        float GetHei() { return iHei; }
        bool GetSmoothAppear() { return bSmoothAppear; }
        bool GetSmoothDisappear() { return bSmoothDisappear; }
        bool GetSizeUp() { return bSizeUp; }
        bool GetHover() { return bHover; }
        Vector2 GetOriginPos() { return originPos; }
    private :
        int iConstant;
        int idDir;
        int idVar;
        bool bBlink;
        bool bSmoothAppear;
        bool bSmoothDisappear;
        bool bCreateAnimation;
        bool bSizeUp;
        float sizeUpUnitx;
        float sizeUpUnity;

        float iWid;
        float iHei;
        BRUSH_TYPE mType;
        Animator* mAnimator;
        Vector2 vMovement;
        Vector2 originPos;
        bool bHover;

    };

}

