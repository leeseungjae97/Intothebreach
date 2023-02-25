#include "MechArtillery.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaAnimator.h"
namespace ya
{
	MechArtillery::MechArtillery()
		: mImage(nullptr)
		, mTime(0.0f)
		, mIndx(0)
	{
		AddComponent(new Animator());
		AddComponent(new Transform());

		Image* image = Resources::Load<Image>(L"mech_artillery_a"
			, L"..\\Resources\\texture\\player\\mech_artillery_a.bmp");

		Animator* animator = GetComponent<Animator>();

		animator->CreateAnimation(
			L"mech_artillery_a"
			, image
			, Vector2(0.f, 0.f)
			, Vector2(44.f, 34.f)
			, Vector2(44.f, 0.f)
			, 44.f
			, 4
			, 0.1f);
		animator->Play(L"mech_artillery_a", true);
	}
	MechArtillery::~MechArtillery()
	{
	}
	void MechArtillery::Initialize()
	{

	}
	void MechArtillery::Update()
	{
		Vector2 mPos = GetComponent<Transform>()->GetPos();

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
		GetComponent<Transform>()->SetPos(mPos);
	}
	void MechArtillery::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		//Transform* tr = GetComponent<Transform>();
		//Vector2 mPos = tr->GetPos();
		//mTime += Time::fDeltaTime();
		//if (mIndx > 4) {
		//	mIndx = 0;
		//}
		//if (mTime > 1.0) {
		//	mIndx++;
		//}
		////44 34
		//TransparentBlt(
		//	hdc
		//	, (int)(mPos.x)
		//	, (int)(mPos.y)
		//	, 44
		//	, 34
		//	, mImage->GetHdc()
		//	, 0
		//	, 0
		//	, 34 * mIndx
		//	, 44
		//	, RGB(255, 0, 255)
		//);
	}
	void MechArtillery::Release()
	{
		GameObject::Release();

	}
}
