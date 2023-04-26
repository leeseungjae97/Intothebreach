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

		Button* upUiBox;
		Button* boxBattleResult;
		Button* btnResultClose;
		Button* savePeople;
		vector<Button*> boxResultPilots;
		Background* boxBlackFade;
		vector<Button*> gridPowers;
		vector<Mech*> infoUnits;
		vector<Button*> clickableMechs;

		Button* mechInfo;
		Button* inventory;
		Button* inventoryPagingNumber;
		Button* boxDragPilot;
		Button* boxDragSkill1;
		Button* boxDragSkill2;

		Button* boxPilot;
		Button* boxSkill1;
		Button* boxSkill2;

		Button* btnInvenUp;
		Button* btnInvenDown;
		vector<Button*> inventoryColumns;

		vector<Button*> reactors;
		Button* btnReactorDeploy;
		Button* btnReactorCancel;
		Button* mM;
		bool bMouseDrag;

		vector<Button*> dragBack;
    };
}

