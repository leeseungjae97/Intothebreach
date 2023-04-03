#include "mSceneManager.h"
#include "mTitleScene.h"
#include "mCombatScene.h"
#include "mSelectLandScene.h"
#include "mSelectRobotScene.h"
#include "mEndingScene.h"
#include "mIntroScene.h"
#include "mInLandScene.h"
namespace m
{	
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
		mScenes.resize((UINT)SCENE_TYPE::END);

		mScenes[(UINT)SCENE_TYPE::TITLE] = new TitleScene();
		mScenes[(UINT)SCENE_TYPE::COMBAT] = new CombatScene();
		mScenes[(UINT)SCENE_TYPE::SELECT_LAND] = new SelectLandScene();
		mScenes[(UINT)SCENE_TYPE::SELECT_ROBOT] = new SelectRobotScene();
		mScenes[(UINT)SCENE_TYPE::ENDING] = new EndingScene();
		mScenes[(UINT)SCENE_TYPE::INTRO] = new IntroScene();
		mScenes[(UINT)SCENE_TYPE::IN_LAND0] = new InLandScene(ISLAND_T::ISLAND0);
		mScenes[(UINT)SCENE_TYPE::IN_LAND1] = new InLandScene(ISLAND_T::ISLAND1);
		mScenes[(UINT)SCENE_TYPE::IN_LAND2] = new InLandScene(ISLAND_T::ISLAND2);
		mScenes[(UINT)SCENE_TYPE::IN_LAND3] = new InLandScene(ISLAND_T::ISLAND3);

		for ( Scene* scene : mScenes )
		{
			if (scene == nullptr)
				continue;
			mActiveScene = scene;
			scene->Initialize();
		}

		mActiveScene = mScenes[(UINT)SCENE_TYPE::TITLE];
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::Render(HDC hdc)
	{
		mActiveScene->Render(hdc);
	}
	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
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

	void SceneManager::LoadScene(SCENE_TYPE type) {
		// ÇöÀç¾À
		mActiveScene->OnExit();

		// ´ÙÀ½¾À
		mActiveScene = mScenes[(UINT)type];
		mActiveScene->OnEnter();
	}

}
