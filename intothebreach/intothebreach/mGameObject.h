#pragma once
#include "mEntity.h"
#include "mComponent.h"
#include "mTransform.h"
namespace m
{
	class Collider;
	class GameObject : public Entity
	{
	public:
		enum class STATE
		{
			Idle,
			Broken,
			Water,
			Death,
			Emerge,
			Invisible,
			Visibie,
			End,
		};
		GameObject(GameObject& other);
		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		void CreateComponent(COMPONENT_TYPE _type);
		Component* CreateComponent(Component* component);
		void AddComponent(Component* component);
		bool GetIsFirstUpdate() { return firstUpdate; }



		virtual void OnCollisionEnter(Collider* other) {};
		virtual void OnCollisionStay(Collider* other) {};
		virtual void OnCollisionExit(Collider* other) {};

		template<typename T>
		T* AddComponent()
		{
			T* comp = new T();
			UINT compType = (UINT)comp->GetType();
			mComponents[compType] = comp;

			return comp;
		}

		template<typename T>
		__forceinline T* GetComponent()
		{
			T* component;
			for (auto c : mComponents)
			{
				component = dynamic_cast<T*>(c);
				if (nullptr != component)
				{
					return component;
				}
			}

			return nullptr;
		}
		__forceinline Component* GetComponentOfType(COMPONENT_TYPE type)
		{
			Component* comp = nullptr;
			for (Component* c : mComponents)
			{
				if (c->GetType() == type)
				{
					comp = c;
					break;
				}
			}
			return comp;
		}
		void SetPos(Vector2 _pos)
		{
			GetComponent<Transform>()->SetPos(_pos);
		}
		Vector2 GetPos()
		{
			return GetComponent<Transform>()->GetPos();
		}
		void SetScale(Vector2 _scale)
		{
			GetComponent<Transform>()->SetScale(_scale);
		}
		Vector2 GetScale()
		{
			return GetComponent<Transform>()->GetScale();
		}
		bool IsDead() { return mbDead; }
		void Death() { mbDead = true; }

		STATE GetState() { return mState; }
		void SetState(STATE _state) { mState = _state; }
	private:
		bool firstUpdate;
		bool mbDead;
		vector<Component*> mComponents;
		STATE mState;
	};

}
