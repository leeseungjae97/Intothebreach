#pragma once
#include "mScene.h"

namespace m
{
	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);
		static void Release();
		static void LoadScene(SCENE_TYPE type);
	private:
		static std::vector<Scene*> mScenes;
		static Scene* mActiveScene;
	};
}
