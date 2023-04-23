#pragma once
#include "mEntity.h"
namespace m {
    class Image;
    class Animator;
    class Animation :public Entity {
    public:
        struct Sprite {
            Vector2 leftTop;
            Vector2 size;
            Vector2 offset;

            float duration;

        public:
            Sprite()
                : leftTop(Vector2::Zero)
                , size(Vector2::Zero)
                , offset(Vector2::Zero)
                , duration(0.0f)
            {

            }
        };
    public:
        Animation(Animation& other);
        Animation();
        ~Animation();

        void Update();
        void Initialize();
        void Render(HDC hdc);
        void Create(Image* image, Vector2 leftTop, Vector2 size, Vector2 offset,
            UINT spriteLength, float duration, UINT alphaCheck = 0, bool affactedCamera = false);
        void Create(Image* image, Vector2 leftTop, Vector2 size, Vector2 offset,
            UINT spriteLength, float duration, bool reverse, UINT alphaCheck = 0, bool affactedCamera = false);

        void Reset();
        void SetReverse(bool _b) { mbReverse = _b; }
        void SetSpriteIdx(int _idx) { mSpriteIndex = _idx; }
        bool IsComplete() { return mbComplete; }
        void SetAnimator(Animator* animator) { mAnimator = animator; }

    private:
        Animator* mAnimator;
        Image* mImage;
        vector<Sprite> mSpriteSheet;

        int mSpriteIndex;
        int mMaxIndex;
        int mAlpha;
        float mTime;
        bool mbComplete;
        bool mbAffectedCamera;
        bool mbReverse;
    };
};