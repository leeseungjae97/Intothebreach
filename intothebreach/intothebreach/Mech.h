#pragma once
#include "mUnit.h"
#include "mImage.h"
namespace m
{
	class Weapon;
	class Pilot;
	class Skill;
	class Animator;
	class Mech : public Unit
	{
	public:
		Mech(MECHS _mech, Vector2 _coord, int _range, int _hp);
		Mech(Mech& _origin);
		~Mech();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void idle() override;
		virtual void broken() override;
		virtual void water() override;
		virtual void emerge() override;

		MECHS GetMechType() { return mMechType; }
	private:
		MECHS mMechType;
	};
}
