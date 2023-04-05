#pragma once
enum class UI_TEXT
{
	CN_TEXT,
	NS_TEXT,
	COF_TEXT,
	E_TEXT,
	T_TEXT,
	END,
};
wstring UI_TEXT_PATH[(UINT)UI_TEXT::END]{
	L"..\\Resources\\texture\\ui\\title\\continue_text.bmp",
	L"..\\Resources\\texture\\ui\\title\\new_start_text.bmp",
	L"..\\Resources\\texture\\ui\\title\\config_text.bmp",
	L"..\\Resources\\texture\\ui\\title\\end_text.bmp",
	L"..\\Resources\\texture\\ui\\title\\tool_text.bmp",
};