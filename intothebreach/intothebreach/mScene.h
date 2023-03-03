#pragma once
#include "mEntity.h"
#include "mLayer.h"

namespace m
{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();
		
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;

		void AddGameObject(GameObject* obj, LAYER_TYPE layer);

	private:
		std::vector<Layer> mLayers;
	};
}
