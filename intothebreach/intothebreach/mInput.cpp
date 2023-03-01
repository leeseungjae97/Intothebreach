#include "mInput.h"


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
		for (UINT i = 0; i < (UINT)KEYCODE_TYPE::END; i++)
		{
			if (GetAsyncKeyState(ASCII[i]) & 0x8000)
			{
				// ���� �����ӿ��� ���� �־���
				if (mKeys[i].bPressed)
					mKeys[i].state = KEY_STATE::PRESSED;
				else
					mKeys[i].state = KEY_STATE::DOWN;
				
				mKeys[i].bPressed = true;
			}
			else // ���� �����ӿ� Ű�� �������� �ʴ�.
			{
				// ���� �����ӿ� ��Ű�� �����־���.
				if (mKeys[i].bPressed)
					mKeys[i].state = KEY_STATE::UP;
				else
					mKeys[i].state = KEY_STATE::NONE;
				
				mKeys[i].bPressed = false;
			}
		}
	}

	void Input::Render(HDC hdc)
	{

	}
}
