#include "yaSceneManager.h"
#include "yaTitleScene.h"
#include "yaCombatScene.h"
#include "yaSelectLandScene.h"
#include "yaSelectRobotScene.h"
namespace ya
{	
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
		mScenes.resize((UINT)eSceneType::Max);

		mScenes[(UINT)eSceneType::Title] = new TitleScene();
		mScenes[(UINT)eSceneType::Combat] = new CombatScene();
		mScenes[(UINT)eSceneType::SelectLand] = new SelectLandScene();
		mScenes[(UINT)eSceneType::SelectRobot] = new SelectRobotScene();

		mActiveScene = mScenes[(UINT)eSceneType::Title];

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
