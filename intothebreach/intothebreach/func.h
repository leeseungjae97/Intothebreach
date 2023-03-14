#pragma once
#include "mGameObject.h"
#include "mScene.h"
#include "mSceneManager.h"
#include "mAnimator.h"
#include "mTransform.h"
#include "mSkill.h"
#include "mTile.h"

namespace m::object {
	template <typename T>
	static inline T* Instantiate(LAYER_TYPE type) {
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(gameObj, type);
		gameObj->Initialize();
		return gameObj;
	}

	template <typename T>
	static inline T* Instantiate(Vector2 pos, LAYER_TYPE type) {
		
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(gameObj, type);
		gameObj->Initialize();
		gameObj->SetPos(pos);
		return gameObj;
	}


	static inline Mech* Instantiate(Vector2 coord, LAYER_TYPE type , MECHS mType) {
		Mech* gameObj = new Mech(mType, coord, MECH_MOVE_RANGE[(UINT)mType], MECH_HP[(UINT)mType]);
		Scene* scene = SceneManager::GetActiveScene();

		gameObj->Initialize();
		gameObj->SetPos(scene->GetPosTiles()[(int)coord.y][(int)coord.x]->GetCenterPos());
		gameObj->SetFinalPos(gameObj->GetPos());
		gameObj->GetAnimator()->SetConstant(255);
		gameObj->SetLayerType(type);
		if (type == LAYER_TYPE::CLONE) {
			gameObj->SetState(GameObject::STATE::Death);
			gameObj->GetAnimator()->SetConstant(100);
			
		}
		if (type == LAYER_TYPE::PLAYER) {
			scene->GetMechs().push_back(gameObj);	
		}



		scene->AddGameObject(gameObj, type);
		return gameObj;
	}
	static inline Alien* Instantiate(Vector2 coord, LAYER_TYPE type, ALIENS mType) {
		Alien* gameObj = new Alien(mType, coord, ALIEN_MOVE_RANGE[(UINT)mType], ALIEN_HP[(UINT)mType]);
		Scene* scene = SceneManager::GetActiveScene();

		gameObj->Initialize();
		gameObj->SetPos(scene->GetPosTiles()[(int)coord.y][(int)coord.x]->GetCenterPos());
		gameObj->SetFinalPos(gameObj->GetPos());
		gameObj->GetAnimator()->SetConstant(255);
		gameObj->SetLayerType(type);

		scene->GetAliens().push_back(gameObj);

		scene->AddGameObject(gameObj, type);
		return gameObj;
	}

	static inline Skill* Instantiate(Vector2 stPos, Vector2 edPos, LAYER_TYPE type, SKILL_T mType) {
		//Vector2 stP = scene->GetPosTiles()[(int)stPos.y][(int)stPos.x]->GetCenterPos();
		//Vector2 enP = scene->GetPosTiles()[(int)edPos.y][(int)edPos.x]->GetCenterPos();
		//Skill* gameObj = new Skill(stP, enP, mType);
		Skill* gameObj = new Skill(mType);
		Scene* scene = SceneManager::GetActiveScene();

		gameObj->Initialize();
		gameObj->SetPos(scene->GetPosTiles()[(int)stPos.y][(int)stPos.x]->GetCenterPos());
		gameObj->SetStPos(gameObj->GetPos());
		gameObj->SetEndPos(scene->GetPosTiles()[(int)edPos.y][(int)edPos.x]->GetCenterPos());
		//if (mType == SKILL_T::ARC) gameObj->PreCal();
		gameObj->SetLayerType(type);
		gameObj->SetSkillType(mType);

		scene->AddGameObject(gameObj, type);
		return gameObj;
	}


	static void Destory(GameObject* obj) {
		obj->SetState(GameObject::STATE::Death);
	}

	
}
namespace m::bitmap {
	static void RotatingImage(RECT* image, RECT*,
		float angle) {
		float sina = sinf(angle);
		float cosa = cosf(angle);
		
		float xc = (image->left + image->right )* 0.5;
		float yc = (image->top + image->bottom) * 0.5;

		float w2 = image->right - xc;
		float h2 = image->bottom - yc;
	}
}