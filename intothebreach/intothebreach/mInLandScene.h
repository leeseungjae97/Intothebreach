#pragma once
#include "mScene.h"
namespace m {
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
		ISLAND_T mSkillType;
		vector<Background*> mSections;
    };
}

