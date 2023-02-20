#include "yaSceneManager.h"
#include "yaPlayeScene.h"

namespace ya
{	//SceneManager scsene;
	//SceneManager* scsene = new SceneManager();
	std::vector<Scene*> SceneManager::mScenes = {};

	void SceneManager::Initialize()
	{
		mScenes.resize((UINT)eSceneType::Max);

		mScenes[(UINT)eSceneType::Play] = new PlayeScene();
		mScenes[(UINT)eSceneType::Play]->SetName(L"PLAYER");

		for ( Scene* scene : mScenes )
		{
			if (scene == nullptr)
				continue;

			scene->Initialize();
		}
	}

	void SceneManager::Update()
	{
		//for (size_t i = 0; i < (UINT)eSceneType::Max; i++)
		//{
		//	if (mScenes[i] == nullptr)
		//		continue;

		//	mScenes[i]->Update();
		//}
		//read only
		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;

			scene->Update();
		}
	}

	void SceneManager::Render(HDC hdc)
	{
		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;

			scene->Render(hdc);
		}
	}

	void SceneManager::Release()
	{
		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;

			scene->Release();
		}

		//delete[] mScene;
	}

}
