#pragma once
#include "mUnit.h"

namespace m {
    class Image;
    class Animator;
    class Building :
        public Unit {
    public:
        Building(STRUCTURES _type, Vector2 _coord, int mIdx);
        ~Building();

 /*       void SetCoord(Vector2 _coord) { mCoord = _coord; }
        void SetFinalPos(Vector2 _pos) { mFinalPos = _pos; }
        void SetFinalCoord(Vector2 _coord) { mFinalCoord = _coord; }

        Vector2 GetFinalPos() { return mFinalPos; }
        Vector2 GetCoord() { return mCoord; }
        Vector2 GetFinalCoord() { return mFinalCoord; }*/

        STRUCTURES GetType() { return mType; }
        virtual void Update() override;
        virtual void Render(HDC hdc) override;

        virtual void idle() override;
        virtual void broken() override;
        virtual void water() override;
        virtual void emerge() override;

    private:
        //Animator* mAnimator;
        //Image* mImage;
        //Vector2 mCoord;
        //Vector2 mFinalCoord;
        //Vector2 mFinalPos;
        Vector2 mOffset;
        STRUCTURES mType;
    };
}

