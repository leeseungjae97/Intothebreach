#pragma once
#include "_Engine.h"
namespace m {
	class Mech;
	class Alien;
	class Skill;
	class Weapon;
	class Pilot;
	class GameComp {
	public:
		struct MechInfo
		{
				
		};
		static vector<Mech*>& GetMechs() { return mMechs; };
		static void Initialize();
		static vector<Mech*> mMechs;
		static vector<Mech*> mSaveMechs;
		
		static vector<Alien*> mAliens;
		static vector<Weapon*> mWeapons;
		static vector<Pilot*> mPilots;
		static int playerUnits[3];
		static int gridPower;
		static int defence;
		static int resetTurn;
		static int reactor;
		static int star;
		static int savePeople;
	private:
	};
}

