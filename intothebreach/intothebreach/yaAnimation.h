#pragma once
#include "YamYamEngine.h"
#include "yaEntity.h"
namespace ya {
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
                : leftTop(0.0f, 0.0f)
                , size(0.0f, 0.0f)
                , offset(0.0f, 0.0f)
                , duration(0.0f)
            {

            }
        };
    public:
        Animation(Animation& other) = default;
        Animation();
        ~Animation();

        void update();
        void Render(HDC hdc);
        void Create(Image* image, Vector2 leftTop, Vector2 size, Vector2 offset,
            float columnLegth, UINT spriteLength, float duration, UINT alphaCheck = 0, bool affactedCamera = false);

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