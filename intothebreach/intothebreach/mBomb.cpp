#include "mBomb.h"
#include "mAnimator.h"
#include "mResources.h"
#include "mSceneManager.h"
#include "mTile.h"
#include "mScene.h"
namespace m
{
	Bomb::Bomb(Vector2 _coord)
		:Unit(_coord, 0, 3, WEAPON_T::NONE, 0, 0)
		, bDeath(false)
		, bombState((BOMB_S)0)
		, iConstant(1)
		, idVar(0)
		, idDir(1)
	{
		GetMImages().resize(4);
		SetHp(3);
		SetUnitConstant(0);

		Vector2 pos = SceneManager::GetActiveScene()->GetPosTiles()[_coord.y][_coord.x]->GetCenterPos();
		SetPos(pos);
		SetFinalPos(pos);

		for (int i = 0; i < 3; i++)
		{
			GetMImages()[i] = Resources::Load<Image>(BOMB_S_KEY[i], BOMB_S_PATH[i]);
		}
		SetState(STATE::Idle);
		SetCurImage(GetMImages()[0]);
	}
	Bomb::~Bomb()
	{}
	void Bomb::Initialize()
	{

	}
	void Bomb::Update()
	{
		switch (GetState())
		{
		case m::GameObject::STATE::NONE:
			break;
		case m::GameObject::STATE::NoMove:
			break;
		case m::GameObject::STATE::Idle:
		{
			idle();
		}
			break;
		case m::GameObject::STATE::Broken:
		{
			broken();
		}
			break;
		case m::GameObject::STATE::Explo:
			break;
		case m::GameObject::STATE::Water:
			break;
		case m::GameObject::STATE::Death:
			break;
		case m::GameObject::STATE::Emerge:
			break;
		case m::GameObject::STATE::Emerge_loop:
			break;
		case m::GameObject::STATE::Retreat:
			break;
		case m::GameObject::STATE::Invisible:
			break;
		case m::GameObject::STATE::Visible:
			break;
		case m::GameObject::STATE::Delete:
			break;
		case m::GameObject::STATE::End:
			break;
		default:
			break;
		}
	}
	void Bomb::Render(HDC hdc)
	{
		Vector2 mPos = GetPos();
		if (bombState == BOMB_S::Blink)
		{
			iConstant += idVar * idDir;
			if (iConstant + idVar >= 255 || iConstant - idVar <= 0) idDir *= -1;

			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			func.SourceConstantAlpha = iConstant;
			Image* im1 = Resources::Load<Image>(L"bombGlow", L"..\\Resources\\texture\\units\\mission\\bomb_glow.bmp");
			Image* im2 = Resources::Load<Image>(L"bombLight", L"..\\Resources\\texture\\units\\mission\\bomb_lights.bmp");

			AlphaBlend(
				hdc
				, (int)mPos.x
				, (int)mPos.y
				, (int)im1->GetWidth()
				, (int)im1->GetHeight()
				, im1->GetHdc()
				, 0
				, 0
				, (int)im1->GetWidth()
				, (int)im1->GetHeight()
				, func);

			AlphaBlend(
				hdc
				, (int)mPos.x
				, (int)mPos.y
				, (int)im2->GetWidth()
				, (int)im2->GetHeight()
				, im2->GetHdc()
				, 0
				, 0
				, (int)im2->GetWidth()
				, (int)im2->GetHeight()
				, func);
		}
	}
	void Bomb::Release()
	{}
	void Bomb::idle()
	{
		GetAnimator()->Stop();
		SetCurImage(GetMImages()[(UINT)BOMB_S::Idle]);
	}
	void Bomb::broken()
	{	
		GetAnimator()->Stop();
		if (nullptr == GetAnimator()->FindAnimation(L"bomb_death"))
		{
			GetAnimator()->CreateAnimation(
				L"bomb_death",
				GetMImages()[(UINT)BOMB_S::Broken],
				Vector2::Zero,
				Vector2(45.f, 35.f),
				Vector2::Zero,
				11,
				0.2f
			);
		}
		if(GetAnimator()->GetStopAnimator())
			GetAnimator()->Play(L"bomb_death", false);

	}
}