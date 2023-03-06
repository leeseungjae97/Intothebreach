#include "mSelectRobotScene.h"
#include "Mech.h"
#include "mSceneManager.h"
#include "mInput.h"
#include "mTransform.h"
#include "mBackground.h"
#include "mSelectGDI.h"
#include "mApplication.h"
#include "mCamera.h"
extern m::Application application;
namespace m
{
	SelectRobotScene::SelectRobotScene()
		:mMech(nullptr)
	{
	}

	SelectRobotScene::~SelectRobotScene()
	{

	}

	void SelectRobotScene::Initialize()
	{
		Scene::Initialize();
		Background* b0 = new Background(L"", L"");
		AddGameObject(b0, LAYER_TYPE::BACKGROUND);

		Background* b1 = new Background(L"selectRobotBg1"
			, L"..\\Resources\\texture\\ui\\selectRobot\\hangar_background.bmp", 0, false, true);
		AddGameObject(b1, LAYER_TYPE::BACKGROUND);

		/*mMech = new Mech(MECHS::artillery, Vector2(0,0));
		mMech->SetPos(Vector2(100.f, 100.f));
		AddGameObject(mMech, LAYER_TYPE::PLAYER);*/

		Camera::PushEffect(CAMERA_EFFECT_TYPE::Fade_In, 2.0f);

	}

	void SelectRobotScene::Update()
	{
		Scene::Update();
		if (Input::GetKeyState(KEYCODE_TYPE::N) == KEY_STATE::DOWN) {
			SceneManager::LoadScene(SCENE_TYPE::SELECT_LAND);
		}
	}

	void SelectRobotScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		//Super::Tick();	
	}

	void SelectRobotScene::Release()
	{
		Scene::Release();
	}
	void SelectRobotScene::OnEnter() {

	}
	void SelectRobotScene::OnExit() {

	}
}
