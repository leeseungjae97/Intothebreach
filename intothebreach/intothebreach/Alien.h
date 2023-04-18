#pragma once
#include "mUnit.h"
namespace m
{
	class Image;
	class Animator;
	class Pilot;
	class Alien :
		public Unit
	{
	public:

		Alien(int unitType, Vector2 _coord, size_t idx);
		Alien(Alien& _origin);
		~Alien();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void idle() override;
		virtual void broken() override;
		virtual void water() override;
		virtual void ActiveSkill(Vector2 otherPos) override;

		void emerge();
		void emerger_loop();

		bool AlienMoveToAttackCheck(Vector2 _alienCoord);
		void AlienMoveCheck(int& curAlien);
		void AlienMapCheck(int curAlien);

		void SetTargetCoord(Vector2 _coord) { tarGetCoord = _coord; }
		void SetFinalMoveCoord(Vector2 _coord) { finalMoveCoord = _coord; }
		void SetFirstEmerge(bool _b) { bFirstEmerge = _b; }

		bool GetFirstEmerge() { return bFirstEmerge; }
		Vector2 GetTargetCoord() { return tarGetCoord; }
		Vector2 GetFinalMoveCoord() { return finalMoveCoord; }

	private:
		int moveCnt;
		bool bFirstEmerge;
		Vector2 tarGetCoord;
		Vector2 finalMoveCoord;
		vector<Vector2_1> alienPathQueue; // ��ü �̵��ؾ��ϴ� �ִܰŸ�.
	};
}

