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
	END,
};


enum class SKILL_N
{
	range,
	machtank,
	punch,
	END,
};
enum class SKILL_FUNC
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
int WEAPON_PUSH_DIR[(UINT)MECHS::END]{
	1,//electrice,
	1,//flame,
	1,//guard,
	1,//judo,
	1,//laser,
	1,//leap,
	1,//punch,

	1,//charge,
	1,//jet,
	1,//mirror,
	1,//tank,
	1,//unstable,
	1,//wall,

	4,//artillery,
	4,//dstrike,
	4,//ice,
	4,//ignite,
	4,//rockart,
	4,//rocket,

	0,//grav,
	0,//nano,
	0,//pulse,
	0,//science,
	0,//tele,
};
int ALIEN_WEAPON_PUSH_DIR[(UINT)ALIENS::END]{
	1,//Beetle,
	0,//Blobber,
	0,//Burrower,
	0,//Centipede,
	0,//Crab,
	0,//Digger,
	0,//Firefly,
	0,//Hornet,
	0,//Jelly,
	0,//Leaper,
	0,//Scarab,
	0,//Scorpion,
	0,//Slime,
	0,//Spider,
};
int BASIC_WEAPON[(UINT)MECHS::END]{
	(int)SKILL_T::ST,//electrice,
	(int)SKILL_T::ST,//flame,
	(int)SKILL_T::ST,//guard,
	(int)SKILL_T::ST,//judo,
	(int)SKILL_T::ST,//laser,
	(int)SKILL_T::ST,//leap,
	(int)SKILL_T::ST,//punch,

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
};
int ALIEN_BASIC_WEAPON[(UINT)ALIENS::END]{
	(int)SKILL_T::ST,//Beetle,
	(int)SKILL_T::ST,//Blobber,
	(int)SKILL_T::ST,//Burrower,
	(int)SKILL_T::ST,//Centipede,
	(int)SKILL_T::ARC,//Crab,
	(int)SKILL_T::ST,//Digger,
	(int)SKILL_T::ST,//Firefly,
	(int)SKILL_T::ST,//Hornet,
	(int)SKILL_T::ST,//Jelly,
	(int)SKILL_T::ST,//Leaper,
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