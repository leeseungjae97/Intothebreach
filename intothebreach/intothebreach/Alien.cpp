#include "Alien.h"
#include "mAnimator.h"
#include "mTransform.h"
#include "mResources.h"
#include "mInput.h"
namespace m {
	Alien::Alien(ALIENS mType, Vector2 _coord, int _range, int _hp)
		: Unit(_coord, _range, _hp)
		, mAlienType(mType)
	{
		//GetMImages().resize((UINT)ALIEN_CONDITION::END);

		//for (UINT i = 0; i < (UINT)ALIEN_CONDITION::END; i++) {
		//	GetMImages()[i] = Resources::Load<Image>(
		//		MAKE_ALIEN_KEY(mAlienType, (ALIEN_CONDITION)i)
		//		, MAKE_ALIEN_PATH(mAlienType, (ALIEN_CONDITION)i));
		//	if (nullptr == GetMImages()[i]) continue;
		//	GetMImages()[i]->SetOffset(ALIEN_OFFSET[(UINT)mAlienType]);
		//}

		//UINT len = UINT(GetMImages()[(UINT)ALIEN_CONDITION::IDLE]->GetWidth() / (GetMImages()[(UINT)ALIEN_CONDITION::SIZE]->GetWidth() + ALIENS_IMAGE_SIZE[(UINT)mAlienType].x));
		//float fHei = GetMImages()[(UINT)ALIEN_CONDITION::SIZE]->GetHeight() + ALIENS_IMAGE_SIZE[(UINT)mAlienType].y;
		//float fWid = (float)(GetMImages()[(UINT)ALIEN_CONDITION::IDLE]->GetWidth() / len);

		//GetAnimator()->CreateAnimation(
		//	MAKE_ALIEN_KEY(mAlienType, ALIEN_CONDITION::IDLE)
		//	, GetMImages()[(UINT)ALIEN_CONDITION::IDLE]
		//	, Vector2(Vector2::Zero)
		//	, Vector2(fWid, fHei)
		//	, GetMImages()[(UINT)ALIEN_CONDITION::IDLE]->GetOffset()
		//	, len
		//	, 0.5f
		//	, AC_SRC_ALPHA
		//);
		//GetAnimator()->Play(MAKE_ALIEN_KEY(mAlienType, ALIEN_CONDITION::IDLE), true);
		SetMState(STATE::Idle);
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
			SetMState(STATE::Broken);
		}
		if (KEY_PRESSED(KEYCODE_TYPE::E)) {
			SetMState(STATE::Idle);
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