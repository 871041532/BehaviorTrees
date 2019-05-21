#pragma once

#include "math.hpp"

class Color32
{
public:
	inline Color32()
	{
		r = g = b = a = 0;
	}
	inline Color32(u8 _r, u8 _g, u8 _b, u8 _a)
		: r(_r), g(_g), b(_b), a(_a)
	{}
	inline Color32(u8 _r, u8 _g, u8 _b)
		: r(_r), g(_g), b(_b), a(0xff)
	{}
	inline Color32(uint _uiColor)
	{
		r = (u8)(_uiColor & 0x000000ff);
		g = (u8)((_uiColor & 0x0000ff00) >> 8);
		b = (u8)((_uiColor & 0x00ff0000) >> 16);
		a = (u8)((_uiColor & 0xff000000) >> 24);
	}
	inline Color32(const Color32& _Color)
		:r(_Color.r), g(_Color.g), b(_Color.b), a(_Color.a)
	{}

	Bool operator == (const Color32& _Color) const
	{
		return a == _Color.a && g == _Color.g && b == _Color.b && a == _Color.a;
	}
	Bool operator != (const Color32& _Color) const
	{
		return !operator==(_Color);
	}
	inline Color32 operator + (const Color32& _Color)
	{
		return Color32((u8)(r + _Color.r), (u8)(g + _Color.g), (u8)(b + _Color.b), (u8)(a + _Color.a));
	}
	inline Color32 operator * (const f32 _fv)
	{
		return Color32((u8)(r * _fv), (u8)(g * _fv), (u8)(b * _fv), (u8)(a * _fv));
	}
	inline friend Color32 operator * (const f32 _fv, const Color32& _v)
	{
		return Color32((u8)(_fv * _v.r), (u8)(_fv * _v.g), (u8)(_fv * _v.b), (u8)(_fv * _v.a));
	}
	inline friend Color32 operator * (const Color32& _v, const f32 _fv)
	{
		return Color32((u8)(_fv * _v.r), (u8)(_fv * _v.g), (u8)(_fv * _v.b), (u8)(_fv * _v.a));
	}
	inline Color32 operator / (const f32 _fv)
	{
		return Color32((u8)(r / _fv), (u8)(g / _fv), (u8)(b / _fv), (u8)(a / _fv));
	}
	inline friend Color32 operator / (const f32 _fv, const Color32& _v)
	{
		return Color32((u8)(_fv / _v.r), (u8)(_fv / _v.g), (u8)(_fv / _v.b), (u8)(_fv / _v.a));
	}
	inline friend Color32 operator / (const Color32& _v, const f32 _fv)
	{
		return Color32((u8)(_fv / _v.r), (u8)(_fv / _v.g), (u8)(_fv / _v.b), (u8)(_fv / _v.a));
	}

public:
	u8 r, g, b, a;
};

#define D_Color	Color32