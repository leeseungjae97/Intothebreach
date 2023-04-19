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

		bool GetText() { return bText; }
		bool GetClicked() { return bClicked; }
		wstring GetBtnName() { return btnName; }
		Vector2 GetTextPos() { return textPos; }
		BYTE GetTextAlpha() { return textAlpha; }

		void SetText(bool _t) { bText = _t; }
		void SetClicked(bool _b) { bClicked = _b; }
		void ChangeText(const wstring& _path) { btnName = _path; }
		void UseTextAlpha(bool _t) { bTextAlpha = _t; }
		void SetTextConstant(BYTE _a) { textAlpha = _a; }
		void SetMoveScene(SCENE_TYPE _type) { eBtnMoveScene = _type; }
		void SetTextPos(Vector2 _textPos) { textPos = _textPos; }
		void SetReSizeable(bool _b) { bReSzieable = _b; }
		void SetTextMag(int mag) { iTextScale = mag; }
		void SetConstant(BYTE _cons) { btConstant = _cons; }


	private:
		Vector2 textPos;
		wstring btnName;
		SCENE_TYPE eBtnMoveScene;
		bool bText;
		bool bTextAlpha;
		bool bReSzieable;
		bool bClicked;
		BYTE btConstant;
		BYTE textAlpha;
		int iTextScale;
	};
}