#pragma once
#include "yaScene.h"
namespace ya {
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

    };
}

