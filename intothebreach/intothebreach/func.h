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
	static void RotatingImage(Image* image, Image* output, int img_width
		, int img_height, float theta) {
		for (int y = 0; y < img_height; y++) {
			for (int x = img_width - 1; x >= 0; x--) {
				output->SetPixel(img_width - x, y, image->GetPixel(x, y));
				/*float _x = cosf(theta) * x + sinf(theta) * y;
				float _y = -1 * sinf(theta) * x + cosf(theta) * y;
				float pY = abs(_y);*/
				//만약 가져오려는 좌표가 캔버스를 벗어나면, 그냥 검정색으로 처리
				/*if ((pY < img_width && _x < img_height))
					output->SetPixel(x, y, image->GetPixel(_x, pY));*/
				//else
					//output->SetPixel(x, y, Pixel{ 0,0,0,0 }); //0
			}
		}
	}
}