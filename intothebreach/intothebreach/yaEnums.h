#pragma once


enum class eSceneType
{
	Title,
	SelectRobot,
	SelectLand,
	Combat,
	Ending,
	Max,
};

enum class eLayerType
{
	BackGround,
	Monster,
	Player,
	Test,
	Effect,
	UI,
	End,
};
enum class eComponentType {
	Transform,
	Collider,
	SpriteRenderer,
	Animator,
	Audio,
	End,
};

enum class BRUSH_TYPE {
	HOLLOW,
	BLACK,
	CUSTOM_BLACK,
	END,
};
enum class PEN_TYPE {
	RED,
	GREEN,
	BLUE,
	END
};