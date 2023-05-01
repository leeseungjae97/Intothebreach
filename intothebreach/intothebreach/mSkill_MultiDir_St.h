#pragma once
#include "mSkill.h"
namespace m
{
    class Unit;
    class Skill_St;
	class Skill_MultiDir_St
		: public Skill
	{
    public:
        Skill_MultiDir_St(WEAPON_T _type, Unit* onwer, int num);
        ~Skill_MultiDir_St();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void Render(HDC hdc) override;
        virtual void Release() override;

        void ReInit(Vector2 stPos, Vector2* enPos, Vector2* glp, SKILL_T type);
        virtual void Active(HDC hdc) override;
        virtual void GuideWire(HDC hdc) override;
        virtual void SetEndFire(bool _endFire) override;
        virtual void SetStartFire(bool _stFire) override;
        virtual void SetStartRender(bool _sR) override;
        virtual void CheckDirection() override;
        virtual bool GetStartFire() override;
        virtual bool GetEndFire() override;
        virtual bool GetStartRender() override;
        virtual Vector2 GetEndCoord() override;

        int GetNum() { return num; }
        void SetNum(int _num) { num = _num; }
        vector<Skill_St*>& GetMSkills() { return mSkills; }
    private:
        vector<Skill_St*> mSkills;
        int num;
	};
}


