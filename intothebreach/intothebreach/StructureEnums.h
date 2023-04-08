#pragma once
enum class STRUCTURES {
	airfield,
	bar,
	battry,
	energy,
	factory,
	hospital,
	military,
	power,
	radar,
	recycle,
	research,
	shield,
	solar,
	supply,
	timelab,
	tower,
	wind,
	train,
	END,
};
wstring STRUCTURES_PATH[(UINT)STRUCTURES::END]{
	L"str_airfield1_",
	L"str_bar1_",
	L"str_battery1_",
	L"str_energy1_",
	L"str_factory1_",
	L"str_hospital1_",
	L"str_military1_",
	L"str_power1_",
	L"str_radar1_",
	L"str_recycle1_",
	L"str_research1_",
	L"str_shield1_",
	L"str_solar1_",
	L"str_supply1_",
	L"str_timelab1_",
	L"str_tower1_",
	L"str_wind1_",
	L"train1_",
};
m::Vector2 STRUCTURES_OFFSET[(UINT)STRUCTURES::END]{
	{11.f,-17.f},//L"str_airfield1_",
	{12.f,-7.f},//L"str_bar1_",
	{6.f,-25.f},//L"str_battery1_",
	{5.f,0.f},//L"str_energy1_",
	{5.f,0.f},//L"str_factory1_",
	{5.f,0.f},//L"str_hospital1_",
	{5.f,0.f},//L"str_military1_",
	{5.f,0.f},//L"str_power1_",
	{5.f,0.f},//L"str_radar1_",
	{5.f,0.f},//L"str_recycle1_",
	{5.f,0.f},//L"str_research1_",
	{5.f,0.f},//L"str_shield1_",
	{5.f,0.f},//L"str_solar1_",
	{5.f,0.f},//L"str_supply1_",
	{5.f,0.f},//L"str_timelab1_",
	{30.f,-45.f},//L"str_tower1_",
	{5.f,0.f},//L"str_wind1_",
	{5.f,0.f},//L"train1_",
};
enum class STRUCTURES_CONDITION_T
{
	Broken,
	Off,
	On,
	END,
};
wstring STRUCTURES_CON_PATH[(UINT)STRUCTURES_CONDITION_T::END]{
	L"broken",
	L"off",
	L"on",
};
m::Vector2 STRUCTURE_OFFSET[(UINT)STRUCTURES::END]{
	
};
wstring MAKE_UNIT_KEY(STRUCTURES _st, STRUCTURES_CONDITION_T _cond)
{
	wstring key = L"";

	key.append(STRUCTURES_PATH[(UINT)_st]);
	key.append(STRUCTURES_CON_PATH[(UINT)_cond]);

	return key;
};
wstring MAKE_UNIT_PATH(STRUCTURES _st, STRUCTURES_CONDITION_T _cond)
{
	wstring path = L"..\\Resources\\texture\\structures\\";
	path.append(STRUCTURES_PATH[(UINT)_st]);
	path.append(STRUCTURES_CON_PATH[(UINT)_cond]);
	path.append(L".bmp");

	return path;
};