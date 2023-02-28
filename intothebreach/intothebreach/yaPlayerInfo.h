#pragma once
#include "YamYamEngine.h"
namespace ya {
	class Mech;
	class Skill;
	class Weapon;
	class Pilot;
	class PlayerInfo {
	public:
		PlayerInfo();
		~PlayerInfo();

	public:
		vector<Mech*>& GetMechs() { return mMechs; };

	private:
		vector<Mech*> mMechs;
		vector<Skill*> mSkills;
		vector<Weapon*> mWeapons;
		vector<Pilot*> mPilots;
	};
}

