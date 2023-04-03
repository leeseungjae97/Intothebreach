#pragma once

#define RIGHT				0x01
#define LEFT				0x02
#define TOP					0x04
#define BOTTOM				0x08
#define CENTER				0x10
#define DEFAULT				0x00

#define RIGHT_NUM			0
#define UP_NUM				1
#define DOWN_NUM			2
#define LEFT_NUM			3

#define TILE_SIZE			64
#define TILE_X				8
#define TILE_Y				8

#define CONDITIONS			7
#define RESOURCES_1			10

#define WEAPONS_			3
#define MAX_WEAPONS			2

#define ARC_CONST			3

#define PRIMES_				9
#define BRUTES_				10
#define RANGES_				10
#define SCIENCES_			10
#define CYBORGS_			3

#define MECH_IDLE_SIZE_X	44
#define MECH_IDLE_SIZE_Y	34

#define ISLANDS				5

#define TILE_SIZE_X			56.f
#define TILE_SIZE_Y			74.f

#define TILE_X_DIVIDE_RECT	2.f
#define TILE_Y_DIVIDE_RECT	3.53f

#define ONE_BUILDING_SCALE	Vector2(31.f , 0.f)
#define ONE_BUILDING_POS	Vector2(10.f, 5.f)

#define KEY_PRESSED(KEY)	m::KEY_STATE::PRESSED == m::Input::GetKeyState(KEY)
#define KEY_DOWN(KEY)		m::KEY_STATE::DOWN == m::Input::GetKeyState(KEY)
#define KEY_UP(KEY)			m::KEY_STATE::UP == m::Input::GetKeyState(KEY)
#define KEY_CLICKED(KEY)	m::Input::GetKeyClicked(KEY)

#define SQUARE__PATH		L"..\\Resources\\texture\\terrain\\tile_square.bmp"
#define SQUARE__KEY			L"square"

#define SQUARE_LINE__PATH	L"..\\Resources\\texture\\terrain\\square_line.bmp"
#define SQUARE_LINE__KEY	L"square_line"

#define SQUARE_Y_LINE__PATH L"..\\Resources\\texture\\terrain\\square_yellow_line.bmp"
#define SQUARE_Y_LINE__KEY	L"square_yellow_line"

#define HP_BAR				L"..\\Resources\\texture\\combat\\overlay\\icon_healthbar.bmp"
#define HP_BAR_BACK			L"..\\Resources\\texture\\combat\\overlay\\healthbar_back.bmp"

#define MOUSE_POS m::Input::GetMousePos()

#define CLONE(type) type* Clone() {return new type(*this);}

#define MOVE				 1
#define MECH				-2
#define ALIEN				-3
#define BUILDING			-1

template <typename T>
void Safe_Delete_X_Vec(vector<T>& _vec) {
	for (size_t i = 0; i < _vec.size(); i++) {
		if (nullptr != _vec[i]) delete _vec[i];
	}
	_vec.clear();
}
template <typename T>
void Safe_Delete_Y_Vec(vector<vector<T>>& _vec) {
	for (size_t i = 0; i < _vec.size(); i++) {
		if (!_vec[i].empty()) {
			Safe_Delete_X_Vec(_vec[i]);
		}
	}
	_vec.clear();
}