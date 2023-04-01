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

        virtual void ReInit(Vector2 stPos, Vector2 enPos) override;
        virtual void Active(HDC hdc) override;
        virtual void GuideWire(HDC hdc) override;
        virtual void CheckDirection();
    private:
        float m_fMissile_distance;
        Vector2 Missile_vec;
        Vector2 curPos;
        float arcXMaxTime;
        float arcYMaxTime;
        float maxHeight;
    };

}

