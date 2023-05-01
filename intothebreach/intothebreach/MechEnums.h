#pragma once
enum class MECH_T {
	Prime,
	Brute,
	Range,
	Science,
	Cyborg,
	END,
};
wstring MECH_T_NAME_PATH[(UINT)MECH_T::END]{
	L"..\\Resources\\texture\\ui\\selectRobot\\mech_class_text_prime.bmp",
	L"..\\Resources\\texture\\ui\\selectRobot\\mech_class_text_brute.bmp",
	L"..\\Resources\\texture\\ui\\selectRobot\\mech_class_text_range.bmp",
};
enum class COMMON_CONDITION_T {
	NONE,
	HOLO,
	NO_S,
	END
};
enum class COMBAT_CONDITION_T {
	S_SIZE,
	IDLE,
	BROKEN,
	WATER,
	WATER_BROKEN,
	NO_SHADOW,
	HOLO,
	END
};
enum class MECHS {
	electrice,
	flame,
	guard,
	judo,
	laser,
	leap,
	punch,

	charge,
	jet,
	mirror,
	tank,
	unstable,
	wall,

	artillery,
	dstrike,
	ice,
	ignite,
	rockart,
	rocket,

	grav,
	nano,
	pulse,
	science,
	tele,

	END
};
int MECH_HP[(UINT)MECHS::END]{
	3,//electrice,
	3,//flame,
	4,//guard,
	4,//judo,
	3,//laser,
	4,//leap,
	3,//punch,

	3,//charge,
	4,//jet,
	3,//mirror,
	3,//tank,
	3,//unstable,
	3,//wall,

	2,//artillery,
	3,//dstrike,
	3,//ice,
	3,//ignite,
	3,//rockart,
	3,//rocket,

	4,//grav,
	4,//nano,
	4,//pulse,
	4,//science,
	4//tele,
};
int MECH_MOVE_RANGE[(UINT)MECHS::END]{
	3,//electrice,
	3,//flame,
	4,//guard,
	4,//judo,
	3,//laser,
	4,//leap,
	3,//punch,

	3,//charge,
	4,//jet,
	3,//mirror,
	3,//tank,
	3,//unstable,
	3,//wall,

	3,//artillery,
	3,//dstrike,
	3,//ice,
	3,//ignite,
	3,//rockart,
	3,//rocket,

	4,//grav,
	4,//nano,
	4,//pulse,
	4,//science,
	4//tele,
};
wstring MECHS_RESOURCES_PATH[(UINT)MECHS::END]{
   L"mech_electrice",
   L"mech_flame",
   L"mech_guard",
   L"mech_judo",
   L"mech_laser",
   L"mech_leap",
   L"mech_punch",

   L"mech_charge",
   L"mech_jet",
   L"mech_mirror",
   L"mech_tank",
   L"mech_unstable",
   L"mech_wall",

   L"mech_artillery",
   L"mech_dstrike",
   L"mech_ice",
   L"mech_ignite",
   L"mech_rockart",
   L"mech_rocket",

   L"mech_grav",
   L"mech_nano",
   L"mech_pulse",
   L"mech_science",
   L"mech_tele",
};
int MECHS_T_HT[(UINT)MECHS::END]{
	(int)MECH_T::Prime,
	(int)MECH_T::Prime,
	(int)MECH_T::Prime,
	(int)MECH_T::Prime,
	(int)MECH_T::Prime,
	(int)MECH_T::Prime,
	(int)MECH_T::Prime,

	(int)MECH_T::Brute,
	(int)MECH_T::Brute,
	(int)MECH_T::Brute,
	(int)MECH_T::Brute,
	(int)MECH_T::Brute,
	(int)MECH_T::Brute,

	(int)MECH_T::Range,
	(int)MECH_T::Range,
	(int)MECH_T::Range,
	(int)MECH_T::Range,
	(int)MECH_T::Range,
	(int)MECH_T::Range,

	(int)MECH_T::Science,
	(int)MECH_T::Science,
	(int)MECH_T::Science,
	(int)MECH_T::Science,
	(int)MECH_T::Science,
};
m::Vector2 MECHS_HANGAR_OFFSET[(UINT)MECHS::END]{
	// S_SIZE, IDLE, BROKEN, WATER, WATER_BROKEN, NO_SHADOW, HOLO,
	//x, y
	{}, //   L"mech_electrice",
	{}, //  L"mech_flame",
	{}, //  L"mech_guard",
	{}, //  L"mech_judo",
	{10.f, -10.f}, //  L"mech_laser",
	{}, //  L"mech_leap",
	{}, //  L"mech_punch",

	{}, //  L"mech_charge",
	{}, //  L"mech_jet",
	{0, 10.f}, //  L"mech_mirror",
	{0,15.f}, //  L"mech_tank",
	{}, //  L"mech_unstable",
	{}, //  L"mech_wall",

	{}, //  L"mech_artillery",
	{}, //  L"mech_dstrike",
	{}, //  L"mech_ice",
	{}, //  L"mech_ignite",
	{0, -10.f}, //  L"mech_rockart",
	{0, -10.f}, //  L"mech_rocket",

	{}, //  L"mech_grav",
	{}, //  L"mech_nano",
	{}, //  L"mech_pulse",
	{}, //  L"mech_science",
	{}, //  L"mech_tele",
};
m::Vector2 MECHS_OFFSET[(UINT)MECHS::END][(UINT)COMBAT_CONDITION_T::END]{
	// S_SIZE, IDLE, BROKEN, WATER, WATER_BROKEN, NO_SHADOW, HOLO,
	//x, y
	{{}}, //   L"mech_electrice",
	{{9.f,-6.f}, {9.f,-6.f}, {9.f,-6.f}, {9.f,-6.f}, {9.f,-6.f}, {10.f, -50.f},}, //  L"mech_flame",
	{{}}, //  L"mech_guard",
	{{}}, //  L"mech_judo",
	{{}}, //  L"mech_laser",
	{{}}, //  L"mech_leap",
	{{9.f,-6.f}, {9.f,-6.f}, {9.f,-6.f}, {9.f,-6.f}, {9.f,-6.f}, {10.f, -50.f},}, //  L"mech_punch",

	{{8.f, 0.f},{8.f, 0.f},{8.f, 0.f},{8.f, 0.f},{8.f, 0.f},{10.f, -50}}, //  L"mech_charge",
	{{}}, //  L"mech_jet",
	{{15.f, 6.f},{15.f, 6.f},{15.f, 6.f},{15.f, 6.f},{15.f, 6.f},{10.f, -50}}, //  L"mech_mirror",
	{{15.f, 6.f},{15.f, 6.f},{15.f, 6.f},{15.f, 6.f},{15.f, 6.f},{10.f, -50}}, //  L"mech_tank",
	{{}}, //  L"mech_unstable",
	{{}}, //  L"mech_wall",

	{{15.f, -5.f},{15.f, -5.f},{15.f, -5.f},{15.f, -5.f},{15.f, -5.f},{10.f, -50}}, //  L"mech_artillery",
	{{}}, //  L"mech_dstrike",
	{{}}, //  L"mech_ice",
	{{}}, //  L"mech_ignite",
	{{15.f, -5.f},{15.f, -5.f},{15.f, -5.f},{15.f, -5.f},{15.f, -5.f},{10.f, -50}}, //  L"mech_rockart",
	{{}}, //  L"mech_rocket",

	{{}}, //  L"mech_grav",
	{{}}, //  L"mech_nano",
	{{}}, //  L"mech_pulse",
	{{}}, //  L"mech_science",
	{{}}, //  L"mech_tele",
};

