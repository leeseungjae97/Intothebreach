#include "mGameObject.h"
#include "mTransform.h"
#include "mAnimator.h"
#include "mTransform.h"
namespace m
{
	GameObject::GameObject(GameObject& other) 
		: mComponents{}
		, mbDead(false)
		, bShown(false)
		, firstUpdate(true)
	{
		mComponents.resize((UINT)COMPONENT_TYPE::END);
		for (Component* component : other.mComponents) {
			if (nullptr == component)
				continue;

			Component* newComp = CreateComponent(component);
			AddComponent(newComp);
		}
	}

	GameObject::GameObject()
		: mComponents{ }
		, mbDead(false)
		, bShown(false)
	{
		mComponents.resize((UINT)COMPONENT_TYPE::END);
	}

	GameObject::~GameObject()
	{
		for (Component* comp : mComponents) {
			delete comp;
			comp = nullptr;
		}
	}

	void GameObject::Initialize()
	{
		
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Initialize();
		}
	}

	void GameObject::Update()
	{
		firstUpdate = false;
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Update();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Render(hdc);
		}
	}

	void GameObject::Release()
	{

	}
	void GameObject::CreateComponent(COMPONENT_TYPE _type) {
		Component* newComp = nullptr;
		switch (_type) {
		case COMPONENT_TYPE::ANIMATOR:
		{
			newComp = new Animator();
		}
		break;

		case COMPONENT_TYPE::TRANSFORM:
		{
			newComp = new Transform();
		}
		break;

		default:
			break;
		}
		AddComponent(newComp);
	}
	Component* GameObject::CreateComponent(Component* component) {
		Component* newComp = nullptr;
		switch (component->GetType()) {
		case COMPONENT_TYPE::ANIMATOR:
		{
			Animator* other = dynamic_cast<Animator*>(component);
			newComp = new Animator(*other);
		}
		break;

		case COMPONENT_TYPE::TRANSFORM:
		{
			Transform* other = dynamic_cast<Transform*>(component);
			newComp = new Transform(*other);
		}
		break;

		default:
			break;
		}

		return newComp;
	}

	void GameObject::AddComponent(Component* component) {
		mComponents[(UINT)component->GetType()] = component;
		component->mOwner = this;
	}

}
