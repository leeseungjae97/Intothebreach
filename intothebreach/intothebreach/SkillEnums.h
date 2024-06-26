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
	MULTI_ST,
	RANGE_ARC,
	NONE,
	END,
};
enum class WEAPON_T
{
	NONE,
	titan_fist,
	artemis_artillery,
	taurus_cannon,
	flame_thrower,
	brust_beam,
	rock_launcher,
	janus_cannon,

	pincers,				// beetle
	spike,					// burrower
	accelerating_thorax,	// firefly
	stinger,				// hornet
	appendages,				// starfish
	tentacles,				// mosquito
	prize,					// dung

	END,
};
//int WEAPON_TYPE[(UINT)WEAPON_T::END]{
//	(int)SKILL_T::RANGE_ST,
//	(int)SKILL_T::ARC,
//	(int)SKILL_T::ST,
//	(int)SKILL_T::MULTI_ST,
//};
wstring WEAPON_PATH[(UINT)WEAPON_T::END]{
	L"",
	L"punch1_",
	L"shotup_tribomb_missile_L",
	L"shot_mechtank_",
	L"flamethrower1_",
	L"laser_",
	L"shotup_rock_L",
	L"shot_mechtank_",

	L"",
	L"sword_",
	L"shot_firefly_",
	L"hornet_",
};

