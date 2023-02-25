#pragma once
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <commdlg.h>
#include <assert.h>
#include <bitset>
#include <string>
#include <vector>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <functional>
#include <memory>
#include <filesystem>

#pragma comment(lib, "Msimg32.lib")

#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

using std::vector;
using std::map;
using std::wstring;
using std::list;
using std::pair;
using std::make_pair;
using std::move;
using std::function;

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

namespace ya {
	struct Pixel {
		BYTE R;
		BYTE G;
		BYTE B;
		BYTE A;

		Pixel(BYTE r, BYTE g, BYTE b, BYTE a)
			: R(r), G(g), B(b), A(a) {

		}
	};

	struct WindowData {
		HWND hWnd;
		HDC  hdc;

		HBITMAP backTexture;
		HDC backBuffer;

		UINT height;
		UINT width;

		void Clear() {
			hWnd = NULL;
			hdc = NULL;
			backTexture = NULL;
			backBuffer = NULL;
			height = 0;
			width = 0;
		}
	};
};
