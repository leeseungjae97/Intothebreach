#pragma once
#include "mEntity.h"
namespace m
{
	class GameObject;
	class Component : public Entity
	{
	public:
		friend class GameObject;
		Component(COMPONENT_TYPE type);
		Component(Component& other);
		~Component();

		virtual void Initialize();
		virtual void Update() = 0;
		virtual void Render(HDC hdc) {};
		virtual void Release();

		COMPONENT_TYPE GetType() { return mSkillType; }
		GameObject* GetOwner() { return mOwner; }

	private:
		GameObject* mOwner;
		const COMPONENT_TYPE mSkillType;
	};
}
