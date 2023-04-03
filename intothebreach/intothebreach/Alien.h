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

        Alien(ALIENS mType, Vector2 _coord, size_t idx);
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

        bool AlienMoveToAttackCheck(Vector2 _alienCoord, int curAlien);
        void AlienMoveCheck(int& curAlien);
        void AlienMapCheck(int curAlien);

        void SetTargetCoord(Vector2 _coord) { tarGetCoord = _coord; }
        Vector2 GetTargetCoord() { return tarGetCoord; }
        void SetFinalMoveCoord(Vector2 _coord) { finalMoveCoord = _coord; }
        Vector2 GetFinalMoveCoord() { return finalMoveCoord; }

    private:
        ALIENS mAlienType;
        int moveCnt;
        Vector2 tarGetCoord;
        Vector2 finalMoveCoord;
        vector<Vector2_1> directQueue;
        vector<Vector2_1> alienPathQueue; // 전체 이동해야하는 최단거리.
    };
}

