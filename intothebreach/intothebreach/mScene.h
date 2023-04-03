#pragma once
#include "mEntity.h"
namespace m
{
	class Unit;
	class Alien;
	class Mech;
	class Layer;
	class Tile;
	class Building;
	class Background;
	class Scene : public Entity
	{
	public:
		typedef vector<vector<Tile*>> TILES;
		typedef vector<vector<Building*>> BUILDINGS;
		typedef int(*INT_ARR)[TILE_Y];
	
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
		virtual void Destroy();

		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;

	public:
		void MoveSkill();
		void MoveMech();

		void AlienAlgorithm();

		void AddGameObject(GameObject* obj, LAYER_TYPE layer);
		void MakeTile(int iX, int iY, TILE_T _type, TILE_HEAD_T _type2);
		void MakeVariTile(int iX, int iY);
		void HighlightTile();
		void ClearMTiles(TILE_T _type, TILE_HEAD_T _hT);
		void ClearMap();
		void DrawFootTile();
		void CheckNumInput();
		
		void UndoMove();

		TILES& GetPosTiles() { return mPosTiles; }
		Tile* GetPosTile(int y, int x) { return mPosTiles[y][x]; };
		TILES& GetTiles() { return mTiles; }
		TILES& GetArrowTiles() { return mArrowTiles; }
		TILES& GetBoundaryTiles() { return mBoundaryTiles; }
		vector<Tile*>& GetBackTiles() { return mBackTiles; }
		vector<Mech*>& GetMechs() { return mMechs; }
		vector<Alien*>& GetAliens() { return mAliens; }
		vector<Unit*>& GetEffectUnit(int y, int x) { return effectUnits[y][x]; }

		void CheckMouseOutOfMapRange();
		void SetPosTiles(int _y, int _x, TILE_T _type1, MOVE_TILE_T _type2);
		void SetArrowTiles(int _y, int _x, MOVE_ARROW_T _type);
		void RobotDrag();
		void MoveEffectUnit(Unit* unit);
		void MoveEffectUnit(Unit* unit, Vector2 _coord);
		void SetBoundaryTiles(int y, int x, MOVE_TILE_T _type);


		bool GetPlayerTurn() { return playerTurn; }
		bool GetFirstUpdate() { return firstUpdate; }
		Mech* GetMouseFollower() { return mMouseFollower; }
		Mech* GetAlphaFollower() { return mAlphaFollower; }

		void SetMouseFollower(Mech* _mM);
		void SetAlphaFollower(Mech* _mM);
		void SetAlphaState(GameObject::STATE state);
		void SetPlayerTurn(bool _playerTurn) { playerTurn = _playerTurn; }
		void SetFirstUpdate(bool _isFirstUpdate) { firstUpdate = _isFirstUpdate; }

		int GetMap(int y, int x) { return map[y][x]; }
		void SetMap(int y, int x, int value) { map[y][x] = value; }
		void SetMap();
	private:
		void drawTile();

	protected:
		vector<Background*> mBacks;

	private:
		vector<Layer> mLayers;
		
		bool firstUpdate;


		TILES mTiles;				// 기본 타일(땅)
		TILES mPosTiles;			// 타일 위 타일 (이동 반경, 스킬 반경)
		TILES mPosOutLineTiles;		// 타일 외곽선 타일 Highlight
		TILES mBoundaryTiles;		// 타일 반경 외곽선 타일
		TILES mArrowTiles;			// 최단 이동거리 표시 타일
		TILES mEffectedTiles;
		TILES mEnemyEmerge;
		vector<Tile*> mBackTiles;			// 기타 타일들 (그리지 않고 저장공간 용도로만 사용)

		vector<Unit*> effectUnits[TILE_Y][TILE_X];

		vector<Vector2_2> moveSave;	//	undoMove를 할때 불러올 move, attack시 초기화.

		BUILDINGS mStruturesTiles;

		vector<Mech*> mMechs;
		vector<Alien*> mAliens;

		Mech* mMouseFollower;
		Mech* mAlphaFollower;

		bool playerTurn;
		int curAttackAlien;
		int map[TILE_Y][TILE_X]{};				// 이동 BFS 맵
	};
}
