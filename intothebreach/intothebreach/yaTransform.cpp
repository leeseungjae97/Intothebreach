#include "yaTransform.h"
namespace ya {
	Transform::Transform(Transform& other)
		: Component(other)
		, mPos{0.f,0.f}
		, mScale{ 0.f,0.f }
	{
	}
	Transform::Transform()
		: Component(eComponentType::Transform)
		, mPos{ 0.f,0.f }
		, mScale{ 0.f,0.f }
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