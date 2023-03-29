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
	class Scene : public Entity
	{
	public:
		typedef vector<vector<Tile*>> TILES;
		typedef vector<vector<Building*>> BUILDINGS;
		typedef int(*INT_ARR)[TILE_Y];
		struct Vector2_1
		{
			Vector2 coord;
			int level;
			int parentIdx;
		};
		struct Vector2_2
		{
			Vector2 coord;
			Vector2 pos;
			int mechIdx;
		};
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
		void AddGameObject(GameObject* obj, LAYER_TYPE layer);
		void MakeTile(int iX, int iY, TILE_T _type, TILE_HEAD_T _type2);
		void MakeVariTile(int iX, int iY);
		void HighlightTile();
		void DrawSkillRangeTile();
		void ClearMTiles(TILE_T _type, TILE_HEAD_T _hT);
		void ClearMap();
		void DrawFootTile();
		void CheckNumInput();
		void DrawTile();
		void UndoMove();

		Vector2 GetCoordCenterPos(Vector2 _coord);

		TILES& GetPosTiles() { return mPosTiles; }
		TILES& GetTiles() { return mTiles; }
		TILES& GetArrowTiles() { return mArrowTiles; }
		vector<Tile*>& GetBackTiles() { return mBackTiles; }
		vector<Mech*>& GetMechs() { return mMechs; }
		vector<Alien*>& GetAliens() { return mAliens; }
		vector<Unit*>& GetEffectUnit(int _y, int _x) { return effectUnits[_y][_x]; }

		void DrawMoveRangeTile();
		void DrawMoveDirectionTile();
		void DrawOutLineTile(int _type);
		void CheckMouseOutOfMapRange();
		void RobotDrag();
		void ActiveSkill();
		void ClearSkillRangeMap();
		void MoveEffectUnit(Unit* unit);
		void MoveEffectUnit(Unit* unit, Vector2 _coord);
		//void CheckSkillDirection();

		Mech* GetMouseFollower() { return mMouseFollower; }
		Mech* GetAlphaFollower() { return mAlphaFollower; }

		void SetMouseFollower(Mech* _mM);
		void SetAlphaFollower(Mech* _mM);
		void SetAlphaState(GameObject::STATE state);

	private:
		void SetMap(int y, int x);

	private:
		vector<Layer> mLayers;
		TILES mTiles;				// �⺻ Ÿ��(��)
		TILES mPosTiles;			// Ÿ�� �� Ÿ�� (�̵� �ݰ�, ��ų �ݰ�)
		TILES mPosOutLineTiles;		// Ÿ�� �ܰ��� Ÿ�� Highlight
		TILES mBoundaryTiles;		// Ÿ�� �ݰ� �ܰ��� Ÿ��
		TILES mArrowTiles;			// �ִ� �̵��Ÿ� ǥ�� Ÿ��
		TILES mEffectedTiles;
		TILES mEnemyEmerge;
		vector<Tile*> mBackTiles;			// ��Ÿ Ÿ�ϵ� (�׸��� �ʰ� ������� �뵵�θ� ���)

		vector<Unit*> effectUnits[TILE_Y][TILE_X];

		vector<Vector2_2> moveSave;	//	undoMove�� �Ҷ� �ҷ��� move, attack�� �ʱ�ȭ.

		BUILDINGS mStruturesTiles;

		vector<Vector2_1> pathQueue;
		vector<Mech*> mMechs;
		vector<Alien*> mAliens;

		Mech* mMouseFollower;
		Mech* mAlphaFollower;

		int map[TILE_Y][TILE_X]{};				// �̵� BFS ��
		int skill_range_map[TILE_Y][TILE_X]{};	// ��ų BFS ��
	};
}
