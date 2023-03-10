#pragma once
#include "mGameObject.h"
#include "mScene.h"
#include "mSceneManager.h"
#include "mAnimator.h"
#include "mTransform.h"

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


	static inline Mech* Instantiate(Vector2 pos, LAYER_TYPE type , MECHS mType) {
		Mech* gameObj = new Mech(mType, pos, MECH_MOVE_RANGE[(UINT)mType], MECH_HP[(UINT)mType]);
		Scene* scene = SceneManager::GetActiveScene();

		gameObj->Initialize();
		gameObj->SetPos(scene->GetPosTiles()[(int)pos.y][(int)pos.x]->GetCenterPos());
		gameObj->SetFinalPos(gameObj->GetPos());
		gameObj->GetAnimator()->SetConstant(255);
		gameObj->SetLayerType(type);
		if (type == LAYER_TYPE::CLONE) {
			gameObj->GetAnimator()->SetConstant(100);
			
		}
		if (type == LAYER_TYPE::PLAYER) {
			scene->GetMechs().push_back(gameObj);
		}



		scene->AddGameObject(gameObj, type);
		return gameObj;
	}
	static inline Alien* Instantiate(Vector2 pos, LAYER_TYPE type, ALIENS mType) {
		Alien* gameObj = new Alien(mType, pos, ALIEN_MOVE_RANGE[(UINT)mType], ALIEN_HP[(UINT)mType]);
		Scene* scene = SceneManager::GetActiveScene();

		gameObj->Initialize();
		gameObj->SetPos(scene->GetPosTiles()[(int)pos.y][(int)pos.x]->GetCenterPos());
		gameObj->SetFinalPos(gameObj->GetPos());
		gameObj->GetAnimator()->SetConstant(255);
		gameObj->SetLayerType(type);

		scene->AddGameObject(gameObj, type);
		return gameObj;
	}

	static void Destory(GameObject* obj) {
		obj->SetState(GameObject::STATE::Death);
	}
}