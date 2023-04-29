#pragma once

wstring MISSION_LANDS[4]{
	L"land0\\",
	L"land1\\",
	L"land2\\",
	L"land3\\",
};
wstring MISSION_PREVIEW_PATH[8]{
	L"mission_final",
	L"mission1",
	L"mission2",
	L"mission3",
	L"mission4",
	L"mission5",
	L"mission6",
	L"mission7",
};
wstring MAKE_MISSION_KEY(int land, int mission)
	{return L"..\\Resources\\texture\\ui\\inLand\\mission\\" + MISSION_LANDS[land] + MISSION_PREVIEW_PATH[mission];}
wstring MAKE_MISSION_PATH(int land, int mission)
	{return L"..\\Resources\\texture\\ui\\inLand\\mission\\" + MISSION_LANDS[land] + MISSION_PREVIEW_PATH[mission] + L".bmp";}