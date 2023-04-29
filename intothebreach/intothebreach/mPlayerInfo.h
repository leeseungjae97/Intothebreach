#pragma once
#include "_Engine.h"
namespace m {
	class Mech;
	class Alien;
	class Skill;
	class Weapon;
	class Pilot;
	class GameComp {
	public:
		struct MechInfo
		{
			int unitNum;
			WEAPON_T weapons[MAX_WEAPONS]{ WEAPON_T::NONE, WEAPON_T::NONE};
		};
		struct Inven
		{
			static Inven None;
			int type;
			int item;

			bool operator== (const Inven& other)
			{
				return (type == other.type && item == other.item);
			}
			bool operator!= (const Inven& other)
			{
				return (type != other.type || item != other.item);
			}
		};
		static vector<Mech*>& GetMechs() { return mMechs; };
		static void Initialize();
		static vector<MechInfo> mechInfos;
		static vector<Mech*> mMechs;
		static vector<Mech*> mSaveMechs;
		static int clearLandMatric[4][8];
		static int checkClearLand[5];
		static vector<Alien*> mAliens;
		static PILOT_T mPilots[3];
		static vector<Inven> inventoryItems;

		static int curLandSection;
		static int curLand;
		static int gridPower;
		static int defence;
		static int resetTurn;

		static int reactor;
		static int star;

		static int savedPeople;
		static int saveTurnPeople;

		static int structResident;
		static int buildingResident;

		static bool combatEnd;
		
	private:
	};
}

