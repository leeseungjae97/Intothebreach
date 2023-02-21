#include "yaCuphead.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaResources.h"
#include "yImage.h"
namespace ya
{
	Cuphead::Cuphead()
	{
	}
	Cuphead::~Cuphead()
	{
	}
	void Cuphead::Initialize()
	{
		Image* cupheadImg = Resources::Load<Image>(L"cupheadImage", L"...\\Resource\\cupheadImage.bmp");

		GameObject::Initialize();
	}
	void Cuphead::Update()
	{
		Vector2 mPos = GetPos();
		GameObject::Update();
		if (Input::GetKeyState(eKeyCode::A) == eKeyState::Pressed)
		{
			mPos.x -= 100.0f * Time::fDeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::D) == eKeyState::Pressed)
		{
			mPos.x += 100.0f * Time::fDeltaTime();
		}

		//if (Input::GetKeyState(eKeyCode::D) == eKeyState::Up)
		//{
		//	mPos.x = 0.0f;
		//	mPos.y = 0.0f;
		//}

		if (Input::GetKeyState(eKeyCode::W) == eKeyState::Pressed)
		{
			mPos.y -= 100.0f * Time::fDeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::S) == eKeyState::Pressed)
		{
			mPos.y += 100.0f * Time::fDeltaTime();
		}
		SetPos(mPos);
	}
	void Cuphead::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		Vector2 mPos = GetPos();
		//BitBlt(hdc, mPos.x, mPos.y, mImage->GetWidth());

	}
	void Cuphead::Release()
	{
		GameObject::Release();

	}
}
