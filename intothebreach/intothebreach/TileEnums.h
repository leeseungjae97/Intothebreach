#pragma once
enum class TILE_HEAD_T
{
	ground,
	forest,
	building,
	building_water,
	building_collapse,
	mountain,
	mountain_broken,
	mountain_explode,
	END,
};
wstring TILE_HEAD_PATH[(UINT)TILE_HEAD_T::END]{
	L"ground_0",
	L"forest_0",
	L"building_sheet",
	L"building_sheet_water",
	L"building_collapse",
	L"mountain_0",
	L"mountain_0_broken",
	L"mountain_explode",
};
m::Vector2 TILE_OFFSET[(UINT)TILE_HEAD_T::END]{
	//{47.f, -18.f},
	{47.f, -18.f},
	{47.f, -18.f},
	{47.f, -18.f},
	{47.f, -18.f},
	{47.f, -18.f},
};
enum class TILE_T
{
	GREEN,
	SAND,
	SNOW,
	ACID,
	VOLCANO,
	CAVE,
	COMMON,
	MOVE_RANGE,
	PLAYER,
	MONSTER,
	END,
};
wstring TILE_PATH[(UINT)TILE_T::END]{
   L"green\\",
   L"sand\\",
   L"snow\\",
   L"acid\\",
   L"volcano\\",
   L"cave\\",
   L""
};
wstring MAKE_DUST_KEY(TILE_T _type, int i) { 

	return TILE_PATH[(UINT)_type] + L"dust" +(i == 0 ? L"_f" : L"") + L".bmp";
}
wstring MAKE_DUST_PATH(TILE_T _type, int i ) { 
	return L"..\\Resources\\texture\\terrain\\" + TILE_PATH[(UINT)_type] + L"dust" + (i == 0 ? L"_f" : L"") + L".bmp";
}
wstring MAKE_TILE_KEY(TILE_T _type, TILE_HEAD_T _type2)
{
	wstring key = L"";

	key.append(TILE_PATH[(UINT)_type]);
	key.append(TILE_HEAD_PATH[(UINT)_type2]);


	return key;
}
wstring MAKE_TILE_PATH(TILE_T _type, TILE_HEAD_T _type2)
{
	wstring path = L"..\\Resources\\texture\\terrain\\";

	path.append(TILE_PATH[(UINT)_type]);
	path.append(TILE_HEAD_PATH[(UINT)_type2]);

	path.append(L".bmp");

	return path;
}
enum class ARROW_ETC_T
{
	push_box,
	push_y_box,
	END,
};
wstring ARROW_ETC_PATH[(UINT)ARROW_ETC_T::END]{
	L"push_box_g",
	L"push_box_y",
};

wstring MAKE_TILE_KEY(ARROW_ETC_T _type) { return ARROW_ETC_PATH[(UINT)_type]; }
wstring MAKE_TILE_PATH(ARROW_ETC_T _type) { return L"..\\Resources\\texture\\combat\\" + ARROW_ETC_PATH[(UINT)_type] + L".bmp"; }

