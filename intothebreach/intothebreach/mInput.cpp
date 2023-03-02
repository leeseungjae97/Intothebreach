#include "mInput.h"
#include "mApplication.h"
extern m::Application application;
namespace m
{
	int ASCII[(UINT)KEYCODE_TYPE::END] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
	};

	std::vector<Input::Key> Input::mKeys;

	void Input::Initialize()
	{
		for (UINT i = 0; i < (UINT)KEYCODE_TYPE::END; i++)
		{
			Key keyInfo;
			keyInfo.key = (KEYCODE_TYPE)i;
			keyInfo.state = KEY_STATE::NONE;
			keyInfo.bPressed = false;

			mKeys.push_back(keyInfo);
		}
	}
	
	void Input::Update()
	{
		HWND hwnd = GetFocus();
		if (nullptr != hwnd) {
			for (UINT i = 0; i < (UINT)KEYCODE_TYPE::END; i++) {
				if (GetAsyncKeyState(ASCII[i]) & 0x8000) {
					// 이전 프레임에도 눌려 있었다
					if (mKeys[i].bPressed)
						mKeys[i].state = KEY_STATE::PRESSED;
					else
						mKeys[i].state = KEY_STATE::DOWN;

					mKeys[i].bPressed = true;
				}
				else // 현재 프레임에 키가 눌려있지 않다.
				{
					// 이전 프레임에 내키가 눌려있엇다.
					if (mKeys[i].bPressed)
						mKeys[i].state = KEY_STATE::UP;
					else
						mKeys[i].state = KEY_STATE::NONE;

					mKeys[i].bPressed = false;
				}
			}
		}
		else {
			for (int i = 0; i < (int)KEYCODE_TYPE::END; i++) {
				mKeys[i].bPressed = false;
				if (KEY_STATE::DOWN == mKeys[i].state || KEY_STATE::PRESSED == mKeys[i].state) {
					mKeys[i].state = KEY_STATE::UP;
				}
				else if (KEY_STATE::UP == mKeys[i].state) {
					mKeys[i].state = KEY_STATE::NONE;
				}
			}
			
		}
		
	}

	void Input::Render(HDC hdc)
	{

	}
}
