#include "Skill_Range.h"
#include "mResources.h"
namespace m {
	Skill_Range::Skill_Range() {
	}
	Skill_Range::~Skill_Range() {
	}
	void Skill_Range::Initialize() {
	}
	void Skill_Range::Update() {
	}
	void Skill_Range::Render(HDC hdc) {
		Vector2 mPos = GetPos();
		//Resources::Load<Image>();
		SetPos(mPos);
	}
	void Skill_Range::Release() {
	}
}