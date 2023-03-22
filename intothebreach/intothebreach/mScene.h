#pragma once
#include "mEntity.h"
#include "mLayer.h"
#include "Mech.h"
#include "Alien.h"
#include "mUnit.h"
#include "mTile.h"
namespace m
{
	class Unit;
	class Building;
	class Scene : public Entity
	{
	public:
		typedef vector<vector<Tile*>> TILES;
		typedef vector<vector<Building*>> BUILDINGS;
		typedef int(*INT_ARR)[TILE_Y];
		struct Vector2_1 {
			Vector2 coord;
			int level;
			int parentIdx;
		};
		Scene();
		virtual ~Scene();
		
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;

	public:
		void MoveMech();
		void AddGameObject(GameObject* obj, LAYER_TYPE layer);
		void MakeTile(int iX, int iY, TILE_T _type, TILE_HEAD_T _type2);
		void MakeVariTile(int iX, int iY);
		void HighlightTile();
		void DrawSkillRangeTile();
		void ClearMTiles(TILE_T _type, TILE_HEAD_T _hT);
		void ClearMap();
		void DrawFootTile();

		Vector2 GetCoordCenterPos(Vector2 _coord) {
			return mPosTiles[(int)_coord.y][(int)_coord.x]->GetCenterPos();
		}

		TILES GetPosTiles() { return mPosTiles; }
		TILES GetTiles() { return mTiles; }
		vector<Mech*>& GetMechs() { return mMechs; }
		vector<Alien*>& GetAliens() { return mAliens; }


		void DrawMoveRangeTile();
		void DrawMoveDirectionTile();
		void CheckMouseOutOfMapRange();
		void RobotDrag();

		Mech* GetMouseFollower() { return mMouseFollower; }
		Mech* GetAlphaFollower() { return mAlphaFollower; }

		void SetMouseFollower(Mech* _mM) { 
			mMouseFollower = _mM; 
			if(nullptr == _mM) SetAlphaFollower(_mM);
		}
		void SetAlphaFollower(Mech* _mM) {
			if (nullptr != mAlphaFollower) {
				SetAlphaState(GameObject::STATE::Death);
			}
			mAlphaFollower= _mM; 
		}
		void SetAlphaState(GameObject::STATE state) {
			mAlphaFollower->SetState(state);
		}
		

	private:
		void SetMap(int y, int x);
		
 	private:
		vector<Layer> mLayers;
		TILES mTiles;
		TILES mPosTiles;
		TILES mPosOutLineTiles;
		TILES mBoundaryTiles;
		TILES mArrowTiles;
		BUILDINGS mStruturesTiles;
		TILES mEffectedTiles;
		TILES mEnemyEmerge;

		vector<Vector2_1> pathQueue;

		vector<Mech*> mMechs;
		vector<Alien*> mAliens;

		Mech* mMouseFollower;
		Mech* mAlphaFollower;

		bool isAttack;
		int index;
		int finalIndex;
		int map[TILE_Y][TILE_X]{};
		int skill_range_map[TILE_Y][TILE_X]{};
	};
}
