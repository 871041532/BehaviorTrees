#pragma once
#include "Math.hpp"
class Vec3;
class Quat;
class Vec4;
class Mat4
{
public:
	inline Mat4()
	{
		operator=(Mat4::IDENTITY);
	}
	inline Mat4(f32 m00, f32 m01, f32 m02, f32 m03,
		f32 m10, f32 m11, f32 m12, f32 m13,
		f32 m20, f32 m21, f32 m22, f32 m23,
		f32 m30, f32 m31, f32 m32, f32 m33)
	{
		mat[0][0] = m00; mat[0][1] = m01; mat[0][2] = m02; mat[0][3] = m03;
		mat[1][0] = m10; mat[1][1] = m11; mat[1][2] = m12; mat[1][3] = m13;
		mat[2][0] = m20; mat[2][1] = m21; mat[2][2] = m22; mat[2][3] = m23;
		mat[3][0] = m30; mat[3][1] = m31; mat[3][2] = m32; mat[3][3] = m33;
	}

	inline Mat4(f32 transX, f32 transY, f32 transZ)
	{
		mat[0][0] = 1.f;	mat[0][1] = 0.f;	mat[0][2] = 0.f;	mat[0][3] = 0.f;
		mat[1][0] = 0.f;	mat[1][1] = 1.f;	mat[1][2] = 0.f;	mat[1][3] = 0.f;
		mat[2][0] = 0.f;	mat[2][1] = 0.f;	mat[2][2] = 1.f;	mat[2][3] = 0.f;
		mat[3][0] = transX;	mat[3][1] = transY;	mat[3][2] = transZ;	mat[3][3] = 1.f;
	}
	inline Mat4(const Vec3& v);

	Bool operator == (const Mat4& m);
	inline Bool operator != (const Mat4& m)
	{
		return !operator==(m);
	}

	inline Mat4& operator = (const Mat4& m)
	{
		memcpy(mat, m.mat, 16 * sizeof(f32));
		return *this;
	}

	Mat4 operator - (const Mat4& m);
	Mat4 operator + (const Mat4& m);
	Mat4 operator * (const Mat4& m);
	Mat4& operator *=(const Mat4& m);

	inline const Mat4& operator + ()
	{
		return *this;
	}
	inline f32* operator[] (uint row) const
	{
		return (f32*)mat[row];
	}

	Mat4 operator - ();

	Vec4 operator * (const Vec4& v);
	Mat4 operator * (const f32 fv);
	friend Mat4 operator * (const f32 fv, const Mat4& m);
	friend Vec4 operator * (const Vec4& v, const Mat4& m);

	Mat4& Translation(const Vec3& v);
	Mat4& Translation(f32 x, f32 y, f32 z);
	Mat4& Rotation(const Quat& q);
	Mat4& Scale(const f32 x, const f32 y, const f32 z);

	Mat4 Transpose();
	Mat4 Inverse();


	static const Mat4 ZERO;
	static const Mat4 IDENTITY;

	void Dump()
	{
		printf("m00 = %f, m01 = %f, m02 = %f, m03 = %f\n", mat[0][0], mat[0][1], mat[0][2], mat[0][3]);
		printf("m10 = %f, m11 = %f, m12 = %f, m13 = %f\n", mat[1][0], mat[1][1], mat[1][2], mat[1][3]);
		printf("m20 = %f, m21 = %f, m22 = %f, m23 = %f\n", mat[2][0], mat[2][1], mat[2][2], mat[2][3]);
		printf("m30 = %f, m31 = %f, m32 = %f, m33 = %f\n", mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
	}

	void MakeProjectionOrthoMatrix(f32 l, f32 r, f32 t, f32 b, f32 zn, f32 zf)
	{
		float m[] = {
				2 / (r - l) ,     0,            0,           0,
				0,            2 / (t - b),      0,           0,
				0,            0,            1 / (zf - zn),   0,
				(l + r) / (l - r),  (t + b) / (b - t),  zn / (zn - zf),  1 };

		memcpy(mat, m, 16 * sizeof(f32));
	}
public:
	f32 mat[4][4];
};
