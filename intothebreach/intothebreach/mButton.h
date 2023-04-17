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
		void SetText(bool _t) { bText = _t; }
		bool GetText() { return bText; }
		bool GetClicked() { return bClicked; }
		void ChangeText(const wstring& _path) { btnName = _path; }
		wstring GetBtnName() { return btnName; }
		Vector2 GetTextPos() { return textPos; }
		void UseTextAlpha(bool _t) { bTextAlpha = _t; }
		void SetTextAlpha(int _a) { textAlpha = _a; }
		void SetMoveScene(SCENE_TYPE _type) { eBtnMoveScene = _type; }
		void SetTextPos(Vector2 _textPos) { textPos = _textPos; }
		void SetReSizeable(bool _b) { bReSzieable = _b; }
		int GetTextAlpha() { return textAlpha; }
		void SetTextMag(int mag) { iTextMag = mag; }



	private:
		Vector2 textPos;
		wstring btnName;
		SCENE_TYPE eBtnMoveScene;
		bool bText;
		bool bTextAlpha;
		bool bReSzieable;
		bool bClicked;
		int textAlpha;
		int iTextMag;
	};
}