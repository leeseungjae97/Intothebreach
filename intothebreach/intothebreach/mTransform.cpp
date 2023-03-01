#include "mTransform.h"
namespace m {
	Transform::Transform(Transform& other)
		: Component(other)
		, mPos(Vector2::Zero)
		, mScale(Vector2::One)
	{
	}
	Transform::Transform()
		: Component(COMPONENT_TYPE::TRANSFORM)
		, mPos(Vector2::Zero)
		, mScale(Vector2::One)
	{
	}
	Transform::~Transform() {
	}
	void Transform::Initialize() {
	}
	void Transform::Update() {
	}
	void Transform::Render(HDC hdc) {
	}
	void Transform::Release() {
	}
}