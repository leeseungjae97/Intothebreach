#pragma once
#include "mComponent.h"
#include "mAnimation.h"

namespace m {
    class Animator : public Component {
    public:
        struct Event {
            void operator =(function<void()> func) {
                mEvent = move(func);
            }
            void operator()() {
                if (mEvent) 
                    mEvent();
            }
            function<void()> mEvent;
        };
        struct Events {
            Event mStartEvent;
            Event mCompleteEvent;
            Event mEndEvent;
        };
    public:
        Animator(Animator& other);
        Animator();
        ~Animator();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        // 한 파일에 이어져있는 애니메이션
        void CreateAnimation(const wstring& name, Image* image, Vector2 leftTop, Vector2 size, Vector2 offset
            , UINT spriteLength, float duration, UINT alphaCheck = 0, bool bAffectedCamera = false);
        // 파일별로 있는 애니메이션
        void CreateAnimations(const wstring& path, const wstring& name, Vector2 offset = Vector2::Zero, float duration = 0.1f);
        void SetConstant(BYTE _constant) { mConstant = _constant; }
        BYTE GetConstant() { return mConstant; }
        Animation* FindAnimation(const wstring& name);
        void Play(const wstring& name, bool loop);
        void Stop();

        Events* FindEvents(const wstring name);
        function<void()>& GetStartEvent(const wstring name);
        function<void()>& GetCompleteEvent(const wstring name);
        function<void()>& GetEndEvent(const wstring name);



    private:
        map<wstring, Animation*> mAnimations;
        map<wstring, Events*> mEvents;

        Image* mSpriteSheet;
        Animation* mActiveAnimation;

        bool mbLoop;
        bool stopAnimator;

        BYTE mConstant;
    };

    typedef map<wstring, Animation*>::iterator AnimationIter;
    typedef pair<wstring, Animation*> AnimationPair;
}

