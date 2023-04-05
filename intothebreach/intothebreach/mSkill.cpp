#include "mSkill.h"
#include "mSelectGDI.h"
#include "mTime.h"
#include "mTransform.h"
#include "mAnimator.h"
#include "func.h"
#include "mApplication.h"
#include "mImage.h"
#include "mResources.h"
#include "mSceneManager.h"
extern m::Application application;
namespace m {
	Skill::Skill(SKILL_T _type, Unit* onwer)
		: mType(_type) 
		, mOnwer(onwer)
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
		, Missile_vec(Vector2::One)
		, endCoord(Vector2::One)
		, mStPos(Vector2::Zero)
		, mFinalEdPos(Vector2::One)
	{
		AddComponent(new Transform);
		AddComponent(new Animator);
	}
	Skill::Skill(Skill& _origin) 
		: mType(_origin.mType)
		, mLayerType(LAYER_TYPE::SKILL)
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
	{
	}
	Skill::~Skill() {
	}
	void Skill::Initialize() {
	}
	void Skill::CalEndFire() {
		Vector2 vec = GetPos();
		float absD = abs(mFinalEdPos.x - mStPos.x);
		float absMD = abs(vec.x - mStPos.x);
		float diff = absD - absMD;

		if (mStPos == Vector2::Zero || mFinalEdPos == Vector2::One) endFire = false;
		else diff <= 0.f ? endFire = true : endFire = false;
	}
	void Skill::CheckDirection()
	{
	}
	void Skill::ClearPushTile()
	{
		Scene* scene = SceneManager::GetActiveScene();
		//if (scene->GetBackTiles().size() == 0) return;
		for (int i = 0; i < scene->GetBackTiles().size(); i++)
		{
			scene->GetBackTiles()[i]->SetState(GameObject::STATE::Delete);
		}

		scene->GetBackTiles().clear();
	}
	bool Skill::CheckSkillFiring()
	{
		if (endFire && startFire) return false;
		if (!endFire && !startFire) return false;
		if (!endFire && startFire)
		{
			ClearPushTile();
			return true;
		}
		return false;
	}

	void Skill::Update() {
		GameObject::Update();
		CheckSkillFiring();
	}
	void Skill::ReInit(Vector2 stPos, Vector2 enPos, Vector2 guideLinePos, SKILL_T _type)
	{
		Scene* scene = SceneManager::GetActiveScene();

		SetEndCoord(enPos);

		SetPos(scene->GetPosTiles()[(int)stPos.y][(int)stPos.x]->GetCenterPos());
		SetStPos(GetPos());
		SetEndPos(scene->GetPosTiles()[(int)enPos.y][(int)enPos.x]->GetCenterPos());
		if (_type == SKILL_T::ST)
		{
			SetGuideLinePos(scene->GetPosTiles()[(int)guideLinePos.y][(int)guideLinePos.x]->GetPos());
			SetGuideLineCoord(guideLinePos);
		}
	}
	void Skill::Active(HDC hdc)
	{
	}
	void Skill::GuideWire(HDC hdc)
	{
	}
	void Skill::DrawPushTile(int (*direct)[2], int size)
	{
		Scene* scene = SceneManager::GetActiveScene();

		ClearPushTile();
		// right, up, down, left
		for (int i = 0; i < size; i++)
		{
			int dy = (int)GetEndCoord().y + direct[i][0];
			int dx = (int)GetEndCoord().x + direct[i][1];
			if (dx < 0 || dy < 0 || dx > TILE_X - 1 || dy > TILE_Y - 1) continue;

			ARROW_TILE_T _type = ARROW_TILE_T::arrow_down;
			
			if (scene->GetEffectUnit(dy, dx).size() != 0)
				_type = (ARROW_TILE_T)(i + 4);
			else
				_type = (ARROW_TILE_T)(i);

			Tile* tile = new Tile(Vector2((float)dx, (float)dy));
			tile->SetPos(scene->GetPosTiles()[dy][dx]->GetCenterPos());

			tile->SetTileTexture(
				MAKE_ARROW_TILE_KEY(_type)
				, MAKE_ARROW_TILE_PATH(_type)
			);
			scene->GetBackTiles().push_back(tile);
			scene->AddGameObject(tile, LAYER_TYPE::TILE);
		}
	}
	void Skill::PushUnit(int (*direct)[2], int size)
	{
		Scene* scene = SceneManager::GetActiveScene();
		for (int i = 0; i < size; i++)
		{
			int dy = (int)GetEndCoord().y + direct[i][0];
			int dx = (int)GetEndCoord().x + direct[i][1];

			if (dx < 0 || dy < 0 || dx > TILE_X - 1 || dy > TILE_Y - 1) continue;
			if (scene->GetEffectUnit(dy, dx).size() == 0)continue;
			for (int _i = 0; _i < scene->GetEffectUnit(dy, dx).size(); _i++)
			{
				Unit* unit = scene->GetEffectUnit(dy, dx)[_i];
				int _dy = (int)dy + direct[i][0];
				int _dx = (int)dx + direct[i][1];
				if (_dx < 0 || _dy < 0 || _dx > TILE_X - 1 || _dy > TILE_Y - 1) continue;
				scene->MoveEffectUnit(unit, Vector2((float)_dx, (float)_dy));
			}
		}
	}
	void Skill::Render(HDC hdc) {

	}
	void Skill::Release() {
	}
}