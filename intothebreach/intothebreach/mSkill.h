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

        Vector2 GetCurCoord() { return curCoord; }
        void SetLayerType(LAYER_TYPE _type) { mLayerType = _type; }
        LAYER_TYPE GetLayerType() { return mLayerType; }
        void PreCal();
        void SetSkillType(SKILL_T _type) { mType = _type; }
        SKILL_T GetSkillType() { return mType; }
        void SetStPos(Vector2 _pos) { mStPos = _pos; }
        void SetEndPos(Vector2 _pos) {
            mEdPos = _pos;
            mEdPos -= mStPos;
            mFinalEdPos = _pos;
            mEdPos.Normalize();
        }
        Vector2 GetEndPos() { mEdPos; }

    private:
        float mTheta;
        
        float vx;
        float vy;
        float g;

        float dat;
        float mh;
        float dh;
        float t = 0.0f;
        float MAX_Y;
        float mht = 1.5f;
        LAYER_TYPE mLayerType;
        SKILL_T mType;
        Vector2 curCoord;
        Vector2 mStPos;
        Vector2 mEdPos;
        Vector2 mFinalEdPos;
    };
}

