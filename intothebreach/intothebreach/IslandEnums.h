#pragma once
wstring ISLAND_FOLDER_PATH[ISLANDS]{
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
wstring ISLANDS_PATH[ISLANDS]{
   L"island1x_0",
   L"island1x_1",
   L"island1x_2",
   L"island1x_3",
   L"island1x_4",
};
enum class ISLAND_T {
	ISLAND0,
	ISLAND1,
	ISLAND2,
	ISLAND3,
	ISLAND4,
	END
};
m::Vector2 ISLAND_OUTLINE_OFFSET[(UINT)ISLAND_T::END]{
   {0, 0},
   {-8, 18},
   {6, -4},
   {-2, -5},
   {0, 0}
};
m::Vector2 ISLANDS_POS[(UINT)ISLAND_T::END]{
	//{100, 80},
	//{250, 370},
	//{580, 250},
	//{900, 440},
	//{500, 50}
	{150, 80},
	{280, 370},
	{590, 250},
	{910, 440},
	{510, 50}
};
UINT ISLANDS_SECTIONS[(UINT)ISLAND_T::END]{
   8,
   8,
   8,
   8,
   0,
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
m::Vector2* ISLANDS_SECTION_POS[(UINT)ISLAND_T::END]{
	ISLAND0_POS,
	ISLAND1_POS,
	ISLAND2_POS,
	ISLAND3_POS,
};
wstring MAKE_SECTION_KEY(ISLAND_T _type, int sectionIdx) {
	wstring key = L"";

	key.append(ISLAND_FOLDER_PATH[(UINT)_type]);
	if (sectionIdx < 0) key.append(L"island");
	else {
		key.append(ISLANDS_SECTIONS_PATH[(UINT)_type]);
		key.append(std::to_wstring(sectionIdx));
	}
	return key;
};
wstring MAKE_SECTION_PATH(ISLAND_T _type, int sectionIdx) {
	wstring path = L"..\\Resources\\texture\\ui\\inLand\\";
	path.append(ISLAND_FOLDER_PATH[(UINT)_type]);
	if (sectionIdx < 0) {
		path.append(L"island");
	}
	else {
		path.append(ISLANDS_SECTIONS_PATH[(UINT)_type]);
		path.append(std::to_wstring(sectionIdx));
	}
	path.append(L".bmp");

	return path;
};

wstring MAKE_ISLAND_KEY(ISLAND_T _type) {
	wstring key = L"";

	key.append(ISLANDS_PATH[(UINT)_type]);

	return key;
};
wstring MAKE_ISLAND_PATH(ISLAND_T _type) {
	wstring path = L"..\\Resources\\texture\\ui\\selectLand\\";

	path.append(ISLANDS_PATH[(UINT)_type]);
	path.append(L".bmp");

	return path;
};
wstring MAKE_ISLAND_OUTLINE_KEY(ISLAND_T _type) {
	wstring key = L"";

	key.append(ISLAND_FOLDER_PATH[(UINT)_type]);
	key.append(L"island_out.bmp");

	return key;
};
wstring MAKE_ISLAND_OUTLINE_PATH(ISLAND_T _type) {
	wstring path = L"..\\Resources\\texture\\ui\\inLand\\";

	path.append(ISLAND_FOLDER_PATH[(UINT)_type]);
	path.append(L"island_out.bmp");

	return path;
};