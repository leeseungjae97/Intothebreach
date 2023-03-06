#pragma once
#include "mEntity.h"
#include "mLayer.h"

namespace m
{

	class Mech;
	class Tile;
	class Scene : public Entity
	{
	public:
		typedef vector<vector<Tile*>> TILES;
		typedef int(*INT_ARR)[TILE_Y];
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
		void HighlightTile();
		void ClearMTiles(TILE_T _type, TILE_HEAD_T _hT);
		void ClearMap();
		
		TILES GetPosTiles() { return mPosTiles; }
		TILES GetTiles() { return mTiles; }
		vector<Mech*>& GetMechs() { return mMechs; }

		Mech* GetMouseFollower() { return mMouseFollower; }
		void SetMouseFollower(Mech* _mM) { mMouseFollower = _mM; }

		int** GetMap() { return map; }
		void SetMap(int y, int x) {
			map = new int* [y];
			for (int i = 0; i < y; i++) {
				map[i] = new int[x];
			}
		}
		void DrawMoveRangeTile();
		void DrawMoveDirectionTile();
		void CheckMouseOutOfMapRange();
		void RobotDrag();

 	private:
		vector<Layer> mLayers;
		TILES mTiles;
		TILES mPosTiles;
		TILES mBoundaryTiles;
		TILES mArrowTiles;
		vector<Mech*> mMechs;
		
		Mech* mMouseFollower;
		int **map;
	};
}
