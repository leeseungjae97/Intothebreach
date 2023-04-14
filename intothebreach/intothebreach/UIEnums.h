#pragma once
enum class UI_TEXT
{
	CN_TEXT,
	NS_TEXT,
	COF_TEXT,
	E_TEXT,
	T_TEXT,
	WARN_TEXT,
	WARN_A_TEXT,
	END,
};
wstring UI_TEXT_PATH[(UINT)UI_TEXT::END]{
	L"..\\Resources\\texture\\ui\\title\\continue_text.bmp",
	L"..\\Resources\\texture\\ui\\title\\new_start_text.bmp",
	L"..\\Resources\\texture\\ui\\title\\config_text.bmp",
	L"..\\Resources\\texture\\ui\\title\\end_text.bmp",
	L"..\\Resources\\texture\\ui\\title\\tool_text.bmp",
	L"..\\Resources\\texture\\combat\\icons\\warn_emerge.bmp",
	L"..\\Resources\\texture\\combat\\icons\\warn_enemy_activity.bmp",
};
enum class LINE_T
{
	RED_POINT,
	RED_UNDERLINE,
	RED_SQUARELINE,
	END,
};
wstring UNDERLINE_PATH[(UINT)LINE_T::END]{
	L"..\\Resources\\texture\\combat\\icons\\warn_line1.bmp"
	L"..\\Resources\\texture\\combat\\icons\\warn_line2.bmp",
	L"..\\Resources\\texture\\combat\\icons\\warn_spawn_tile_red.bmp",
};