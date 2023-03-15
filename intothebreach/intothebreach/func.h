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
	static void DrawText(wstring ar ...) {
	/*	wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"degree : %f", _theta * 180 / PI);
		size_t iLen = wcsnlen_s(szFloat, 50);
		RECT rt = { 50, 100, 150, 150 };
		DrawText(hdc, szFloat, iLen, &rt, DT_CENTER | DT_WORDBREAK);*/
	}
	
}
namespace m::bitmap {
	void RotateBitmap(HDC hdc, Vector2 pos, HBITMAP hBitmap
		, int iw, int he, float angle, HDC sourceDC) {
		// Get the dimensions of the bitmap
		BITMAP bmp;
		GetObject(hBitmap, sizeof(BITMAP), &bmp);

		//float rad = angle * PI / 180;

		float centerX = 300;
		float centerY = 300;

		XFORM xform;
		//xform.eM11 = (FLOAT)0.8660;
		//xform.eM12 = (FLOAT)0.5000;
		//xform.eM21 = (FLOAT)-0.5000;
		//xform.eM22 = (FLOAT)0.8660;

		xform.eM11 = cos(angle);
		xform.eM12 = sin(angle);
		xform.eM21 = -sin(angle);
		xform.eM22 = cos(angle);
		float cos_ang = cos(angle);
		float sin_ang = sin(angle);
		xform.eDx = (pos.x - (cos_ang * pos.x) )+ (sin_ang * pos.y);
		xform.eDy = (pos.y - (sin_ang * pos.x) )- (cos_ang * pos.y);

		SetGraphicsMode(hdc, GM_ADVANCED);
		SetWorldTransform(hdc, &xform);

		//StretchBlt(hdc, 0, 0, bmp.bmWidth, bmp.bmHeight,
		//	sourceDC, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
		//StretchBlt(hdc, 0, 0, bmp.bmWidth, bmp.bmHeight,
		//	sourceDC, 0,0,bmp.bmWidth, bmp.bmHeight, SRCCOPY);
		/*BitBlt(hdc, 0, 0, bmp.bmWidth, bmp.bmHeight,
			sourceDC, bmp.bmWidth, bmp.bmHeight, SRCCOPY);*/

		TransparentBlt(hdc,
			(int)(pos.x),
			(int)(pos.y),
			(int)(iw * 2),
			(int)(he * 2),
			sourceDC,
			0, 0,
			iw, he,
			RGB(255, 0, 255));

		xform.eM11 = 1;
		xform.eM12 = 0;
		xform.eM21 = 0;
		xform.eM22 = 1;
		xform.eDx = 0;
		xform.eDy = 0;
		SetWorldTransform(hdc, &xform);		
	}
}