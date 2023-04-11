#pragma once
#include "mGameObject.h"
namespace m
{
	class Weapon;
	class Image;
	class Pilot;
	class Skill;
	class Animator;
	class Unit :
		public GameObject
	{
	public:
		Unit(Vector2 _coord, int _range, int hp, int type, size_t idx, int unitValue);
		Unit(Unit& _origin);
		Unit(Vector2 _coord);
		Unit();
		~Unit();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
		virtual void ActiveSkill(Vector2 otherPos);

		void SetSkill();
		void SetSkill(int type);
		void SetSkill(int idx, SKILL_T type);

		void ChangePilotSlot();
		Weapon* ChangeWeaponSlot(int index);
		Skill* GetSkill(int idx);

		void SetCoord(Vector2 _coord) { mCoord = _coord; }
		void SetFinalPos(Vector2 _pos) { mFinalPos = _pos; }
		void SetFinalCoord(Vector2 _coord) { mFinalCoord = _coord; }
		void SetCurAttackSkill();
		void SetCurImage(Image* m) { curImage = m; }
		void SetLayerType(LAYER_TYPE _type) { lType = _type; }
		void SetUnitCoord(Vector2 _coord) { unitCoord = _coord; }
		void SetMIdx(int _idx) { mIdx = _idx; }
		void SetMoveRange(int _move) { moveRange = _move; }
		void SetSkillIdx(int _idx);
		void SetMove(bool _move) { move = _move; }
		void SetEndMove(bool _endMove) { endMove = _endMove; }
		void SetEndAttack(bool _endAttack) { endAttack = _endAttack; }

		void SetWeaponType(WEAPON_T _type) { mWeaponType = _type; }
		void ClearSkillRangeMap();
		void DrawOutLineTile(int _type);
		void DrawSkillRangeTile();
		
		void DrawMoveRangeTile();
		void DrawMoveDirectionTile();

		void Hit(int damage)
		{
			if (curHp < damage) curHp = 0;
			else curHp -= damage;
		}
		void Repair(int repair)
		{
			if (curHp + repair < mHp) curHp = mHp;
			else curHp += repair;
		}
		

		void SetStructure(bool _b) { bStructure = _b; }
		void DrawSkill(Vector2 pos, Vector2 guideLinePos);
		void SetHp(int _hp) { mHp = curHp = _hp; }

		Vector2 GetUnitIdx() { return unitCoord; }
		size_t GetMIdx() { return mIdx; }
		WEAPON_T GetWeaponType() { return mWeaponType; }
		int GetFullHp() { return mHp; }
		int GetCurHp() { return curHp; }

		int GetSkillIdx() { return skillIdx; }
		int GetMoveRange() { return moveRange; }
		int GetUnitName() { 
			if ((int)MECHS::tele < unitName) return unitName - (int)MECHS::tele - 1;
			return unitName; 
		}
		bool CheckSkillFiring();
		bool GetMove() { return move; }
		bool GetEndMove() { return endMove; }
		bool GetEndAttack() { return endAttack; }
		
		int GetSkillMap(int y, int x) { return skill_range_map[y][x]; }
		void SetSkillMap(int y, int x, int num) { skill_range_map[y][x] = num; }

		void ClearSearchMap();

		vector<Image*>& GetMImages() { return mImages; }
		Animator* GetAnimator() { return mAnimator; }

		Image* GetCurImage() { return curImage; }

		LAYER_TYPE GetLayerType() { return lType; }

		Skill* GetCurAttackSkill() { return curAttactSkill; }
		Vector2 GetFinalPos()
		{
			return mFinalPos;
		}
		Vector2 GetCoord()
		{
			return mCoord;
		}
		Vector2 GetFinalCoord()
		{
			return mFinalCoord;
		}
		virtual void idle() = 0;
		virtual void broken() = 0;
		virtual void water() = 0;
		virtual void emerge() = 0;

	protected:
		vector<Vector2_1> pathQueue;
		vector<Skill*> mSkills;
		Skill* curAttactSkill;
		vector<Image*> mImages; // 전체 이미지
		float moveDelay;
		int skill_range_map[TILE_Y][TILE_X]{};	// 스킬 BFS 맵
		int searchMap[TILE_Y][TILE_X];
	private:
		Animator* mAnimator;
		Image* curImage;
		Image* hpImage;
		Image* hpBack;
		vector<Image*> hpBar;
		LAYER_TYPE lType;

		Vector2 mCoord;

		Vector2 mFinalCoord;
		Vector2 mFinalPos;

		int mHp;			// 전체 hp
		int curHp;			// 현재 hp
		int moveRange;		// 로봇 타입의 enum으로 가져온 이동거리
		Vector2 unitCoord;		// effecUnit vector에 들어갈 Vector
		size_t mIdx;		// Scene의 Mechs vector에 들어갈 index
		int skillIdx;		// 사용할 스킬 index
		int unitName;

		bool drag;			//
		bool endMove;		//
		bool endAttack;		// 공격을 마치면
		bool move;			// 공격에서 이동으로 넘갈때 사용.
							// 이 값을 통해 공격과 이동의 분기가 나뉨.
		bool bStructure;

		WEAPON_T mWeaponType;
		Pilot* mPilot;		// 미사용
		//vector<SKILL_T> mSkills;
	};
}


