#include "yaAnimator.h"
#include "yaAnimation.h"
#include "yaImage.h"
#include "yaResources.h"
namespace ya {
	Animator::Animator(Animator& _origin)
		: Component(_origin)
		, mActiveAnimation(nullptr)
		, mbLoop(false) {
		for (AnimationPair animationPair : _origin.mAnimations) {
			Animation* animation = new Animation(*(animationPair.second));
			animation->SetAnimator(this);
			mAnimations.insert(make_pair(animationPair.first, animation));
		}
	}
	Animator::Animator()
		: Component(eComponentType::Animator)
		, mActiveAnimation(nullptr)
		, mbLoop(false)
	{
	}
	Animator::~Animator() {
		for (auto iter : mAnimations) {
			delete iter.second;
		}
		for (auto iter : mEvents) {
			delete iter.second;
		}
	}
	void Animator::Initialize() {
	}

	void Animator::Update() {
		if (nullptr != mActiveAnimation) {
			mActiveAnimation->Update();
			if (mbLoop && mActiveAnimation->IsComplete()) {
				Animator::Events* events = FindEvents(mActiveAnimation->GetName());

				if (events != nullptr) events->mCompleteEvent();

				mActiveAnimation->Reset();
			}
		}
	}
	void Animator::Render(HDC hdc) {
		if (nullptr != mActiveAnimation) {
			mActiveAnimation->Render(hdc);
		}
	}
	void Animator::CreateAnimation(const wstring& name, Image* image, Vector2 leftTop, Vector2 size, Vector2 offset
		, float columnLegth, UINT spriteLength, float duration, UINT alphaCheck, bool bAffectedCamera) {
		Animation* animation = FindAnimation(name);
		if (animation != nullptr) {
			MessageBox(nullptr, L"Animation 이름 중복", L"Animation 생성 실패", MB_OK);
			return;
		}

		animation = new Animation();
		animation->Create(image, leftTop, size, offset, columnLegth, spriteLength, duration, alphaCheck, bAffectedCamera);
		animation->SetName(name);
		animation->SetAnimator(this);

		mAnimations.insert(std::make_pair(name, animation));

	}
	void Animator::CreateAnimations(const wstring& path, const wstring& name, Vector2 offset, float duration) {
		UINT width = 0;
		UINT height = 0;
		UINT fileCount = 0;

		std::filesystem::path fs(path);
		std::vector<Image*> images;
		for (auto& p : std::filesystem::recursive_directory_iterator(path)) {
			std::wstring fileName = p.path().filename();
			std::wstring fullName = path + L"\\" + fileName;
			Image* image = Resources::Load<Image>(fileName, fullName);
			images.push_back(image);

			if (width < image->GetWidth())
				width = image->GetWidth();

			if (height < image->GetHeight())
				height = image->GetHeight();

			fileCount++;
		}

		mSpriteSheet = Image::Create(name, width * fileCount, height);
		int index = 0;

		for (Image* image : images) {
			BitBlt(mSpriteSheet->GetHdc(), width * index, 0, image->GetWidth(), image->GetHeight()
				, image->GetHdc(), 0, 0, SRCCOPY);
			index++;
		}

		CreateAnimation(name, mSpriteSheet
			, Vector2(0.0f, 0.0f), Vector2((float)width, (float)height)
			, offset, (float)fileCount, fileCount, duration);

	}

	Animation* Animator::FindAnimation(const wstring& name) {
		AnimationIter iter = mAnimations.find(name);
		if (mAnimations.end() == iter)
			return nullptr;

		return iter->second;
	}
	void Animator::Play(const wstring& name, bool loop) {
		Animator::Events* events = FindEvents(name);
		if (events != nullptr) events->mStartEvent();

		Animation* prevAnimation = mActiveAnimation;

		mActiveAnimation = FindAnimation(name);
		mActiveAnimation->Reset();
		mbLoop = loop;

		if (prevAnimation != mActiveAnimation) {
			if (events != nullptr) events->mEndEvent();
		}
	}
	Animator::Events* Animator::FindEvents(const wstring name) {
		auto pair = mEvents.find(name);
		if (pair == mEvents.end()) return nullptr;
		return pair->second;
	}
	function<void()>& Animator::GetStartEvent(const wstring name) {
		Animator::Events* events = FindEvents(name);
		
		return events->mStartEvent.mEvent;
	}
	function<void()>& Animator::GetCompleteEvent(const wstring name) {
		Animator::Events* events = FindEvents(name);
		
		return events->mCompleteEvent.mEvent;
	}
	function<void()>& Animator::GetEndEvent(const wstring name) {
		Animator::Events* events = FindEvents(name);

		return events->mEndEvent.mEvent;
	}
}