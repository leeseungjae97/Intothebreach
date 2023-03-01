#pragma once
#include "_Engine.h"
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
        Animation(Animation& other) = default;
        Animation();
        ~Animation();

        void Update();
        void Initialize();
        void Render(HDC hdc);
        void Create(Image* image, Vector2 leftTop, Vector2 size, Vector2 offset,
            UINT spriteLength, float duration, UINT alphaCheck = 0, bool affactedCamera = false);

        void Reset();

        bool IsComplete() { return mbComplete; }
        void SetAnimator(Animator* animator) { mAnimator = animator; }

    private:
        Animator* mAnimator;
        Image* mImage;
        vector<Sprite*> mSpriteSheet;

        int mSpriteIndex;
        int mAlpha;
        float mTime;
        bool mbComplete;
        bool mbAffectedCamera;

    };
};