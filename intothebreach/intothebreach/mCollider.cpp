#include "mCollider.h"
#include "mGameObject.h"
#include "mSelectGDI.h"
#include "mCamera.h"
namespace m {
	Collider::Collider() 
		: Component(COMPONENT_TYPE::COLLIDER)
		, mScale(Vector2::One)
		, mPos(Vector2::Zero)
		, mOffset(Vector2::One)
		, mCollisionCount(0)
	{
	}
	Collider::Collider(Collider& _origin) 
		: Component(COMPONENT_TYPE::COLLIDER)
		, mScale(_origin.GetScale())
		, mPos(_origin.GetPos())
		, mOffset(_origin.GetOffset())
		, mCollisionCount(0)
	{

	}
	Collider::~Collider() {
	}
	
	void Collider::Initialize() {
	}
	void Collider::Update() {
		mPos = GetOwner()->GetPos();
	}
	void Collider::Render(HDC hdc) {
		SelectGDI p(hdc, PEN_TYPE::GREEN);
		SelectGDI b(hdc, BRUSH_TYPE::HOLLOW);
		Vector2 vRenderPos = Camera::CalculatePos(mPos);
		Rectangle(hdc
			, (int)(vRenderPos.x - mScale.x / 2.f)
			, (int)(vRenderPos.y - mScale.y / 2.f)
			, (int)(vRenderPos.x + mScale.x / 2.f)
			, (int)(vRenderPos.y + mScale.y / 2.f));
	}
	void Collider::Release() {
	}
	void Collider::OnCollisionEnter(Collider* other) {
		++mCollisionCount;
		GetOwner()->OnCollisionEnter(other);
	}
	void Collider::OnCollisionStay(Collider* other) {
		GetOwner()->OnCollisionEnter(other);
	}
	void Collider::OnCollisionExit(Collider* other) {
		--mCollisionCount;
		GetOwner()->OnCollisionEnter(other);	
	}
}