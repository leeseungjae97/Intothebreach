#pragma once
#include "mGameObject.h"
#include "mScene.h"
#include "mSceneManager.h"
#include "mAnimator.h"
#include "mTransform.h"
#include "mSkill.h"
#include "mTile.h"
#include "CommonInclude.h"
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
		Skill* gameObj = new Skill(mType);
		Scene* scene = SceneManager::GetActiveScene();

		gameObj->Initialize();
		gameObj->SetPos(scene->GetPosTiles()[(int)stPos.y][(int)stPos.x]->GetCenterPos());
		gameObj->SetStPos(gameObj->GetPos());
		gameObj->SetEndPos(scene->GetPosTiles()[(int)edPos.y][(int)edPos.x]->GetCenterPos());
		gameObj->PreCal();
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
	void RotateBitmap(HDC hdc, Vector2 pos, HBITMAP hBitmap, float _theta, HDC sourceDC) {
		BITMAP bmp;
		GetObject(hBitmap, sizeof(bmp), &bmp);
		float angle = _theta * 180.f / PI;

		angle = fmod(angle, 360.0f);
		if (angle < 0) {
			angle += 360.0f;
		}
		_theta = angle * PI / 180.f;

		wchar_t szFloat[500] = {};
		swprintf_s(szFloat, 500, L"angle : %f, theta : %f", _theta * 180.f / PI, _theta);
		size_t iLen = wcsnlen_s(szFloat, 500);
		//left top right bottom
		RECT rt = { 50, 120, 400, 140 };
		DrawText(hdc, szFloat, iLen, &rt, DT_LEFT | DT_WORDBREAK);

		float cos_ang = cos(_theta);
		float sin_ang = sin(_theta);

		float _cos_ang = cos(_theta* -1);
		float _sin_ang = sin(_theta* -1);

		float cx = bmp.bmWidth / 2.0f;
		float cy = bmp.bmHeight / 2.0f;
	

		

		XFORM xform;
		xform.eM11 = cos_ang;
		xform.eM12 = sin_ang;
		xform.eM21 = -sin_ang;
		xform.eM22 = cos_ang;
		//if (_theta < 0) {
		//	xform.eDx = (pos.x - (cos_ang * pos.x)) + (sin_ang * pos.y) - bmp.bmWidth;
		//}else xform.eDx = (pos.x - (cos_ang * pos.x)) + (sin_ang * pos.y) + bmp.bmWidth;
		//xform.eDx = cx - ((cos_ang * cx) - (sin_ang * cy));
		//xform.eDy = cy - ((sin_ang * cx) + (cos_ang * cy));
		xform.eDx = pos.x - cos_ang * pos.x + sin_ang * pos.y + bmp.bmWidth;
		xform.eDy = pos.y - sin_ang * pos.x - cos_ang * pos.y - bmp.bmHeight;


		SetGraphicsMode(hdc, GM_ADVANCED);
		SetWorldTransform(hdc, &xform);
	
		TransparentBlt(hdc,
			(int)(pos.x),
			(int)(pos.y),
			(int)(bmp.bmWidth * 2),
			(int)(bmp.bmHeight * 2),
			sourceDC,
			0, 0,
			bmp.bmWidth, bmp.bmHeight,
			RGB(255, 0, 255));

		xform.eM11 = 1;
		xform.eM12 = 0;
		xform.eM21 = 0;
		xform.eM22 = 1;
		xform.eDx = 0;
		xform.eDy = 0;
		SetWorldTransform(hdc, &xform);		


		float cosine = (float)cos(_theta);
		float sine = (float)sin(_theta);

		// Compute dimensions of the resulting bitmap
		// First get the coordinates of the 3 corners other than origin
		int x1 = (int)(bmp.bmHeight * sine);
		int y1 = (int)(bmp.bmHeight * cosine);
		int x2 = (int)(bmp.bmWidth * cosine + bmp.bmHeight * sine);
		int y2 = (int)(bmp.bmHeight * cosine - bmp.bmWidth * sine);
		int x3 = (int)(bmp.bmWidth * cosine);
		int y3 = (int)(-bmp.bmWidth * sine);

		int minx = min(0, min(x1, min(x2, x3)));
		int miny = min(0, min(y1, min(y2, y3)));
		int maxx = max(0, max(x1, max(x2, x3)));
		int maxy = max(0, max(y1, max(y2, y3)));

		int w = maxx - minx;
		int h = maxy - miny;

	}
}