#pragma once
#include "mUnit.h"
namespace m {
    class Image;
    class Animator;
    class Pilot;
    class Weapon;
    class Alien :
        public Unit {
    public:

        Alien(ALIENS mType, Vector2 _coord, int idx);
        Alien(Alien& _origin);
        ~Alien();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void Render(HDC hdc) override;
        virtual void Release() override;

        virtual void idle() override;
        virtual void broken() override;
        virtual void water() override;
        virtual void emerge() override;

        void SetTargetCoord(Vector2 _coord) { tarGetCoord = _coord; }
        Vector2 GetTargetCoord() { return tarGetCoord; }

    private:
        ALIENS mAlienType;
        Vector2 tarGetCoord;
        vector<Scene::Vector2_1> alienPathQueue; // 전체 이동해야하는 최단거리.

        int mIdx;
    };
}

