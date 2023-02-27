#include "Mech.h"
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
	Mech::Mech(MECHS _mech)
		: mImage(nullptr)
		, mTime(0.0f)
		, mIndx(0)
		, mMech(_mech)
	{
		AddComponent(new Animator());
		AddComponent(new Transform());

		Image* image = Resources::Load<Image>(
				MAKE_MECH_KEY(mMech, CONDITION_T::ANIM)
			, MAKE_MECH_PATH(mMech, CONDITION_T::ANIM));

		Animator* animator = GetComponent<Animator>();

		animator->CreateAnimation(
			MAKE_MECH_KEY(mMech, CONDITION_T::ANIM)
			, image
			, Vector2(0.f, 0.f)
			, Vector2(44.f, 34.f)
			, Vector2(44.f, 0.f)
			, 44.f
			, 4
			, 0.1f
			, 0x01
		);
		animator->Play(MAKE_MECH_KEY(mMech, CONDITION_T::ANIM), true);
	}
	Mech::~Mech()
	{
	}
	void Mech::Initialize() {
	}
	void Mech::Update()
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
	void Mech::Render(HDC hdc)
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
	void Mech::Release()
	{
		GameObject::Release();

	}
}
