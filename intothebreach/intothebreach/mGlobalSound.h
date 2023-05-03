#pragma once
#include "_Engine.h"
namespace m
{
	class Sound;
	class GlobalSound
	{
	public:
		static void InitSound();
		static void AllStop();
		static Sound* titleTheme;
	private:
	};
}


