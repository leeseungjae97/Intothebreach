#include "yaSceneManager.h"
#include "yaPlayeScene.h"
#include "yaTitleScene.h"
namespace ya
{	
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
		mScenes.resize((UINT)eSceneType::Max);

		mScenes[(UINT)eSceneType::Play] = new PlayeScene();
		mScenes[(UINT)eSceneType::Title] = new TitleScene();

		mActiveScene = mScenes[(UINT)eSceneType::Play];

		for ( Scene* scene : mScenes )
		{
			if (scene == nullptr)
				continue;

			scene->Initialize();
		}
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::Render(HDC hdc)
	{
		mActiveScene->Render(hdc);
	}

	void SceneManager::Release()
	{
		for (Scene* scene : mScenes)
		{
			if (nullptr == scene)
				continue;

			delete scene;
			scene = nullptr;
			//scene->Release();
		}
	}

	void SceneManager::LoadScene(eSceneType type) {
		// ÇöÀç¾À
		mActiveScene->OnExit();

		// ´ÙÀ½¾À
		mActiveScene = mScenes[(UINT)type];
		mActiveScene->OnEnter();
	}

}
