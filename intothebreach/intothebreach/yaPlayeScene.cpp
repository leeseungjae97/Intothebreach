#include "yaPlayeScene.h"
#include "yaCuphead.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaTransform.h"
namespace ya
{
	PlayeScene::PlayeScene()
	{
	}

	PlayeScene::~PlayeScene()
	{
	}

	void PlayeScene::Initialize()
	{
		mCuphead = new Cuphead();
		Transform* tr = mCuphead->GetComponent<Transform>();
		mCuphead->SetName(L"Player");
		AddGameObeject(mCuphead, eLayerType::Player);
		Scene::Initialize();
	}

	void PlayeScene::Update()
	{
		Scene::Update();
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down) {
			SceneManager::LoadScene(eSceneType::Title);
		}
	}

	void PlayeScene::Render(HDC hdc)
	{
		//Super::Tick();
		Scene::Render(hdc);
	}

	void PlayeScene::Release()
	{
		Scene::Release();
	}
	void PlayeScene::OnEnter() {

	}
	void PlayeScene::OnExit() {
		//mCuphead->SetPos(Vector2(0.0f, 0.0f));
	}
}
