#pragma once
namespace m
{
	class Unit;
	class Skill;
	class TurnManager
	{
	public:
		struct TurnInfo
		{
			Vector2 coord;
			int hp;
			vector<Skill*> mSkills;
		};
		static void SaveTurn();
		static void ResetTurn();

	private:
	};
}


