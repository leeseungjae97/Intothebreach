#pragma once
#include "yaScene.h"
#include "MechArtillery.h"
namespace ya
{
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
		MechArtillery* m_MechArtillery;
	};
}
