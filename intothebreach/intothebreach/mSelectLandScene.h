#pragma once
#include "mScene.h"
namespace m {
	class Button;
	class Mech;
    class SelectLandScene :
        public Scene {
	public:
		SelectLandScene();
		~SelectLandScene();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	private:
		vector<Background*> Islands;
		vector<Background*> outLine;
		Button* upUiBox;
		vector<Button*> gridPowers;
		vector<Mech*> infoUnits;
		vector<Button*> clickableMechs;
		Background* boxBlackFade;

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
    };
}

