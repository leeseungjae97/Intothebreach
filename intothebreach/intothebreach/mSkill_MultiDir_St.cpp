#include "mSkill_MultiDir_St.h"
#include "mSkill_St.h"
#include "mUnit.h"
namespace m
{
	Skill_MultiDir_St::Skill_MultiDir_St(WEAPON_T _type, Unit* onwer, int _num)
		: Skill(_type, onwer)
		, num(_num)
	{
		
		for (int i = 0; i < _num; i++)
		{
			Skill_St* st = new Skill_St(_type, onwer);
			mSkills.push_back(st);
		}

	}
	Skill_MultiDir_St::~Skill_MultiDir_St()
	{
	}
	void Skill_MultiDir_St::Initialize()
	{
		for (int i = 0; i < mSkills.size(); i++)
		{
			mSkills[i]->Initialize();
		}
	}
	void Skill_MultiDir_St::Update()
	{
		if (GetOwner()->GetState() == GameObject::STATE::Death
			|| GetOwner()->GetState() == GameObject::STATE::Delete)
		{
			for (int i = 0; i < mSkills.size(); i++)
			{
				mSkills[i]->SetState(GameObject::STATE::Delete);
			}
		}
		for (int i = 0; i < mSkills.size(); i++)
		{
			mSkills[i]->Update();
		}
	}
	void Skill_MultiDir_St::Render(HDC hdc)
	{
		for (int i = 0; i < mSkills.size(); i++)
		{
			mSkills[i]->Render(hdc);
		}
	}
	void Skill_MultiDir_St::Release()
	{}
	void Skill_MultiDir_St::ReInit(Vector2 stPos, Vector2* enPos, Vector2* glp, SKILL_T type)
	{
		for (int i = 0; i < mSkills.size(); i++)
		{
			if (enPos[i] == Vector2::Minus) continue;
			if (stPos == enPos[i])
			{
				mSkills[i]->SetStartRender(false);
				continue;
			}
			mSkills[i]->SetStartRender(true);
			mSkills[i]->ReInit(stPos, enPos[i], glp[i], type);
		}
	}
	void Skill_MultiDir_St::Active(HDC hdc)
	{
		for (int i = 0; i < mSkills.size(); i++)
		{
			mSkills[i]->Active(hdc);
		}
	}
	void Skill_MultiDir_St::GuideWire(HDC hdc)
	{
		for (int i = 0; i < mSkills.size(); i++)
		{
			mSkills[i]->GuideWire(hdc);
		}
	}
	void Skill_MultiDir_St::SetEndFire(bool _endFire)
	{
		for (int i = 0; i < mSkills.size(); i++)
		{
			mSkills[i]->SetEndFire(_endFire);
		}
	}
	void Skill_MultiDir_St::SetStartFire(bool _stFire)
	{
		for (int i = 0; i < mSkills.size(); i++)
		{
			mSkills[i]->SetStartFire(_stFire);
		}
	}
	void Skill_MultiDir_St::SetStartRender(bool _sR)
	{
		for (int i = 0; i < mSkills.size(); i++)
		{
			mSkills[i]->SetStartRender(_sR);
		}
	}
	void Skill_MultiDir_St::CheckDirection()
	{
		for (int i = 0; i < mSkills.size(); i++)
		{
			if (mSkills[i]->GetStartFire())
			{
				mSkills[i]->CheckDirection();
			}
		}
	}
	bool Skill_MultiDir_St::GetStartFire()
	{
		bool aSF = true;
		for (int i = 0; i < mSkills.size(); i++)
		{
			if (!mSkills[i]->GetStartFire()) aSF = false;
		}
		return aSF;
	}
	bool Skill_MultiDir_St::GetEndFire()
	{
		bool aSF = true;
		for (int i = 0; i < mSkills.size(); i++)
		{
			if (!mSkills[i]->GetEndFire()) aSF = false;
		}
		return aSF;
	}
	bool Skill_MultiDir_St::GetStartRender()
	{
		return true;
	}
	Vector2 Skill_MultiDir_St::GetEndCoord()
	{
		return mSkills[0]->GetEndCoord();
	}
}