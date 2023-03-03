#pragma once
#include "mComponent.h"
namespace m {
    class Collider :
        public Component {
    public:
        Collider(Collider& _origin);
        Collider();
        ~Collider();

        void OnCollisionEnter(Collider* other);
        void OnCollisionStay(Collider* other);
        void OnCollisionExit(Collider* other);

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void Render(HDC hdc) override;
        virtual void Release() override;

        void SetScale(Vector2 _scale) { mScale = _scale; }
        void SetOffset(Vector2 _offset) { mOffset = _offset; }
        
        Vector2 GetScale() { return mScale; }
        Vector2 GetOffset() { return mOffset; }
        Vector2 GetPos() { return mPos; }


    private:
        Vector2 mScale;
        Vector2 mPos;
        Vector2 mOffset;
        UINT mCollisionCount;
    };
}