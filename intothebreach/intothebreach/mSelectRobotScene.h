#pragma once
#include "mScene.h"
namespace m
{
	class Mech;
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
		Mech* mMech[3];

		Background* moon;
		Background* cloud[2];
		Background* lights[3];
		Background* swapFake;
		float cloudDiff;
	};
}
