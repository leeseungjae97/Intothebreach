#include "yaAnimator.h"
namespace ya {
	Animator::Animator(eComponentType type) 
		: Component(type)
	{
	}
	Animator::~Animator() {
	}
	void Animator::Initialize() {
	}
	void Animator::Update() {
	}
	void Animator::Render(HDC hdc) {
	}
	void Animator::Release() {
	}
	void Animator::CreateAnimation() {
	}
	void Animator::CreateAnimations() {
	}
	Animation* Animator::FindAnimation(const wstring& name) {
		return nullptr;
	}
	void Animator::Play(const wstring& name, bool loop) {
	}
	Animator::Events* Animator::FindEvents(const wstring& name) {
		return nullptr;
	}
	//function<void>& Animator::GetStartEvent(const wstring& name) {
	//	return;
	//}
	//function<void>& Animator::GetCompleteEvent(const wstring& name) {
	//	return;
	//}
	//function<void>& Animator::GetEndEvent(const wstring& name) {
	//	return;
	//}
}