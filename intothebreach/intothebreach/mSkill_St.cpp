#include "mSkill_St.h"
#include "mTime.h"
#include "Mech.h"
#include "func.h"
#include "mResources.h"
namespace m
{
	Skill_St::Skill_St(SKILL_T _type, Unit* onwer)
		: Skill(_type, onwer)
	{
	}
	Skill_St::~Skill_St()
	{

	}
	void Skill_St::Initialize()
	{
		Vector2 diff = mFinalEdPos - mStPos;
		fDistance = diff.Length();
		Missile_vec = mFinalEdPos - mStPos;
		Missile_vec.Normalize();
	}
	void Skill_St::Update()
	{
		Skill::Update();
		Vector2 mPos = GetPos();
		if (startFire)
		{
			mPos.x += 500.f * Missile_vec.x * Time::fDeltaTime();
			mPos.y += 500.f * Missile_vec.y * Time::fDeltaTime();
		}
		CalEndFire();
		SetPos(mPos);

		if (endFire)
		{
			object::Invisible(this);
		}
	}
	void Skill_St::Render(HDC hdc)
	{
		if (!startRender) return;
		if (endFire) startFire = false;
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
	void Skill_St::ReInit(Vector2 stPos, Vector2 enPos)
	{
		Skill::ReInit(stPos, enPos);
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
		Image* im = Resources::Load<Image>(MAKE_SKILL_KEY(mType, dir), MAKE_SKILL_PATH(mType, dir));

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
		Image* im = Resources::Load<Image>(L"line", L"..\\Resources\\texture\\combat\\artillery_dot.bmp");

		int len = (int)(mFinalEdPos - mStPos).Length() / im->GetWidth() / 2;
		for (int i = 0; i < len; i++)
		{
			mPos.x += Missile_vec.x * im->GetWidth() * 2;
			mPos.y += Missile_vec.y * im->GetHeight() * 2;

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
	}
	void Skill_St::CheckDirection()
	{
		Scene* scene = SceneManager::GetActiveScene();
		Scene::TILES mPosTiles = scene->GetPosTiles();
		Unit* unit = nullptr;
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();
		Vector2 rPos(pos.x + scale.x * 2, pos.y + scale.y * 2);
		Vector2 bigRhombusPos(mPosTiles[7][0]->GetPos().x, mPosTiles[0][0]->GetPos().y);

		Vector2 bigRhombusDownPos(
			mPosTiles[0][7]->GetPos().x + mPosTiles[0][7]->GetScale().x,
			mPosTiles[7][7]->GetPos().y + mPosTiles[7][7]->GetScale().y);

		Vector2 bigRhombusScale(bigRhombusDownPos.x - bigRhombusPos.x, bigRhombusDownPos.y - bigRhombusPos.y);

		if (!math::CheckRhombusPos(bigRhombusPos, bigRhombusScale, rPos))
		{
			SetEndFire(false);
			SetStartFire(false);
			SetStartRender(false);
			return;
		}

		if (GetOwner()->GetLayerType() == LAYER_TYPE::MONSTER)
		{
			unit = GetOwner();
		}else unit = scene->GetMouseFollower();

		for (int y = 0; y < mPosTiles.size(); y++)
		{
			for (int x = 0; x < mPosTiles[y].size(); x++)
			{
				Tile* p = mPosTiles[y][x];
				if (p->GetCoord() == unit->GetCoord()) continue;

				if (math::CheckRhombusPos(p->GetPos(), p->GetScale(), rPos))
				{
					mPosTiles[(int)p->GetCoord().y][(int)p->GetCoord().x]->SetTileTexture(MAKE_MOVE_TILE_KEY(MOVE_TILE_T::square_r)
						, MAKE_MOVE_TILE_PATH(MOVE_TILE_T::square_r));
				}

				if (math::CheckRhombusPos(p->GetPos(), p->GetScale(), rPos))
				{
					if (scene->GetEffectUnit((int)p->GetCoord().y,(int)p->GetCoord().x).size() != 0)
					{
						for (int i = 0; i < scene->GetEffectUnit((int)p->GetCoord().y, (int)p->GetCoord().x).size(); i++)
						{
							scene->GetEffectUnit((int)p->GetCoord().y, (int)p->GetCoord().x)[i]->Hit(1);
						}
						SetEndFire(false);
						SetStartFire(false);
						SetStartRender(false);
						return;
					}
					if (p->GetCoord() == GetEndCoord())
					{
						SetEndFire(false);
						SetStartFire(false);
						SetStartRender(false);
						return;
					}
				}
			}
		}
	}
}