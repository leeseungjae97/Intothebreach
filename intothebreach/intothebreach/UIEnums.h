#pragma once
wstring A_BTN_BACK = L"..\\Resources\\texture\\ui\\in_btn.bmp";
wstring A_BTN_SELECT_BACK = L"..\\Resources\\texture\\ui\\select_btn.bmp";
wstring NO_BACK = L"..\\Resources\\texture\\ui\\no_back.bmp";
wstring TURN_BACK = L"..\\Resources\\texture\\ui\\combat\\turn_box.bmp";
wstring ALPHA_BACK = L"..\\Resources\\texture\\ui\\btnBack.bmp";
enum class TITLE_UI_TEXT
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
wstring TITLE_UI_TEXT_PATH[(UINT)TITLE_UI_TEXT::END]{
	L"..\\Resources\\texture\\ui\\title\\continue_text.bmp",
	L"..\\Resources\\texture\\ui\\title\\new_start_text.bmp",
	L"..\\Resources\\texture\\ui\\title\\config_text.bmp",
	L"..\\Resources\\texture\\ui\\title\\end_text.bmp",
	L"..\\Resources\\texture\\ui\\title\\tool_text.bmp",
	L"..\\Resources\\texture\\combat\\icons\\warn_emerge.bmp",
	L"..\\Resources\\texture\\combat\\icons\\warn_enemy_activity.bmp",
};
enum class COMBAT_UI_TEXT
{
	CON_TEXT,
	DEPLOY_TEXT,
	DEPLOYING_TEXT,
	TURN_TEXT,
	TURN_NUM_5,
	TURN_NUM_4,
	TURN_NUM_3,
	TURN_NUM_2,
	TURN_NUM_1,
	END,
};
wstring COMBAT_UI_TEXT_PATH[(UINT)COMBAT_UI_TEXT::END]{
	L"..\\Resources\\texture\\ui\\combat\\confirm_text.bmp",
	L"..\\Resources\\texture\\ui\\combat\\deploy_text.bmp",
	L"..\\Resources\\texture\\ui\\combat\\deploying_text.bmp",
	L"..\\Resources\\texture\\ui\\combat\\towin_text.bmp",
	L"..\\Resources\\texture\\ui\\combat\\turn_num5.bmp",
	L"..\\Resources\\texture\\ui\\combat\\turn_num4.bmp",
	L"..\\Resources\\texture\\ui\\combat\\turn_num3.bmp",
	L"..\\Resources\\texture\\ui\\combat\\turn_num2.bmp",
	L"..\\Resources\\texture\\ui\\combat\\turn_num1.bmp",
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