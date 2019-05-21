#pragma once
#include "Math.hpp"
class Quat;
class Mat4;
class Vec2;

class Vec3
{
public:
	inline Vec3()
		:x(0.f), y(0.f), z(0.f)
	{}
	inline explicit Vec3(const f32 fx, const f32 fy, const f32 fz)
		:x(fx), y(fy), z(fz)
	{};
	inline Vec3(const Vec3& v)
		:x(v.x), y(v.y), z(v.z)
	{}

	inline Bool operator == (const Vec3& v) const
	{
		return Math::IsEqual(x, v.x) && Math::IsEqual(y, v.y) && Math::IsEqual(z, v.z);
	}
	inline Bool operator!= (const Vec3& v)
	{
		return !operator==(v);
	}
	inline Vec3& operator = (const Vec3& v)
	{
		x = v.x; y = v.y; z = v.z;
		return *this;
	}
	inline f32& operator[](const uint i)
	{
		return *(&x + i);
	}
	inline const f32& operator[](const uint i) const
	{
		return *(&x + i);
	}
	inline const Vec3& operator +()
	{
		return *this;
	}
	inline Vec3 operator - ()
	{
		return Vec3(-x, -y, -z);
	}
	inline Vec3 operator + (const Vec3& v) const
	{
		return Vec3(x + v.x, y + v.y, z + v.z);
	}
	inline Vec3& operator += (const Vec3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	inline Vec3 operator + (const f32 fv)
	{
		return Vec3(x + fv, y + fv, z + fv);
	}
	inline Vec3& operator += (const f32 fv)
	{
		x += fv;
		y += fv;
		z += fv;
		return *this;
	}
	inline Vec3 operator - (const Vec3& v) const
	{
		return Vec3(x - v.x, y - v.y, z - v.z);
	}
	inline Vec3& operator -= (const Vec3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	inline Vec3 operator - (const f32 fv)
	{
		return Vec3(x - fv, y - fv, z - fv);
	}
	inline Vec3& operator -= (const f32 fv)
	{
		x -= fv;
		y -= fv;
		z -= fv;
		return *this;
	}
	inline Vec3 operator * (const Vec3& v)
	{
		return Vec3(x * v.x, y * v.y, z * v.z);
	}
	inline Vec3& operator *= (const Vec3& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}
	inline Vec3 operator * (const f32 fv)
	{
		return Vec3(x * fv, y * fv, z * fv);
	}
	inline Vec3& operator *= (const f32 fv)
	{
		x *= fv;
		y *= fv;
		z *= fv;
		return *this;
	}
	inline Vec3 operator / (const Vec3& v)
	{
		return Vec3(x / v.x, y / v.y, z / v.z);
	}
	inline Vec3& operator /= (const Vec3& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}
	inline Vec3 operator / (const f32 fv)
	{
		return Vec3(x / fv, y / fv, z / fv);
	}
	inline Vec3& operator /= (const f32 fv)
	{
		x /= fv;
		y /= fv;
		z /= fv;
		return *this;
	}
	inline friend Vec3 operator + (const f32 fv, const Vec3& v)
	{
		return Vec3(fv + v.x, fv + v.y, fv + v.z);
	}
	inline friend Vec3 operator - (const f32 fv, const Vec3& v)
	{
		return Vec3(fv - v.x, fv - v.y, fv - v.z);
	}
	inline friend Vec3 operator * (const f32 fv, const Vec3& v)
	{
		return Vec3(fv * v.x, fv * v.y, fv * v.z);
	}
	inline friend Vec3 operator / (const f32 fv, const Vec3& v)
	{
		return Vec3(fv / v.x, fv / v.y, fv / v.z);
	}

	Vec3 operator *(const Mat4& m) const;

	inline f32 LengthSq()
	{
		return x * x + y * y + z * z;
	}
	inline f32 Length()
	{
		return Math::Sqrt(LengthSq());
	}
	inline f32 DotProduct(const Vec3& v)
	{
		return x * v.x + y * v.y + z * v.z;
	}
	inline Vec3 CrossProduct(const Vec3& v)
	{
		return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
	inline f32 Normalize()
	{
		f32 len = Length();

		if (!Math::IsZero(len))
		{
			x /= len;
			y /= len;
			z /= len;
		}
		return len;
	}
	Vec3 TransformCoord(const Quat& q);
	inline void Dump()
	{
		printf("x = %f, y = %f, z = %f\n", x, y, z);
	}

	static Vec3 FromVec2(const Vec2& v);

	static const Vec3 ZERO;
	static const Vec3 XUNIT;
	static const Vec3 YUNIT;
	static const Vec3 ZUNIT;
	static const Vec3 NXUNIT;
	static const Vec3 NYUNIT;
	static const Vec3 NZUNIT;

public:
	f32 x, y, z;
};


