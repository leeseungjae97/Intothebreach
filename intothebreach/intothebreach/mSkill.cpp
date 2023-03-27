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
	Skill::Skill(SKILL_T _type)
		: mType(_type) 
		, mLayerType(LAYER_TYPE::SKILL)
		, endFire(false)
		, stFire(false)
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
		, stFire(false)
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
		object::Visible(this);
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
	void Skill::Update() {
		GameObject::Update();
		
	}
	void Skill::ReInit(Vector2 stPos, Vector2 enPos)
	{
		Scene* scene = SceneManager::GetActiveScene();

		SetEndCoord(enPos);

		SetPos(scene->GetPosTiles()[(int)stPos.y][(int)stPos.x]->GetCenterPos());
		SetStPos(GetPos());
		SetEndPos(scene->GetPosTiles()[(int)enPos.y][(int)enPos.x]->GetCenterPos());
		this->Initialize();
	}
	void Skill::Active(HDC hdc)
	{
	}
	void Skill::GuideWire(HDC hdc)
	{
	}
	void Skill::Render(HDC hdc) {

	}
	void Skill::Release() {
	}
}