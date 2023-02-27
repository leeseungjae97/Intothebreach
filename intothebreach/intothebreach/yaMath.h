#pragma once

#define PI 3.14159265f

#include <cmath>
#include <algorithm>

namespace ya {
	struct Vector2 {
		static Vector2 Zero;
		static Vector2 One;

        static Vector2 Up;
        static Vector2 Right;

		float x;
		float y;

		Vector2() = default;

		Vector2(Vector2& other) = default;
		Vector2& operator = (const Vector2&) = default;

		Vector2(Vector2 && other) = default;
		Vector2& operator = (Vector2&&) = default;

		Vector2 operator -() {
			return Vector2(-x, -y);
		}

        Vector2 operator+(const Vector2& other) {
            Vector2 temp;
            temp.x = x + other.x;
            temp.y = y + other.y;

            return temp;
        }

        Vector2 operator-(const Vector2& other) {
            Vector2 temp;
            temp.x = x - other.x;
            temp.y = y - other.y;

            return temp;
        }

        Vector2 operator*(const Vector2& other) {
            Vector2 temp;
            temp.x = x * other.x;
            temp.y = y * other.y;

            return temp;
        }

        Vector2 operator*(const float& value) {
            Vector2 temp;
            temp.x = x * value;
            temp.y = y * value;

            return temp;
        }

        Vector2 operator/(const float& value) {
            Vector2 temp;

            temp.x = x / value;
            temp.y = y / value;

            return temp;
        }

        Vector2& operator +=(const Vector2& other) {
            x += other.x;
            y += other.y;

            return *this;
        }

        Vector2& operator *=(const float value) {
            x *= value;
            y *= value;

            return *this;
        }

        Vector2& operator -=(const Vector2& other) {
            x -= other.x;
            y -= other.y;

            return *this;
        }
        bool operator ==(const Vector2& other) {
            return (x == other.x && y == other.y);
        }
        Vector2(float _x, float _y)
			: x(_x)
			, y(_y) {

		}
		void clear() {
			x = 0.0f;
			y = 0.0f;
		}

		float Length() {
			return sqrtf(x * x + y * y);
		}

		Vector2 Normalize() {
			float length = Length();
			x /= length;
			y /= length;

			return *this;
		}
    };

	typedef Vector2 Pos;
	typedef Vector2 Size;

	inline Vector2 Vector2::Zero = Vector2(0.0f, 0.0f);
	inline Vector2 Vector2::One = Vector2(1.0f, 1.0f);

    inline Vector2 Vector2::Up = Vector2(0.f, -1.f);
    inline Vector2 Vector2::Right = Vector2(1.f, 0.f);
};

namespace ya::math {

}