#pragma once
#include "mSkill.h"
namespace m
{
    class Skill_Arc :
        public Skill
    {
    public:
        Skill_Arc(SKILL_T _type, Unit* onwer);
        ~Skill_Arc();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void Render(HDC hdc) override;
        virtual void Release() override;

        virtual void ReInit(Vector2 stPos, Vector2 enPos, Vector2 glp, SKILL_T type) override;
        virtual void Active(HDC hdc) override;
        virtual void GuideWire(HDC hdc) override;
        virtual void CheckDirection();
        void DrawSmoke();

    private:
        float m_curTime = 0;
        float m_curZ = 0;
        vector<Background*> smokeVector;
    };

}

