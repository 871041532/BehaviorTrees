#include "Vec3.h"
#include "Quat.h"
#include "Mat4.h"
#include "Vec2.h"
const Vec3 Vec3::ZERO(0.f, 0.f, 0.f);
const Vec3 Vec3::XUNIT(1.f, 0.f, 0.f);
const Vec3 Vec3::YUNIT(0.f, 1.f, 0.f);
const Vec3 Vec3::ZUNIT(0.f, 0.f, 1.f);
const Vec3 Vec3::NXUNIT(-1.f, 0.f, 0.f);
const Vec3 Vec3::NYUNIT(0.f, -1.f, 0.f);
const Vec3 Vec3::NZUNIT(0.f, 0.f, -1.f);

Vec3 Vec3::TransformCoord(const Quat& q)
{
	Quat oq = q;
	Quat iq = oq.UnitInverse();
	Quat p(0, x, y, z);
	Quat rq = oq * p * iq;
	return Vec3(rq.x, rq.y, rq.z);
}

Vec3 Vec3::operator *(const Mat4& m) const
{
	return Vec3(x * m.mat[0][0] + y * m.mat[1][0] + z * m.mat[2][0] + m.mat[3][0],
		x * m.mat[0][1] + y * m.mat[1][1] + z * m.mat[2][1] + m.mat[3][1],
		x * m.mat[0][2] + y * m.mat[1][2] + z * m.mat[2][2] + m.mat[3][2]);
}

Vec3 Vec3::FromVec2(const Vec2& v)
{
	return Vec3(v.x, v.y, 0.f);
}
