#pragma once
enum class ALIENS
{
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
wstring ALIEN_PATH[(UINT)ALIENS::END]{
	L"beetle",
	L"blobber",
	L"burrower",
	L"centipede",
	L"crab",
	L"digger",
	L"firefly",
	L"hornet",
	L"jelly",
	L"leaper",
	L"scarab",
	L"scorpion",
	L"slime",
	L"spider",
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
m::Vector2 ALIEN_OFFSET[(UINT)ALIENS::END]{
	//x, y
	{},//Beetle,
	{},//Blobber,
	{},//Burrower,
	{},//Centipede,
	{},//Crab,
	{},//Digger,
	{},//Firefly,
	{},//Hornet,
	{},//Jelly,
	{},//Leaper,
	{},//Scarab,
	{},//Scorpion,
	{},//Slime,
	{},//Spider,
};
m::Vector2 ALIENS_IDLE_SIZE[(UINT)ALIENS::END]{
	{0,0},//Beetle,
	{0,0},//Blobber,
	{0,0},//Burrower,
	{0,0},//Centipede,
	{0,0},//Crab,
	{0,0},//Digger,
	{37,37},//Firefly,
	{32,48},//Hornet,
	{0,0},//Jelly,
	{42,37},//Leaper,
	{0,0},//Scarab,
	{0,0},//Scorpion,
	{0,0},//Slime,
	{0,0},//Spider,
};
m::Vector2 ALIENS_DEATH_SIZE[(UINT)ALIENS::END]{
	{0,0},//Beetle,
	{0,0},//Blobber,
	{0,0},//Burrower,
	{0,0},//Centipede,
	{0,0},//Crab,
	{0,0},//Digger,
	{41,39},//Firefly,
	{30,48},//Hornet,
	{0,0},//Jelly,
	{54,38},//Leaper,
	{0,0},//Scarab,
	{0,0},//Scorpion,
	{0,0},//Slime,
	{0,0},//Spider,
};
m::Vector2 ALIENS_EMERGE_SIZE[(UINT)ALIENS::END]{
	{0,0},//Beetle,
	{0,0},//Blobber,
	{0,0},//Burrower,
	{0,0},//Centipede,
	{0,0},//Crab,
	{0,0},//Digger,
	{42,43},//Firefly,
	{41,52},//Hornet,
	{0,0},//Jelly,
	{43,44},//Leaper,
	{0,0},//Scarab,
	{0,0},//Scorpion,
	{0,0},//Slime,
	{0,0},//Spider,
};
m::Vector2 ALIENS_IMAGE_SIZE[(UINT)ALIENS::END]{
	//x, y
	{0,0},//Beetle,
	{0,0},//Blobber,
	{0,0},//Burrower,
	{0,0},//Centipede,
	{0,0},//Crab,
	{0,0},//Digger,
	{0,0},//Firefly,
	{30,48},//Hornet,
	{0,0},//Jelly,
	{42,37},//Leaper,
	{0,0},//Scarab,
	{0,0},//Scorpion,
	{0,0},//Slime,
	{0,0},//Spider,
};
//
int ALIENS_APL_COND[(UINT)ALIENS::END][(UINT)ALIEN_CONDITION::END]{
	//idle, death, emeger, water
	{},//Beetle,
	{},//Blobber,
	{},//Burrower,
	{},//Centipede,
	{},//Crab,
	{},//Digger,
	{1,1,1,1},//Firefly,
	{1,1,1,0},//Hornet,
	{},//Jelly,
	{1,1,1,1},//Leaper,
	{},//Scarab,
	{},//Scorpion,
	{},//Slime,
	{},//Spider,

};
m::Vector2 ALIENS_SIZES[(UINT)ALIENS::END][3]{
	{ALIENS_IDLE_SIZE[0], ALIENS_DEATH_SIZE[0], ALIENS_EMERGE_SIZE[0]},//Beetle,
	{ALIENS_IDLE_SIZE[1], ALIENS_DEATH_SIZE[1], ALIENS_EMERGE_SIZE[1]},//Blobber,
	{ALIENS_IDLE_SIZE[2], ALIENS_DEATH_SIZE[2], ALIENS_EMERGE_SIZE[2]},//Burrower,
	{ALIENS_IDLE_SIZE[3], ALIENS_DEATH_SIZE[3], ALIENS_EMERGE_SIZE[3]},//Centipede,
	{ALIENS_IDLE_SIZE[4], ALIENS_DEATH_SIZE[4], ALIENS_EMERGE_SIZE[4]},//Crab,
	{ALIENS_IDLE_SIZE[5], ALIENS_DEATH_SIZE[5], ALIENS_EMERGE_SIZE[5]},//Digger,
	{ALIENS_IDLE_SIZE[6], ALIENS_DEATH_SIZE[6], ALIENS_EMERGE_SIZE[6]},//Firefly,
	{ALIENS_IDLE_SIZE[7], ALIENS_DEATH_SIZE[7], ALIENS_EMERGE_SIZE[7]},//Hornet,
	{ALIENS_IDLE_SIZE[8], ALIENS_DEATH_SIZE[8], ALIENS_EMERGE_SIZE[8]},//Jelly,
	{ALIENS_IDLE_SIZE[9], ALIENS_DEATH_SIZE[9], ALIENS_EMERGE_SIZE[9]},//Leaper,
	{ALIENS_IDLE_SIZE[10], ALIENS_DEATH_SIZE[10], ALIENS_EMERGE_SIZE[10]},//Scarab,
	{ALIENS_IDLE_SIZE[11], ALIENS_DEATH_SIZE[11], ALIENS_EMERGE_SIZE[11]},//Scorpion,
	{ALIENS_IDLE_SIZE[12], ALIENS_DEATH_SIZE[12], ALIENS_EMERGE_SIZE[12]},//Slime,
	{ALIENS_IDLE_SIZE[13], ALIENS_DEATH_SIZE[13], ALIENS_EMERGE_SIZE[13]},//Spider,
};
int ALIEN_MOVE_RANGE[(UINT)ALIENS::END]{
	3,//Beetle,
	3,//Blobber,
	3,//Burrower,
	3,//Centipede,
	3,//Crab,
	3,//Digger,
	3,//Firefly,
	3,//Hornet,
	3,//Jelly,
	3,//Leaper,
	3,//Scarab,
	3,//Scorpion,
	3,//Slime,
	3,//Spider,

};
int ALIEN_HP[(UINT)ALIENS::END]{
	3,//Beetle,
	3,//Blobber,
	3,//Burrower,
	3,//Centipede,
	3,//Crab,
	3,//Digger,
	3,//Firefly,
	3,//Hornet,
	3,//Jelly,
	3,//Leaper,
	3,//Scarab,
	3,//Scorpion,
	3,//Slime,
	3,//Spider,
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