m::Vector2 MECHS_IMAGE_SIZE[(UINT)MECHS::END]{
	//x, y
	{0,0},//   L"mech_electrice",
	{0,0},//  L"mech_flame",
	{0,0},//  L"mech_guard",
	{0,0},//  L"mech_judo",
	{0,0},//  L"mech_laser",
	{0,0},//  L"mech_leap",
	{-2,-1},//  L"mech_punch",

	{0,0},//  L"mech_charge",
	{0,0},//  L"mech_jet",
	{0,0},//  L"mech_mirror",
	{0,0},//  L"mech_tank",
	{0,0},//  L"mech_unstable",
	{0,0},//  L"mech_wall",

	{0,0},//  L"mech_artillery",
	{0,0},//  L"mech_dstrike",
	{0,0},//  L"mech_ice",
	{0,0},//  L"mech_ignite",
	{0,0},//  L"mech_rockart",
	{0,0},//  L"mech_rocket",

	{0,0},//  L"mech_grav",
	{0,0},//  L"mech_nano",
	{0,0},//  L"mech_pulse",
	{0,0},//  L"mech_science",
	{0,0},//  L"mech_tele",
};
wstring MECH_CONDITION[(UINT)COMBAT_CONDITION_T::END]{
   L"",
   L"_a",
   L"_broken",
   L"_w",
   L"_w_broken",
   L"_ns",
   L"_h",
};
wstring COMMON_MECH_T[(UINT)COMMON_CONDITION_T::END]{
   L"",
   L"_ns",
   L"_h"
};
enum class PRIME_T {
	electrice,
	flame,
	guard,
	judo,
	laser,
	leap,
	punch,
	END,
};
wstring PRIME_MECH_NAMES[(UINT)PRIME_T::END]{
   L"mech_electrice",
   L"mech_flame",
   L"mech_guard",
   L"mech_judo",
   L"mech_laser",
   L"mech_leap",
   L"mech_punch"
};
enum class BRUTE_T {
	charge,
	jet,
	mirror,
	tank,
	unstable,
	wall,
	END,
};
wstring BRUTE_MECH_NAMES[(UINT)BRUTE_T::END]{
   L"mech_charge",
   L"mech_jet",
   L"mech_mirror",
   L"mech_tank",
   L"mech_unstable",
   L"mech_wall"
};
enum class RANGE_T {
	artillery,
	dstrike,
	ice,
	ignite,
	rockart,
	rocket,
	END,
};
wstring RANGE_MECH_NAMES[(UINT)RANGE_T::END]{
   L"mech_artillery",
   L"mech_dstrike",
   L"mech_ice",
   L"mech_ignite",
   L"mech_rockart",
   L"mech_rocket"
};
enum class SCIENCE_T {
	grav,
	nano,
	pulse,
	science,
	tele,
	END,
};
wstring SCIENCE_MECH_NAMES[(UINT)SCIENCE_T::END]{
   L"mech_grav",
   L"mech_nano",
   L"mech_pulse",
   L"mech_science",
   L"mech_tele"
};
wstring MECH_S_PATH[(UINT)MECH_T::END]{
   L"prime\\",
   L"brute\\",
   L"range\\",
   L"science\\"
};
wstring MECH_NAMES_PATH[(UINT)MECHS::END]{
   L"",//L"mech_electrice",
   L"..\\Resources\\texture\\ui\\selectRobot\\flame_mech.bmp",//L"mech_flame",
   L"",//L"mech_guard",
   L"",//L"mech_judo",
   L"..\\Resources\\texture\\ui\\selectRobot\\laser_mech.bmp",//L"mech_laser",
   L"",//L"mech_leap",
   L"..\\Resources\\texture\\ui\\selectRobot\\combat_mech.bmp",//L"mech_punch",
   //
   L"",//L"mech_charge",
   L"",//L"mech_jet",
   L"..\\Resources\\texture\\ui\\selectRobot\\mirror_mech.bmp",//L"mech_mirror",
   L"..\\Resources\\texture\\ui\\selectRobot\\canno_mech.bmp",//L"mech_tank",
   L"",//L"mech_unstable",
   L"",//L"mech_wall",
   //
   L"..\\Resources\\texture\\ui\\selectRobot\\artillery_mech.bmp",//L"mech_artillery",
   L"",//L"mech_dstrike",
   L"",//L"mech_ice",
   L"",//L"mech_ignite",
   L"..\\Resources\\texture\\ui\\selectRobot\\rock_mech.bmp",//L"mech_rockart",
   L"",//L"mech_rocket",
   //
   L"",//L"mech_grav",
   L"",//L"mech_nano",
   L"",//L"mech_pulse",
   L"",//L"mech_science",
   L"",//L"mech_tele",
};
wstring MAKE_UNIT_KEY(MECHS _mech, COMBAT_CONDITION_T _cond) {
	wstring key = L"";
	int _type = MECHS_T_HT[(UINT)_mech];
	
	wstring path_1 = MECH_S_PATH[_type];
	wstring path_2 = MECHS_RESOURCES_PATH[(UINT)_mech];
	wstring path_3 = MECH_CONDITION[(UINT)_cond];

	key.append(path_1);
	key.append(path_2);
	key.append(path_3);

	return key;
};
wstring MAKE_UNIT_PATH(MECHS _mech, COMBAT_CONDITION_T _cond) {
	wstring path = L"..\\Resources\\texture\\player\\";
	int _type = MECHS_T_HT[(UINT)_mech];

	wstring path_1 = MECH_S_PATH[_type];
	wstring path_2 = MECHS_RESOURCES_PATH[(UINT)_mech];
	wstring path_3 = MECH_CONDITION[(UINT)_cond];

	path.append(path_1);
	path.append(path_2);
	path.append(path_3);
	path.append(L".bmp");

	return path;
};