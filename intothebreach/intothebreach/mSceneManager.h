#pragma once
namespace m
{
	class Scene;
	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);
		static void Release();
		static void Destroy();
		static void LoadScene(SCENE_TYPE type);
		static void SelectLand(int land);
		static Scene* GetActiveScene() { return mActiveScene; }
		static SCENE_TYPE GetSelectLand() { return selectedLand; }

	private:
		static std::vector<Scene*> mScenes;
		static Scene* mActiveScene;
		static SCENE_TYPE selectedLand;
	};
}
