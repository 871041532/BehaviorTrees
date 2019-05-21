#pragma once
#include "Math.hpp"
class Vec3;
class Mat3;
class Quat
{
public:
	inline Quat()
		:x(0.f), y(0.f), z(0.f), w(1.f)
	{}
	inline explicit Quat(const f32 fw, const f32 fx, const f32 fy, const f32 fz)
		:x(fx), y(fy), z(fz), w(fw)
	{};
	inline Quat(const Quat& q)
		:x(q.x), y(q.y), z(q.z), w(q.w)
	{}
	inline Quat(const f32 rad, const Vec3& axis)
	{
		RadAxisToQuat(rad, axis);
	}

	inline Bool operator == (const Quat& q)
	{
		return Math::IsEqual(x, q.x) && Math::IsEqual(y, q.y) && Math::IsEqual(z, q.z) && Math::IsEqual(w, q.w);
	}
	inline Bool operator!= (const Quat& q)
	{
		return !operator==(q);
	}
	inline Quat& operator = (const Quat& q)
	{
		x = q.x; y = q.y; z = q.z; w = q.w;
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
	inline const Quat& operator +()
	{
		return *this;
	}
	inline Quat operator - ()
	{
		return Quat(-x, -y, -z, -w);
	}
	inline Quat operator + (const Quat& q)
	{
		return Quat(x + q.x, y + q.y, z + q.z, w + q.w);
	}
	inline Quat& operator += (const Quat& q)
	{
		x += q.x;
		y += q.y;
		z += q.z;
		w += q.w;
		return *this;
	}
	inline Quat operator - (const Quat& q)
	{
		return Quat(x - q.x, y - q.y, z - q.z, w - q.w);
	}
	inline Quat& operator -= (const Quat& q)
	{
		x -= q.x;
		y -= q.y;
		z -= q.z;
		w -= q.w;
		return *this;
	}
	inline Quat operator * (const Quat& q)
	{
		return Quat(
			w * q.w - x * q.x - y * q.y - z * q.z,
			w * q.x + x * q.w + y * q.z - z * q.y,
			w * q.y + y * q.w + z * q.x - x * q.z,
			w * q.z + z * q.w + x * q.y - y * q.x
		);
	}
	inline Quat& operator *= (const Quat& q)
	{
		w = w * q.w - x * q.x - y * q.y - z * q.z;
		x = w * q.x + x * q.w + y * q.z - z * q.y;
		y = w * q.y + y * q.w + z * q.x - x * q.z;
		z = w * q.z + z * q.w + x * q.y - y * q.x;
		return *this;
	}
	inline Quat operator * (const f32 fv)
	{
		return Quat(x * fv, y * fv, z * fv, w * fv);
	}
	inline Quat& operator *= (const f32 fv)
	{
		x *= fv;
		y *= fv;
		z *= fv;
		w *= fv;
		return *this;
	}
	inline Quat operator / (const f32 fv)
	{
		return Quat(x / fv, y / fv, z / fv, w / fv);
	}
	inline Quat& operator /= (const f32 fv)
	{
		x /= fv;
		y /= fv;
		z /= fv;
		w /= fv;
		return *this;
	}
	inline friend Quat operator * (const f32 fv, const Quat& q)
	{
		return Quat(fv * q.x, fv * q.y, fv * q.z, fv * q.w);
	}
	inline friend Quat operator / (const f32 fv, const Quat& q)
	{
		return Quat(fv / q.x, fv / q.y, fv / q.z, fv / q.w);
	}
	inline Vec3 operator * (const Vec3& v);
	inline f32 DotProduct(const Quat& q)
	{
		return x * q.x + y * q.y + z * q.z + w * q.w;
	}
	inline f32 LengthSq()
	{
		return x * x + y * y + z * z + w * w;
	}
	inline f32 Length()
	{
		return Math::Sqrt(LengthSq());
	}
	inline Quat Inverse()
	{
		f32 len = Length();
		if (!Math::IsZero(len))
		{
			*this /= len;
			return *this;
		}
		else
			return *this;
	}
	inline Quat UnitInverse()
	{
		return Quat(w, -x, -y, -z);
	}
	inline void Dump()
	{
		printf("x = %f, y = %f, z = %f, w = %f\n", x, y, z, w);
	}

	void RadAxisToQuat(const f32 rad, const Vec3& axis);
	void ArcToQuat(const Vec3& f, const Vec3& t);
	void MatToQuat(const Mat3& _Rot);
	void AngleAxisToQuat(const f32 angle, const Vec3& axis);
	void AxesToQuat(const Vec3& x, const Vec3& y, const Vec3& z);

	void QuatToRadAxis(f32& rad, Vec3& axis);
	void QuatToAngleAxis(f32& angle, Vec3& axis);
	void QuatToAxes(Vec3& ex, Vec3& ey, Vec3& ez);
	Vec3 QuatToXAxis();
	Vec3 QuatToYAxis();
	Vec3 QuatToZAxis();

	static const Quat ZERO;
	static const Quat IDENTITY;

public:
	f32 w, x, y, z;
};



