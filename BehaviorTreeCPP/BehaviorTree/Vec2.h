#pragma once
#include "Math.hpp"
class Vec3;
class Vec2
{
public:
	inline Vec2()
		:x(0.f), y(0.f)
	{}
	inline explicit Vec2(const float p_fX, const float p_fY)
		:x(p_fX), y(p_fY)
	{};
	inline Vec2(const Vec2& p_V)
		:x(p_V.x), y(p_V.y)
	{}

	inline bool operator == (const Vec2& p_V)
	{
		return Math::IsEqual(x, p_V.x) && Math::IsEqual(y, p_V.y);
	}
	inline bool operator!= (const Vec2& p_V)
	{
		return !operator==(p_V);
	}
	inline Vec2& operator = (const Vec2& p_V)
	{
		x = p_V.x; y = p_V.y;
		return *this;
	}
	inline f32& operator[](uint p_uiIdx)
	{
		return *(&x + p_uiIdx);
	}
	inline const f32& operator[](const uint p_uiIdx) const
	{
		return *(&x + p_uiIdx);
	}
	inline const Vec2& operator +() const
	{
		return *this;
	}
	inline Vec2 operator - () const
	{
		return Vec2(-x, -y);
	}
	inline Vec2 operator + (const Vec2& p_V) const
	{
		return Vec2(x + p_V.x, y + p_V.y);
	}
	inline Vec2& operator += (const Vec2& p_V)
	{
		x += p_V.x;
		y += p_V.y;
		return *this;
	}
	inline Vec2 operator + (const f32 p_fVal) const
	{
		return Vec2(x + p_fVal, y + p_fVal);
	}
	inline Vec2& operator += (const f32 p_fVal)
	{
		x += p_fVal;
		y += p_fVal;
		return *this;
	}
	inline Vec2 operator - (const Vec2& p_V) const
	{
		return Vec2(x - p_V.x, y - p_V.y);
	}
	inline Vec2& operator -= (const Vec2& p_V)
	{
		x -= p_V.x;
		y -= p_V.y;
		return *this;
	}
	inline Vec2 operator - (const f32 p_fVal)
	{
		return Vec2(x - p_fVal, y - p_fVal);
	}
	inline Vec2& operator -= (const f32 p_fVal)
	{
		x -= p_fVal;
		y -= p_fVal;
		return *this;
	}
	inline Vec2 operator * (const Vec2& p_V) const
	{
		return Vec2(x * p_V.x, y * p_V.y);
	}
	inline Vec2& operator *= (const Vec2& p_V)
	{
		x *= p_V.x;
		y *= p_V.y;
		return *this;
	}
	inline Vec2 operator * (const f32 p_fVal) const
	{
		return Vec2(x * p_fVal, y * p_fVal);
	}
	inline Vec2& operator *= (const f32 p_fVal)
	{
		x *= p_fVal;
		y *= p_fVal;
		return *this;
	}
	inline Vec2 operator / (const Vec2& p_V) const
	{
		return Vec2(x / p_V.x, y / p_V.y);
	}
	inline Vec2& operator /= (const Vec2& p_V)
	{
		x /= p_V.x;
		y /= p_V.y;
		return *this;
	}
	inline Vec2 operator / (const f32 p_fVal) const
	{
		return Vec2(x / p_fVal, y / p_fVal);
	}
	inline Vec2& operator /= (const float p_fVal)
	{
		x /= p_fVal;
		y /= p_fVal;
		return *this;
	}
	inline friend Vec2 operator + (const float p_fVal, const Vec2& p_V)
	{
		return Vec2(p_fVal + p_V.x, p_fVal + p_V.y);
	}
	inline friend Vec2 operator - (const float p_fVal, const Vec2& p_V)
	{
		return Vec2(p_fVal - p_V.x, p_fVal - p_V.y);
	}
	inline friend Vec2 operator * (const float p_fVal, const Vec2& p_V)
	{
		return Vec2(p_fVal * p_V.x, p_fVal * p_V.y);
	}
	inline friend Vec2 operator / (const float p_fVal, const Vec2& p_V)
	{
		return Vec2(p_fVal / p_V.x, p_fVal / p_V.y);
	}
	inline f32 LengthSq()
	{
		return x * x + y * y;
	}
	inline f32 Length()
	{
		return Math::Sqrt(LengthSq());
	}
	inline f32 DotProduct(const Vec2& p_V)
	{
		return x * p_V.x + y * p_V.y;
	}
	inline f32 Nomalize()
	{
		f32 l_fLen = Length();

		if (!Math::IsZero(l_fLen))
		{
			x /= l_fLen;
			y /= l_fLen;
		}
		return l_fLen;
	}
	inline void Dump()
	{
		printf("x = %f, y = %f\n", x, y);
	}

	static Vec2 FromVec3(const Vec3& v);

	static const Vec2 kZERO;
	static const Vec2 kXUNIT;
	static const Vec2 kYUNIT;
	static const Vec2 kNXUNIT;
	static const Vec2 kNYUNIT;

public:
	float x, y;
};


