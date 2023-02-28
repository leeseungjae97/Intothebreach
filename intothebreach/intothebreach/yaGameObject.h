#pragma once
#include "yaEntity.h"
#include "yaComponent.h"
#include "yaTransform.h"
namespace ya
{
	class GameObject : public Entity
	{
	public:
		GameObject(GameObject& other);
		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		void CreateComponent(eComponentType _type);
		Component* CreateComponent(Component* component);
		void AddComponent(Component* component);

		template<typename T>
		T* AddComponent()
		{
			T* comp = new T();
			UINT compType = (UINT)comp->GetType();
			mComponents[compType] = comp;

			return comp;
		}

		template<typename T>
		__forceinline T* GetComponent() {
			/*for (Component* comp : mComponents) {
				if (dynamic_cast<T*>(comp)) {
					return dynamic_cast<T*>(comp);
				}
			}*/
			T* component;
			for (auto c : mComponents) {
				component = dynamic_cast<T*>(c);
				if (nullptr != component) {
					return component;
				}
			}

			return nullptr;
		}
		__forceinline Component* GetComponentOfType(eComponentType type) {
			Component* comp = nullptr;
			for (Component* c : mComponents) {
				if (c->GetType() == type) {
					comp = c;
					break;
				}
			}
			return comp;
		}
		void SetPos(Vector2 _pos) {
			GetComponent<Transform>()->SetPos(_pos);
		}
		Vector2 GetPos() {
			return GetComponent<Transform>()->GetPos();
		}
		void SetScale(Vector2 _scale) {
			GetComponent<Transform>()->SetScale(_scale);
		}
		Vector2 GetScale() {
			return GetComponent<Transform>()->GetScale();
		}
		bool IsDead() { return mbDead; }
		void Death() { mbDead = true; }
	private:
		bool mbDead;
		std::vector<Component*> mComponents;
	};

}
