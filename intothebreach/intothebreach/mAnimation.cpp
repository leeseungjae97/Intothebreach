#include "mAnimation.h"
#include "mTime.h"
#include "mGameObject.h"
#include "mAnimator.h"
#include "mImage.h"
#include "mCamera.h"
#include "mResources.h"
namespace m {
	Animation::Animation() 
		: mAnimator(nullptr)
		, mImage(nullptr)
		//, mSpriteIndex(0)
		, mTime(0.0f)
		, mbComplete(false)
		, mbAffectedCamera(false)
		, mAlpha(AC_SRC_OVER)
		, mbReverse(false)
	{
	}
	Animation::Animation(Animation& other)
		: mAnimator(other.mAnimator)
		, mImage(other.mImage)
		, mSpriteSheet(other.mSpriteSheet)
		, mSpriteIndex(other.mSpriteIndex)
		, mAlpha(other.mAlpha)
		, mTime(other.mTime)
		, mbComplete(other.mbComplete)
		, mbAffectedCamera(other.mbAffectedCamera)
	{

	}
	Animation::~Animation() {

	}
	void Animation::Update() {
		if (mbComplete) return;
		mTime += Time::fDeltaTime();
		if (mSpriteSheet[mSpriteIndex].duration < mTime) {
			mTime = 0.0f;
			if (mbReverse)
			{
				if (mSpriteIndex - 1 < 0)
				{
					mbComplete = true;
				}
				else
				{
					mSpriteIndex -= 1;
				}
			}else{
				if (mSpriteSheet.size() <= mSpriteIndex + 1)
				{
					mbComplete = true;
				}
				else
				{
					mSpriteIndex += 1;
				}
			}
			
		}
	}
	void Animation::Initialize() {
	}
	void Animation::Render(HDC hdc) {
		GameObject* gObject = mAnimator->GetOwner();
		Vector2 pos = gObject->GetPos();

		if (mbAffectedCamera)
			pos = Camera::CalculatePos(pos);

		pos += mSpriteSheet[mSpriteIndex].offset;

		if (mAlpha == AC_SRC_OVER) {
			TransparentBlt(hdc
			, int(pos.x - mSpriteSheet[mSpriteIndex].size.x / 2.0f)
			, int(pos.y - mSpriteSheet[mSpriteIndex].size.y / 2.0f)
			, int(mSpriteSheet[mSpriteIndex].size.x * 2)
			, int(mSpriteSheet[mSpriteIndex].size.y * 2)
			, mImage->GetHdc()
			, int(mSpriteSheet[mSpriteIndex].leftTop.x)
			, int(mSpriteSheet[mSpriteIndex].leftTop.y)
			, int(mSpriteSheet[mSpriteIndex].size.x)
			, int(mSpriteSheet[mSpriteIndex].size.y)
			, RGB(255, 0, 255));
		}
		else {
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = mAlpha;
			func.SourceConstantAlpha = mAnimator->GetConstant();

			float fPosX = pos.x - mSpriteSheet[mSpriteIndex].size.x / 2.0;
			float fPosY = pos.y - mSpriteSheet[mSpriteIndex].size.y / 2.0;
			if (mAnimator->GetBackAnim())
			{
				fPosX = pos.x;
				fPosY = pos.y;
			}
			AlphaBlend(hdc
				, int(fPosX)
				, int(fPosY)
				, int(mSpriteSheet[mSpriteIndex].size.x * 2)
				, int(mSpriteSheet[mSpriteIndex].size.y * 2)
				, mImage->GetHdc()
				, int(mSpriteSheet[mSpriteIndex].leftTop.x)
				, int(mSpriteSheet[mSpriteIndex].leftTop.y)
				, int(mSpriteSheet[mSpriteIndex].size.x)
				, int(mSpriteSheet[mSpriteIndex].size.y)
				, func);
		}
		//AlphaBlend(hdc
		//	, int(pos.x)
		//	, int(pos.y)
		//	, int(mSpriteSheet[mSpriteIndex].size.x * 2)
		//	, int(mSpriteSheet[mSpriteIndex].size.y * 2)
		//	, mImage.GetHdc()
		//	, int(mSpriteSheet[mSpriteIndex].leftTop.x)
		//	, int(mSpriteSheet[mSpriteIndex].leftTop.y)
		//	, int(mSpriteSheet[mSpriteIndex].size.x)
		//	, int(mSpriteSheet[mSpriteIndex].size.y)
		//	, func);

		/*TransparentBlt(hdc
			, int(pos.x - mSpriteSheet[mSpriteIndex].size.x / 2.0f)
			, int(pos.y - mSpriteSheet[mSpriteIndex].size.y / 2.0f)
			, int(mSpriteSheet[mSpriteIndex].size.x)
			, int(mSpriteSheet[mSpriteIndex].size.y)
			, mImage.GetHdc()
			, int(mSpriteSheet[mSpriteIndex].leftTop.x)
			, int(mSpriteSheet[mSpriteIndex].leftTop.y)
			, int(mSpriteSheet[mSpriteIndex].size.x)
			, int(mSpriteSheet[mSpriteIndex].size.y)
			, RGB(255,0,255));*/
	}
	void Animation::Create(
		Image* image, Vector2 leftTop, Vector2 size
		, Vector2 offset, UINT spriteLength, float duration
		, UINT alphaCheck, bool affactedCamera) {
		mImage = image;
		mbAffectedCamera = affactedCamera;
		mAlpha = alphaCheck;
		mSpriteIndex = 0;
		for (size_t i = 0; i < spriteLength; i++) {
			Sprite sprite;

			sprite.leftTop.x = leftTop.x + (size.x * float(i));
			sprite.leftTop.y = leftTop.y;
			sprite.size = size;
			sprite.offset = offset;
			sprite.duration = duration;

			mSpriteSheet.push_back(Sprite(sprite));
		}

	}
	void Animation::Create(
		Image* image, Vector2 leftTop, Vector2 size
		, Vector2 offset, UINT spriteLength, float duration
		, bool reverse, UINT alphaCheck, bool affactedCamera)
	{
		mImage = image;
		mbAffectedCamera = affactedCamera;
		mbReverse = reverse;
		mAlpha = alphaCheck;
		mSpriteIndex = spriteLength - 1;
		mMaxIndex = spriteLength - 1;

		for (size_t i = 0; i < spriteLength; i++)
		{
			Sprite sprite;

			sprite.leftTop.x = leftTop.x + (size.x * float(i));
			sprite.leftTop.y = leftTop.y;
			sprite.size = size;
			sprite.offset = offset;
			sprite.duration = duration;

			mSpriteSheet.push_back(Sprite(sprite));
		}

	}
	void Animation::Reset() {
		if(mbReverse) mSpriteIndex = mMaxIndex;
		else mSpriteIndex = 0;
		
		mTime = 0.0f;
		mbComplete = false;
	}
}