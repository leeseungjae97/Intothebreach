#pragma once
#include "mUI.h"
namespace m
{
	class Button :
		public UI
	{
	public:
		Button(const wstring& inner
			, const wstring& background
			, int _sizeUp = 0
			, bool _full = false
			, int _direction = LEFT
			, bool _alphaCheck = false);
		~Button();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
		void SetText(bool _t) {bText = _t; }
		bool GetText() { return bText; }
		void UseTextAlpha(bool _t) { bTextAlpha = _t; }
		void SetTextAlpha(int _a) { textAlpha = _a; }
		void SetMoveScene(SCENE_TYPE _type) { eBtnMoveScene = _type; }
		int GetTextAlpha() { return textAlpha; }

	private:
		wstring btnName;
		SCENE_TYPE eBtnMoveScene;
		bool bText;
		bool bTextAlpha;
		int textAlpha;
	};
}