#pragma once
#include "mGameObject.h"
namespace m{
	class Image;
	class UI :
		public GameObject
	{
	public:
		UI(const wstring& key
			, const wstring& path
			, int _sizeUp
			, bool _full
			, int _direction
			, bool _alphaCheck);
		~UI();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
		float GetWidth();
		float GetHeight();
		Vector2 GetSize() { 
			if (mSize != Vector2::Zero) return mSize;
			return Vector2(GetWidth(), GetHeight()); 
		}
		BTN_TYPE GetButtonType() { return bType; }
		void SetSize(Vector2 _size) { mSize = _size; }
		void SetTex(const wstring& key, const wstring& path);
		void SetTex(const wstring& key, const wstring& path, ISLAND_T type);
		void Clear();

		void SetButtonType(BTN_TYPE _type) { bType = _type; }
		void SetCutPos(bool _cp) { cutPos = _cp; }
		void SetEC(bool _ec) { effectCamera = _ec; }
		void SetAlpha(bool _mA) { mAlpha = _mA; }
		Image* GetImage() { return mImage; }

	protected:
		Image* mImage;
		wstring mPath;
		wstring mKey;
		BTN_TYPE bType;

		Vector2 mSize;
		bool mIsFull;
		int mDir;
		bool mAlpha;
		bool cutPos;
		bool effectCamera;
		int mSizeUp;
	};
}


