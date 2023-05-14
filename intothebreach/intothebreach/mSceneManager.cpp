#include "mSceneManager.h"
#include "mTitleScene.h"
#include "mCombatScene.h"
#include "mSelectLandScene.h"
#include "mSelectRobotScene.h"
#include "mEndingScene.h"
#include "mIntroScene.h"
#include "mInLandScene.h"
#include "mCamera.h"
#include "mApplication.h"
extern m::Application application;
namespace m
{	
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;
	SCENE_TYPE SceneManager::selectedLand = SCENE_TYPE::IN_LAND0;
	void SceneManager::Initialize()
	{
		mScenes.resize((UINT)SCENE_TYPE::END);

		mScenes[(UINT)SCENE_TYPE::TITLE] = new TitleScene();
		mScenes[(UINT)SCENE_TYPE::SELECT_ROBOT] = new SelectRobotScene();
		mScenes[(UINT)SCENE_TYPE::ENDING] = new EndingScene();
		mScenes[(UINT)SCENE_TYPE::INTRO] = new IntroScene();
		mScenes[(UINT)SCENE_TYPE::SELECT_LAND] = new SelectLandScene();
		mScenes[(UINT)SCENE_TYPE::COMBAT] = new CombatScene();
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

		mActiveScene = mScenes[(UINT)SCENE_TYPE::INTRO];
		//LoadScene(SCENE_TYPE::SELECT_LAND);
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
		//mScenes[(UINT)SCENE_TYPE::COMBAT]->Destroy();
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
		// «ˆ¿Áæ¿
		mActiveScene->OnExit();
		//if (Camera::CheckEffectEnd())
		//{
		Camera::SetLookAt(Vector2((float)application.GetResolutionWidth() / 2, (float)application.GetResolutionHeight() / 2));
		//}
		mActiveScene = mScenes[(UINT)type];
		mActiveScene->OnEnter();
		// ¥Ÿ¿Ωæ¿
		
	}

	void SceneManager::SelectLand(int land)
	{
		selectedLand = (SCENE_TYPE)land;
	}

}
