#pragma once
wstring WEAPONS_FOLDER_PATH[3]{
	L"EnemyWeapons",
	L"passives",
	L"PlayerWeapons"
};

enum class SKILL_T
{
	ARC,
	ST,
	RANGE_ST,
	RANGE_ARC,
	END,
};
enum class WEAPON_T
{
	titan_fist,
	artemis_artillery,
	taurus_cannon,

	stinging,				// scorpion
	fangs,					// leaper
	stinger,				// hornet
	accelerating_thorax,	// firefly
	NONE,
	END,
};
int WEAPON_TYPE[(UINT)WEAPON_T::END]{
	(int)SKILL_T::RANGE_ST,
	(int)SKILL_T::ARC,
	(int)SKILL_T::ST,
};
enum class SKILL_N
{
	range,
	machtank,
	punch,
	firefly1,
	hornet1,
	END,
};
enum class SKILL_FUNC_T
{
	PUSH,
	CHAIN,
	FIRE,
	ICE,

	END,
};
wstring SKILL_PATH[(UINT)SKILL_N::END]{
	L"shotup_tribomb_missile",
	L"shot_mechtank_",
	L"punch1_",
	L"shot_firefly_",
	L"hornet_",
};
enum class SKILL_DIR
{
	R,
	L,
	U,
	D,
	NONE,
};
wstring SKILL_DIR_PATH[(UINT)SKILL_DIR::NONE]{
	L"R",
	L"L",
	L"U",
	L"D",
};
int WEAPON_LEN[(UINT)WEAPON_T::END]{
	1,
	1,
	6,
};
int WEAPON_RANGE[(UINT)WEAPON_T::END]{
	1,
	99,
	99,

	99,
	1,
	1,
	99,
};
WEAPON_T BASIC_WEAPON_TYPE[(UINT)((int)MECHS::END + (int)ALIENS::END)]{
	WEAPON_T::NONE,//electrice,
	WEAPON_T::NONE,//flame,
	WEAPON_T::NONE,//guard,
	WEAPON_T::NONE,//judo,
	WEAPON_T::NONE,//laser,
	WEAPON_T::NONE,//leap,
	WEAPON_T::titan_fist,//punch,

	WEAPON_T::NONE,//charge,
	WEAPON_T::NONE,//jet,
	WEAPON_T::NONE,//mirror,
	WEAPON_T::taurus_cannon,//tank,
	WEAPON_T::NONE,//unstable,
	WEAPON_T::NONE,//wall,

	WEAPON_T::artemis_artillery,//artillery,
	WEAPON_T::NONE,//dstrike,
	WEAPON_T::NONE,//ice,
	WEAPON_T::NONE,//ignite,
	WEAPON_T::NONE,//rockart,
	WEAPON_T::NONE,//rocket,

	WEAPON_T::NONE,//grav,
	WEAPON_T::NONE,//nano,
	WEAPON_T::NONE,//pulse,
	WEAPON_T::NONE,//science,
	WEAPON_T::NONE,//tele,

	WEAPON_T::NONE,//Beetle,
	WEAPON_T::NONE,//Blobber,
	WEAPON_T::NONE,//Burrower,
	WEAPON_T::NONE,//Centipede,
	WEAPON_T::NONE,//Crab,
	WEAPON_T::NONE,//Digger,
	WEAPON_T::accelerating_thorax,//Firefly,
	WEAPON_T::stinger,//Hornet,
	WEAPON_T::NONE,//Jelly,
	WEAPON_T::fangs,//Leaper,
	WEAPON_T::NONE,//Scarab,
	WEAPON_T::stinging,//Scorpion,
	WEAPON_T::NONE,//Slime,
	WEAPON_T::NONE,//Spider,
};
int WEAPON_PUSH_DIR[(UINT)((int)MECHS::END + (int)ALIENS::END)]{
	1,//titan_fist,
	4,//artemis_artillery,
	1,//taurus_cannon,

	0,//stinging,				// scorpion
	0,//fangs,					// leaper
	0,//stinger,				// hornet
	0,//accelerating_thorax,	// firefly
	//NONE,
};
int BASIC_SKILL[(UINT)((int)MECHS::END + (int)ALIENS::END)]{
	(int)SKILL_T::ST,//electrice,
	(int)SKILL_T::ST,//flame,
	(int)SKILL_T::ST,//guard,
	(int)SKILL_T::ST,//judo,
	(int)SKILL_T::ST,//laser,
	(int)SKILL_T::ST,//leap,
	(int)SKILL_T::RANGE_ST,//punch,

	(int)SKILL_T::ST,//charge,
	(int)SKILL_T::ST,//jet,
	(int)SKILL_T::ST,//mirror,
	(int)SKILL_T::ST,//tank,
	(int)SKILL_T::ST,//unstable,
	(int)SKILL_T::ST,//wall,

	(int)SKILL_T::ARC,//artillery,
	(int)SKILL_T::ARC,//dstrike,
	(int)SKILL_T::ARC,//ice,
	(int)SKILL_T::ARC,//ignite,
	(int)SKILL_T::ARC,//rockart,
	(int)SKILL_T::ARC,//rocket,

	(int)SKILL_T::ST,//grav,
	(int)SKILL_T::ST,//nano,
	(int)SKILL_T::ST,//pulse,
	(int)SKILL_T::ST,//science,
	(int)SKILL_T::ST,//tele,

	(int)SKILL_T::ST,//Beetle,
	(int)SKILL_T::ST,//Blobber,
	(int)SKILL_T::ST,//Burrower,
	(int)SKILL_T::ST,//Centipede,
	(int)SKILL_T::ARC,//Crab,
	(int)SKILL_T::ST,//Digger,
	(int)SKILL_T::ST,//Firefly,
	(int)SKILL_T::ST,//Hornet,
	(int)SKILL_T::ST,//Jelly,
	(int)SKILL_T::RANGE_ST,//Leaper,
	(int)SKILL_T::ST,//Scarab,
	(int)SKILL_T::ST,//Scorpion,
	(int)SKILL_T::ST,//Slime,
	(int)SKILL_T::ARC,//Spider,
};
wstring MAKE_SKILL_KEY(SKILL_T skill, SKILL_DIR dir)
{
	wstring key = L"";

	key.append(SKILL_PATH[(UINT)skill]);
	if (dir != SKILL_DIR::NONE)
	{
		key.append(SKILL_DIR_PATH[(UINT)dir]);
	}

	return key;
};
wstring MAKE_SKILL_PATH(SKILL_T skill, SKILL_DIR dir)
{
	wstring path = L"..\\Resources\\texture\\effect\\";

	path.append(SKILL_PATH[(UINT)skill]);
	if (dir != SKILL_DIR::NONE)
	{
		path.append(SKILL_DIR_PATH[(UINT)dir]);
	}
	path.append(L".bmp");

	return path;
};