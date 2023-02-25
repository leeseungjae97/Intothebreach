#include "yaSelectRobotScene.h"
#include "MechArtillery.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaTransform.h"
#include "yaBackground.h"
#include "yaSelectGDI.h"
#include "yaApplication.h"
extern ya::Application application;
namespace ya
{
	SelectRobotScene::SelectRobotScene()
		:m_MechArtillery(nullptr)
	{
	}

	SelectRobotScene::~SelectRobotScene()
	{

	}

	void SelectRobotScene::Initialize()
	{
		Background* b0 = new Background(L"", L"");
		AddGameObeject(b0, eLayerType::BackGround);

		Background* b1 = new Background(L"selectRobotBg1"
			, L"..\\Resources\\texture\\ui\\selectRobot\\hangar_background.bmp", 0, false, true);
		AddGameObeject(b1, eLayerType::BackGround);

		m_MechArtillery = new MechArtillery();
		m_MechArtillery->SetPos(Vector2(10.f, 10.f));
		AddGameObeject(m_MechArtillery, eLayerType::Player);

		Scene::Initialize();
	}

	void SelectRobotScene::Update()
	{
		Scene::Update();
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down) {
			SceneManager::LoadScene(eSceneType::SelectLand);
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
