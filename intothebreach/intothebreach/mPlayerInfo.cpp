#include "mPlayerInfo.h"
#include "Mech.h"
#include "mPilot.h"
namespace m {

	vector<Mech*> PlayerInfo::mMechs;
	//vector<Weapon*> PlayerInfo::mWeapons;
	vector<Pilot*> PlayerInfo::mPilots;
	int PlayerInfo::gridPower;
	int PlayerInfo::defence;

	void PlayerInfo::Initialize()
	{
		gridPower = 5;
		defence = 15;
	}

}