wstring WEAPON_IMAGES[(UINT)WEAPON_T::END]{
	L"..\\Resources\\texture\\ui\\inventory\\inven_skill_box_.bmp",
	L"..\\Resources\\texture\\weapons\\PlayerWeapons\\prime_punchmech.bmp",
	L"..\\Resources\\texture\\weapons\\PlayerWeapons\\ranged_artillery.bmp",
	L"..\\Resources\\texture\\weapons\\PlayerWeapons\\brute_tankmech.bmp",
	L"..\\Resources\\texture\\weapons\\PlayerWeapons\\prime_flamethrower.bmp",
	L"..\\Resources\\texture\\weapons\\PlayerWeapons\\prime_lasermech.bmp",
	L"..\\Resources\\texture\\weapons\\PlayerWeapons\\ranged_rockthrow.bmp",
	L"..\\Resources\\texture\\weapons\\PlayerWeapons\\brute_mirror.bmp",

	L"..\\Resources\\texture\\weapons\\PlayerWeapons\\",
	L"..\\Resources\\texture\\weapons\\PlayerWeapons\\",
	L"..\\Resources\\texture\\weapons\\PlayerWeapons\\enemy_firefly1.bmp",
	L"..\\Resources\\texture\\weapons\\PlayerWeapons\\enemy_hornet1.bmp",
};
wstring WEAPON_LAUNCH_SOUNDS[(UINT)WEAPON_T::END]{
	L"",
	L"..\\Resources\\sound\\sfx\\mech_prime_skill_titanfist_flesh.wav",
	L"..\\Resources\\sound\\sfx\\mech_distance_skill_artillery_volley.wav",
	L"..\\Resources\\sound\\sfx\\mech_brute_skill_modified_cannons.wav",
	L"..\\Resources\\sound\\sfx\\mech_prime_skill_flamespreader.wav",
	L"..\\Resources\\sound\\sfx\\mech_prime_skill_prismbeam.wav",
	L"..\\Resources\\sound\\sfx\\mech_distance_skill_rock_throw.wav",
	L"..\\Resources\\sound\\sfx\\mech_brute_skill_mirror_shot.wav",

	L"..\\Resources\\sound\\sfx\\enemy_beetle_1_attack_charge.wav",
	L"..\\Resources\\sound\\sfx\\mech_prime_skill_sword.wav",
	L"..\\Resources\\sound\\sfx\\enemy_firefly_sold_1_attack_spit.wav",
	L"..\\Resources\\sound\\sfx\\enemy_hornet_1_attack_metal.wav",
	L"..\\Resources\\sound\\sfx\\enemy_starfish_1_attack_launch.wav",
	L"..\\Resources\\sound\\sfx\\enemy_mosquito_1_attack_launch.wav",
	L"..\\Resources\\sound\\sfx\\enemy_dungbeetle_1_attack_launch.wav",
};
wstring WEAPON_IMPACT_SOUNDS[(UINT)WEAPON_T::END]{
	L"",
	L"",
	L"..\\Resources\\sound\\sfx\\impact_generic_explosion.wav",
	L"..\\Resources\\sound\\sfx\\impact_generic_explosion.wav",
	L"",
	L"",
	L"..\\Resources\\sound\\sfx\\impact_rock.wav",
	L"..\\Resources\\sound\\sfx\\mech_brute_skill_mirror_shot.wav",

	L"..\\Resources\\sound\\sfx\\enemy_beetle_1_impact.wav",
	L"",
	L"..\\Resources\\sound\\sfx\\enemy_firefly_sold_1_attack_impact.wav",
	L"",
	L"",
	L"",
	L"",
};
enum class SKILL_DIR
{
	R,
	U,
	D,
	L,
	NONE,
};
wstring SKILL_DIR_PATH[(UINT)SKILL_DIR::NONE]{
	L"R",
	L"U",
	L"D",
	L"L",
};
int WEAPON_LEN[(UINT)WEAPON_T::END]{
	0,
	6,
	1,
	1,
	9,
	1,
	1,


	1,
	1,
	12,
	1,
};
int WEAPON_RANGE[(UINT)WEAPON_T::END]{
	0,
	1,
	99,
	99,
	1,
	99,
	99,
	99,

	99,
	1,
	99,
	1,
};
WEAPON_T BASIC_WEAPON_TYPE[(UINT)((int)MECHS::END + (int)ALIENS::END)]{
	WEAPON_T::NONE,//electrice,
	WEAPON_T::flame_thrower,//flame,
	WEAPON_T::NONE,//guard,
	WEAPON_T::NONE,//judo,
	WEAPON_T::brust_beam,//laser,
	WEAPON_T::NONE,//leap,
	WEAPON_T::titan_fist,//punch,

	WEAPON_T::NONE,//charge,
	WEAPON_T::NONE,//jet,
	WEAPON_T::janus_cannon,//mirror,
	WEAPON_T::taurus_cannon,//tank,
	WEAPON_T::NONE,//unstable,
	WEAPON_T::NONE,//wall,

	WEAPON_T::artemis_artillery,//artillery,
	WEAPON_T::NONE,//dstrike,
	WEAPON_T::NONE,//ice,
	WEAPON_T::NONE,//ignite,
	WEAPON_T::rock_launcher,//rockart,
	WEAPON_T::NONE,//rocket,

	WEAPON_T::NONE,//grav,
	WEAPON_T::NONE,//nano,
	WEAPON_T::NONE,//pulse,
	WEAPON_T::NONE,//science,
	WEAPON_T::NONE,//tele,

	WEAPON_T::pincers,//Beetle,
	WEAPON_T::spike,//Burrower,
	WEAPON_T::accelerating_thorax,//Firefly,
	WEAPON_T::stinger,//Hornet,
	WEAPON_T::appendages,//starfish,
	WEAPON_T::tentacles,//mosquito,
	WEAPON_T::prize,//dung,
};
int WEAPON_PUSH_DIR[(UINT)((int)MECHS::END + (int)ALIENS::END)]{
	0,
	1,//titan_fist,
	4,//artemis_artillery,
	1,//taurus_cannon,
	1,//flame
	0,//laser
	4,//rock
	1,//mirror

	1,//stinging,				// scorpion
	0,//fangs,					// leaper
	0,//accelerating_thorax,	// firefly
	0,//stinger,				// hornet
	0,//accelerating_thorax,	// star
	0,//accelerating_thorax,	// ms
	0,//accelerating_thorax,	// dug
	//NONE,
};
int WEAPON_SKILL[(UINT)WEAPON_T::END]{
	(int)SKILL_T::NONE,
	(int)SKILL_T::RANGE_ST,//titan_fist,
	(int)SKILL_T::ARC,//artemis_artillery,
	(int)SKILL_T::ST,//taurus_cannon,
	(int)SKILL_T::RANGE_ST,//flame
	(int)SKILL_T::ST,//laser,
	(int)SKILL_T::ARC,//rock,
	(int)SKILL_T::MULTI_ST,//mirror,

	//pincers
	//spike
	//stinger
	//accelerating_thorax
	//appendages
	//tentacles
	//prize

	(int)SKILL_T::RANGE_ST,//pincers,				
	(int)SKILL_T::RANGE_ST,//spike,				
	(int)SKILL_T::ST,//accelerating_thorax,
	(int)SKILL_T::RANGE_ST,//stinger,				
	(int)SKILL_T::RANGE_ST, //apped
	(int)SKILL_T::RANGE_ST,
	(int)SKILL_T::RANGE_ST
	//NONE,
	//END,
};
//int WEAPON_SKILL[(UINT)((int)MECHS::END + (int)ALIENS::END)]{
//	(int)SKILL_T::ST,//electrice,
//	(int)SKILL_T::ST,//flame,
//	(int)SKILL_T::ST,//guard,
//	(int)SKILL_T::ST,//judo,
//	(int)SKILL_T::ST,//laser,
//	(int)SKILL_T::ST,//leap,
//	(int)SKILL_T::RANGE_ST,//punch,
//
//	(int)SKILL_T::ST,//charge,
//	(int)SKILL_T::ST,//jet,
//	(int)SKILL_T::ST,//mirror,
//	(int)SKILL_T::ST,//tank,
//	(int)SKILL_T::ST,//unstable,
//	(int)SKILL_T::ST,//wall,
//
//	(int)SKILL_T::ARC,//artillery,
//	(int)SKILL_T::ARC,//dstrike,
//	(int)SKILL_T::ARC,//ice,
//	(int)SKILL_T::ARC,//ignite,
//	(int)SKILL_T::ARC,//rockart,
//	(int)SKILL_T::ARC,//rocket,
//
//	(int)SKILL_T::ST,//grav,
//	(int)SKILL_T::ST,//nano,
//	(int)SKILL_T::ST,//pulse,
//	(int)SKILL_T::ST,//science,
//	(int)SKILL_T::ST,//tele,
//
//	(int)SKILL_T::ST,//Beetle,
//	(int)SKILL_T::ST,//Blobber,
//	(int)SKILL_T::ST,//Burrower,
//	(int)SKILL_T::ST,//Centipede,
//	(int)SKILL_T::ARC,//Crab,
//	(int)SKILL_T::ST,//Digger,
//	(int)SKILL_T::ST,//Firefly,
//	(int)SKILL_T::RANGE_ST,//Hornet,
//	(int)SKILL_T::ST,//Jelly,
//	(int)SKILL_T::RANGE_ST,//Leaper,
//	(int)SKILL_T::ST,//Scarab,
//	(int)SKILL_T::ST,//Scorpion,
//	(int)SKILL_T::ST,//Slime,
//	(int)SKILL_T::ARC,//Spider,
//};
wstring MAKE_SKILL_KEY(WEAPON_T weapon, SKILL_DIR dir)
{
	wstring key = L"";

	key.append(WEAPON_PATH[(UINT)weapon]);

	if (dir != SKILL_DIR::NONE)
		key.append(SKILL_DIR_PATH[(UINT)dir]);

	return key;
};
wstring MAKE_SKILL_PATH(WEAPON_T weapon, SKILL_DIR dir)
{
	wstring path = L"..\\Resources\\texture\\effect\\";

	path.append(WEAPON_PATH[(UINT)weapon]);
	if (dir != SKILL_DIR::NONE)
	{
		path.append(SKILL_DIR_PATH[(UINT)dir]);
	}
	path.append(L".bmp");

	return path;
};