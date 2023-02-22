#include "yaCuphead.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaResources.h"
#include "yImage.h"
#include "yaTransform.h"
namespace ya
{
	Cuphead::Cuphead()
		: mImage(nullptr)
	{
	}
	Cuphead::~Cuphead()
	{
	}
	void Cuphead::Initialize()
	{
		mImage = Resources::Load<Image>(L"cupheadImage", L"..\\Resources\\cupheadImage.bmp");
		
		GameObject::Initialize();
	}
	void Cuphead::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 mPos = tr->GetPos();

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
		tr->SetPos(mPos);
	}
	void Cuphead::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		Transform* tr = GetComponent<Transform>();
		Vector2 mPos = tr->GetPos();
		TransparentBlt(
			hdc
			, (int)(mPos.x)
			, (int)(mPos.y)
			, (int)(mImage->GetWidth())
			, (int)(mImage->GetHeight())
			, mImage->GetHdc()
			, 0
			, 0
			, (int)(mImage->GetWidth())
			, (int)(mImage->GetHeight())
			, RGB(255, 0, 255)
		);
	}
	void Cuphead::Release()
	{
		GameObject::Release();

	}
}
