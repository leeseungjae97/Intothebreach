#include "MechArtillery.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaTransform.h"
#include "yaTime.h"
namespace ya
{
	MechArtillery::MechArtillery()
		: mImage(nullptr)
		, mTime(0.0f)
		, mIndx(0)
	{
	}
	MechArtillery::~MechArtillery()
	{
	}
	void MechArtillery::Initialize()
	{
		
		mImage = Resources::Load<Image>(L"mech_artillery"
			, L"..\\Resources\\texture\\units\\player\\mech_artillery_a.bmp");
		
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
		mTime += Time::fDeltaTime();
		if (mIndx > 4) {
			mIndx = 0;
		}
		if (mTime > 1.0) {
			mIndx++;
		}
		//44 34
		TransparentBlt(
			hdc
			, (int)(mPos.x)
			, (int)(mPos.y)
			, 44
			, 34
			, mImage->GetHdc()
			, 0
			, 0
			, 34 * mIndx
			, 44
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
