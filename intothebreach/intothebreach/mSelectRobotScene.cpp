#include "mSelectRobotScene.h"
#include "Mech.h"
#include "mSceneManager.h"
#include "mInput.h"
#include "mTransform.h"
#include "mBackground.h"
#include "mSelectGDI.h"
#include "mApplication.h"
#include "mCamera.h"
#include "func.h"
extern m::Application application;
namespace m
{
	SelectRobotScene::SelectRobotScene()
		//: Scene()
	{
	}

	SelectRobotScene::~SelectRobotScene()
	{

	}

	void SelectRobotScene::Initialize()
	{
		Scene::Initialize();
		//Background* b0 = new Background(L"", L"");
		//AddGameObject(b0, LAYER_TYPE::BACKGROUND);

		/*GameComp::mMechs.push_back((Mech*)object::Instantiate(Vector2::Minus, LAYER_TYPE::PLAYER, UNITS[(UINT)MECHS::artillery]));
		GameComp::mMechs.push_back((Mech*)object::Instantiate(Vector2::Minus, LAYER_TYPE::PLAYER, UNITS[(UINT)MECHS::tank]));
		GameComp::mMechs.push_back((Mech*)object::Instantiate(Vector2::Minus, LAYER_TYPE::PLAYER, UNITS[(UINT)MECHS::punch]));*/

		//GameComp::playerUnits[0] = (UINT)MECHS::artillery;
		//GameComp::playerUnits[1] = (UINT)MECHS::tank;
		//GameComp::playerUnits[2] = (UINT)MECHS::punch;
		//GameComp::mSaveMechs.push_back((Mech*)object::Instantiate(Vector2::Minus, LAYER_TYPE::PLAYER, UNITS[(UINT)MECHS::artillery]));
		//GameComp::mSaveMechs.push_back((Mech*)object::Instantiate(Vector2::Minus, LAYER_TYPE::PLAYER, UNITS[(UINT)MECHS::tank]));
		//GameComp::mSaveMechs.push_back((Mech*)object::Instantiate(Vector2::Minus, LAYER_TYPE::PLAYER, UNITS[(UINT)MECHS::punch]));

		moon = new Background(L"moon", L"..\\Resources\\texture\\ui\\selectRobot\\hangar_sky_top.bmp", 2, false);
		moon->SetCutPos(true);
		moon->SetPos(Vector2(165.f, -2.f));


		cloud[0] = new Background(L"cloud", L"..\\Resources\\texture\\ui\\selectRobot\\hangar_sky_bottom.bmp", 2, false);
		cloudDiff = cloud[0]->GetWidth() * 2 - moon->GetWidth() * 2 - 40.f;

		cloud[0]->SetCutPos(true);
		cloud[0]->SetPos(Vector2(moon->GetPos().x - cloudDiff, (moon->GetPos().y + moon->GetHeight() * 2)));


		cloud[1] = new Background(L"cloud", L"..\\Resources\\texture\\ui\\selectRobot\\hangar_sky_bottom.bmp", 2, false);
		cloud[1]->SetCutPos(true);
		cloud[1]->SetPos(Vector2(cloud[0]->GetPos().x - cloud[0]->GetWidth() * 2, (moon->GetPos().y + moon->GetHeight() * 2)));



		Background* hanger = new Background(L"selectRobotBg1"
			, L"..\\Resources\\texture\\ui\\selectRobot\\hangar_main.bmp", 2, false);
		hanger->SetCutPos(true);
		hanger->SetPos(Vector2(-100.f, -70.f));

		hanger->SetEC(true);

		moon->SetEC(true);
		cloud[0]->SetEC(true);
		cloud[1]->SetEC(true);
		AddGameObject(moon, LAYER_TYPE::BACKGROUND);
		AddGameObject(cloud[0], LAYER_TYPE::BACKGROUND);
		AddGameObject(cloud[1], LAYER_TYPE::BACKGROUND);

		AddGameObject(hanger, LAYER_TYPE::BACKGROUND);

		float _x = 264.f;
		float _y = 328.f;
		for (int i = 0; i < 3; i++)
		{
			lights[i] = new Background(L"light", L"..\\Resources\\texture\\ui\\selectRobot\\hangar_lights.bmp", 2, false);
			lights[i]->SetCutPos(true);
			lights[i]->SetAlphaConstant(50);
			lights[i]->SetPos(Vector2(_x, _y));
			lights[i]->SetAlpha(true);
			lights[i]->SetBlink(true);
			lights[i]->SetEC(true);
			AddGameObject(lights[i], LAYER_TYPE::BACKGROUND);
			_x += 90.f;
			_y -= 68.f;
		}


		Background* line = new Background(L"line", L"..\\Resources\\texture\\ui\\selectRobot\\waterbg_transition.bmp", 2, false); 
		line->SetCutPos(true);
		line->SetPos(Vector2(0, (float)application.GetResolutionHeight()));
		line->SetEC(true);

		AddGameObject(line, LAYER_TYPE::BACKGROUND);

		swapFake = new Background(L"sf", L"..\\Resources\\texture\\ui\\selectRobot\\shot.bmp", 0, false);
		swapFake->SetCutPos(true);
		swapFake->SetPos(Vector2(0, (float)(line->GetHeight() * 2 + application.GetResolutionHeight())));
		swapFake->SetEC(true);

		AddGameObject(swapFake, LAYER_TYPE::BACKGROUND);
		/*mMech = new Mech(MECHS::artillery, Vector2(0,0));
		mMech->SetPos(Vector2(100.f, 100.f));
		AddGameObject(mMech, LAYER_TYPE::PLAYER);*/

	}

	void SelectRobotScene::Update()
	{
		Scene::Update();
		if (KEY_DOWN(KEYCODE_TYPE::LBTN))
		{
			Camera::SetMoveTime(1.f);
			Camera::SetLookAt(Vector2((float)application.GetResolutionWidth() / 2.f, (float)swapFake->GetPos().y + swapFake->GetHeight() / 2.f));
		}
		if (Camera::GetCurPos() == Vector2((float)application.GetResolutionWidth() / 2.f, (float)swapFake->GetPos().y + swapFake->GetHeight() / 2.f))
		{
			SceneManager::LoadScene(SCENE_TYPE::SELECT_LAND);
		}

		for (int i = 0; i < 2; i++)
		{
			if (cloud[i]->GetPos().x > moon->GetPos().x + moon->GetWidth() * 2 + 40.f)
			{
				cloud[i]->SetPos(Vector2(moon->GetPos().x + 1 - cloudDiff - cloud[i]->GetWidth() * 2, cloud[i]->GetPos().y));
			}
			cloud[i]->SetPos(Vector2(cloud[i]->GetPos().x + 0.5f , cloud[i]->GetPos().y));
		}
		//for(int bright = 50; bright <= 255; bright++)
		
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
		Camera::SetLookAt(Vector2((float)application.GetResolutionWidth() / 2, (float)application.GetResolutionHeight() / 2));
	}
	void SelectRobotScene::OnExit() {
		Camera::SetLookAt(Vector2((float)application.GetResolutionWidth() / 2, (float)application.GetResolutionHeight() / 2));
	}
}
