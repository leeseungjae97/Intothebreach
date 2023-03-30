#include "Alien.h"
#include "mAnimator.h"
#include "mTransform.h"
#include "mResources.h"
#include "mInput.h"
#include "mScene.h"
#include "mSceneManager.h"
namespace m
{
	Alien::Alien(ALIENS mType, Vector2 _coord, int idx)
		: Unit(_coord
			, ALIEN_MOVE_RANGE[(UINT)mType]
			, ALIEN_HP[(UINT)mType]
			, ALIEN_BASIC_WEAPON[(UINT)mType]
		)
		, mAlienType(mType)
		, mIdx(idx)
	{
		vector<Image*> vImage = GetMImages();
		vImage.resize((UINT)ALIEN_CONDITION::END);

		for (UINT i = 0; i < (UINT)ALIEN_CONDITION::END; i++)
		{
			if (ALIENS_APL_COND[(UINT)mType][i] != 1) continue;
			vImage[i] = Resources::Load<Image>(
				MAKE_ALIEN_KEY(mAlienType, (ALIEN_CONDITION)i)
				, MAKE_ALIEN_PATH(mAlienType, (ALIEN_CONDITION)i));
			if (nullptr == vImage[i]) continue;
			vImage[i]->SetOffset(ALIEN_OFFSET[(UINT)mAlienType]);
		}
		for (int i = 0; i < 3; i++)
		{
			Vector2 size = ALIENS_SIZES[(UINT)mAlienType][i];
			UINT len = (UINT)((float)vImage[(int)i]->GetWidth() / size.x);

			GetAnimator()->CreateAnimation(
				MAKE_ALIEN_KEY(mAlienType, (ALIEN_CONDITION)i)
				, vImage[i]
				, Vector2(Vector2::Zero)
				, Vector2(size.x, size.y)
				, vImage[i]->GetOffset()
				, len
				, 0.2f
				, AC_SRC_OVER
			);
		}
		GetAnimator()->Play(MAKE_ALIEN_KEY(mAlienType, ALIEN_CONDITION::IDLE), true);
		SetState(STATE::Idle);

		SetSkillIdx(0);
		SetCurAttackSkill();
	}
	Alien::Alien(Alien& _origin)
		: mAlienType(_origin.mAlienType)
	{}
	Alien::~Alien()
	{}
	void Alien::Initialize()
	{

	}
	void Alien::Update()
	{
		Unit::Update();
		if (KEY_PRESSED(KEYCODE_TYPE::Q))
		{
			SetState(STATE::Broken);
		}
		if (KEY_PRESSED(KEYCODE_TYPE::R))
		{
			SetState(STATE::Emerge);
		}
		if (KEY_PRESSED(KEYCODE_TYPE::E))
		{
			SetState(STATE::Idle);
		}

		if (Unit::GetCurHp() == 0)
		{
			SetState(STATE::Broken);
		}
		//else
		//{
		//	SetState(STATE::Idle);
		//}
		switch (GetState())
		{
		case STATE::Idle:
			idle();
			break;
		case STATE::Broken:
			if (GetAnimator()->GetStopAnimator())
			{
				SetState(STATE::Death);
			}
			broken();
			break;
		case STATE::Water:
			water();
			break;
		case STATE::Emerge:
		{
			if (GetAnimator()->GetStopAnimator())
			{
				SetState(STATE::Idle);
			}
			emerge();
		}
			break;
		case STATE::End:
			break;
		default:
			break;
		}
	}
	void Alien::Render(HDC hdc)
	{
		Unit::Render(hdc);
	}
	void Alien::Release()
	{
		Unit::Release();
	}
	void Alien::idle()
	{
		GetAnimator()->Play(MAKE_ALIEN_KEY(mAlienType, ALIEN_CONDITION::IDLE), true);
		SetCurImage(nullptr);
	}
	void Alien::broken()
	{
		GetAnimator()->Stop();
		GetAnimator()->Play(MAKE_ALIEN_KEY(mAlienType, ALIEN_CONDITION::DEATH), false);

		SetCurImage(nullptr);
	}
	void Alien::water()
	{
		GetAnimator()->Stop();
		SetCurImage(GetMImages()[(UINT)ALIEN_CONDITION::WATER]);
	}
	void Alien::emerge()
	{
		GetAnimator()->Stop();
		GetAnimator()->Play(MAKE_ALIEN_KEY(mAlienType, ALIEN_CONDITION::EMERGE), false);
		SetCurImage(nullptr);
	}
}