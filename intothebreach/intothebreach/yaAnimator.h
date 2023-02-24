#pragma once
#include "yaComponent.h"
#include "yaAnimation.h"
#include "YamYamEngine.h"
#include "yaImage.h"
namespace ya {
    class Animator :
        public Component {
    public:
        struct Event {
            void operator =(function<void()> func) {
                mEvent = move(func);
            }
            void operator()() {
                if (mEvent) mEvent();
            }
            //void (*)();
            function<void()> mEvent;
        };
        struct Events {
            Event mStartEvent;
            Event mCompleteEvent;
            Event mEndEvent;
        };
        Animator(eComponentType type);
        ~Animator();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);
        virtual void Release();

        // 한 파일에 이어져있는 애니메이션
        void CreateAnimation();
        // 파일별로 있는 애니메이션
        void CreateAnimations();

        Animation* FindAnimation(const wstring& name);
        void Play(const wstring& name, bool loop);

        Events* FindEvents(const wstring& name);
        function<void>& GetStartEvent(const wstring& name);
        function<void>& GetCompleteEvent(const wstring& name);
        function<void>& GetEndEvent(const wstring& name);

    private:
        map<wstring, Animation*> mAnimations;
        map<wstring, Events*> mEvents;
        Animation* mActiveAnimation;
        Image* mSpriteSheet;
    };
}

