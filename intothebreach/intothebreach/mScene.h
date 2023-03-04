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
		
		TILES GetPosTiles() { return mPosTiles; }
		TILES GetTiles() { return mTiles; }
		vector<Mech*>& GetMechs() { return mMechs; }

 	private:
		vector<Layer> mLayers;
		TILES mTiles;
		TILES mPosTiles;
		vector<Mech*> mMechs;
	};
}
