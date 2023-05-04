#pragma once
#include "mScene.h"
namespace m
{
	class Tile;
	class TileHead;
	class Button;
	class Alien;
	class Sound;
	class CombatScene : public Scene
	{
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
		wstring battleThemes[6][5]{
			{
				L"..\\Resources\\sound\\music\\mus_grass_combat_delta.wav",
				L"..\\Resources\\sound\\music\\mus_grass_combat_gamma.wav",
				L"..\\Resources\\sound\\music\\mus_grass_combat_new.wav",
				L"",
				L"..\\Resources\\sound\\music\\mus_grass_bossmap.wav"
			},
			{
				L"..\\Resources\\sound\\music\\mus_sand_combat_eastwood.wav",
				L"..\\Resources\\sound\\music\\mus_sand_combat_guitar.wav",
				L"..\\Resources\\sound\\music\\mus_sand_combat_montage.wav",
				L"..\\Resources\\sound\\music\\mus_sand_combat_western.wav",
				L"..\\Resources\\sound\\music\\mus_sand_bossmap.wav"
			},
			{
				L"..\\Resources\\sound\\music\\mus_snow_combat_ice.wav",
				L"..\\Resources\\sound\\music\\mus_snow_combat_train.wav",
				L"..\\Resources\\sound\\music\\mus_snow_combat_zimmer.wav",
				L"",
				L"..\\Resources\\sound\\music\\mus_snow_bossmap.wav"
			},
			{
				L"..\\Resources\\sound\\music\\mus_acid_combat_detritus.wav",
				L"..\\Resources\\sound\\music\\mus_acid_combat_new.wav",
				L"..\\Resources\\sound\\music\\mus_acid_combat_ominous.wav",
				L"..\\Resources\\sound\\music\\mus_acid_combat_synth.wav",
				L"..\\Resources\\sound\\music\\mus_acid_bossmap.wav"
			},
			{
				L"..\\Resources\\sound\\music\\mus_finalboss.wav",
				L"..\\Resources\\sound\\music\\mus_finalboss.wav",
				L"..\\Resources\\sound\\music\\mus_finalboss.wav",
				L"..\\Resources\\sound\\music\\mus_finalboss.wav",
				L"..\\Resources\\sound\\music\\mus_finalboss.wav",
			},
			{
				L"..\\Resources\\sound\\music\\mus_title_B.wav",
				L"..\\Resources\\sound\\music\\mus_title_B.wav",
				L"..\\Resources\\sound\\music\\mus_title_B.wav",
				L"..\\Resources\\sound\\music\\mus_title_B.wav",
				L"..\\Resources\\sound\\music\\mus_title_B.wav",
			}
			
		};
		wstring deploySounds[3]{
			L"..\\Resources\\sound\\sfx\\ui_battle_preplan_place_mech_01.wav",
			L"..\\Resources\\sound\\sfx\\ui_battle_preplan_place_mech_02.wav",
			L"..\\Resources\\sound\\sfx\\ui_battle_preplan_place_mech_03.wav",
		};
		wstring battleAmbis[5]{
			L"..\\Resources\\sound\\ambience\\amb_grass_base.wav",
			L"..\\Resources\\sound\\ambience\\amb_desert_base.wav",
			L"..\\Resources\\sound\\ambience\\amb_snow_base.wav",
			L"..\\Resources\\sound\\ambience\\amb_acid_base.wav",
			L"..\\Resources\\sound\\ambience\\amb_final_base.wav",
		};
		Background* explosion;
		Sound* deploySound;
		Sound* battleTheme;
		Sound* battleAmbi;
		bool battleInFirst;
		bool battleThemePlayed;
		bool battleVictory;

		Sound* bombTickingSound;
		Sound* bombTickingSound2;
		Sound* bombTickingSound3;
		Sound* finalTheme;
		bool bombF2;
		bool bombF3;
		bool bombF4;
		float mT = 1.f;
		float mTT = 0.f;
		int prevBlinkCnt;

	};
}

