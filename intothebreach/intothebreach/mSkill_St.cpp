#include "mSkill_St.h"
#include "mTime.h"
#include "Mech.h"
#include "Alien.h"
#include "func.h"
#include "mResources.h"
namespace m
{
	Skill_St::Skill_St(SKILL_T _type, Unit* owner)
		: Skill(_type, owner)
	{
	}
	Skill_St::~Skill_St()
	{

	}
	void Skill_St::Initialize()
	{
		//object::Visible(this);
		Vector2 diff = mFinalEdPos - mStPos;
		fDistance = diff.Length();
		Missile_vec = mFinalEdPos - mStPos;
		Missile_vec.Normalize();

		//GetAnimator()->Stop();
	}
	void Skill_St::Update()
	{
		if (mOwner->GetState() == GameObject::STATE::Death
			||
			mOwner->GetState() == GameObject::STATE::Invisible
			||
			mOwner->GetState() == GameObject::STATE::Broken) return;
		Skill::Update();
		Vector2 mPos = GetPos();
		CalEndFire();

		if (startFire)
		{
			mPos.x += 500.f * Missile_vec.x * Time::fDeltaTime();
			mPos.y += 500.f * Missile_vec.y * Time::fDeltaTime();
		}
		SetPos(mPos);

		//if (endFire)
		//{
		//	
		//}
	}
	void Skill_St::Render(HDC hdc)
	{
		if (mOwner->GetState() == GameObject::STATE::Death
			||
			mOwner->GetState() == GameObject::STATE::Invisible
			||
			mOwner->GetState() == GameObject::STATE::Broken) return;
		if (endFire)
		{
			startFire = false;
			endFire = false;
			startRender = false;
			//object::Invisible(this);
		}
		if (!startRender) return;
		if (startFire)
		{
			Active(hdc);
		}
		else
		{
			GuideWire(hdc);
		}
	}
	void Skill_St::Release()
	{}
	void Skill_St::ReInit(Vector2 stPos, Vector2 enPos, Vector2 glp, SKILL_T type)
	{
		if (mOwner->GetState() == GameObject::STATE::Death
			||
			mOwner->GetState() == GameObject::STATE::Invisible
			||
			mOwner->GetState() == GameObject::STATE::Broken) return;
		Skill::ReInit(stPos, enPos, glp, type);
		this->Initialize();
	}
	void Skill_St::Active(HDC hdc)
	{
		Vector2 mPos = GetPos();

		SKILL_DIR dir = SKILL_DIR::D;
		if (mStPos < mFinalEdPos)
			dir = SKILL_DIR::R;
		if (mStPos > mFinalEdPos)
			dir = SKILL_DIR::L;
		if (mStPos.x < mFinalEdPos.x
			&& mStPos.y > mFinalEdPos.y)
			dir = SKILL_DIR::U;
		if (mStPos.x > mFinalEdPos.x
			&& mStPos.y < mFinalEdPos.y)
			dir = SKILL_DIR::D;

		Image* im = Resources::Load<Image>(MAKE_SKILL_KEY(mSkillType, dir), MAKE_SKILL_PATH(mSkillType, dir));

		TransparentBlt(hdc,
			(int)(mPos.x),
			(int)(mPos.y),
			(int)(im->GetWidth() * 2),
			(int)(im->GetHeight() * 2),
			im->GetHdc(),
			0, 0,
			im->GetWidth(),
			im->GetHeight(),
			RGB(255, 0, 255));
	}
	void Skill_St::GuideWire(HDC hdc)
	{

		Vector2 mPos = mStPos;
		Image* im;
		if (mOwner->GetLayerType() == LAYER_TYPE::MONSTER) im = Resources::Load<Image>(L"dot_r", L"..\\Resources\\texture\\combat\\artillery_dot_r.bmp");
		else im = Resources::Load<Image>(L"dot", L"..\\Resources\\texture\\combat\\artillery_dot.bmp");

		float diff = (GetGuideLinePos() - mStPos).Length();
		float len = diff / im->GetWidth() / 2.f;

		if (endCoord == guideLineCoord) (int)len == 3 ? len = 2 : 0;
		for (int i = 0; i < (int)len; i++)
		{
			mPos.x += Missile_vec.x * im->GetWidth() * 2.f;
			mPos.y += Missile_vec.y * im->GetHeight() * 2.f;

			TransparentBlt(hdc,
				(int)(mPos.x),
				(int)(mPos.y),
				(int)(im->GetWidth() * 2),
				(int)(im->GetHeight() * 2),
				im->GetHdc(),
				0, 0,
				im->GetWidth(),
				im->GetHeight(),
				RGB(255, 0, 255));
		}

		Scene* scene = SceneManager::GetActiveScene();

		//scene->SetPosTiles((int)endCoord.y, (int)endCoord.x, TILE_T::MOVE_RANGE, COMBAT_ANIM_TILE_T::warning_sprite, 125);
		//if (mOnwer->GetLayerType() == LAYER_TYPE::MONSTER)
		//{
		//	//scene->SetPosTiles((int)endCoord.y, (int)endCoord.x, TILE_T::MOVE_RANGE, COMBAT_ANIM_TILE_T::warning_sprite, 125);
		//	//scene->SetPosTiles((int)endCoord.y, (int)endCoord.x, TILE_T::MOVE_RANGE, MOVE_TILE_T::square_g);
		//}


		//if (mOnwer->GetLayerType() == LAYER_TYPE::MONSTER 
		//	&& scene->GetPlayerTurn()) return;

		ARROW_TILE_T arrow[1];
		if (mOwner->GetCoord().y < guideLineCoord.y)arrow[0] = ARROW_TILE_T::arrow_down;
		if (mOwner->GetCoord().y > guideLineCoord.y)arrow[0] = ARROW_TILE_T::arrow_up;
		if (mOwner->GetCoord().x < guideLineCoord.x)arrow[0] = ARROW_TILE_T::arrow_right;
		if (mOwner->GetCoord().x > guideLineCoord.x)arrow[0] = ARROW_TILE_T::arrow_left;

		/*if (endCoord == guideLineCoord)
		{
			if (mStPos.y > mFinalEdPos.y)arrow[0] = ARROW_TILE_T::arrow_up;
			if (mStPos.y < mFinalEdPos.y)arrow[0] = ARROW_TILE_T::arrow_down;
			if (mStPos.x > mFinalEdPos.x)arrow[0] = ARROW_TILE_T::arrow_left;
			if (mStPos.x < mFinalEdPos.x)arrow[0] = ARROW_TILE_T::arrow_right;
		}*/

		if (mOwner->GetLayerType() == LAYER_TYPE::MONSTER) Skill::DrawPushTile(arrow, ALIEN_WEAPON_PUSH_DIR[(UINT)((Alien*)mOwner)->GetAlienType()]);
		if (mOwner->GetLayerType() == LAYER_TYPE::PLAYER) Skill::DrawPushTile(arrow, WEAPON_PUSH_DIR[(UINT)((Mech*)mOwner)->GetMechType()]);

		//scene->SetPosTiles((int)endCoord.y, (int)endCoord.x, TILE_T::MOVE_RANGE, MOVE_TILE_T::square_g);
		//scene->GetPosTiles()[endCoord.y][endCoord.x]->SetCombatTileAnimator(COMBAT_ANIM_TILE_T::warning_sprite, 100);
		//scene->GetPosTile(endCoord.y, endCoord.x)->SetCombatTileAnimator(COMBAT_ANIM_TILE_T::warning_sprite, 100);
	}
	void Skill_St::CheckDirection()
	{
		Scene* scene = SceneManager::GetActiveScene();
		Scene::TILES mPosTiles = scene->GetPosTiles();
		Unit* unit = nullptr;
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();
		Vector2 rPos(pos.x + scale.x * 2, pos.y + scale.y * 2);
		HitEffectDir();

		//Vector2 bigRhombusPos(mPosTiles[7][0]->GetPos().x, mPosTiles[0][0]->GetPos().y);
		//Vector2 bigRhombusDownPos(
		//	mPosTiles[0][7]->GetPos().x + mPosTiles[0][7]->GetScale().x,
		//	mPosTiles[7][7]->GetPos().y + mPosTiles[7][7]->GetScale().y);
		//Vector2 bigRhombusScale(bigRhombusDownPos.x - bigRhombusPos.x, bigRhombusDownPos.y - bigRhombusPos.y);
		//if (!math::CheckRhombusPos(bigRhombusPos, bigRhombusScale, rPos))
		//{
		//	SetStartRender(false);
		//	return;
		//}

		if (GetOwner()->GetLayerType() == LAYER_TYPE::MONSTER)
		{
			unit = GetOwner();
		}
		else unit = scene->GetMouseFollower();

		for (int y = 0; y < mPosTiles.size(); y++)
		{
			for (int x = 0; x < mPosTiles[y].size(); x++)
			{
				Tile* p = mPosTiles[y][x];
				if (p->GetCoord() == unit->GetCoord()) continue;

				if (math::CheckRhombusPos(p->GetPos(), p->GetScale(), rPos))
				{
					mPosTiles[(int)p->GetCoord().y][(int)p->GetCoord().x]->SetTileTexture(MAKE_TILE_KEY(MOVE_TILE_T::square_r)
						, MAKE_TILE_PATH(MOVE_TILE_T::square_r));
				}

				if (math::CheckRhombusPos(p->GetPos(), p->GetScale(), rPos))
				{
					if (scene->GetEffectUnit((int)p->GetCoord().y, (int)p->GetCoord().x) != 0)
					{
						//for (int i = 0; i < scene->GetEffectUnit((int)p->GetCoord().y, (int)p->GetCoord().x).size(); i++)
						//{
						//	scene->GetEffectUnit((int)p->GetCoord().y, (int)p->GetCoord().x)[i]->Hit(1);
						//}
						scene->GetEffectUnit((int)p->GetCoord().y, (int)p->GetCoord().x)->Hit(1);
						//SetEndFire(false);
						//SetStartFire(false);
						//SetStartRender(false);
						
						ARROW_TILE_T arrow[1] = {(ARROW_TILE_T)iDir};
						PushUnit(arrow, 1);
						return;
					}
					if (p->GetCoord() == GetEndCoord())
					{
						//SetEndFire(false);
						//SetStartFire(false);
						//SetStartRender(false);
						ARROW_TILE_T arrow[1] = { (ARROW_TILE_T)iDir };
						PushUnit(arrow, 1);
						return;
					}
				}
			}
		}
	}
}