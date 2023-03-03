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
		void MakeTile(int iX, int iY);
		vector<Tile*>& GetPosTiles() { return mPosTiles; }
		vector<Tile*>& GetTiles() { return mTiles; }

 	private:
		vector<Layer> mLayers;
		vector<Tile*> mTiles;
		vector<Tile*> mPosTiles;
		vector<Mech*> mMechs;
	};
}
