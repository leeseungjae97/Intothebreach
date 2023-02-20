#include "yaPlayeScene.h"
#include "yaCuphead.h"

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
		/*for (size_t i = 0; i < 100; i++) {
			
		}*/
		Cuphead* cuphead = new Cuphead();
		//cuphead->SetPos(Vector2{ 0.0f, 0.0f } );
		cuphead->SetName(L"Player");
		AddGameObeject(cuphead, eLayerType::Player);
		Scene::Initialize();
	}

	void PlayeScene::Update()
	{
		Scene::Update();
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
}
