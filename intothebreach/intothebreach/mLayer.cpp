#include "mLayer.h"
#include "mGameObject.h"

namespace m
{
	Layer::Layer()
	{
	}
	Layer::~Layer()
	{
		for (GameObject* gameObj : mGameObjects) {
			delete gameObj;
			gameObj = nullptr;
		}
	}
	void Layer::Initialize()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			if (gameObj->GetState()
				== GameObject::STATE::Death
				||
				gameObj->GetState()
				== GameObject::STATE::Invisible
				||
				gameObj->GetState()
				== GameObject::STATE::Delete)
				continue;

			gameObj->Initialize();
		}
	}
	void Layer::Update()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj == nullptr)
				continue;
			if (gameObj->GetState()
				== GameObject::STATE::Death
				||
				gameObj->GetState()
				== GameObject::STATE::Invisible
				||
				gameObj->GetState()
				== GameObject::STATE::Delete)
				continue;

			gameObj->Update();
		}
	}
	void Layer::Render(HDC hdc)
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (!gameObj->GetShown())
			{
				gameObj->SetShown(true);
			}

			if (gameObj->GetIsFirstUpdate()) continue;
			
			if (gameObj == nullptr)
				continue;

			if (gameObj->GetState()
				== GameObject::STATE::Death
				||
				gameObj->GetState()
				== GameObject::STATE::Invisible
				||
				gameObj->GetState()
				== GameObject::STATE::Delete)
				continue;

			gameObj->Render(hdc);
		}
	}
	void Layer::Release()
	{

	}
	void Layer::AddGameObject(GameObject* gameObj)
	{
		if (gameObj == nullptr)
			return;

		mGameObjects.push_back(gameObj);
	}
	void Layer::ObjectFront(GameObject* gameObj)
	{
		if (gameObj == nullptr) return;
		vector<GameObject*>::iterator iter = mGameObjects.begin();
		while (iter != mGameObjects.end())
		{
			if ((*iter) == gameObj)
			{
				iter = mGameObjects.erase(iter);
			}
			else iter++;
		}
		mGameObjects.push_back(gameObj);
	}
}
