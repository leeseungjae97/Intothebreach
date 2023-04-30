#pragma once
#include "def.h"
#include "mMath.h"
#include "CommonInclude.h"
#include "BattleFieldEnums.h"
#include "MissionEnums.h"
#include "MechEnums.h"
#include "AlienEnums.h"
#include "IslandEnums.h"
#include "TileEnums.h"
#include "StructureEnums.h"
#include "SkillEnums.h"
#include "UIEnums.h"
#include "EffectEnums.h"
#include "UnitEnums.h"
#include "PilotEnums.h"
enum class SCENE_TYPE
{
	IN_LAND0,
	IN_LAND1,
	IN_LAND2,
	IN_LAND3,
	IN_LAND4,
	INTRO,
	TITLE,
	SELECT_ROBOT,
	SELECT_LAND,
	COMBAT,
	ENDING,
	END,
};

enum class LAYER_TYPE
{
	FUNCTIONCAL_BACK,
	BACKGROUND,
	TILE_0,
	TILE,
	TERRAIN,
	STRUCT,
	MONSTER,
	PLAYER,
	CLONE,
	TILE_HEAD,
	EFFECT,
	SKILL,
	UI,
	FRONT_UI,
	DRAG_PI,
	DRAG_WE,
	END,
};
enum class PLAYERINFO_TYPE {
	SKILL,
	WEAPON,
	PILOT,
	END
};
enum class COMPONENT_TYPE {
	TRANSFORM,
	COLLIDER,
	SPRITERENDERER,
	ANIMATOR,
	//AUDIO,
	END,
};
enum class BRUSH_TYPE {
	HOLLOW,
	BLACK,
	CUSTOM_BLACK,
	GRAY,
	GREEN,
	END,
};
enum class PEN_TYPE {
	RED,
	GREEN,
	BLUE,
	END
};
enum class BTN_TYPE
{
	NONE,
	DRAG_PI,
	DRAG_WE,
	DRAG,
	END
};