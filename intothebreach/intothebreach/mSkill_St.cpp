#include "mSkill_St.h"
#include "mTime.h"
#include "Mech.h"
#include "Alien.h"
#include "func.h"
#include "mResources.h"
namespace m
{
	Skill_St::Skill_St(WEAPON_T _type, Unit* owner)
		: Skill(_type, owner)
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
		CalEndFire();

		if (startFire)
		{
			mPos.x += 500.f * Missile_vec.x * Time::fDeltaTime();
			mPos.y += 500.f * Missile_vec.y * Time::fDeltaTime();
			//if (bOppsite)
			//{
			//	opPos.x += 500.f * opMissile_vec.x * Time::fDeltaTime();
			//	opPos.y += 500.f * opMissile_vec.y * Time::fDeltaTime();
			//}
		}

		SetPos(mPos);
	}
	void Skill_St::Render(HDC hdc)
	{
		Skill::Render(hdc);
		if (endFire)
		{
			startFire = false;
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
		Skill::ReInit(stPos, enPos, glp, type);
		this->Initialize();
	}
	void Skill_St::Active(HDC hdc)
	{
		Vector2 mPos = GetPos();
		SKILL_DIR dir = SKILL_DIR::D;
		//SKILL_DIR opDir = SKILL_DIR::D;
		if (mStPos < mFinalEdPos)
		{
			dir = SKILL_DIR::R;
			//opDir = SKILL_DIR::L;
		}
		if (mStPos > mFinalEdPos)
		{
			dir = SKILL_DIR::L;
			//opDir = SKILL_DIR::R;
		}
		if (mStPos.x < mFinalEdPos.x
			&& mStPos.y > mFinalEdPos.y)
		{
			dir = SKILL_DIR::U;
			//opDir = SKILL_DIR::D;
		}
		if (mStPos.x > mFinalEdPos.x
			&& mStPos.y < mFinalEdPos.y)
		{
			dir = SKILL_DIR::D;
			//opDir = SKILL_DIR::U;
		}

		Image* im = Resources::Load<Image>(MAKE_SKILL_KEY(mWeaponType, dir), MAKE_SKILL_PATH(mWeaponType, dir));
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

		//if (bOppsite)
		//{
		//	im = Resources::Load<Image>(MAKE_SKILL_KEY(mWeaponType, opDir), MAKE_SKILL_PATH(mWeaponType, opDir));
		//	TransparentBlt(hdc,
		//		(int)(opPos.x),
		//		(int)(opPos.y),
		//		(int)(im->GetWidth() * 2),
		//		(int)(im->GetHeight() * 2),
		//		im->GetHdc(),
		//		0, 0,
		//		im->GetWidth(),
		//		im->GetHeight(),
		//		RGB(255, 0, 255));
		//}
	}
	void Skill_St::GuideWire(HDC hdc)
	{

		Vector2 mPos = mStPos;
		Image* im;
		if (mOwner->GetButtonType() == LAYER_TYPE::MONSTER) im = Resources::Load<Image>(L"dot_r", L"..\\Resources\\texture\\combat\\artillery_dot_r.bmp");
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

		ARROW_TILE_T arrow[1];
		if (mOwner->GetCoord().y < guideLineCoord.y)arrow[0] = ARROW_TILE_T::arrow_down;
		if (mOwner->GetCoord().y > guideLineCoord.y)arrow[0] = ARROW_TILE_T::arrow_up;
		if (mOwner->GetCoord().x < guideLineCoord.x)arrow[0] = ARROW_TILE_T::arrow_right;
		if (mOwner->GetCoord().x > guideLineCoord.x)arrow[0] = ARROW_TILE_T::arrow_left;

		
		Skill::DrawPushTile(arrow, WEAPON_PUSH_DIR[(UINT)GetWeaponType()]);

		//if (bOppsite)
		//{
		//	mPos = mStPos;
		//	Scene* scene = SceneManager::GetActiveScene();
		//	diff = (scene->GetPosTiles()[opGuideEndCoord.y][opGuideEndCoord.x]->GetCenterPos() - mStPos).Length();
		//	len = diff / im->GetWidth() / 2.f;

		//	if (opEndCoord == opGuideEndCoord)(int)len == 3 ? len = 2 : 0;
		//	for (int i = 0; i < (int)len; i++)
		//	{
		//		mPos.x += opMissile_vec.x * im->GetWidth() * 2.f;
		//		mPos.y += opMissile_vec.y * im->GetHeight() * 2.f;

		//		TransparentBlt(hdc,
		//			(int)(mPos.x),
		//			(int)(mPos.y),
		//			(int)(im->GetWidth() * 2),
		//			(int)(im->GetHeight() * 2),
		//			im->GetHdc(),
		//			0, 0,
		//			im->GetWidth(),
		//			im->GetHeight(),
		//			RGB(255, 0, 255));
		//	}
		//	if (mOwner->GetCoord().y < opGuideEndCoord.y)arrow[0] = ARROW_TILE_T::arrow_down;
		//	if (mOwner->GetCoord().y > opGuideEndCoord.y)arrow[0] = ARROW_TILE_T::arrow_up;
		//	if (mOwner->GetCoord().x < opGuideEndCoord.x)arrow[0] = ARROW_TILE_T::arrow_right;
		//	if (mOwner->GetCoord().x > opGuideEndCoord.x)arrow[0] = ARROW_TILE_T::arrow_left;


		//	Skill::DrawPushTile(arrow, WEAPON_PUSH_DIR[(UINT)GetWeaponType()], true);
		//}
	}
	void Skill_St::CheckDirection()
	{
		Scene* scene = SceneManager::GetActiveScene();
		Scene::TILES mPosTiles = scene->GetPosTiles();
		Unit* unit = nullptr;
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();
		Vector2 rPos(pos.x + scale.x * 2, pos.y + scale.y * 2);
		//Vector2 pPos = opPos;
		//Vector2 pRPos(opPos.x + scale.x * 2, opPos.y + scale.y * 2);
		HitEffectDir();

		if (GetOwner()->GetButtonType() == LAYER_TYPE::MONSTER) unit = GetOwner();
		else unit = scene->GetMouseFollower();

		for (int y = 0; y < mPosTiles.size(); y++)
		{
			for (int x = 0; x < mPosTiles[y].size(); x++)
			{
				Tile* p = mPosTiles[y][x];
				if (p->GetCoord() == unit->GetCoord()) continue;

				//if (math::CheckRhombusPos(p->GetPos(), p->GetScale(), rPos))
				//{
				//	//mPosTiles[(int)p->GetCoord().y][(int)p->GetCoord().x]->SetTileTexture(MAKE_TILE_KEY(MOVE_TILE_T::square_r)
				//	//	, MAKE_TILE_PATH(MOVE_TILE_T::square_r));
				//}

				if (math::CheckRhombusPos(p->GetPos(), p->GetScale(), rPos))
				{
					if (scene->SearchAffectUnit((int)p->GetCoord().y, (int)p->GetCoord().x))
					{
						scene->HitAffectUnit((int)p->GetCoord().y, (int)p->GetCoord().x, 1);
						SetEndFire(false);
						SetStartFire(false);
						SetStartRender(false);
						

						ARROW_TILE_T arrow[1] = { (ARROW_TILE_T)iDir };
						PushUnit(arrow, WEAPON_PUSH_DIR[(UINT)mOwner->GetWeaponType()]);
						return;
					}
					if (p->GetCoord() == GetEndCoord())
					{
						SetEndFire(false);
						SetStartFire(false);
						SetStartRender(false);

						ARROW_TILE_T arrow[1] = { (ARROW_TILE_T)iDir };
						PushUnit(arrow, WEAPON_PUSH_DIR[(UINT)mOwner->GetWeaponType()]);
						return;
					}
				}
				//if (bOppsite)
				//{
				//	if (math::CheckRhombusPos(p->GetPos(), p->GetScale(), pRPos))
				//	{
				//		if (scene->SearchAffectUnit((int)p->GetCoord().y, (int)p->GetCoord().x))
				//		{
				//			scene->HitAffectUnit((int)p->GetCoord().y, (int)p->GetCoord().x, 1);
				//			SetEndFire(false);
				//			SetStartFire(false);
				//			SetStartRender(false);


				//			ARROW_TILE_T arrow[1] = { (ARROW_TILE_T)pIDir };
				//			PushUnit(arrow, WEAPON_PUSH_DIR[(UINT)mOwner->GetWeaponType()]);
				//		}
				//		if (p->GetCoord() == GetEndCoord())
				//		{
				//			SetEndFire(false);
				//			SetStartFire(false);
				//			SetStartRender(false);

				//			ARROW_TILE_T arrow[1] = { (ARROW_TILE_T)pIDir };
				//			PushUnit(arrow, WEAPON_PUSH_DIR[(UINT)mOwner->GetWeaponType()]);
				//		}
				//	}
				//}
			}
		}
	}
	void Skill_St::CalEndFire()
	{
		Vector2 vec = GetPos();
		//if (vec.x == mStPos.x) return;

		float absD = abs(mFinalEdPos.x - mStPos.x);
		float absMD = abs(vec.x - mStPos.x);
		float diff = absD - absMD;

		if (mStPos == Vector2::Zero || mFinalEdPos == Vector2::One) endFire = false;
		else diff <= 0.f ? endFire = true : endFire = false;
	}
}