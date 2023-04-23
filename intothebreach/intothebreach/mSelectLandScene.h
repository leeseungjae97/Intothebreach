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
    };
}

