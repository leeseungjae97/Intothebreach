#include "mPlayerInfo.h"
#include "Mech.h"
#include "Alien.h"
//#include "mPilot.h"
namespace m {

	vector<Mech*> GameComp::mMechs;
	vector<Mech*> GameComp::mSaveMechs;
	vector<GameComp::MechInfo> GameComp::mechInfos;
	vector<Alien*> GameComp::mAliens;
	//vector<Pilot*> GameComp::mPilots;
	int GameComp::gridPower;
	int GameComp::defence;
	int GameComp::resetTurn;
	int GameComp::reactor;
	int GameComp::star;
	int GameComp::savedPeople;
	int GameComp::saveTurnPeople;
	PILOT_T GameComp::mPilots[3]{};
	vector<GameComp::Inven> GameComp::inventoryItems;
	bool GameComp::combatEnd;
	GameComp::Inven GameComp::Inven::None = Inven(-1, -1);
	void GameComp::Initialize()
	{
		combatEnd = false;
		gridPower = 5;
		defence = 15;
		resetTurn = 1;
		reactor = 0;
		star = 0;
		savedPeople = 0;
		saveTurnPeople = 500;
	}

}