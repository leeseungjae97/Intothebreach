#pragma once
#include "mUnit.h"
namespace m
{
	class Bomb :
		public Unit
	{
	public:
		enum class BOMB_S
		{
			Idle,
			Broken,
			Blink,
			END,
		};

		Bomb(Vector2 _coord);
		~Bomb();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void idle() override;
		virtual void broken() override;

		void SetBombState(BOMB_S _state) { bombState = _state; }
		void SetDeath(bool _b) { bDeath = _b; }

		BOMB_S GetBombState() { return bombState; }
		bool GetDeath() { return bDeath; }
	private:
		wstring BOMB_S_PATH[(UINT)BOMB_S::END]{
			L"..\\Resources\\texture\\units\\mission\\bomb.bmp",
			L"..\\Resources\\texture\\units\\mission\\bomb_death.bmp",
			L"..\\Resources\\texture\\units\\mission\\bomb2.bmp",
		};
		wstring BOMB_S_KEY[(UINT)BOMB_S::END]{
			L"bidle",
			L"bdeath",
			L"bblink",

		};
		bool bDeath;
		BOMB_S bombState;
		int iConstant;
		int idVar;
		int idDir;
	};
}


