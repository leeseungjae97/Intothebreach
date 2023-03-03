#pragma once
#include "def.h"
#include "mMath.h"

enum class SCENE_TYPE
{
	INTRO,
	TITLE,
	SELECT_ROBOT,
	SELECT_LAND,
	IN_LAND0,
	IN_LAND1,
	IN_LAND2,
	IN_LAND3,
	COMBAT,
	ENDING,
	END,
};

enum class LAYER_TYPE
{
	BACKGROUND,
	MONSTER,
	PLAYER,
	TILE,
	TILE_HEAD,
	EFFECT,
	UI,
	END,
};
enum class PLAYERINFO_TYPE {
	SKILL,
	WEAPON,
	PILOT,
	END
};
enum class COMPONENT_TYPE {
	TRANSFORM,
	COLLIDER,
	SPRITERENDERER,
	ANIMATOR,
	//AUDIO,
	END,
};

enum class BRUSH_TYPE {
	HOLLOW,
	BLACK,
	CUSTOM_BLACK,
	GRAY,
	END,
};
enum class PEN_TYPE {
	RED,
	GREEN,
	BLUE,
	END
};
enum class MECH_T {
	Prime,
	Brute,
	Range,
	Science,
	Cyborg,
	END,
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
enum class COMMON_CONDITION_T {
	NONE,
	HOLO,
	NO_S,
	END
};
enum class COMBAT_CONDITION_T {
	IDLE,
	BROKEN,
	WATER,
	WATER_BROKEN,
	END
};
 wstring RESOURCES_PATH[RESOURCES_1]{
	L"alien",
	L"combat",
	L"effect",
	L"player",
	L"skill",
	L"structures",
	L"terrain",
	L"ui",
	L"units",
	L"weapons",
};
 wstring MECH_S_PATH[(UINT)MECH_T::END]{
	L"prime\\",
	L"brute\\",
	L"range\\",
	L"science\\"
};


