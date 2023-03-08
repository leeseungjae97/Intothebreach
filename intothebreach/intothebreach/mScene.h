#pragma once
#include "mEntity.h"
#include "mLayer.h"

namespace m
{
	class Mech;
	class Alien;
	class Tile;
	class Building;
	class Scene : public Entity
	{
	public:
		typedef vector<vector<Tile*>> TILES;
		typedef vector<vector<Building*>> BUILDINGS;
		typedef int(*INT_ARR)[TILE_Y];
		struct Vector2_1 {
			Vector2 pos;
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

		void AddGameObject(GameObject* obj, LAYER_TYPE layer);
		bool CheckRhombusPos(Tile* tile, Vector2 _pos);
		void MakeTile(int iX, int iY, TILE_T _type, TILE_HEAD_T _type2);
		void MakeVariTile(int iX, int iY);
		void HighlightTile();
		void ClearMTiles(TILE_T _type, TILE_HEAD_T _hT);
		void ClearMap();
		
		TILES GetPosTiles() { return mPosTiles; }
		TILES GetTiles() { return mTiles; }
		vector<Mech*>& GetMechs() { return mMechs; }

		void DrawMoveRangeTile();
		void DrawMoveDirectionTile();
		void CheckMouseOutOfMapRange();
		void RobotDrag();

		Mech* GetMouseFollower() { return mMouseFollower; }
		void SetMouseFollower(Mech* _mM) { mMouseFollower = _mM; }

		//int** GetMap() { return map; }
	private:
		void SetMap(int y, int x);
		
 	private:
		vector<Layer> mLayers;
		TILES mTiles;
		TILES mPosTiles;
		TILES mBoundaryTiles;
		TILES mArrowTiles;
		BUILDINGS mStruturesTiles;
		TILES mEffectedTiles;
		TILES mEnemyEmerge;

		vector<Vector2_1> pathQueue;

		vector<Mech*> mMechs;
		vector<Alien*> mAilens;

		Mech* mMouseFollower;
		int map[TILE_Y][TILE_X]{};
	};
}
