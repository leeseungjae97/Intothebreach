#pragma once
#include "mComponent.h"
namespace m {
    class Collider :
        public Component {
    public:
        Collider();
        ~Collider();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void Render(HDC hdc) override;
        virtual void Release() override;

        void SetScale(Vector2 _scale) { mScale = _scale; }
        Vector2 GetScale() { return mScale; }
        void SetOffset(Vector2 _offset) { mOffset = _offset; }
        Vector2 GetOffset() { return mOffset; }

    private:
        Vector2 mCenter;
        Vector2 mScale;
        Vector2 mPos;
        Vector2 mOffset;
    };
}