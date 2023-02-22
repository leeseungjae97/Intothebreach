#pragma once


struct Vector2
{
	float x;
	float y;

	Vector2()
		: x(0.0f)
		, y(0.0f)
	{

	}
	Vector2(int x, int y)
		: x((float)x)
		, y((float)y)
	{

	}
	Vector2(float x, float y)
		: x(x)
		, y(y) {

	}
	Vector2(Vector2& other) = default;
	Vector2& operator = (const Vector2&) = default;

	Vector2(Vector2&& other) = default;
	Vector2& operator = (Vector2&&) = default;


	//Vector2(Vector2& other)
	//	: x(other.x)
	//	, y(other.y)
	//{

	//}
};