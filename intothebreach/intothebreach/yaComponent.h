#pragma once
#include "yaEntity.h"

namespace ya
{
	class Component : public Entity
	{
	public:
		Component(const eComponentType type);
		~Component();
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		eComponentType GetType() { return mType; }

	private:
		eComponentType mType;
	};
}