 wstring WEAPONS_PATH[WEAPONS_]{
	L"EnemyWeapons",
	L"passives",
	L"PlayerWeapons"
};
 wstring MECH_CONDITION[(UINT)COMBAT_CONDITION_T::END]{
	L"_a",
	L"_broken",
	L"_w",
	L"_w_broken"
};
 wstring COMMON_MECH_T[(UINT)COMMON_CONDITION_T::END]{
	L"",
	L"_ns",
	L"_h"
};
 wstring& MAKE_COMBAT_MECH_KEY(MECHS _mech, COMBAT_CONDITION_T _cond) {
	 wstring* key = new wstring(L"");
	 int _type = MECHS_T_HT[(UINT)_mech];

	 wstring path_1 = MECH_S_PATH[_type];
	 wstring path_2 = MECHS_RESOURCES_PATH[(UINT)_mech];
	 wstring path_3 = MECH_CONDITION[(UINT)_cond];
	 key->append(path_1);
	 key->append(path_2);
	 key->append(path_3);

	 return (*key);
 }
 wstring& MAKE_COMBAT_MECH_PATH(MECHS _mech, COMBAT_CONDITION_T _cond) {
	 wstring* path = new wstring(L"..\\Resources\\texture\\player\\");
	 int _type = MECHS_T_HT[(UINT)_mech];

	 wstring path_1 = MECH_S_PATH[_type];
	 wstring path_2 = MECHS_RESOURCES_PATH[(UINT)_mech];
	 wstring path_3 = MECH_CONDITION[(UINT)_cond];
	 path->append(path_1);
	 path->append(path_2);
	 path->append(path_3);
	 path->append(L".bmp");

	 return (*path);
 }
 wstring ISLANDS_PATH[ISLANDS]{
	L"island0\\",
	L"island1\\",
	L"island2\\",
	L"island3\\",
	L"island4\\",
};
 wstring ISLANDS_SECTIONS_PATH[ISLANDS]{
	L"island_0_",
	L"island_1_",
	L"island_2_",
	L"island_3_",
	L"island_4_",
};
 enum class ISLAND_T {
	 ISLAND0,
	 ISLAND1,
	 ISLAND2,
	 ISLAND3,
	 END
 };
 UINT ISLANDS_SECTIONS[(UINT)ISLAND_T::END]{
	8,
	8,
	8,
	8,
};

m::Vector2 ISLAND0_POS[8]{
	m::Vector2{250.f, 230.f},
	m::Vector2{462.f, 69.f},
	m::Vector2{404.f, 267.f},
	m::Vector2{608.f, 187.f},
	m::Vector2{726.f, 225.f},
	m::Vector2{824.f, 250.f},
	m::Vector2{412.f, 430.f},
	m::Vector2{801.f, 486.f},
};
m::Vector2 ISLAND1_POS[8]{
	m::Vector2{324.f, 280.f},
	m::Vector2{364.f, 96.f},
	m::Vector2{622.f, 88.f},
	m::Vector2{622.f, 191.f},
	m::Vector2{804.f, 243.f},
	m::Vector2{606.f, 341.f},
	m::Vector2{382.f, 449.f},
	m::Vector2{640.f, 455.f}
};
m::Vector2 ISLAND2_POS[8]{
	m::Vector2{351.f, 390.f},
	m::Vector2{216.f, 140.f},
	m::Vector2{284.f, 280.f},
	m::Vector2{486.f, 220.f},
	m::Vector2{624.f, 140.f},
	m::Vector2{624.f, 298.f},
	m::Vector2{774.f, 174.f},
	m::Vector2{880.f, 265.f}
};
m::Vector2 ISLAND3_POS[8]{
	m::Vector2{257.f, 138.f},
	m::Vector2{393.f, 134.f},
	m::Vector2{589.f, 160.f},
	m::Vector2{739.f, 262.f},
	m::Vector2{393.f, 289.f},
	m::Vector2{549.f, 313.f},
	m::Vector2{739.f, 384.f},
	m::Vector2{873.f, 402.f}
};
m::Vector2* ISLANDS_POS[(UINT)ISLAND_T::END]{
	ISLAND0_POS,
	ISLAND1_POS,
	ISLAND2_POS,
	ISLAND3_POS,
};
wstring& MAKE_ISLAND_KEY(ISLAND_T _type, int sectionIdx) {
	wstring* key = new wstring(L"");

	key->append(ISLANDS_PATH[(UINT)_type]);
	if(sectionIdx < 0) key->append(L"island");
	else {
		key->append(ISLANDS_SECTIONS_PATH[(UINT)_type]);
		key->append(std::to_wstring(sectionIdx));
	}

	return (*key);
}
wstring& MAKE_ISLAND_PATH(ISLAND_T _type, int sectionIdx) {
	wstring* path = new wstring(L"..\\Resources\\texture\\ui\\inLand\\");
	path->append(ISLANDS_PATH[(UINT)_type]);
	if (sectionIdx < 0) {
		path->append(L"island");
	}
	else {
		path->append(ISLANDS_SECTIONS_PATH[(UINT)_type]);
		path->append(std::to_wstring(sectionIdx));
	}
	path->append(L".bmp");

	return (*path);
}
enum class TILE_HEAD_T {
	ground,
	forest,
	building,
	building_water,
	building_collapse,
	mountain,
	mountain_broken,
	END,
};
wstring TILE_HEAD_PATH[(UINT)TILE_HEAD_T::END]{
	L"ground_0",
	L"forest_0",
	L"building_sheet",
	L"building_sheet_water",
	L"building_collapse",
	L"mountain_0",
	L"mountain_0_broken",
};
enum class TILE_T {
	GREEN,
	SAND,
	SNOW,
	ACID,
	VOLCANO,
	CAVE,
	COMMON,
	END,
};
wstring TILE_PATH[(UINT)TILE_T::END]{
   L"green\\",
   L"sand\\",
   L"snow\\",
   L"acid\\",
   L"volcano\\",
   L"cave\\",
   L""
};
wstring& MAKE_TILE_KEY(TILE_T _type, TILE_HEAD_T _type2) {
	wstring* key = new wstring(L"");

	key->append(TILE_PATH[(UINT)_type]);
	key->append(TILE_HEAD_PATH[(UINT)_type2]);


	return (*key);
}
wstring& MAKE_TILE_PATH(TILE_T _type, TILE_HEAD_T _type2) {
	wstring* path = new wstring(L"..\\Resources\\texture\\terrain\\");

	path->append(TILE_PATH[(UINT)_type]);
	path->append(TILE_HEAD_PATH[(UINT)_type2]);

	path->append(L".bmp");

	return (*path);
}
enum class ALIEN_T {
	Beetle,
	Blobber,
	Burrower,
	Centipede,
	Crab,
	Digger,
	Firefly,
	Hornet,
	Jelly,
	Leaper,
	Scarab,
	Scorpion,
	Slime,
	Spider,
	END
};
int ALIEN_T_HT[(UINT)ALIEN_T::END]{
	5,
	5,
	4,
	5,
	5,
	5,
	5,
	4,
	5,
	5,
	5,
	5,
	7,
	5,
};



wstring& MAKE_ALIEN_KEY(TILE_T _type, TILE_HEAD_T _type2) {
	wstring* key = new wstring(L"");

	key->append(TILE_PATH[(UINT)_type]);
	key->append(TILE_HEAD_PATH[(UINT)_type2]);


	return (*key);
}
wstring& MAKE_ALIEN_PATH(TILE_T _type, TILE_HEAD_T _type2) {
	wstring* path = new wstring(L"..\\Resources\\texture\\alien\\");

	path->append(TILE_PATH[(UINT)_type]);
	path->append(TILE_HEAD_PATH[(UINT)_type2]);

	path->append(L".bmp");

	return (*path);
}