#include "mSkill.h"
#include "mSelectGDI.h"
#include "mTime.h"
#include "mTransform.h"
#include "mAnimator.h"
#include "func.h"
#include "mApplication.h"
#include "mImage.h"
#include "mUnit.h"
#include "mResources.h"
#include "mSound.h"
#include "mSceneManager.h"
extern m::Application application;
namespace m
{
	Skill::Skill(WEAPON_T _type, Unit* owner)
		: mType((SKILL_T)WEAPON_SKILL[(UINT)_type])
		, mOwner(owner)
		, mWeaponType(_type)
		, mLayerType(LAYER_TYPE::SKILL)
		, endFire(false)
		, startFire(false)
		, startRender(false)
		, fTime(0)
		, offsetHeight(0)
		, maxTheta(0)
		, minTheta(0)
		, fHeight(0)
		, fMaxTime(0)
		, velocityY(0)
		, velocityX(0)
		, gravityAccel(0)
		, arcTheta(0)
		, Missile_vec(Vector2::Minus)
		, endCoord(Vector2::Minus)
		, mStPos(Vector2::Minus)
		, mFinalEdPos(Vector2::Minus)
	{
		AddComponent(new Transform);
		AddComponent(new Animator);
		mAnimator = GetComponent<Animator>();
		if(WEAPON_LAUNCH_SOUNDS[(UINT)_type] != L"")
			launchSound = Resources::Load<Sound>(WEAPON_LAUNCH_SOUNDS[(UINT)_type], WEAPON_LAUNCH_SOUNDS[(UINT)_type]);
		if (WEAPON_IMPACT_SOUNDS[(UINT)_type] != L"")
			impactSound = Resources::Load<Sound>(WEAPON_IMPACT_SOUNDS[(UINT)_type], WEAPON_IMPACT_SOUNDS[(UINT)_type]);
	}
	Skill::Skill(Skill& _origin)
		: mType(_origin.mType)
		, mLayerType(LAYER_TYPE::SKILL)
		, mOwner(_origin.mOwner)
		, endFire(false)
		, startFire(false)
		, startRender(false)
		, fTime(_origin.fTime)
		, offsetHeight(_origin.offsetHeight)
		, maxTheta(_origin.maxTheta)
		, minTheta(_origin.minTheta)
		, fHeight(_origin.fHeight)
		, fMaxTime(_origin.fMaxTime)
		, velocityY(_origin.velocityY)
		, velocityX(_origin.velocityX)
		, gravityAccel(_origin.gravityAccel)
		, arcTheta(_origin.arcTheta)
		, Missile_vec(_origin.Missile_vec)
		, endCoord(_origin.endCoord)
		, mStPos(_origin.mStPos)
		, mFinalEdPos(_origin.mFinalEdPos)
	{}
	Skill::~Skill()
	{}
	void Skill::Initialize()
	{
	}
	void Skill::CalEndFire()
	{
		Vector2 vec = GetPos();
		//if (vec.x == mStPos.x) return;

		float absD = abs(mFinalEdPos.x - mStPos.x);
		float absMD = abs(vec.x - mStPos.x);
		float diff = absD - absMD;

		if (mStPos == Vector2::Minus || mFinalEdPos == Vector2::Minus) endFire = false;
		else diff <= 0.f ? endFire = true : endFire = false;
		//if (bOppsite)
		//{
		//	Vector2 vec2 = opPos;
		//	float absD2 = abs(opEndPos.x - mStPos.x);
		//	float absMD2 = abs(vec2.x - mStPos.x);
		//	float diff2 = absD2 - absMD2;

		//	if (mStPos == Vector2::Zero || opEndPos == Vector2::One) endFire = false;
		//	else diff <= 0.f ? endFire = true : endFire = false;
		//}
	}
	void Skill::CheckDirection()
	{
		//impactSoundPlayed = false;
		//if (!impactSoundPlayed)
		//{
		//	if (impactSound)
		//		impactSound->Play(false);
		//	impactSoundPlayed = true;
		//}
	}
	void Skill::HitEffectDir()
	{
		if (mOwner->GetCoord().y < guideLineCoord.y) iDir = DOWN_NUM;
		if (mOwner->GetCoord().y > guideLineCoord.y) iDir = UP_NUM;
		if (mOwner->GetCoord().x < guideLineCoord.x) iDir = RIGHT_NUM;
		if (mOwner->GetCoord().x > guideLineCoord.x) iDir = LEFT_NUM;


		//if (mOwner->GetCoord().y < opGuideEndCoord.y) pIDir = DOWN_NUM;
		//if (mOwner->GetCoord().y > opGuideEndCoord.y) pIDir = UP_NUM;
		//if (mOwner->GetCoord().x < opGuideEndCoord.x) pIDir = RIGHT_NUM;
		//if (mOwner->GetCoord().x > opGuideEndCoord.x) pIDir = LEFT_NUM;
	}
	void Skill::ClearPushTile()
	{
		Scene* scene = SceneManager::GetActiveScene();
		if (scene->GetBackTiles().size() == 0) return;
		for (int i = 0; i < scene->GetBackTiles().size(); i++)
		{
			scene->GetBackTiles()[i]->SetState(GameObject::STATE::Delete);
			scene->GetBackTiles()[i] = nullptr;
		}
		scene->GetBackTiles().clear();

		//Safe_Delete_X_Vec(scene->GetBackTiles());
	}
	bool Skill::CheckSkillFiring()
	{
		if (endFire && startFire)
		{
			return false;
		}
		if (!endFire && !startFire) return false;
		if (!endFire && startFire)
		{

			return true;
		}
		return false;
	}

