#pragma once
#include "mGameObject.h"
#include "mScene.h"
#include "mSceneManager.h"
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
		Mech* gameObj = new Mech(mType, pos, MECH_MOVE_RANGE[(UINT)mType]);
		Scene* scene = SceneManager::GetActiveScene();

		gameObj->Initialize();
		gameObj->SetPos(scene->GetPosTiles()[(int)pos.y][(int)pos.x]->GetCenterPos());
		gameObj->SetFinalPos(gameObj->GetPos());
		if(type != LAYER_TYPE::PLAYER_CLONE) 
			scene->GetMechs().push_back(gameObj);

		scene->AddGameObject(gameObj, type);
		return gameObj;
	}


	static void Destory(GameObject* obj) {
		obj->SetState(GameObject::STATE::Death);
	}
}