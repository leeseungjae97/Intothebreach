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

#define KEY_PREESED(KEY) m::KEY_STATE::PRESSED == m::Input::GetKeyState(KEY)
#define KEY_DOWN(KEY) m::KEY_STATE::DOWN == m::Input::GetKeyState(KEY)
#define KEY_UP(KEY) m::KEY_STATE::UP == m::Input::GetKeyState(KEY)
