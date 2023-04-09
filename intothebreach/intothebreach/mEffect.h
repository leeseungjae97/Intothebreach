#pragma once
#include "mGameObject.h"
namespace m
{
    class mEffect :
        public GameObject
    {
    public:
        mEffect();
        ~mEffect();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);
        virtual void Release();

    private:
        bool bRandVector;
        bool bRandConstant;
        bool bRandMoveVector;
    };
}