	//void Skill::SetOppsiteDraw(Vector2 _coord, Vector2 guideCoord)
	//{
	//	Scene* scene = SceneManager::GetActiveScene();
	//	opEndCoord = _coord; 
	//	opGuideEndCoord = guideCoord; 
	//	opEndPos = scene->GetPosTiles()[opEndCoord.y][opEndCoord.x]->GetCenterPos();
	//	opMissile_vec = opEndPos - mStPos;
	//	opPos = mStPos;
	//	opMissile_vec.Normalize();
	//}

	void Skill::LaunchSound()
	{
		if (!launchSoundPlayed)
		{
			launchSound->Play(false);
			impactSoundPlayed = false;
			launchSoundPlayed = true;
		}
	}

	void Skill::ImpactSound()
	{
		if (!impactSoundPlayed)
		{
			impactSound->Play(false);
			impactSoundPlayed = true;
			launchSoundPlayed = false;
		}
	}

	void Skill::Clear()
	{
		if (nullptr == this) return;
		endFire = false;
		startFire = false;
		startRender = false;

		offsetHeight = 0;
		maxTheta = 0;
		minTheta = 0;
		fHeight = 0;
		fMaxTime = 0;
		fTime = 0;
		velocityY = 0;
		velocityX = 0;
		gravityAccel = 0;

		fDistance = 0;

		arcTheta = 0;
		theta = 0;

		iDir = 0;

		guideLinePos = Vector2::Zero;
		guideLineCoord = Vector2::Zero;
		Missile_vec = Vector2::Zero;
		Missile_vec2 = Vector2::Zero;
		endCoord = Vector2::Zero;
		mStPos = Vector2::Zero;
		mFinalEdPos = Vector2::Zero;
	}

