#pragma once
wstring WEAPONS_FOLDER_PATH[3]{
	L"EnemyWeapons",
	L"passives",
	L"PlayerWeapons"
};

enum class SKILL_T {
	ARC,
	ST,
	END,
};


enum class SKILL_N {
	range,
	machtank,
	punch,
	END,
};
wstring SKILL_PATH[(UINT)SKILL_N::END]{
	L"shotup_tribomb_missile",
	L"shot_mechtank_",
	L"punch1_",
};
enum class SKILL_DIR {
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
wstring MAKE_SKILL_KEY(SKILL_T skill, SKILL_DIR dir) {
	wstring key = L"";

	key.append(SKILL_PATH[(UINT)skill]);
	if (dir != SKILL_DIR::NONE) {
		key.append(SKILL_DIR_PATH[(UINT)dir]);
	}

	return key;
};
wstring MAKE_SKILL_PATH(SKILL_T skill, SKILL_DIR dir) {
	wstring path = L"..\\Resources\\texture\\effect\\";

	path.append(SKILL_PATH[(UINT)skill]);
	if (dir != SKILL_DIR::NONE) {
		path.append(SKILL_DIR_PATH[(UINT)dir]);
	}
	path.append(L".bmp");

	return path;
};