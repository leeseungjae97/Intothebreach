#include "mAnimation.h"
#include "mTime.h"
#include "mGameObject.h"
#include "mAnimator.h"
#include "mImage.h"

namespace m {
	Animation::Animation() 
		: mAnimator(nullptr)
		, mImage(nullptr)
		, mSpriteIndex(0)
		, mTime(0.0f)
		, mbComplete(false)
		, mbAffectedCamera(false)
	{
	}
	Animation::~Animation() {

	}
	void Animation::Update() {
		if (mbComplete) return;
		mTime += Time::fDeltaTime();
		if (mSpriteSheet[mSpriteIndex]->duration < mTime) {
			mTime = 0.0f;
			if (mSpriteSheet.size() <= mSpriteIndex + 1) {
				mbComplete = true;
			}
			else {
				mSpriteIndex += 1;
			}
		}
		
	}
	void Animation::Initialize() {
	}
	void Animation::Render(HDC hdc) {
		GameObject* gObject = mAnimator->GetOwner();
		Vector2 pos = gObject->GetPos();
		//if (mbAffectedCamera) {

		//}

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = mAlpha;
		func.SourceConstantAlpha = 255;

		pos += mSpriteSheet[mSpriteIndex]->offset;
		AlphaBlend(hdc
			, int(pos.x - mSpriteSheet[mSpriteIndex]->size.x / 2.0f)
			, int(pos.y - mSpriteSheet[mSpriteIndex]->size.y / 2.0f)
			, int(mSpriteSheet[mSpriteIndex]->size.x)
			, int(mSpriteSheet[mSpriteIndex]->size.y)
			, mImage->GetHdc()				
			, int(mSpriteSheet[mSpriteIndex]->leftTop.x)
			, int(mSpriteSheet[mSpriteIndex]->leftTop.y)
			, int(mSpriteSheet[mSpriteIndex]->size.x)
			, int(mSpriteSheet[mSpriteIndex]->size.y)
			, func);

		/*TransparentBlt(hdc
			, int(pos.x - mSpriteSheet[mSpriteIndex]->size.x / 2.0f)
			, int(pos.y - mSpriteSheet[mSpriteIndex]->size.y / 2.0f)
			, int(mSpriteSheet[mSpriteIndex]->size.x)
			, int(mSpriteSheet[mSpriteIndex]->size.y)
			, mImage->GetHdc()
			, int(mSpriteSheet[mSpriteIndex]->leftTop.x)
			, int(mSpriteSheet[mSpriteIndex]->leftTop.y)
			, int(mSpriteSheet[mSpriteIndex]->size.x)
			, int(mSpriteSheet[mSpriteIndex]->size.y)
			, RGB(255,0,255));*/
	}
	void Animation::Create(
		Image* image, Vector2 leftTop, Vector2 size
		, Vector2 offset, UINT spriteLength, float duration
		, UINT alphaCheck, bool affactedCamera) {
		mImage = image;
		mbAffectedCamera = affactedCamera;
		mAlpha = alphaCheck;

		for (size_t i = 0; i < spriteLength; i++) {
			Sprite* sprite = new Sprite;

			sprite->leftTop.x = leftTop.x + (size.x * float(i));
			sprite->leftTop.y = leftTop.y;
			sprite->size = size;
			sprite->offset = offset;
			sprite->duration = duration;

			mSpriteSheet.push_back(sprite);
		}
	}
	void Animation::Reset() {
		mSpriteIndex = 0;
		mTime = 0.0f;
		mbComplete = false;
	}
}