	void Skill::Update()
	{
		if (mOwner->GetState() == GameObject::STATE::Invisible) return;
		if (mOwner->GetState() == GameObject::STATE::Death
			||
			mOwner->GetState() == GameObject::STATE::Broken)
		{
			SetState(GameObject::STATE::Death);
			return;
		}
		GameObject::Update();
	}
	void Skill::ReInit(Vector2 stPos, Vector2 enPos, Vector2 guideLinePos, SKILL_T _type)
	{
		if (mOwner->GetState() == GameObject::STATE::Invisible) return;
		Scene* scene = SceneManager::GetActiveScene();

		SetEndCoord(enPos);

		SetPos(scene->GetPosTiles()[(int)stPos.y][(int)stPos.x]->GetCenterPos());
		SetStPos(GetPos());
		SetEndPos(scene->GetPosTiles()[(int)enPos.y][(int)enPos.x]->GetCenterPos());
		if (_type != SKILL_T::ARC)
		{
			SetGuideLinePos(scene->GetPosTiles()[(int)guideLinePos.y][(int)guideLinePos.x]->GetCenterPos());
			SetGuideLineCoord(guideLinePos);
		}
	}
	void Skill::Active(HDC hdc)
	{	}
	void Skill::GuideWire(HDC hdc)
	{}
	void Skill::DrawPushTile(ARROW_TILE_T* arrows, int size)
	{
		Scene* scene = SceneManager::GetActiveScene();
		for (int i = 0; i < size; i++)
		{
			int dy = 0;
			int dx = 0;
			if (GetSkillType() == SKILL_T::ARC)
			{
				dy = (int)GetEndCoord().y + (int)ARROW_TILE_DIRECTION[(UINT)arrows[i]].y;
				dx = (int)GetEndCoord().x + (int)ARROW_TILE_DIRECTION[(UINT)arrows[i]].x;

			}
			else
			{
				dy = (int)GetEndCoord().y;
				dx = (int)GetEndCoord().x;
			}
			//if (reverse)
			//{
			//	dy = (int)opEndCoord.y;
			//	dx = (int)opEndCoord.x;
			//}
			//if (GetWeaponType() == WEAPON_T::janus_cannon)
			//{

			//}
			//if (GetSkillType() == SKILL_T::ST)
			//{
			//	
			//}

			if (dx < 0 || dy < 0 || dx > TILE_X - 1 || dy > TILE_Y - 1) continue;

			ARROW_TILE_T _type = arrows[i];
			ARROW_ETC_T _type2;

			//if (scene->GetEffectUnit(dy, dx).size() != 0)
			if (mOwner->GetButtonType() == LAYER_TYPE::MONSTER)
			{
				_type = arrows[i];
				_type2 = ARROW_ETC_T::push_box;
			}
			else
			{
				if (scene->SearchAffectUnit(dy, dx)
					&& !scene->SearchAffectUnit(dy, dx, LAYER_TYPE::STRUCT))
				{
					_type = (ARROW_TILE_T)((UINT)arrows[i] + 4);
					_type2 = ARROW_ETC_T::push_y_box;
				}
				else
				{
					_type = arrows[i];
					_type2 = ARROW_ETC_T::push_box;
				}
			}

			Tile* pushBox = new Tile(Vector2((float)dx, (float)dy));
			pushBox->SetPos(scene->GetPosTiles()[dy][dx]->GetPos());
			pushBox->SetTileTexture(MAKE_TILE_KEY(_type2), MAKE_TILE_PATH(_type2));

			Tile* tile = new Tile(Vector2((float)dx, (float)dy));
			tile->SetPos(scene->GetPosTiles()[dy][dx]->GetPos());

			tile->SetTileTexture(
				MAKE_TILE_KEY(_type)
				, MAKE_TILE_PATH(_type)
				, ARROW_TILE_OFFSET[(UINT)_type]
			);

			scene->GetBackTiles().push_back(tile);
			scene->GetBackTiles().push_back(pushBox);


			scene->AddGameObject(pushBox, LAYER_TYPE::TILE);
			scene->AddGameObject(tile, LAYER_TYPE::TILE);
		}
	}
	void Skill::DrawSkillEffect()
	{
		Scene* scene = SceneManager::GetActiveScene();
		Tile* blow = new Tile(GetEndCoord());
		switch (mOwner->GetWeaponType())
		{
		case WEAPON_T::titan_fist:
		{
			
			blow->SetTileAnimator((DIR_EFFECT_T)(iDir + (int)DIR_EFFECT_T::pun_r));
		}
		break;
		case WEAPON_T::artemis_artillery:
		{
			blow->SetTileAnimator(IMMO_EFFECT_T::ep_ar1);
		}
		break;
		case WEAPON_T::janus_cannon:
		case WEAPON_T::taurus_cannon:
		{
			blow->SetTileAnimator((DIR_EFFECT_T)(iDir + (int)DIR_EFFECT_T::st_r));

		}
		break;
		case WEAPON_T::flame_thrower:
		{
			blow->SetTileAnimator((DIR_EFFECT_T)(iDir + (int)DIR_EFFECT_T::flame1_r));
		}
		break;
		case WEAPON_T::brust_beam:
		{

		}
		break;
		case WEAPON_T::rock_launcher:
		{
			blow->SetTileAnimator(IMMO_EFFECT_T::ep_ar1);
		}
		break;
		case WEAPON_T::stinger:
		{
			blow->SetTileAnimator((DIR_EFFECT_T)(iDir + (int)DIR_EFFECT_T::hornet1_r));
		}
		break;
		case WEAPON_T::accelerating_thorax:
		{
			blow->SetTileAnimator(IMMO_EFFECT_T::ep_firefly1);
		}
		break;
		case WEAPON_T::NONE:
			break;
		case WEAPON_T::END:
			break;
		default:
			break;
		}
		blow->SetPos(scene->GetPosTiles()[(int)GetEndCoord().y][(int)GetEndCoord().x]->GetCenterPos());
		scene->GetBackTiles().push_back(blow);
		scene->AddGameObject(blow, LAYER_TYPE::TILE_HEAD);
	}
	void Skill::PushUnit(ARROW_TILE_T* arrows, int size)
	{
		Scene* scene = SceneManager::GetActiveScene();
		DrawSkillEffect();

		for (int i = 0; i < size; i++)
		{
			int dy = 0;
			int dx = 0;
			if (GetSkillType() == SKILL_T::ARC)
			{
				dy = (int)GetEndCoord().y + (int)ARROW_TILE_DIRECTION[(UINT)arrows[i]].y;
				dx = (int)GetEndCoord().x + (int)ARROW_TILE_DIRECTION[(UINT)arrows[i]].x;
			}
			else
			{
				dy = (int)GetEndCoord().y;
				dx = (int)GetEndCoord().x;
			}
			if (dx < 0 || dy < 0 || dx > TILE_X - 1 || dy > TILE_Y - 1) continue;

			if (GetSkillType() == SKILL_T::ARC)
			{
				Tile* animTile = new Tile(Vector2((float)dx, (float)dy));
				animTile->SetPos(scene->GetPosTiles()[dy][dx]->GetCenterPos());
				animTile->SetTileAnimator((DIR_EFFECT_T)i);
				scene->GetBackTiles().push_back(animTile);
				scene->AddGameObject(animTile, LAYER_TYPE::TILE_HEAD);
			}


			if (!scene->SearchAffectUnit(dy, dx)) continue;
			if (scene->SearchAffectUnit(dy, dx, LAYER_TYPE::STRUCT)) continue;
			if (scene->SearchAffectUnit(dy, dx, LAYER_TYPE::TERRAIN)) continue;

			vector<Unit*> units = scene->GetAffectUnits(dy, dx);

			int _dy = (int)dy + (int)ARROW_TILE_DIRECTION[(UINT)arrows[i]].y;
			int _dx = (int)dx + (int)ARROW_TILE_DIRECTION[(UINT)arrows[i]].x;
			
			if (_dx < 0 || _dy < 0 || _dx > TILE_X - 1 || _dy > TILE_Y - 1) continue;
			if (scene->SearchAffectUnit(_dy, _dx))
			{
				scene->HitAffectUnit(dy, dx, 1);
				scene->HitAffectUnit(_dy, _dx, 1);
			}
			else
			{
				for (int i = 0; i < units.size(); i++)
				{
					if(units[i]->GetState() != GameObject::STATE::Death
						|| units[i]->GetState() != GameObject::STATE::Emerge_loop
						|| units[i]->GetState() != GameObject::STATE::Emerge)
					scene->MoveAffectUnit(units[i], Vector2((float)_dx, (float)_dy), true);
				}
			}
		}
	}
	void Skill::Render(HDC hdc)
	{
		//if (mOwner->GetState() == GameObject::STATE::Invisible) return;
	}
	void Skill::Release()
	{}
}