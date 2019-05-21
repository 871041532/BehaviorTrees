#include "Vec2.h"
#include "Vec3.h"
const Vec2 Vec2::kZERO(0.f, 0.f);
const Vec2 Vec2::kXUNIT(1.f, 0.f);
const Vec2 Vec2::kYUNIT(0.f, 1.f);
const Vec2 Vec2::kNXUNIT(-1.f, 0.f);
const Vec2 Vec2::kNYUNIT(0.f, -1.f);

Vec2 Vec2::FromVec3(const Vec3& v)
{
	return Vec2(v.x, v.y);
}