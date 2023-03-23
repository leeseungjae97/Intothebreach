#pragma once
#include "mGameObject.h"
namespace m {
    class Skill :
        public GameObject {
    public:
        Skill(SKILL_T _type);
        Skill(Skill& _origin);
        Skill();
        ~Skill();
        
        virtual void Initialize() override;
        virtual void Update() override;
        virtual void Render(HDC hdc) override;
        virtual void Release() override;

        Vector2 GetEndCoord() { return endCoord; }
        void SetEndCoord(Vector2 _coord) { endCoord = _coord; }

        void SetLayerType(LAYER_TYPE _type) { mLayerType = _type; }
        LAYER_TYPE GetLayerType() { return mLayerType; }
        void PreCal();
        void SetSkillType(SKILL_T _type) { mType = _type; }
        SKILL_T GetSkillType() { return mType; }
        void SetStPos(Vector2 _pos) { mStPos = _pos; }

        void SetEndPos(Vector2 _pos) {mFinalEdPos = _pos;}
        Vector2 GetEndPos() { return mFinalEdPos; }
        void SetEndFire(bool _endFire) { endFire = _endFire; }

        bool GetEndFire() { return endFire; }
        void CalEndFire();
    private:
        Vector2 Missile_vec;

        float maxHeight;

        float m_fMissile_distance;

        bool endFire;
        bool underAttack;

        float offsetHeight;
        float maxTheta;
        float minTheta;
        float fHeight;
        float fMaxTime;
        float fTime;
        float velocityY;
        float velocityX;
        float gravityAccel;

        Vector2 prevMPos;
        float arcTheta;

        LAYER_TYPE mLayerType;

        SKILL_T mType;

        Vector2 endCoord;
        Vector2 curPos;

        Vector2 mStPos;
        Vector2 mFinalEdPos;
    };
}

