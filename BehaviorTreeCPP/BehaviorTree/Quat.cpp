#include "Quat.h"
#include "Vec3.h"
#include "Mat3.h"

inline Vec3 Quat::operator * (const Vec3& v)
{
	Vec3 uv, uuv;
	Vec3 qvec(x, y, z);
	uv = qvec.CrossProduct(v);
	uuv = qvec.CrossProduct(uv);
	uv *= (2.0f * w);
	uuv *= 2.0f;

	return v + uv + uuv;
}

void Quat::RadAxisToQuat(const f32 rad, const Vec3& axis)
{
	f32 halfRad = 0.5f * rad;
	f32 fSin = Math::Sin(halfRad);
	w = Math::Cos(halfRad);
	x = fSin * axis.x;
	y = fSin * axis.y;
	z = fSin * axis.z;
}
void Quat::AngleAxisToQuat(const f32 angle, const Vec3& axis)
{
	RadAxisToQuat(Math::DegToRad(angle), axis);
}
void Quat::ArcToQuat(const Vec3& f, const Vec3& t)
{
	f32 dot = f.x * t.x + f.y * t.y + f.z * t.z;
	f32 div;
	if (Math::IsEqual(dot, 1.f)) // Unit quaternion
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 1.0f;
	}
	else if (Math::IsEqual(dot, -1.f)) // 180 quaternion
	{
		x = 0.0f;
		y = 1.0f;
		z = 0.0f;
		w = 0.0f;
	}
	else
	{
		div = Math::Sqrt((dot + 1.0f)*2.0f);
		x = (f.y*t.z - f.z*t.y) / div;
		y = (f.z*t.x - f.x*t.z) / div;
		z = (f.x*t.y - f.y*t.x) / div;
		w = div * 0.5f;
	}
}
void Quat::MatToQuat(const Mat3& _Rot)
{
	f32 fTrace = _Rot.mat[0][0] + _Rot.mat[1][1] + _Rot.mat[2][2];
	f32 fRoot;

	if (fTrace > 0.0)
	{
		fRoot = Math::Sqrt(fTrace + 1.0);
		w = 0.5*fRoot;
		fRoot = 0.5 / fRoot;
		x = (_Rot.mat[2][1] - _Rot.mat[1][2])*fRoot;
		y = (_Rot.mat[0][2] - _Rot.mat[2][0])*fRoot;
		z = (_Rot.mat[1][0] - _Rot.mat[0][1])*fRoot;
	}
	else
	{
		static uint s_iNext[3] = { 1, 2, 0 };
		uint i = 0;
		if (_Rot.mat[1][1] > _Rot.mat[0][0])
			i = 1;
		if (_Rot.mat[2][2] > _Rot.mat[i][i])
			i = 2;
		uint j = s_iNext[i];
		uint k = s_iNext[j];

		fRoot = Math::Sqrt(_Rot.mat[i][i] - _Rot.mat[j][j] - _Rot.mat[k][k] + 1.0);
		f32* apkQuat[3] = { &x, &y, &z };
		*apkQuat[i] = 0.5*fRoot;
		fRoot = 0.5 / fRoot;
		w = (_Rot.mat[k][j] - _Rot.mat[j][k])*fRoot;
		*apkQuat[j] = (_Rot.mat[j][i] + _Rot.mat[i][j])*fRoot;
		*apkQuat[k] = (_Rot.mat[k][i] + _Rot.mat[i][k])*fRoot;
	}
}
void Quat::AxesToQuat(const Vec3& ex, const Vec3& ey, const Vec3& ez)
{
	Mat3 mRot;

	mRot.mat[0][0] = ex.x;
	mRot.mat[1][0] = ex.y;
	mRot.mat[2][0] = ex.z;

	mRot.mat[0][1] = ey.x;
	mRot.mat[1][1] = ey.y;
	mRot.mat[2][1] = ey.z;

	mRot.mat[0][2] = ez.x;
	mRot.mat[1][2] = ez.y;
	mRot.mat[2][2] = ez.z;

	MatToQuat(mRot);
}

void Quat::QuatToAxes(Vec3& ex, Vec3& ey, Vec3& ez)
{
	f32 tx = 2.0f*x;
	f32 ty = 2.0f*y;
	f32 tz = 2.0f*z;
	f32 twx = tx * w;
	f32 twy = ty * w;
	f32 twz = tz * w;
	f32 txx = tx * x;
	f32 txy = ty * x;
	f32 txz = tz * x;
	f32 tyy = ty * y;
	f32 tyz = tz * y;
	f32 tzz = tz * z;
	ex.x = 1.0f - tyy - tzz;
	ex.y = txy + twz;
	ex.z = txz - twy;
	ey.x = txy - twz;
	ey.y = 1.0f - txx - tzz;
	ey.z = tyz + twx;
	ez.x = txz + twy;
	ez.y = tyz - twx;
	ez.z = 1.0f - txx - tyy;
}
Vec3 Quat::QuatToXAxis()
{
	f32 ty = 2.0f*y;
	f32 tz = 2.0f*z;
	return Vec3(1.0f - ty * y - tz * z, ty*x + tz * w, tz*x - ty * w);
}
Vec3 Quat::QuatToYAxis()
{
	f32 tx = 2.0f*x;
	f32 tz = 2.0f*z;
	return Vec3(tx*y - tz * w, 1.0f - tx * x - tz * z, tz*y + tx * w);
}
Vec3 Quat::QuatToZAxis()
{
	f32 tx = 2.0f*x;
	f32 ty = 2.0f*y;
	return Vec3(tx*z + ty * w, ty*z - tx * w, 1.0f - tx * x - ty * y);
}
void Quat::QuatToRadAxis(f32& rad, Vec3& axis)
{
	f32 len = LengthSq();
	if (len > 0.0)
	{
		rad = 2.f * Math::ACos(w);
		f32 invLen = Math::InvSqrt(len);
		axis.x = x * invLen;
		axis.y = y * invLen;
		axis.z = z * invLen;
	}
	else
	{
		rad = 0.f;
		axis.x = 1.f;
		axis.y = 0.f;
		axis.z = 0.f;
	}
}
void Quat::QuatToAngleAxis(f32& angle, Vec3& axis)
{
	f32 rad;
	QuatToRadAxis(rad, axis);
	angle = Math::RadToDeg(rad);
}