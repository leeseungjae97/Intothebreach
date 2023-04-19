#pragma once
#include "mUI.h"
namespace m
{
	class Image;
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

		bool GetInner() { return bInner; }
		bool GetClicked() { return bClicked; }
		bool GetHover() { return bHover; }
		wstring GetBtnName() { return btnName; }
		Vector2 GetInnerPos() { return innerPos; }
		Image* GetInnerImage() { return innerImage; }
		BYTE GetInnerAlpha() { return innerAlpha; }

		void SetInner(bool _t) { bInner = _t; }
		void SetClicked(bool _b) { bClicked = _b; }
		void ChangeInner(const wstring& _path) { btnName = _path; }
		void UseInnerAlpha(bool _t) { bInnerAlpha = _t; }
		void SetInnerConstant(BYTE _a) { innerAlpha = _a; }
		void SetMoveScene(SCENE_TYPE _type) { eBtnMoveScene = _type; }
		void SetInnerPos(Vector2 _textPos) { innerPos = _textPos; }
		void SetReSizeable(bool _b) { bReSzieable = _b; }
		void SetInnerMag(int mag) { iInnerScale = mag; }
		void SetConstant(BYTE _cons) { btConstant = _cons; }
		void SetHover(bool _b) { bHover = _b; }

	private:
		Vector2 innerPos;
		wstring btnName;

		SCENE_TYPE eBtnMoveScene;
		Image* innerImage;
		bool bInner;
		bool bInnerAlpha;
		bool bReSzieable;
		bool bClicked;
		bool bHover;
		BYTE btConstant;
		BYTE innerAlpha;
		int iInnerScale;
	};
}