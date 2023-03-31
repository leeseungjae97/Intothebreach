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
		Unit(Vector2 _coord, int _range, int hp, int type);
		Unit(Unit& _origin);
		Unit();
		~Unit();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetSkill();
		void SetSkill(int type);
		void SetSkill(int idx, SKILL_T type);

		//SKILL_T GetSkill(int idx);
		Skill* GetSkill(int idx);

		void ChangePilotSlot();
		Weapon* ChangeWeaponSlot(int index);

		void SetCoord(Vector2 _coord) { mCoord = _coord; }
		void SetFinalPos(Vector2 _pos) { mFinalPos = _pos; }
		void SetFinalCoord(Vector2 _coord) { mFinalCoord = _coord; }
		void SetCurAttackSkill();
		void SetCurImage(Image* m) { curImage = m; }
		void SetLayerType(LAYER_TYPE _type) { lType = _type; }
		void SetUnitIdx(int _idx) { unitIdx = _idx; }
		void SetMechIdx(int _idx) { mechIdx = _idx; }
		void SetMoveRange(int _move) { moveRange = _move; }
		void SetSkillIdx(int _idx);
		void SetMove(bool _move) { move = _move; }
		void SetEndMove(bool _endMove) { endMove = _endMove; }
		void SetEndAttack(bool _endAttack) { endAttack = _endAttack; }

		void ClearSkillRangeMap();
		void DrawOutLineTile(int _type);
		void DrawSkillRangeTile();
		void ActiveSkill();
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
		void DrawSkill(Vector2 pos);
		void SetHp(int _hp) { mHp = curHp = _hp; }
		int GetFullHp() { return mHp; }
		int GetCurHp() { return curHp; }
		int GetUnitIdx() { return unitIdx; }
		int GetMechIdx() { return mechIdx; }
		int GetSkillIdx() { return skillIdx; }
		int GetMoveRange() { return moveRange; }
		bool CheckSkillFiring();
		bool GetMove() { return move; }
		bool GetEndMove() { return endMove; }
		bool GetEndAttack() { return endAttack; }
		
		int GetSkillMap(int y, int x) { return skill_range_map[y][x]; }
		void SetSkillMap(int y, int x, int num) { skill_range_map[y][x] = num; }

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

		int mHp;			// ��ü hp
		int curHp;			// ���� hp
		int moveRange;		// �κ� Ÿ���� enum���� ������ �̵��Ÿ�
		int unitIdx;		// effecUnit vector�� �� index
		int mechIdx;		// Scene�� Mechs vector�� �� index
		int skillIdx;		// ����� ��ų index

		bool drag;			//
		bool endMove;		//
		bool endAttack;		// ������ ��ġ��
		bool move;			// ���ݿ��� �̵����� �Ѱ��� ���.
							// �� ���� ���� ���ݰ� �̵��� �бⰡ ����.

		Weapon* mWeapon;	// �̻��
		Pilot* mPilot;		// �̻��
		//vector<SKILL_T> mSkills;
		vector<Vector2_1> pathQueue;
		vector<Skill*> mSkills;
		Skill* curAttactSkill;
		vector<Image*> mImages; // ��ü �̹���

		int skill_range_map[TILE_Y][TILE_X]{};	// ��ų BFS ��
	};
}


