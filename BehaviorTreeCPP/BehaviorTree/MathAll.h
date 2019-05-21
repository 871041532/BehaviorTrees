#pragma once
#include "Math.hpp"
#include "Color32.hpp"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Quat.h"
#include "Mat3.h"
#include "Mat4.h"

const Mat3 Mat3::ZERO(0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
const Mat3 Mat3::IDENTITY(1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f);
const Mat4 Mat4::ZERO(0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
const Mat4 Mat4::IDENTITY(1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f);
const Quat Quat::ZERO(0.f, 0.f, 0.f, 0.f);
const Quat Quat::IDENTITY(1.f, 0.f, 0.f, 0.f);
const f32 Math::kTPI = 3.1416;
const f32 Math::kFLOAT_EPSILON = 0.001;

