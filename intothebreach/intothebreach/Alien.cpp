#include "Alien.h"
#include "mAnimator.h"
#include "mTransform.h"
#include "mResources.h"
#include "mInput.h"
namespace m {
	Alien::Alien(ALIENS mType, Vector2 _coord, int _range, int _hp, SKILL_T _type)
		: Unit(_coord, _range, _hp, (int)_type)
		, mAlienType(mType)
	{
		GetMImages().resize((UINT)ALIEN_CONDITION::END);


		for (UINT i = 0; i < (UINT)ALIEN_CONDITION::END; i++) {
			if (ALIENS_APL_COND[(UINT)mType][i] != 1) continue;
			GetMImages()[i] = Resources::Load<Image>(
				MAKE_ALIEN_KEY(mAlienType, (ALIEN_CONDITION)i)
				, MAKE_ALIEN_PATH(mAlienType, (ALIEN_CONDITION)i));
			if (nullptr == GetMImages()[i]) continue;
			GetMImages()[i]->SetOffset(ALIEN_OFFSET[(UINT)mAlienType]);
		}
		for (int i = 0; i < 3; i++) {
			Vector2 size = ALIENS_SIZES[(UINT)mAlienType][i];
			UINT len = (UINT)GetMImages()[(UINT)i]->GetWidth() / size.x;

			GetAnimator()->CreateAnimation(
				MAKE_ALIEN_KEY(mAlienType, (ALIEN_CONDITION)i)
				, GetMImages()[i]
				, Vector2(Vector2::Zero)
				, Vector2(size.x, size.y)
				, GetMImages()[i]->GetOffset()
				, len
				, 0.5f
				, AC_SRC_OVER
			);
		}
		GetAnimator()->Play(MAKE_ALIEN_KEY(mAlienType, ALIEN_CONDITION::IDLE), true);
		SetState(STATE::Idle);
	}
	Alien::Alien(Alien& _origin) 
		: mAlienType(_origin.mAlienType)
	{
	}
	Alien::~Alien() 
	{
	}
	void Alien::Initialize() {

	}
	void Alien::Update() {
		Unit::Update();
		if (KEY_PRESSED(KEYCODE_TYPE::Q)) {
			SetState(STATE::Broken);
		}
		if (KEY_PRESSED(KEYCODE_TYPE::E)) {
			SetState(STATE::Idle);
		}
	}
	void Alien::Render(HDC hdc) {
		Unit::Render(hdc);
	}
	void Alien::Release() {
		Unit::Release();
	}
	void Alien::idle() {
		GetAnimator()->Play(MAKE_ALIEN_KEY(mAlienType, ALIEN_CONDITION::IDLE), true);
		SetCurImage(nullptr);
	}
	void Alien::broken() {
		GetAnimator()->Stop();
		SetCurImage(GetMImages()[(UINT)ALIEN_CONDITION::DEATH]);
	}
	void Alien::water() {
		GetAnimator()->Stop();
		SetCurImage(GetMImages()[(UINT)ALIEN_CONDITION::WATER]);
	}
}