#pragma once
#include "Math.hpp"
class Vec4
{
public:
	inline Vec4()
		:x(0.f), y(0.f), z(0.f), w(0.f)
	{}
	inline explicit Vec4(const f32 fx, const f32 fy, const f32 fz, const f32 fw)
		:x(fx), y(fy), z(fz), w(fw)
	{};
	inline Vec4(const Vec4& v)
		:x(v.x), y(v.y), z(v.z), w(v.w)
	{}

	inline Bool operator == (const Vec4& v)
	{
		return Math::IsEqual(x, v.x) && Math::IsEqual(y, v.y) && Math::IsEqual(z, v.z) && Math::IsEqual(w, v.w);
	}
	inline Bool operator!= (const Vec4& v)
	{
		return !operator==(v);
	}
	inline Vec4& operator = (const Vec4& v)
	{
		x = v.x; y = v.y; z = v.z; w = v.w;
		return *this;
	}
	inline f32& operator[](uint i)
	{
		return *(&x + i);
	}
	inline const f32& operator[](const uint i) const
	{
		return *(&x + i);
	}
	inline const Vec4& operator +()
	{
		return *this;
	}
	inline Vec4 operator - ()
	{
		return Vec4(-x, -y, -z, -w);
	}
	inline Vec4 operator + (const Vec4& v)
	{
		return Vec4(x + v.x, y + v.y, z + v.z, w + v.w);
	}
	inline Vec4& operator += (const Vec4& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}
	inline Vec4 operator + (const f32 fv)
	{
		return Vec4(x + fv, y + fv, z + fv, w + fv);
	}
	inline Vec4& operator += (const f32 fv)
	{
		x += fv;
		y += fv;
		z += fv;
		w += fv;
		return *this;
	}
	inline Vec4 operator - (const Vec4& v)
	{
		return Vec4(x - v.x, y - v.y, z - v.z, w - v.w);
	}
	inline Vec4& operator -= (const Vec4& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}
	inline Vec4 operator - (const f32 fv)
	{
		return Vec4(x - fv, y - fv, z - fv, w - fv);
	}
	inline Vec4& operator -= (const f32 fv)
	{
		x -= fv;
		y -= fv;
		z -= fv;
		w -= fv;
		return *this;
	}
	inline Vec4 operator * (const Vec4& v)
	{
		return Vec4(x * v.x, y * v.y, z * v.z, w * v.w);
	}
	inline Vec4& operator *= (const Vec4& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		w *= v.w;
		return *this;
	}
	inline Vec4 operator * (const f32 fv)
	{
		return Vec4(x * fv, y * fv, z * fv, w * fv);
	}
	inline Vec4& operator *= (const f32 fv)
	{
		x *= fv;
		y *= fv;
		z *= fv;
		w *= fv;
		return *this;
	}
	inline Vec4 operator / (const Vec4& v)
	{
		return Vec4(x / v.x, y / v.y, z / v.z, w / v.w);
	}
	inline Vec4& operator /= (const Vec4& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		w /= v.w;
		return *this;
	}
	inline Vec4 operator / (const f32 fv)
	{
		return Vec4(x / fv, y / fv, z / fv, w / fv);
	}
	inline Vec4& operator /= (const f32 fv)
	{
		x /= fv;
		y /= fv;
		z /= fv;
		w /= fv;
		return *this;
	}
	inline friend Vec4 operator + (const f32 fv, const Vec4& v)
	{
		return Vec4(fv + v.x, fv + v.y, fv + v.z, fv + v.w);
	}
	inline friend Vec4 operator - (const f32 fv, const Vec4& v)
	{
		return Vec4(fv - v.x, fv - v.y, fv - v.z, fv - v.w);
	}
	inline friend Vec4 operator * (const f32 fv, const Vec4& v)
	{
		return Vec4(fv * v.x, fv * v.y, fv * v.z, fv * v.w);
	}
	inline friend Vec4 operator / (const f32 fv, const Vec4& v)
	{
		return Vec4(fv / v.x, fv / v.y, fv / v.z, fv / v.w);
	}
	inline f32 DotProduct(const Vec4& v)
	{
		return x * v.x + y * v.y + z * v.z + w * v.w;
	}
	inline void Dump()
	{
		printf("x = %f, y = %f, z = %f, w = %f\n", x, y, z, w);
	}

	static const Vec4 ZERO;

public:
	f32 x, y, z, w;
};



