#pragma once
#include "mScene.h"
namespace m
{
	class Mech;
	class Button;
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

	private:

		Background* moon;
		Background* cloud[2];
		Background* lights[3];
		Background* swapFake;

		Button* btnStart;
		Button* btnChangeSquad;
		Button* btnChangePilot;

		float cloudDiff;
	};
}
