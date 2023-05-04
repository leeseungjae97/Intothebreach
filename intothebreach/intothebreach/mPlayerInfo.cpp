#include "mPlayerInfo.h"
#include "Mech.h"
#include "Alien.h"
//#include "mPilot.h"
namespace m
{

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
	int GameComp::clearLandMatric[4][8]{};
	int GameComp::curLandSection = 0;
	int GameComp::curLand = 0;
	int GameComp::checkClearLand[5]{};

	Building* GameComp::bomb;
	bool GameComp::bKillLeader;
	int GameComp::iBlockCnt;
	int GameComp::iKillEnCnt;
	int GameComp::iMechDamageCnt;
	int GameComp::iGridDamageCnt;
	bool GameComp::bStructureAlive;
	int GameComp::iStructDesCnt;

	void GameComp::Initialize()
	{
		//clearLandMatric[0][] = CLEAR;
		//clearLandMatric[0][2] = CLEAR;
		//clearLandMatric[0][3] = CLEAR;
		//clearLandMatric[0][4] = CLEAR;
		//clearLandMatric[0][1] = CLEAR;
		combatEnd = false;
		gridPower = 5;
		defence = 15;
		resetTurn = 1;
		reactor = 0;
		star = 0;
		savedPeople = 0;
		saveTurnPeople = 500;

		bKillLeader = false;
		iBlockCnt = 0;
		iKillEnCnt = 0;
		iMechDamageCnt = 0;
		iGridDamageCnt = 0;
		iStructDesCnt = 0;
		bStructureAlive = true;

		bomb = nullptr;
	}
	void GameComp::startGame()
	{
		for (int i = 0; i < mAliens.size(); i++)
		{
			mAliens[i]->SetVisibleHp(false);
			mAliens[i]->SetState(GameObject::STATE::Delete);
		}
		mAliens.clear();

		saveTurnPeople = 500;
		resetTurn = 1;
		bKillLeader = false;
		iBlockCnt = 0;
		iKillEnCnt = 0;
		iMechDamageCnt = 0;
		iGridDamageCnt = 0;
		iStructDesCnt = 0;
		bStructureAlive = true;
	}

}