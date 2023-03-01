#pragma once
#include "_Engine.h"

namespace m
{
	enum class KEYCODE_TYPE
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,
		END,
	};

	enum class KEY_STATE
	{
		DOWN,
		PRESSED,
		UP,
		NONE,
	};

	class Input
	{
	public:
		struct Key
		{
			KEYCODE_TYPE key;
			KEY_STATE state;
			bool bPressed;
		};

		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		inline static KEY_STATE GetKeyState(KEYCODE_TYPE keyCode)
		{
			return mKeys[(UINT)keyCode].state;
		};

	private:
		static std::vector<Key> mKeys;
	};
}
