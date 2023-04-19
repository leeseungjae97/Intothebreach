#include "mTitleScene.h"
#include "mInput.h"
#include "mSceneManager.h"
#include "mBackground.h"
#include "mApplication.h"
#include "mTime.h"
#include "mCamera.h"
#include "mButton.h"
extern m::Application application;
namespace m {
	TitleScene::TitleScene() {

	}
	TitleScene::~TitleScene() {

	}
	void TitleScene::Initialize() {
		Background* b1 = new Background(L"title1", L"..\\Resources\\texture\\ui\\title\\bg0.bmp", 2, false, BOTTOM);
		Background* b2 = new Background(L"title2", L"..\\Resources\\texture\\ui\\title\\bg1.bmp", 2, false, BOTTOM);
		Background* b3 = new Background(L"title3", L"..\\Resources\\texture\\ui\\title\\bg2.bmp", 2, false, BOTTOM);
		Background* b4 = new Background(L"title4", L"..\\Resources\\texture\\ui\\title\\bg3.bmp", 2, false, BOTTOM | RIGHT);
		Background* b5 = new Background(L"title5", L"..\\Resources\\texture\\ui\\title\\title_large.bmp", 2, false, TOP | LEFT);
		Background* b6 = new Background(L"backTitle",L"..\\Resources\\texture\\ui\\title\\calibration.bmp", 0, true, DEFAULT);

		float yPos = 210.f;
		for (int i = 0; i < 5; i++)
		{
			Button* btn = new Button(TITLE_UI_TEXT_PATH[i], L"..\\Resources\\texture\\ui\\btnBack.bmp", 2, false, LEFT);
			btn->SetText(true);
			btn->SetAlpha(true);
			btn->SetMoveScene(SCENE_TYPE::SELECT_ROBOT);
			btn->UseTextAlpha(true);
			btn->SetPos(Vector2(-300.f, yPos));
			btn->SetSize(Vector2(300.f, 45.f));
			btn->SetReSizeable(true);
			yPos += 52.f;

			AddGameObject(btn, LAYER_TYPE::UI);
			btns.push_back(btn);
		}

		b4->SetCutPos(true);
		b4->SetEC(true);
		b4->SetPos(Vector2((float)application.GetResolutionWidth() * 2 
			, (float)application.GetResolutionHeight()));

		b5->SetPos(Vector2(0, 0));

		b6->SetState(GameObject::STATE::Invisible);
		AddGameObject(b1, LAYER_TYPE::BACKGROUND);
		AddGameObject(b2, LAYER_TYPE::BACKGROUND);
		AddGameObject(b3, LAYER_TYPE::BACKGROUND);
		AddGameObject(b4, LAYER_TYPE::BACKGROUND);
		AddGameObject(b5, LAYER_TYPE::BACKGROUND);
		AddGameObject(b6, LAYER_TYPE::BACKGROUND);

		scrollSpeed = 100.f;
		Scene::Initialize();
	}
	void TitleScene::Update() {
		Scene::Update();
		//if (KEY_DOWN(KEYCODE_TYPE::N)) {
		//	SceneManager::LoadScene(SCENE_TYPE::SELECT_ROBOT);
		//}
		//if (btns[1]->GetBtnName() == TITLE_UI_TEXT_PATH[(UINT)TITLE_UI_TEXT::NS_TEXT])
		//{
		//	
		//}
		if (btns[1]->GetClicked())
		{
			Camera::PushEffect(CAMERA_EFFECT_TYPE::Fade_In, 0.5f);
			SceneManager::LoadScene(SCENE_TYPE::SELECT_ROBOT);
		}
		if (GetFirstUpdate())
		{
			if (!Camera::SetLookAt(Vector2((float)application.GetResolutionWidth() * 2, (float)application.GetResolutionHeight()/2)))
			{
				mBacks[0]->SetPos(Vector2(mBacks[0]->GetPos().x - scrollSpeed * Time::fDeltaTime(), mBacks[0]->GetPos().y));
				mBacks[1]->SetPos(Vector2(mBacks[1]->GetPos().x - (scrollSpeed + 150.f) * Time::fDeltaTime(), mBacks[1]->GetPos().y));
				mBacks[2]->SetPos(Vector2(mBacks[2]->GetPos().x - (scrollSpeed + 350.f) * Time::fDeltaTime(), mBacks[2]->GetPos().y));
				scrollSpeed -= 2.f;
				//Camera::SetLookAt(Vector2(application.GetResolutionWidth(), application.GetResolutionHeight() / 2));
			}
			else
			{
				for (int i = 0; i < btns.size();i++)
				{
					if (btns[i]->GetPos().x >= 1.f)
					{
						if (btns[i]->GetTextAlpha() + 10 < 255) btns[i]->SetTextConstant(btns[i]->GetTextAlpha() + 10);
						btns[i]->SetPos(Vector2(1.f, btns[i]->GetPos().y));
						continue;
					}
					if (i != 0)
					{
						if (btns[i - 1]->GetPos().x > -150.f)
						{
							btns[i]->SetPos(Vector2(btns[i]->GetPos().x + 500.f * Time::fDeltaTime(), btns[i]->GetPos().y));
						}
					}
					else
					{
						btns[i]->SetPos(Vector2(btns[i]->GetPos().x + 500.f * Time::fDeltaTime(), btns[i]->GetPos().y));
					}
					
				}
			}
		}
		else
		{
			mBacks[5]->SetState(GameObject::STATE::Visible);
		}
		
		
	}
	void TitleScene::Render(HDC hdc) {
		Scene::Render(hdc);
	}
	void TitleScene::Release() {
		Scene::Release();
	}
	void TitleScene::OnEnter() {
		Camera::SetLookAt(Vector2((float)application.GetResolutionWidth() / 2, (float)application.GetResolutionHeight() /2));
	}
	void TitleScene::OnExit() {
		for (int i = 0; i < btns.size(); i++)
			btns[i]->SetTextConstant(255);

		//Camera::SetLookAt(Vector2((float)application.GetResolutionWidth() / 2, (float)application.GetResolutionHeight() / 2));
		SetFirstUpdate(false);
	}
}