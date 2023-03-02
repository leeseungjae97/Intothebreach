#pragma once
#include "mGameObject.h"
namespace m {
	class Skill_Range :public GameObject {
	public:
		Skill_Range();
		~Skill_Range();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
	};
}

