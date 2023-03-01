#pragma once
#include "mComponent.h"	
namespace m {
	class Transform : public Component{
	public:
		Transform(Transform& other);
		Transform();
		~Transform();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		Vector2 GetPos() { return mPos; }
		void SetPos(Vector2 pos) { mPos = pos; }
		void SetScale(Vector2 _scale) { mScale = _scale; }
		Vector2 GetScale() { return mScale; }


	private:
		Vector2 mPos;
		Vector2 mScale;
	};
}

