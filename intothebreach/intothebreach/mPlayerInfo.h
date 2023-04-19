#pragma once
#include "_Engine.h"
namespace m {
	class Mech;
	class Skill;
	class Weapon;
	class Pilot;
	class PlayerInfo {
	public:
		static vector<Mech*>& GetMechs() { return mMechs; };
		static void Initialize();
		static vector<Mech*> mMechs;
		static vector<Weapon*> mWeapons;
		static vector<Pilot*> mPilots;
		static int gridPower;
		static int defence;
		static int resetTurn;
	private:
	};
}

