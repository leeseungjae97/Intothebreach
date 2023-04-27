#pragma once
enum class PILOT_T
{
	Pilot_Artificial,
	Pilot_Original,
	Pilot_Ice,
	Pilot_Sand,
	Pilot_Genius,
	Pilot_Leader,
	Pilot_Assassin,
	END,
};
wstring PILOT_PATH[(UINT)PILOT_T::END]{
	L"..\\Resources\\texture\\pilot\\Pilot_Artificial.bmp",
	L"..\\Resources\\texture\\pilot\\Pilot_Original.bmp",
	L"..\\Resources\\texture\\pilot\\ice1.bmp",
	L"..\\Resources\\texture\\pilot\\sand1.bmp",
	L"..\\Resources\\texture\\pilot\\Pilot_Genius.bmp",
	L"..\\Resources\\texture\\pilot\\Pilot_Leader.bmp",
	L"..\\Resources\\texture\\pilot\\Pilot_Assassin.bmp",
};