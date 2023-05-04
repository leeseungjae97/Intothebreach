#pragma once
#include "mScene.h"
namespace m {
	class Mech;
	class Button;
	class Background;
    class InLandScene :
        public Scene {
	public:
		InLandScene(ISLAND_T _type);
		~InLandScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		ISLAND_T mType;
		vector<Background*> mSections;
		vector<Background*> mSectionsOL;
		vector<Background*> mMissionsPreview;
		vector<Background*> mFunctionSections;

		Button* upUiBox;
		Button* boxBattleResult;
		Button* btnResultClose;
		//Button* savePeople;
		vector<Background*> stars;
		vector<Background*> gridPowers;

		Background* savePeopleNum[5];
		Background* reactorNum[5];
		Background* starNum[5];
		Background* defenceNum[5];
		Background* resultPeopleNum[3];


		vector<Button*> boxResultPilots;
		Background* boxBlackFade2;
		Background* text1;
		Background* text2;

		Background* boxBlackFade;
		vector<Background*> infoUnits;
		vector<Button*> clickableMechs;
		vector<Button*> upGridPowers;

		Button* mechInfo;
		Button* boxDragPilot;
		Button* boxDragSkill1;
		Button* boxDragSkill2;
		Button* boxPilot;
		Button* boxSkill1;
		Button* boxSkill2;
		vector<Button*> reactors;
		Button* btnReactorDeploy;
		Button* btnReactorCancel;
		Button* mM;
		int curMech;

		Button* inventory;
		Button* inventoryPagingNumber;
		Button* btnInvenUp;
		Button* btnInvenDown;
		vector<Button*> inventoryColumns;
		int curItemIndex;
		vector<Button*> inventoryParts;

		bool bMouseDrag;
		vector<Button*> dragBack;
		wstring themes[4]{
			L"..\\Resources\\sound\\music\\mus_grass_map.wav",
			L"..\\Resources\\sound\\music\\mus_sand_map.wav",
			L"..\\Resources\\sound\\music\\mus_snow_map.wav",
			L"..\\Resources\\sound\\music\\mus_acid_map.wav",

		};
		Sound* inLandTheme;
		Sound* sectionHoverSound;
		bool sectionHoverPlayed[8];
		bool bBossShake;
		Sound* victorySound3;
    };
}

