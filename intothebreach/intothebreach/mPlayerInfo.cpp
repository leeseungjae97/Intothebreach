#include "mPlayerInfo.h"
#include "Mech.h"
#include "Alien.h"
#include "mPilot.h"
namespace m {

	int GameComp::playerUnits[3] = {};
	vector<Mech*> GameComp::mMechs;
	vector<Mech*> GameComp::mSaveMechs;
	vector<Alien*> GameComp::mAliens;
	vector<Pilot*> GameComp::mPilots;
	int GameComp::gridPower;
	int GameComp::defence;
	int GameComp::resetTurn;
	int GameComp::reactor;
	int GameComp::star;
	int GameComp::savePeople;
	void GameComp::Initialize()
	{
		gridPower = 5;
		defence = 15;
		resetTurn = 1;
		reactor = 0;
		star = 0;
		savePeople = 0;
	}

}