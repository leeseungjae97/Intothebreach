#pragma once
#include "mEntity.h"
namespace m
{
	class GameObject;
	class Layer : public Entity
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		void AddGameObject(GameObject* gameObj);
		void ObjectFront(GameObject* gameObj);
		vector<GameObject*>& GetGameObjects() { return mGameObjects; }
	private:
		vector<GameObject*> mGameObjects;
	};
}
