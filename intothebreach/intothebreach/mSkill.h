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

            if (mStPos < mFinalEdPos) minPos = mStPos;
            else minPos = mFinalEdPos;
        }
        Vector2 GetEndPos() { mEdPos; }

    private:
        float mTheta;
        float fTime;

        float fEndHeight;
        float fHeight;

        float fg;
        float fy;
        float fMaxTime = 1.f;
        float fEndTime;
        float fx;

        float mSpeed;

        float time2;
        Vector2 Missile_vec = Vector2(0,0);
        Vector2 Missile_vec2;
        float a;

        float m_Z;
        float m_fZ;
        float time;

        bool ifChild;

        float m_fTarget_distance;

        Skill* mC;
        
        float vx;
        float vy;

        float h;
        float k;

        float tm = 0;

        LAYER_TYPE mLayerType;
        SKILL_T mType;
        Vector2 curCoord;
        Vector2 minPos;
        Vector2 mStPos;
        Vector2 mEdPos;
        Vector2 mFinalEdPos;
    };
}

