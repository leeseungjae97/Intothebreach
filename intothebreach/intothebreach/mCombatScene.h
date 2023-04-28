#pragma once
#include "mScene.h"
namespace m
{
	class Tile;
	class TileHead;
	class Button;
	class Alien;
	class CombatScene : public Scene
	{
	public:
		CombatScene(TILE_T mapType, int mapNum);
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
		void LoadMap();

		Button* GetTurnBox1() { return playerTurnBox; }
		Button* GetTurnBox2() { return alienTurnBox; }
		void ShowMechInfo(Mech* mech, bool show);
		void SetWPBow(int selection);
		Button* GetWeaponPilotBox() { return boxWeaponPilot; }
		Button* GetPilotBackBox() { return boxPilotBack; }
		Button* GetWeaponBox() { return boxWeapon; }
		Button* GetPilotBox() { return boxPilot; }

	private:
		vector<Background*> combatBack;
		bool bSetPosition;
		bool endGame;
		bool showEnd;
		bool bLoadMap;
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

		Button* boxWeaponPilot;
		Button* boxWPBack;
		Button* boxPilotBack;
		Button* boxPilot;
		Button* boxWeapon;

		Button* endMissionBox;
		vector<Mech*> infoUnits;
		//vector<Alien*> mAliens;
		TILE_T mapTileType;
		int mapNum;
		int mechIdx;
		int iTurn;
	};
}

