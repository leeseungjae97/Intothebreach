#pragma once
#include "mScene.h"
namespace m
{
	class Mech;
	class Button;
	class Background;
	class SelectRobotScene : public Scene
	{
	public:
		SelectRobotScene();
		~SelectRobotScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
		void DrawMechInfos();
	private:

		Background* moon;
		Background* cloud[2];
		Background* lights[3];
		Background* platformL[3];
		Background* platformR[3];
		Background* shadows[3];
		Background* hangarMechs[3];

		Background* swapFake;
		Background* boxBlackFade;

		Button* btnStart;
		Button* btnChangeSquad;
		Button* btnChangePilot;

		Button* boxSquad;
		Button* boxSquadInfo;
		vector<Background*> mechs;
		vector<Background*> skills;
		//vector<Background*> mechClass;
		vector<Background*> mechNames;
		vector<Background*> mechMoves;
		vector<Background*> mechHps;
		vector<Background*> classNames;
		vector<Background*> hpBacks;
		vector<Background*> hps;
		
		Background* squadPreview;
		Button* boxEditSquad;
		Button* btnPrime;
		Button* btnBrute;
		Button* btnRange;
		
		Button* btnEditConfirm;
		vector<Button*> previewMechs;
		vector<Background*> mechBacks;
		int previewMechsUnitNum[3]{};

		vector<Button*> clickableMechs;


		float cloudDiff;
	};
}
