#include "mEffect.h"
namespace m
{
	mEffect::mEffect()
	{
		for (int i = 0; i < (UINT)DIR_EFFECT_T::END; i++)
		{
			DIR_EFFECT_T_PATH[i];
		}
	}
	mEffect::~mEffect()
	{}
	void mEffect::Initialize()
	{}
	void mEffect::Update()
	{}
	void mEffect::Render(HDC hdc)
	{}
	void mEffect::Release()
	{}
}