#pragma once
#include "mScene.h"
namespace m {
	class Button;
	class Sound;
	class TitleScene : public Scene {
	public:
		TitleScene();
		~TitleScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		float scrollSpeed;
		vector<Button*> btns;
		bool bStartBtn;
		//vector<Background*> mBacks;
	};
}


