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
enum class MISSION_T
{
	KILL_HORNET,
	KILL_CEN,
	KILL_FF,
	KILL_STAR,
	KILL_5_EN,

	
	PROTECT_RF,
	PROTECT_POWER,
	PROTECT_BAR,
	PROTECT_HQ,
	PROTECT_COAL,
	PROTECT_RESE,
	PROTECT_ESF,

	UNDER_3_GRID_DAMAGE,
	UNDER_4_MECH_DAMAGE,
	BLOCK_3,

	NO_MECH_DAMAGE,
	END,
};
wstring MISSION_TEXT_PATH[(UINT)MISSION_T::END]{
	L"..\\Resources\\texture\\ui\\inLand\\mission\\text_hornet_leader.bmp",
	L"..\\Resources\\texture\\ui\\inLand\\mission\\text_cen_leader.bmp",
	L"..\\Resources\\texture\\ui\\inLand\\mission\\text_firefly_leader.bmp",
	L"..\\Resources\\texture\\ui\\inLand\\mission\\text_star_leader.bmp",
	L"..\\Resources\\texture\\ui\\inLand\\mission\\text_kill_5_en.bmp",

	L"..\\Resources\\texture\\ui\\inLand\\mission\\text_robot_factory_protect.bmp",
	L"..\\Resources\\texture\\ui\\inLand\\mission\\text_power_protect.bmp",
	L"..\\Resources\\texture\\ui\\inLand\\mission\\text_hq_protect.bmp",
	L"..\\Resources\\texture\\ui\\inLand\\mission\\text_coal_protect.bmp",
	L"..\\Resources\\texture\\ui\\inLand\\mission\\text_research_protect.bmp",
	L"..\\Resources\\texture\\ui\\inLand\\mission\\text_esf_protect.bmp",

	L"..\\Resources\\texture\\ui\\inLand\\mission\\text_power_damage_under_3.bmp",
	L"..\\Resources\\texture\\ui\\inLand\\mission\\text_mech_damage_under_4.bmp",
	L"..\\Resources\\texture\\ui\\inLand\\mission\\text_block_bek_3.bmp",

	L"..\\Resources\\texture\\ui\\inLand\\mission\\text_mech_no_damage.bmp",
};
wstring MISSION_TEXT_PATH[4][8][2]{ 
	{
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::KILL_HORNET],
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_HQ],
		},
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::NO_MECH_DAMAGE],
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_COAL],
		},
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::NO_MECH_DAMAGE],
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_RESE],
		},
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::UNDER_4_MECH_DAMAGE],
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_COAL],
		},
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::BLOCK_3],
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_ESF],
		},
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_ESF],
		},
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_COAL],
		},
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::UNDER_3_GRID_DAMAGE],
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_COAL],
		},
	},
	{
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::KILL_FF],
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_HQ],
		},
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_ESF],
		},
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_COAL],
		},
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::UNDER_3_GRID_DAMAGE],
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_COAL],
		},
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::UNDER_3_GRID_DAMAGE],
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_COAL],
		},
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::BLOCK_3],
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_BAR],
		},
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::UNDER_4_MECH_DAMAGE],
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_COAL],
		},
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::UNDER_3_GRID_DAMAGE],
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_POWER],
		},
	},
	{
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::KILL_CEN],
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_HQ],
		},
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::UNDER_3_GRID_DAMAGE],
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_COAL],
		},
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_RF],
		},
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::KILL_5_EN],
		},
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::UNDER_4_MECH_DAMAGE],
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_COAL],
		},
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::BLOCK_3],
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_BAR],
		},
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::NO_MECH_DAMAGE],
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_COAL],
		},
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::UNDER_4_MECH_DAMAGE],
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_COAL],
		},
	},
	{
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::KILL_STAR],
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_HQ],
		},
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::UNDER_4_MECH_DAMAGE],
		},
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::BLOCK_3],
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_BAR],
		},
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::UNDER_4_MECH_DAMAGE],
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_COAL],
		},
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::UNDER_4_MECH_DAMAGE],
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_POWER],
		},
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::NO_MECH_DAMAGE],
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_RESE],
		},
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_COAL],
		},
		{
			MISSION_TEXT_PATH[(UINT)MISSION_T::UNDER_3_GRID_DAMAGE],
			MISSION_TEXT_PATH[(UINT)MISSION_T::PROTECT_COAL],
		},
	},
};
int MISSION_REWARD[4][8][2]{
	// star, grid
	{
		{2, 0},// mission_final
		{1, 1},// mission_1
		{1, 1},// mission_2
		{1, 1},// mission_3
		{1, 0},// mission_4
		{0, 1},// mission_5
		{0, 1},// mission_6
		{1, 1},// mission_7
	},

	{
		{2, 0},// mission_final
		{0, 1},// mission_1
		{0, 1},// mission_2
		{1, 1},// mission_3
		{1, 1},// mission_4
		{2, 0},// mission_5
		{1, 1},// mission_6
		{1, 2},// mission_7
	},

	{
		{2, 0},// mission_final
		{1, 1},// mission_1
		{2, 0},// mission_2
		{1, 0},// mission_3
		{1, 1},// mission_4
		{2, 0},// mission_5
		{1, 1},// mission_6
		{1, 1},// mission_7
	},

	{
		{2, 0},// mission_final
		{1, 0},// mission_1
		{2, 0},// mission_2
		{1, 1},// mission_3
		{1, 2},// mission_4
		{1, 1},// mission_5
		{0, 2},// mission_6
		{1, 1},// mission_7
	},
};
wstring MAKE_MISSION_KEY(int land, int mission)
{
	return L"..\\Resources\\texture\\ui\\inLand\\mission\\" + MISSION_LANDS[land] + MISSION_PREVIEW_PATH[mission];
}
wstring MAKE_MISSION_PATH(int land, int mission)
{
	return L"..\\Resources\\texture\\ui\\inLand\\mission\\" + MISSION_LANDS[land] + MISSION_PREVIEW_PATH[mission] + L".bmp";
}