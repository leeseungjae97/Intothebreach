#include "mPlayerInfo.h"
#include "Mech.h"
#include "mPilot.h"
namespace m {

	vector<Mech*> PlayerInfo::mMechs;
	//vector<Weapon*> PlayerInfo::mWeapons;
	vector<Pilot*> PlayerInfo::mPilots;
	int PlayerInfo::gridPower;
	int PlayerInfo::defence;
	int PlayerInfo::resetTurn;
	void PlayerInfo::Initialize()
	{
		gridPower = 5;
		defence = 15;
		resetTurn = 1;
	}

}