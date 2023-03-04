#pragma once

#define TILE_SIZE 64
#define TILE_X 8
#define TILE_Y 8

#define CONDITIONS 7
#define RESOURCES_1 10

#define WEAPONS_ 3

#define PRIMES_ 9
#define BRUTES_ 10
#define RANGES_ 10
#define SCIENCES_ 10
#define CYBORGS_ 3

#define MECH_IDLE_SIZE_X 44
#define MECH_IDLE_SIZE_Y 34

#define ISLANDS 5

#define TILE_SIZE_X 56.f
#define TILE_SIZE_Y 74.f

#define TILE_X_DIVIDE_RECT 2.f
#define TILE_Y_DIVIDE_RECT 3.53f

#define ONE_BUILDING_SCALE Vector2(31.f , 0.f)
#define ONE_BUILDING_POS Vector2(10.f, 5.f)

#define KEY_PREESED(KEY) m::KEY_STATE::PRESSED == m::Input::GetKeyState(KEY)
#define KEY_DOWN(KEY) m::KEY_STATE::DOWN == m::Input::GetKeyState(KEY)
#define KEY_UP(KEY) m::KEY_STATE::UP == m::Input::GetKeyState(KEY)

#define SQUARE__PATH L"..\\Resources\\texture\\terrain\\tile_square.bmp"
#define SQUARE__KEY L"square"

#define SQUARE_LINE__PATH L"..\\Resources\\texture\\terrain\\square_line.bmp"
#define SQUARE_LINE__KEY L"square_line"

#define SQUARE_Y_LINE__PATH L"..\\Resources\\texture\\terrain\\square_yellow_line.bmp"
#define SQUARE_Y_LINE__KEY L"square_yellow_line"

#define MOUSE_POS m::Input::GetMousePos()

#define CLONE(type) type* Clone() {return new type(*this);}