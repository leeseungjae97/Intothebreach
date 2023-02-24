#include "MechArtillery.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaTransform.h"
namespace ya
{
	MechArtillery::MechArtillery()
		: mImage(nullptr)
	{
	}
	MechArtillery::~MechArtillery()
	{
	}
	void MechArtillery::Initialize()
	{
		mImage = Resources::Load<Image>(L"mech_artillery", L"..\\Resources\\texture\\player\\mech_artillery.bmp");
		
		GameObject::Initialize();
	}
	void MechArtillery::Update()
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
	void MechArtillery::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		Transform* tr = GetComponent<Transform>();
		Vector2 mPos = tr->GetPos();

		TransparentBlt(
			hdc
			, (int)(mPos.x)
			, (int)(mPos.y)
			, (int)(mImage->GetWidth() * 2)
			, (int)(mImage->GetHeight() * 2)
			, mImage->GetHdc()
			, 0
			, 0
			, (int)(mImage->GetWidth())
			, (int)(mImage->GetHeight())
			, RGB(255, 0, 255)
		);
	}
	void MechArtillery::Release()
	{
		GameObject::Release();

	}
	void MechArtillery::SetPos(Vector2 _pos) {
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(_pos);
	}
}
