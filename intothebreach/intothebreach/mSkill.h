#pragma once
#include "mGameObject.h"
namespace m {
    class Skill :
        public GameObject {
    public:
        Skill(SKILL_T _type);
        Skill(Skill& _origin);
        ~Skill();
        
        virtual void Initialize() override;
        virtual void Update() override;
        virtual void Render(HDC hdc) override;
        virtual void Release() override;

        void ReInit(Vector2 stPos, Vector2 enPos);
        void Active(HDC hdc);
        void GuideWire(HDC hdc);
        //void PreCal();

        Vector2 GetEndCoord() { return endCoord; }
        void SetEndCoord(Vector2 _coord) { endCoord = _coord; }
        void CalEndFire();

        LAYER_TYPE GetLayerType() { return mLayerType; }
        SKILL_T GetSkillType() { return mType; }
        Vector2 GetEndPos() { return mFinalEdPos; }
        bool GetEndFire() { return endFire; }
        bool GetStFire() { return stFire; }
        bool GetStartRender(){ return startRender; }

        void SetLayerType(LAYER_TYPE _type) { mLayerType = _type; }
        void SetSkillType(SKILL_T _type) { mType = _type; }
        void SetEndPos(Vector2 _pos) {mFinalEdPos = _pos;}
        void SetStPos(Vector2 _pos) { mStPos = _pos; }
        void SetEndFire(bool _endFire) { endFire = _endFire; }
        void SetStFire(bool _stFire) { stFire = _stFire; }
        void SetStartRender(bool _sR) { startRender = _sR; }

    private:
        bool endFire;
        bool stFire;
        bool startRender;

        float offsetHeight;
        float maxTheta;
        float minTheta;
        float fHeight;
        float fMaxTime;
        float fTime;
        float velocityY;
        float velocityX;
        float gravityAccel;

        float fDistance;

        float arcTheta;

        LAYER_TYPE mLayerType;
        SKILL_T mType;

        Vector2 Missile_vec;
        Vector2 endCoord;
        Vector2 mStPos;
        Vector2 mFinalEdPos;
    };
}

