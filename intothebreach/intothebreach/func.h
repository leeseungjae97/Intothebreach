#pragma once
#include "mGameObject.h"
#include "mScene.h"
#include "mSceneManager.h"
#include "mAnimator.h"
#include "mTransform.h"
#include "mSkill.h"
#include "mSkill_Arc.h"
#include "mSkill_St.h"
#include "mSkill_RS.h"
#include "mTile.h"
#include "CommonInclude.h"
namespace m::object
{
	template <typename T>
	static inline T* Instantiate(LAYER_TYPE type)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(gameObj, type);
		gameObj->Initialize();
		return gameObj;
	}

	template <typename T>
	static inline T* Instantiate(Vector2 pos, LAYER_TYPE type)
	{

		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(gameObj, type);
		gameObj->Initialize();
		gameObj->SetPos(pos);
		return gameObj;
	}

	
	static inline Unit* Instantiate(Vector2 coord, LAYER_TYPE type, int unitName)
	{
		Scene* scene = SceneManager::GetActiveScene();
		Unit* gameObj = nullptr;

		if (type == LAYER_TYPE::PLAYER)
		{
			gameObj = new Mech(unitName, coord
				, MECH_MOVE_RANGE[(UINT)unitName]
				, MECH_HP[(UINT)unitName]
				, scene->GetMechs().size());

			scene->GetMechs().push_back((Mech*)gameObj);
			//gameObj->SetMIdx(scene->GetMechs().size() - 1);
			gameObj->SetMove(true);
		}
		if(type == LAYER_TYPE::MONSTER)
		{
			gameObj = new Alien(GET_UNIT_NUM(unitName), coord, scene->GetAliens().size());
			scene->GetAliens().push_back((Alien*)gameObj);
		}
		if (type == LAYER_TYPE::CLONE)
		{
			gameObj = new Mech(unitName, coord
				, MECH_MOVE_RANGE[(UINT)unitName]
				, MECH_HP[(UINT)unitName]
				, scene->GetMechs().size());

			gameObj->SetState(GameObject::STATE::Invisible);
			gameObj->GetAnimator()->SetConstant(100);
		}

		gameObj->Initialize();
		gameObj->SetPos(scene->GetPosTiles()[(int)coord.y][(int)coord.x]->GetCenterPos());
		gameObj->SetFinalPos(gameObj->GetPos());
		gameObj->SetLayerType(type);

		assert(gameObj);

		scene->AddGameObject(gameObj, type);
		return gameObj;
	}
	static inline Building* Instantiate(Vector2 coord, LAYER_TYPE type, STRUCTURES _sType)
	{
		Scene* scene = SceneManager::GetActiveScene();
		Building* gameObj = new Building(_sType, coord, scene->GetStructuresTiles().size());

		gameObj->Initialize();
		gameObj->SetPos(scene->GetPosTiles()[(int)coord.y][(int)coord.x]->GetCenterPos());
		gameObj->SetFinalPos(gameObj->GetPos());
		gameObj->GetAnimator()->SetConstant(255);
		gameObj->SetLayerType(type);

		scene->GetStructuresTiles().push_back(gameObj);

		scene->AddGameObject(gameObj, type);
		return gameObj;
	}
	//static inline Alien* Instantiate(Vector2 coord, LAYER_TYPE type, int unitName)
	//{
	//	Scene* scene = SceneManager::GetActiveScene();
	//	Alien* gameObj = new Alien(unitName, coord, scene->GetAliens().size());

	//	gameObj->Initialize();
	//	gameObj->SetPos(scene->GetPosTiles()[(int)coord.y][(int)coord.x]->GetCenterPos());
	//	gameObj->SetFinalPos(gameObj->GetPos());
	//	gameObj->GetAnimator()->SetConstant(255);
	//	gameObj->SetLayerType(type);

	//	scene->GetAliens().push_back(gameObj);

	//	scene->AddGameObject(gameObj, type);
	//	return gameObj;
	//}

	static inline Skill* Instantiate(Vector2 stPos, Vector2 edPos, LAYER_TYPE type, SKILL_T _type, Unit* unit)
	{
		Scene* scene = SceneManager::GetActiveScene();
		Skill* gameObj = new Skill(_type, unit);


		gameObj->Initialize();
		gameObj->SetLayerType(type);
		gameObj->SetEndCoord(edPos);

		gameObj->SetPos(scene->GetPosTiles()[(int)stPos.y][(int)stPos.x]->GetCenterPos());
		gameObj->SetStPos(gameObj->GetPos());
		gameObj->SetEndPos(scene->GetPosTiles()[(int)edPos.y][(int)edPos.x]->GetCenterPos());
		//gameObj->PreCal();

		scene->AddGameObject(gameObj, type);
		return gameObj;
	}


	static inline Skill* Instantiate(vector<Skill*>& vS, SKILL_T _type, Unit* unit)
	{
		Skill* gameObj = nullptr;

		switch (_type)
		{
		case SKILL_T::ARC:
		{
			gameObj = new Skill_Arc(_type, unit);
		}
			break;
		case SKILL_T::ST:
		{
			gameObj = new Skill_St(_type, unit);
		}
			break;
		case SKILL_T::RANGE_ST:
		{
			gameObj = new Skill_RS(_type, unit);
		}
			break;
		case SKILL_T::END:
			break;
		default:
			break;
		}
		//if (unit->GetLayerType() == LAYER_TYPE::PLAYER)
		//	
		//else 
		//	gameObj->SetWeaponType(BASIC_A_WEAPON_TYPE[(UINT)_type]);

		gameObj->SetWeaponType(BASIC_WEAPON_TYPE[(UINT)_type]);

		Scene* scene = SceneManager::GetActiveScene();

		vS.push_back(gameObj);
		scene->AddGameObject(gameObj, LAYER_TYPE::SKILL);

		return gameObj;
	}
	static inline void Instantiate(vector<Skill*>& vS, SKILL_T _type, int idx)
	{
		Skill* gameObj = vS[idx];
	}
	template <typename T>
	static inline void DestoryUnitVector(vector<T>& _vec)
	{
		for (size_t i = 0; i < _vec.size(); i++)
		{
			if (nullptr != _vec[i]) _vec[i]->SetState(GameObject::STATE::Delete);
		}
		_vec.clear();
	}
	static void Destory(GameObject* obj)
	{
		obj->SetState(GameObject::STATE::Death);
	}
	static void Visible(GameObject* obj)
	{
		obj->SetState(GameObject::STATE::Visibie);
	}
	static void Invisible(GameObject* obj)
	{
		obj->SetState(GameObject::STATE::Invisible);
	}
	static void DrawText(wstring ar ...)
	{
		/*	wchar_t szFloat[50] = {};
			swprintf_s(szFloat, 50, L"degree : %f", _theta * 180 / PI);
			size_t iLen = wcsnlen_s(szFloat, 50);
			RECT rt = { 50, 100, 150, 150 };
			DrawText(hdc, szFloat, iLen, &rt, DT_CENTER | DT_WORDBREAK);*/
	}

}
namespace m::bitmap
{
	void RotateBitmap(HDC hdc, Vector2 pos, HBITMAP hBitmap, float _theta, HDC sourceDC)
	{
		BITMAP bmp;
		GetObject(hBitmap, sizeof(bmp), &bmp);
		float angle = _theta * 180.f / PI;

		angle = fmod(angle, 360.0f);
		if (angle < 0)
		{
			angle += 360.0f;
		}
		_theta = angle * PI / 180.f;

		//wchar_t szFloat[500] = {};
		//swprintf_s(szFloat, 500, L"angle : %f, theta : %f", _theta * 180.f / PI, _theta);
		//size_t iLen = wcsnlen_s(szFloat, 500);
		////left top right bottom
		//RECT rt = { 50, 120, 400, 140 };
		//DrawText(hdc, szFloat, iLen, &rt, DT_LEFT | DT_WORDBREAK);

		float cos_ang = cos(_theta);
		float sin_ang = sin(_theta);

		float cx = bmp.bmWidth / 2.0f;
		float cy = bmp.bmHeight / 2.0f;

		XFORM xform;
		xform.eM11 = cos_ang;
		xform.eM12 = sin_ang;
		xform.eM21 = -sin_ang;
		xform.eM22 = cos_ang;
		xform.eDx = pos.x - cos_ang * pos.x + sin_ang * pos.y;
		xform.eDy = pos.y - sin_ang * pos.x - cos_ang * pos.y;
		//xform.eDx = 0;
		//xform.eDy = 0;



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
	}
}