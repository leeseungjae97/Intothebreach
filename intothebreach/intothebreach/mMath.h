#pragma once

#define PI 3.14159265f


#include <cmath>
#include <algorithm>
namespace m {
	struct Vector2 {
		static Vector2 Zero;
		static Vector2 One;
        static Vector2 Minus;

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
        bool operator !=(const Vector2& other) {
            return (x != other.x || y != other.y);
        }
        bool operator <(const Vector2& other) {
            return (x < other.x && y < other.y);
        }
        bool operator >(const Vector2& other) {
            return (x > other.x && y > other.y);
        }
        bool operator <=(const Vector2& other) {
            return (x <= other.x && y <= other.y);
        }
        bool operator >=(const Vector2& other) {
            return (x >= other.x && y >= other.y);
        }
        bool operator &&(const Vector2& other) {
            return (x && other.x) && (y && other.y);
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
			return sqrt(x * x + y * y);
		}

		Vector2& Normalize() {
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
    inline Vector2 Vector2::Minus = Vector2(-1.0f, -1.0f);

    inline Vector2 Vector2::Up = Vector2(0.f, -1.f);
    inline Vector2 Vector2::Right = Vector2(1.f, 0.f);
};

namespace m::math {
    float min4(float a, float b, float c, float d) {
        if (a < b) {
            if (c < a) {
                if (d < c)
                    return d;
                else
                    return c;
            }
            else {
                if (d < a)
                    return d;
                else
                    return a;
            }
        }
        else {
            if (c < b) {
                if (d < c)
                    return d;
                else
                    return c;
            }
            else {
                if (d < b)
                    return d;
                else
                    return b;
            }
        }
    }

    // Helper function for getting the maximum of 4 floats
    float max4(float a, float b, float c, float d) {
        if (a > b) {
            if (c > a) {
                if (d > c)
                    return d;
                else
                    return c;
            }
            else {
                if (d > a)
                    return d;
                else
                    return a;
            }
        }
        else {
            if (c > b) {
                if (d > c)
                    return d;
                else
                    return c;
            }
            else {
                if (d > b)
                    return d;
                else
                    return b;
            }
        }
    }

    inline Vector2 Rotate(Vector2 vector, float degree) {
        float radian = (degree / 180.f) * PI;
        vector.Normalize();
        float x = cosf(radian) * vector.x - sinf(radian) * vector.y;
        float y = sinf(radian) * vector.x + cosf(radian) * vector.y;

        return Vector2(x, y);
    }

    inline float Dot(Vector2& v1, Vector2& v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

    inline float Cross(Vector2 v1, Vector2 v2) {
        return v1.x * v2.y - v1.y * v2.x;
    }
    bool CheckRectPos(Vector2 pos, Vector2 scale, Vector2 otherPos) {
        Vector2 fP = { pos.x, pos.y };
        Vector2 lP = { fP.x + scale.x, fP.y + scale.y };

        if (fP <= otherPos && lP >= otherPos) return true;
        else return false;
    }
    /// <summary>
    /// 사각형 땅의 각 꼭짓점을 구하고
    /// 꼭짓점끼리의 절편과 기울기를 이용해 마름모의 좌표를 구함
    /// </summary>
    /// <param name="tile">꼭짓점을 추출할 타일</param>
    /// <param name="_pos">현재 위치(마우스커서)</param>
    /// <returns>현재위치가 타일의 마름모 좌표 내부에 있는지 여부</returns>
    bool CheckRhombusPos(Vector2 pos, Vector2 scale, Vector2 otherPos) {
        Vector2 vertex[4];
        float gradient[4];
        float intercept[4];
        float direct[4][2] = {
            {0, (scale.y / 2)},
            {(scale.x / 2), 0},
            {scale.x, (scale.y / 2)},
            {(scale.x / 2), scale.y}
        };
        for (size_t i = 0; i < 4; i++) {
            vertex[i].x = pos.x + direct[i][0];
            vertex[i].y = pos.y + direct[i][1];
        }
        for (size_t i = 0; i < 4; i++) {
            gradient[i] = ((vertex[i].y - vertex[(i + 1) % 4].y) / (vertex[i].x - vertex[(i + 1) % 4].x));
            intercept[i] = vertex[i].y - gradient[i] * vertex[i].x;
        }
        float _y = otherPos.y;
        float _x = otherPos.x;

        if (gradient[0] * _x + intercept[0] < _y
            && gradient[1] * _x + intercept[1] < _y
            && gradient[2] * _x + intercept[2] > _y
            && gradient[3] * _x + intercept[3] > _y) {
            return true;
        }
        else return false;
    }

}