enum class MOVE_TILE_T
{
	square,
	square_g,
	square_r,
	square_y,
	square_gy,
	square_b,
	square_w,
	square_y_line,
	square_g_line,
	square_g_l,
	square_g_r,
	square_g_u,
	square_g_d,
	square_r_l,
	square_r_r,
	square_r_u,
	square_r_d,
	square_y_l,
	square_y_r,
	square_y_u,
	square_y_d,
	END
};
enum class ARROW_TILE_T
{
	arrow_right,
	arrow_up,
	arrow_down,
	arrow_left,
	arrow_y_right,
	arrow_y_up,
	arrow_y_down,
	arrow_y_left,
	arrow_g_right,
	arrow_g_up,
	arrow_g_down,
	arrow_g_left,
	arrow_h_right,
	arrow_h_up,
	arrow_h_down,
	arrow_h_left,
	END
};
m::Vector2 DIRECTION_[4]{
	{1, 0},
	{0, -1},
	{0, 1},
	{-1, 0},
};
wstring ARROW_TILE_PATH[(UINT)ARROW_TILE_T::END]{
	L"arrow_off_right",
	L"arrow_off_up",
	L"arrow_off_down",
	L"arrow_off_left",
	L"arrow_right",
	L"arrow_up",
	L"arrow_down",
	L"arrow_left",
	L"arrow_guard_right",
	L"arrow_guard_up",
	L"arrow_guard_down",
	L"arrow_guard_left",
	L"arrow_hit_right",
	L"arrow_hit_up",
	L"arrow_hit_down",
	L"arrow_hit_left",
};
m::Vector2 ARROW_TILE_OFFSET[(UINT)ARROW_TILE_T::END]{
	{30.f, 25.f},//{8.f , 8.f},//L"arrow_off_right",
	{30.f, -25.f},//{0, -40.f},//L"arrow_off_up",
	{-30.f, 25.f},//{-58.f, 5.f},//L"arrow_off_down",
	{-30.f, -25.f},//{-55.f, -45.f},//L"arrow_off_left",
	{30.f, 25.f},//L"arrow_right",
	{30.f, -25.f},//L"arrow_up",
	{-30.f, 25.f},//L"arrow_down",
	{-30.f, -25.f},//L"arrow_left",
	{30.f, 25.f},//L"arrow_guard_right",
	{30.f, -25.f},//L"arrow_guard_up",
	{-30.f, 25.f},//L"arrow_guard_down",
	{-30.f, -25.f},//L"arrow_guard_left",
	{30.f, 25.f},//L"arrow_hit_right",
	{30.f, -25.f},//L"arrow_hit_up",
	{-30.f, 25.f},//L"arrow_hit_down",
	{-30.f, -25.f},//L"arrow_hit_left",
};
m::Vector2 ARROW_TILE_DIRECTION[(UINT)ARROW_TILE_T::END]{
	DIRECTION_[RIGHT_NUM],//L"arrow_off_right",
	DIRECTION_[UP_NUM],//L"arrow_off_up",
	DIRECTION_[DOWN_NUM],//L"arrow_off_down",
	DIRECTION_[LEFT_NUM],//L"arrow_off_left",
	DIRECTION_[RIGHT_NUM],//L"arrow_right",
	DIRECTION_[UP_NUM],//L"arrow_up",
	DIRECTION_[DOWN_NUM],//L"arrow_down",
	DIRECTION_[LEFT_NUM],//L"arrow_left",
	DIRECTION_[RIGHT_NUM],//L"arrow_guard_right",
	DIRECTION_[UP_NUM],//L"arrow_guard_up",
	DIRECTION_[DOWN_NUM],//L"arrow_guard_down",
	DIRECTION_[LEFT_NUM],//L"arrow_guard_left",
	DIRECTION_[RIGHT_NUM],//L"arrow_hit_right",
	DIRECTION_[UP_NUM],//L"arrow_hit_up",
	DIRECTION_[DOWN_NUM],//L"arrow_hit_down",
	DIRECTION_[LEFT_NUM],//L"arrow_hit_left",
};
wstring MAKE_TILE_KEY(ARROW_TILE_T _type)
{
	wstring key = L"";
	key.append(ARROW_TILE_PATH[(UINT)_type]);

	return key;
}
wstring MAKE_TILE_PATH(ARROW_TILE_T _type)
{
	wstring path = L"..\\Resources\\texture\\combat\\";

	path.append(ARROW_TILE_PATH[(UINT)_type]);

	path.append(L".bmp");

	return path;
}
wstring MOVE_TILE_PATH[(UINT)MOVE_TILE_T::END]{
	L"square",
	L"square_g",
	L"square_r",
	L"square_y",
	L"square_gy",
	L"square_b",
	L"square_w",
	L"square_y_line",
	L"square_g_line",
	L"square_line_g_l",
	L"square_line_g_r",
	L"square_line_g_u",
	L"square_line_g_d",
	L"square_line_r_l",
	L"square_line_r_r",
	L"square_line_r_u",
	L"square_line_r_d",
	L"square_line_y_l",
	L"square_line_y_r",
	L"square_line_y_u",
	L"square_line_y_d",
};
wstring MAKE_TILE_KEY(MOVE_TILE_T _type)
{
	wstring key = L"";

	key.append(MOVE_TILE_PATH[(UINT)_type]);


	return key;
}
wstring MAKE_TILE_PATH(MOVE_TILE_T _type)
{
	wstring path = L"..\\Resources\\texture\\combat\\move\\";

	path.append(MOVE_TILE_PATH[(UINT)_type]);

	path.append(L".bmp");

	return path;
}
enum class MOVE_ARROW_T
{
	ARROW_D_U,
	ARROW_L_R,
	ARROW_L,
	ARROW_R,
	ARROW_U,
	ARROW_D,
	ARROW_COR_L_D,
	ARROW_COR_L_U,
	ARROW_COR_R_D,
	ARROW_COR_R_U,
	ARROW_ST_D,
	ARROW_ST_U,
	ARROW_ST_L,
	ARROW_ST_R,

