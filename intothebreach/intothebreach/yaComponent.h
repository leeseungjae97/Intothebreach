#pragma once
#include "yaEntity.h"

namespace ya
{
	class GameObject;
	class Component : public Entity
	{
	public:
		friend class GameObject;
		Component(eComponentType type);
		Component(Component& other);
		~Component();

		virtual void Initialize();
		virtual void Update() = 0;
		virtual void Render(HDC hdc) {};
		virtual void Release();

		eComponentType GetType() { return mType; }
		GameObject* GetOwner() { return mOwner; }

	private:
		GameObject* mOwner;
		const eComponentType mType;
	};
}
