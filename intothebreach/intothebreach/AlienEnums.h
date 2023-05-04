#pragma once
enum class ALIENS_RANK
{
	NORMAL,
	ELITE,
	BOSS,
	END,
};
enum class ALIENS
{
	Beetle, // 
	Burrower,
	Firefly, //
	Hornet, //
	StarFish, //
	Mosquito,//
	Dung, //
	END
};
wstring ALIEN_PATH[(UINT)ALIENS::END]{
	L"beetle",
	L"burrower",
	L"firefly",
	L"hornet",
	L"starfish",
	L"mosquito",
	L"dungbeetle",
};
wstring ALIEN_DEATH_SOUNDS[(UINT)ALIENS::END]{

	L"..\\Resources\\sound\\sfx\\enemy_beetle_1_death.wav",
	L"..\\Resources\\sound\\sfx\\enemy_burnbug_1_death.wav",
	L"..\\Resources\\sound\\sfx\\enemy_firefly_sold_1_death.wav",
	L"..\\Resources\\sound\\sfx\\enemy_hornet_1_death.wav",
	L"..\\Resources\\sound\\sfx\\enemy_starfish_1_death.wav",
	L"..\\Resources\\sound\\sfx\\enemy_mosquito_1_death.wav",
	L"..\\Resources\\sound\\sfx\\enemy_dungbeetle_1_death.wav",
};
wstring ALIEN_HURT_SOUNDS[(UINT)ALIENS::END]{
	L"..\\Resources\\sound\\sfx\\enemy_beetle_1_hurt.wav",
	L"..\\Resources\\sound\\sfx\\enemy_burnbug_1_hurt.wav",
	L"..\\Resources\\sound\\sfx\\enemy_firefly_sold_1_hurt.wav",
	L"..\\Resources\\sound\\sfx\\enemy_hornet_1_hurt.wav",
	L"..\\Resources\\sound\\sfx\\enemy_starfish_1_hurt.wav",
	L"..\\Resources\\sound\\sfx\\enemy_mosquito_1_hurt.wav",
	L"..\\Resources\\sound\\sfx\\enemy_dungbeetle_1_hurt.wav",
};
wstring ALIEN_ATTACK_LAUNCH_SOUNDS[(UINT)ALIENS::END]{
	L"..\\Resources\\sound\\sfx\\enemy_beetle_1_attack_charge.wav",
	L"..\\Resources\\sound\\sfx\\mech_prime_skill_sword.wav",
	L"..\\Resources\\sound\\sfx\\enemy_firefly_sold_1_attack_split.wav",
	L"..\\Resources\\sound\\sfx\\enemy_hornet_1_attack_metal.wav",
	L"..\\Resources\\sound\\sfx\\enemy_starfish_1_attack_launch.wav",
	L"..\\Resources\\sound\\sfx\\enemy_mosquito_1_attack_launch.wav",
	L"..\\Resources\\sound\\sfx\\enemy_dungbeetle_1_attack_launch.wav",
};
wstring ALIEN_ATTACK_IMPACT_SOUNDS[(UINT)ALIENS::END]{
	L"..\\Resources\\sound\\sfx\\enemy_beetle_1_impact.wav",
	L"",
	L"..\\Resources\\sound\\sfx\\enemy_firefly_sold_1_attack_impact.wav",
	L"..\\Resources\\sound\\sfx\\enemy_hornet_1_hurt.wav",
	L"..\\Resources\\sound\\sfx\\enemy_starfish_1_hurt.wav",
	L"..\\Resources\\sound\\sfx\\enemy_mosquito_1_hurt.wav",
	L"..\\Resources\\sound\\sfx\\enemy_dungbeetle_1_hurt.wav",
};
wstring ALIEN_MOVE_SOUNDS[(UINT)ALIENS::END][3]{
	{
		L"..\\Resources\\sound\\sfx\\enemy_beetle_1_move_01.wav",
		L"..\\Resources\\sound\\sfx\\enemy_beetle_1_move_02.wav",
		L"..\\Resources\\sound\\sfx\\enemy_beetle_1_move_03.wav",
	},
		{
		L"..\\Resources\\sound\\sfx\\enemy_shared_crawl_out_01.wav",
		L"..\\Resources\\sound\\sfx\\enemy_shared_crawl_out_02.wav",
		L"..\\Resources\\sound\\sfx\\enemy_shared_crawl_out_03.wav",
	},
		{
		L"..\\Resources\\sound\\sfx\\enemy_firefly_sold_1_move_01.wav",
		L"..\\Resources\\sound\\sfx\\enemy_firefly_sold_1_move_02.wav",
		L"..\\Resources\\sound\\sfx\\enemy_firefly_sold_1_move_03.wav",
	},
		{
		L"..\\Resources\\sound\\sfx\\enemy_hornet_1_move_01.wav",
		L"..\\Resources\\sound\\sfx\\enemy_hornet_1_move_02.wav",
		L"..\\Resources\\sound\\sfx\\enemy_hornet_1_move_03.wav",
	},
		{
		L"..\\Resources\\sound\\sfx\\enemy_starfish_1_move_01.wav",
		L"..\\Resources\\sound\\sfx\\enemy_starfish_1_move_02.wav",
		L"..\\Resources\\sound\\sfx\\enemy_starfish_1_move_03.wav",
	},
			{
		L"..\\Resources\\sound\\sfx\\enemy_mosquito_1_move_01.wav",
		L"..\\Resources\\sound\\sfx\\enemy_mosquito_1_move_02.wav",
		L"..\\Resources\\sound\\sfx\\enemy_mosquito_1_move_03.wav",
	},
			{
		L"..\\Resources\\sound\\sfx\\enemy_dungbeetle_1_move_01.wav",
		L"..\\Resources\\sound\\sfx\\enemy_dungbeetle_1_move_02.wav",
		L"..\\Resources\\sound\\sfx\\enemy_dungbeetle_1_move_03.wav",
	},

};
enum class ALIEN_CONDITION
{
	IDLE,
	DEATH,
	EMERGE,
	WATER,
	END
};
wstring ALIEN_CONDITION_PATH[(UINT)ALIEN_CONDITION::END]{
	L"a",
	L"_death",
	L"_emerge",
	L"_Bw",
};
m::Vector2 ALIEN_OFFSET[(UINT)ALIENS::END][(UINT)ALIEN_CONDITION::END]{
	//x, y
	{},//Beetle,
	{},//Burrower,
	{{10, -10.f},{10, -10.f},{2, -8.f},{10, -10.f}},//Firefly,
	{{20, -25.f},{20, -25.f},{3, -21.f},{20, -25.f}},//Hornet,
	{},//starfish,
	{},//mosquito,
	{},//dungbeetle,
};
m::Vector2 ALIENS_IDLE_SIZE[(UINT)ALIENS::END]{
	{0,0},//Beetle,
	{0,0},//Burrower,
	{37,37},//Firefly,
	{32,48},//Hornet,
	{42,37},//starfish,
	{0,0},//mosquito,
	{39,36},//dung,
};
m::Vector2 ALIENS_DEATH_SIZE[(UINT)ALIENS::END]{
	{0,0},//Beetle,
	{0,0},//Burrower,
	{41,39},//Firefly,
	{30,48},//Hornet,
	{0,0},//starfish,
	{54,38},//mosquito,
	{0,0},//dung,
};
m::Vector2 ALIENS_EMERGE_SIZE[(UINT)ALIENS::END]{
	{0,0},//Beetle,
	{0,0},//Burrower,
	{42,43},//Firefly,
	{41,52},//Hornet,
	{0,0},//starfish,
	{48,43},//mosquito,
	{0,0},//dung,
};
m::Vector2 ALIENS_IMAGE_SIZE[(UINT)ALIENS::END]{
	//x, y
	{0,0},//Beetle,
	{0,0},//Burrower,
	{0,0},//Firefly,
	{30,48},//Hornet,
	{0,0},//starfish,
	{0,0},//mosquito,
	{0,0},//dung,
};
//
int ALIENS_APL_COND[(UINT)ALIENS::END][(UINT)ALIEN_CONDITION::END]{
	//idle, death, emeger, water
	{1,1,1,1},//Beetle,
	{1,1,1,0},//Burrower,
	{1,1,1,1},//Firefly,
	{1,1,1,0},//Hornet,
	{1,1,1,1},//starfish,
	{1,1,1,0},//mosquito,
	{1,1,1,1},//dung,

};
m::Vector2 ALIENS_SIZES[(UINT)ALIENS::END][3]{
	{ALIENS_IDLE_SIZE[0], ALIENS_DEATH_SIZE[0], ALIENS_EMERGE_SIZE[0]},//Beetle,
	{ALIENS_IDLE_SIZE[1], ALIENS_DEATH_SIZE[1], ALIENS_EMERGE_SIZE[1]},//Blobber,
	{ALIENS_IDLE_SIZE[2], ALIENS_DEATH_SIZE[2], ALIENS_EMERGE_SIZE[2]},//Burrower,
	{ALIENS_IDLE_SIZE[3], ALIENS_DEATH_SIZE[3], ALIENS_EMERGE_SIZE[3]},//Centipede,
	{ALIENS_IDLE_SIZE[4], ALIENS_DEATH_SIZE[4], ALIENS_EMERGE_SIZE[4]},//Crab,
	{ALIENS_IDLE_SIZE[5], ALIENS_DEATH_SIZE[5], ALIENS_EMERGE_SIZE[5]},//Digger,
	{ALIENS_IDLE_SIZE[6], ALIENS_DEATH_SIZE[6], ALIENS_EMERGE_SIZE[6]},//Firefly,
};
int ALIEN_MOVE_RANGE[(UINT)ALIENS::END]{
	3,//Beetle,
	3,//Blobber,
	3,//Burrower,
	3,//Centipede,
	3,//Crab,
	3,//Digger,
	3,//Firefly,

};
int ALIEN_HP[(UINT)ALIENS::END]{
	3,//Beetle,
	3,//Blobber,
	3,//Burrower,
	3,//Centipede,
	3,//Crab,
	3,//Digger,
	3,//Firefly,
};

wstring MAKE_UNIT_KEY(ALIENS _type, ALIEN_CONDITION _type2)
{
	wstring key = L"";

	key.append(ALIEN_PATH[(UINT)_type]);
	key.append(ALIEN_CONDITION_PATH[(UINT)_type2]);

	return key;
}
wstring MAKE_UNIT_PATH(ALIENS _type, ALIEN_CONDITION _type2)
{
	wstring path = L"..\\Resources\\texture\\alien\\";

	path.append(ALIEN_PATH[(UINT)_type]);
	path.append(ALIEN_CONDITION_PATH[(UINT)_type2]);

	path.append(L".bmp");

	return path;
}
