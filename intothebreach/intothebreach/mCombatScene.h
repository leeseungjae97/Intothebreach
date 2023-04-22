#pragma once
#include "mScene.h"
namespace m {
	class Tile;
	class TileHead;
	class Button;
	class CombatScene : public Scene {
	public:
		CombatScene();
		~CombatScene();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;;
		
		int GetTextTurnNumber() { return iTurn; }
		void RandSpawnAlien(int number);
		void SetTextTurnNumber(int _turn);
		void PutUnitBeforeCombat();
		void PlayerTurnBackground();
		void AlienTurnBackground();
		void AlienIndexReSort();
		void ButtonActivationCondition();

		Button* GetTurnBox1() { return playerTurnBox; }
		Button* GetTurnBox2() { return alienTurnBox; }

	private:
		vector<Background*> combatBack;
		bool bSetPosition;
		//bool bConfirm;
		Button* textDeploy;
		Button* btnConfirm;
		Button* textTurn;
		Button* textTurnNum;

		Button* gridPowerBox;
		vector<Button*> gridPowers;

		Button* textDefence1;
		Button* textDefence2;
		Button* btnTurnEnd;
		Button* btnUndoMove;
		Button* btnInitTurn;
		
		Button* playerTurnBox;
		Button* alienTurnBox;

		Button* playerUnitInfo;
		Button* selectUnitBox;

		Button* endMissionBox;
		vector<Mech*> infoUnits;
		//Button* unit1;
		//Button* unit1Hp;

		//Button* unit2;
		//Button* unit2Hp;

		//Button* unit3;
		//Button* unit3Hp;

		int mechIdx;
		int iTurn;
	};
}

