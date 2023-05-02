#pragma once
#include "mScene.h"
namespace m {
	class Background;
	class Button;
    class EndingScene :
        public Scene {
	public:
		EndingScene();
		~EndingScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	private:

		float mx;
		float my;
		float timer;
		Background* stars;
		Background* stars2;
		Background* stars3;
		Background* plant;
		Background* explsion;
		Background* lines;
		Background* plantglow;
		Background* plantglow2;
		Background* spaceglow;

		Background* scrollText;
		Background* savePeopleNum[6];

    };
}

