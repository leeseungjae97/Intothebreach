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
		Button* savePeople;
		vector<Button*> boxResultPilots;
		Background* boxBlackFade;
		Background* boxBlackFade2;
		vector<Button*> gridPowers;
		vector<Background*> infoUnits;
		vector<Button*> clickableMechs;

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
    };
}

