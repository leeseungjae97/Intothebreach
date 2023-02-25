#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaTransform.h"
namespace ya
{
	GameObject::GameObject(GameObject& other) 
		: mComponents{ }
		, mbDead(false)
	{
		mComponents.resize((UINT)eComponentType::End);
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
	{
		mComponents.resize((UINT)eComponentType::End);
		
		/*for (UINT i = 0; i < (UINT)eComponentType::End; i++) {
			CreateComponent((eComponentType)i);
		}
		SetPos(Vector2(0, 0));*/
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
	void GameObject::CreateComponent(eComponentType _type) {
		Component* newComp = nullptr;
		switch (_type) {
		case eComponentType::Animator:
		{
			newComp = new Animator();
		}
		break;

		case eComponentType::Transform:
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
		case eComponentType::Animator:
		{
			Animator* other = dynamic_cast<Animator*>(component);
			newComp = new Animator(*other);
		}
		break;

		case eComponentType::Transform:
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
