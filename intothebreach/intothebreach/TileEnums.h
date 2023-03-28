#pragma once
enum class TILE_HEAD_T {
	ground,
	forest,
	building,
	building_water,
	building_collapse,
	mountain,
	mountain_broken,
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
};
enum class TILE_T {
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
wstring MAKE_TILE_KEY(TILE_T _type, TILE_HEAD_T _type2) {
	wstring key = L"";

	key.append(TILE_PATH[(UINT)_type]);
	key.append(TILE_HEAD_PATH[(UINT)_type2]);


	return key;
}
wstring MAKE_TILE_PATH(TILE_T _type, TILE_HEAD_T _type2) {
	wstring path = L"..\\Resources\\texture\\terrain\\";

	path.append(TILE_PATH[(UINT)_type]);
	path.append(TILE_HEAD_PATH[(UINT)_type2]);

	path.append(L".bmp");

	return path;
}

enum class MOVE_TILE_T {
	square,
	square_g,
	square_r,
	square_gy,
	square_b,
	square_w,
	square_y_line,
	square_g_line,
	square_g_l,
	square_g_r,
	square_g_u,
	square_g_d,
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
wstring ARROW_TILE_PATH[(UINT)ARROW_TILE_T::END]{
	L"arrow_right",
	L"arrow_up",
	L"arrow_down",
	L"arrow_left",
	L"arrow_y_right",
	L"arrow_y_up",
	L"arrow_y_down",
	L"arrow_y_left",
	L"arrow_g_right",
	L"arrow_g_up",
	L"arrow_g_down",
	L"arrow_g_left",
	L"arrow_h_right",
	L"arrow_h_up",
	L"arrow_h_down",
	L"arrow_h_left",
};
wstring MAKE_ARROW_TILE_KEY(ARROW_TILE_T _type)
{
	wstring key = L"";

	key.append(ARROW_TILE_PATH[(UINT)_type]);

	return key;
}
wstring MAKE_ARROW_TILE_PATH(ARROW_TILE_T _type)
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
	L"square_gy",
	L"square_b",
	L"square_w",
	L"square_y_line",
	L"square_g_line",
	L"square_line_g_l",
	L"square_line_g_r",
	L"square_line_g_u",
	L"square_line_g_d",
};
wstring MAKE_MOVE_TILE_KEY(MOVE_TILE_T _type) {
	wstring key = L"";

	key.append(MOVE_TILE_PATH[(UINT)_type]);


	return key;
}
wstring MAKE_MOVE_TILE_PATH(MOVE_TILE_T _type) {
	wstring path = L"..\\Resources\\texture\\combat\\move\\";

	path.append(MOVE_TILE_PATH[(UINT)_type]);

	path.append(L".bmp");

	return path;
}
enum class MOVE_ARROW_T {
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
wstring MAKE_MOVE_ARROW_TILE_KEY(MOVE_ARROW_T _type) {
	wstring key = L"";

	key.append(MOVE_ARROW_PATH[(UINT)_type]);

	return key;
}
wstring MAKE_MOVE_ARROW_TILE_PATH(MOVE_ARROW_T _type) {
	wstring path = L"..\\Resources\\texture\\combat\\";

	path.append(MOVE_ARROW_PATH[(UINT)_type]);

	path.append(L".bmp");

	return path;
};