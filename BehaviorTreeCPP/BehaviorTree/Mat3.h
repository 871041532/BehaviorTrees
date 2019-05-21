#pragma once
#include "Math.hpp"
class Quat;
class Vec3;

class Mat3
{
public:
	inline Mat3() {}
	inline Mat3(f32 m00, f32 m01, f32 m02,
		f32 m10, f32 m11, f32 m12,
		f32 m20, f32 m21, f32 m22)
	{
		mat[0][0] = m00; mat[0][1] = m01; mat[0][2] = m02;
		mat[1][0] = m10; mat[1][1] = m11; mat[1][2] = m12;
		mat[2][0] = m20; mat[2][1] = m21; mat[2][2] = m22;
	}
	Mat3(const Quat& q);

	Bool operator == (const Mat3& m);
	inline Bool operator != (const Mat3& m)
	{
		return !operator==(m);
	}

	inline Mat3& operator = (const Mat3& m)
	{
		memcpy(mat, m.mat, 9 * sizeof(f32));
		return *this;
	}

	Mat3 operator - (const Mat3& m);
	Mat3 operator + (const Mat3& m);
	Mat3 operator * (const Mat3& m);

	inline const Mat3& operator + ()
	{
		return *this;
	}
	inline f32* operator[] (uint row) const
	{
		return (f32*)mat[row];
	}

	Mat3 operator - ();

	Vec3 operator * (const Vec3& v);
	Mat3 operator * (const f32 fv);
	friend Mat3 operator * (const f32 fv, const Mat3& m);
	friend Vec3 operator * (const Vec3& v, const Mat3& m);

	Mat3 Transpose();
	Mat3 Inverse();

	static const Mat3 ZERO;
	static const Mat3 IDENTITY;

	void Dump()
	{
		printf("m00 = %f, m01 = %f, m02 = %f\n", mat[0][0], mat[0][1], mat[0][2]);
		printf("m10 = %f, m11 = %f, m12 = %f\n", mat[1][0], mat[1][1], mat[1][2]);
		printf("m20 = %f, m21 = %f, m22 = %f\n", mat[2][0], mat[2][1], mat[2][2]);
	}

public:
	f32 mat[3][3];
};


