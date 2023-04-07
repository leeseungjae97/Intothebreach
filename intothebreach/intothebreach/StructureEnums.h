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
	L"str_airfield_",
	L"str_bar_",
	L"str_battry_",
	L"str_energy_",
	L"str_factory_",
	L"str_hospital_",
	L"str_military_",
	L"str_power_",
	L"str_radar_",
	L"str_recycle_",
	L"str_research_",
	L"str_shield_",
	L"str_solar_",
	L"str_supply_",
	L"str_timelab_",
	L"str_tower_",
	L"str_wind_",
	L"train_",
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