#pragma once
#include "mScene.h"
namespace m {
	class Tile;
	class TileHead;
	class CombatScene : public Scene {
	public:
		CombatScene();
		~CombatScene();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;;
		
		void RandSpawnAlien();
		void PutUnitBeforeCombat();
	private:
		bool bSetPosition;

		int mechIdx;
	};
}

