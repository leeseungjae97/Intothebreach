#pragma once
enum class DIR_EFFECT_T
{
	ap_r,
	ap_u,
	ap_d,
	ap_l,
	pun_r,
	pun_u,
	pun_d,
	pun_l,
	st_r,
	st_u,
	st_d,
	st_l,
	st_firefly1_r,
	st_firefly1_u,
	st_firefly1_d,
	st_firefly1_l,
	hornet1_r,
	hornet1_u,
	hornet1_d,
	hornet1_l,
	leaper1_r,
	leaper1_u,
	leaper1_d,
	leaper1_l,
	END,
};
enum class SINGLE_EFFECT_T
{
	ar_s,
	ac_s,
	f_s,
	END,
};
enum class IMMO_EFFECT_T
{
	ep_ar0,
	ep_ar1,
	ep_ar2,
	ep_firefly1,
	END,
};
wstring IMMO_EFFECT_T_PATH[(UINT)IMMO_EFFECT_T::END]{
	L"explo_artillery0",
	L"explo_artillery1",
	L"explo_artillery2",
	L"explo_firefly1",
};
wstring SINGLE_EFFECT_T_PATH[(UINT)SINGLE_EFFECT_T::END]{
	L"art_smoke",
	L"acid_smoke",
	L"fireball_smoke",
};
wstring EFFECT_DIR_PATH[4]{
	L"_0",
	L"_1",
	L"_2",
	L"_3",
};
wstring DIR_EFFECT_T_PATH[(UINT)DIR_EFFECT_T::END]{
	L"airpush_R",
	L"airpush_U",
	L"airpush_D",
	L"airpush_L",
	L"punch1_R",
	L"punch1_U",
	L"punch1_D",
	L"punch1_L",
	L"explo_push2_R",
	L"explo_push2_U",
	L"explo_push2_D",
	L"explo_push2_L",
	L"shot_firefly_R",
	L"shot_firefly_U",
	L"shot_firefly_D",
	L"shot_firefly_L",
	L"hornet_R",
	L"hornet_U",
	L"hornet_D",
	L"hornet_L",
};
m::Vector2 DIR_EFFECT_T_OFFSET[(UINT)DIR_EFFECT_T::END]{
	{20.f, 20.f},//{-20.f,-20.f},//L"airpush_R",
	{30.f, -15.f},//{0.f,0.f},//L"airpush_U",
	{-20.f,25.f},//{-5.f, 20.f},//L"airpush_D",
	{-10.f, -10.f},//{-5.f, 5.f},//L"airpush_L",
	{},//L"punch1_R",
	{},//L"punch1_D",
	{},//L"punch1_U",
	{},//L"punch1_L",
	{},//L"explo_push2_R",
	{},//L"explo_push2_U",
	{},//L"explo_push2_D",
	{},//L"explo_push2_L",
	{},//L"shot_firefly_R",
	{},//L"shot_firefly_U",
	{},//L"shot_firefly_D",
	{},//L"shot_firefly_L",
	{-20, -35.f},//L"hornet_R",
	{-5, -30.f},//L"hornet_U",
	{5, -30.f},//L"hornet_D",
	{20, -30.f},//L"hornet_L",
};
m::Vector2 IMMO_EFFECT_T_OFFSET[(UINT)IMMO_EFFECT_T::END]{
	{10.f, -5.f},
	{10.f, -5.f},
	{10.f, -5.f},
};
int DIR_EFFECT_T_LEN[(UINT)DIR_EFFECT_T::END]{
	8,
	8,
	8,
	8,
	6,
	6,
	6,
	6,
	9,
	9,
	9,
	9,
	1,
	1,
	1,
	1,
	12,
	12,
	12,
	12,
};
int IMMO_EFFECT_T_LEN[(UINT)IMMO_EFFECT_T::END]{
	10,
	10,
	10,
	8,
};
wstring MAKE_EFFECT_KEY(DIR_EFFECT_T _type) { return DIR_EFFECT_T_PATH[(UINT)_type]; }
wstring MAKE_EFFECT_KEY(SINGLE_EFFECT_T _type) { return SINGLE_EFFECT_T_PATH[(UINT)_type]; }
wstring MAKE_EFFECT_KEY(SINGLE_EFFECT_T _type, int i) { 

	return SINGLE_EFFECT_T_PATH[(UINT)_type] + EFFECT_DIR_PATH[i];
}

wstring MAKE_EFFECT_KEY(IMMO_EFFECT_T _type) { return IMMO_EFFECT_T_PATH[(UINT)_type]; }
int GET_LEN(DIR_EFFECT_T _type) { return DIR_EFFECT_T_LEN[(UINT)_type]; }
int GET_LEN(IMMO_EFFECT_T _type) { return IMMO_EFFECT_T_LEN[(UINT)_type]; }
wstring MAKE_EFFECT_PATH(DIR_EFFECT_T _type) { return L"..\\Resources\\texture\\effect\\" + DIR_EFFECT_T_PATH[(UINT)_type] + L".bmp"; }
wstring MAKE_EFFECT_PATH(SINGLE_EFFECT_T _type) { return L"..\\Resources\\texture\\effect\\ac_smoke\\" + SINGLE_EFFECT_T_PATH[(UINT)_type] + L".bmp"; }
wstring MAKE_EFFECT_PATH(SINGLE_EFFECT_T _type, int i) { 
	return L"..\\Resources\\texture\\effect\\ac_smoke\\" 
		+ SINGLE_EFFECT_T_PATH[(UINT)_type]
		+ EFFECT_DIR_PATH[i]
		+ L".bmp"; 
}
wstring MAKE_EFFECT_PATH(IMMO_EFFECT_T _type) { return L"..\\Resources\\texture\\effect\\" + IMMO_EFFECT_T_PATH[(UINT)_type] + L".bmp"; }
