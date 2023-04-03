#pragma once
#include "mUI.h"
namespace m
{
	class Button :
		public UI
	{
	public:
		Button(const wstring& key
			, const wstring& path
			, int _sizeUp = 0
			, bool _full = false
			, int _direction = LEFT
			, bool _alphaCheck = false);
		~Button();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();


	private:
	};
}