	END
};
wstring MOVE_ARROW_PATH[(UINT)MOVE_ARROW_T::END]{
	L"movearrow_du",
	L"movearrow_lr",
	L"movearrow_l",
	L"movearrow_r",
	L"movearrow_u",
	L"movearrow_d",
	L"movearrow_corner4",
	L"movearrow_corner2",
	L"movearrow_corner1",
	L"movearrow_corner3",
	L"movearrow_cap_d",
	L"movearrow_cap_u",
	L"movearrow_cap_l",
	L"movearrow_cap_r",

};
wstring MAKE_TILE_KEY(MOVE_ARROW_T _type)
{
	wstring key = L"";

	key.append(MOVE_ARROW_PATH[(UINT)_type]);

	return key;
}
wstring MAKE_TILE_PATH(MOVE_ARROW_T _type)
{
	wstring path = L"..\\Resources\\texture\\combat\\move\\";

	path.append(MOVE_ARROW_PATH[(UINT)_type]);

	path.append(L".bmp");

	return path;
};
enum class COMBAT_TILE_T
{
	pb,
	pb_y,
	pb_g,
	fire1,
	END,
};
enum class COMBAT_ANIM_TILE_T
{
	warning_sprite,
	END,
};
m::Vector2 COMBAT_ANIM_TIME_OFFSET[(UINT)COMBAT_ANIM_TILE_T::END]{
	{30, 23},
};
wstring COMBAT_ANIM_TILE_PATH[(UINT)COMBAT_ANIM_TILE_T::END]{
	L"warningstripes",
};
wstring MAKE_TILE_KEY(COMBAT_ANIM_TILE_T _type)
{
	wstring key = L"";

	key.append(COMBAT_ANIM_TILE_PATH[(UINT)_type]);

	return key;
}
wstring MAKE_TILE_PATH(COMBAT_ANIM_TILE_T _type)
{
	wstring path = L"..\\Resources\\texture\\combat\\";

	path.append(COMBAT_ANIM_TILE_PATH[(UINT)_type]);

	path.append(L".bmp");

	return path;
};
m::Vector2 COMBAT_ANIM_TILE_SIZE[(UINT)COMBAT_ANIM_TILE_T::END]{

};
UINT COMBAT_ANIM_TILE_LEN[(UINT)COMBAT_ANIM_TILE_T::END]
{
	6,
};
wstring COMBAT_TILE_PATH[(UINT)COMBAT_TILE_T::END]{
	L"push_box",
	L"push_box_y",
	L"push_box_g",
	L"fire_sprite4"
};
wstring MAKE_TILE_KEY(COMBAT_TILE_T _type)
{
	wstring key = L"";

	key.append(COMBAT_TILE_PATH[(UINT)_type]);

	return key;
}
wstring MAKE_TILE_PATH(COMBAT_TILE_T _type)
{
	wstring path = L"..\\Resources\\texture\\combat\\";

	path.append(COMBAT_TILE_PATH[(UINT)_type]);

	path.append(L".bmp");

	return path;
};