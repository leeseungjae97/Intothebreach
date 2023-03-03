#pragma once
#include "mGameObject.h"
namespace m {
    class Alien :
        public GameObject {
    public:
        Alien();
        ~Alien();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void Render(HDC hdc) override;
        virtual void Release() override;

    private:

    };
}

