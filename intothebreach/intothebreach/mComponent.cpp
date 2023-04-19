#include "mComponent.h"

namespace m
{
    Component::Component(COMPONENT_TYPE type)
        : mType(type)
        , mOwner(nullptr)
    {

    }
    Component::Component(Component& other)
        : mType(other.GetType())
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
