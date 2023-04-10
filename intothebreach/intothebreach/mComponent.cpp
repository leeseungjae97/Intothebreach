#include "mComponent.h"

namespace m
{
    Component::Component(COMPONENT_TYPE type)
        : mSkillType(type)
        , mOwner(nullptr)
    {

    }
    Component::Component(Component& other)
        : mSkillType(other.GetType())
        , mOwner(nullptr)
    {

    }
    Component::~Component() {
    }
    void Component::Initialize() {
    }
    void Component::Update() {
    }
    void Component::Release() {
    }
}
