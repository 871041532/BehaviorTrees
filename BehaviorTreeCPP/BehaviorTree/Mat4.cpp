#include "Mat4.h"
#include "Vec3.h"
#include "Mat3.h"
#include "Quat.h"
#include "Vec4.h"

inline Mat4::Mat4(const Vec3& v)
{
	mat[0][0] = 1.f;	mat[0][1] = 0.f;	mat[0][2] = 0.f;	mat[0][3] = 0.f;
	mat[1][0] = 0.f;	mat[1][1] = 1.f;	mat[1][2] = 0.f;	mat[1][3] = 0.f;
	mat[2][0] = 0.f;	mat[2][1] = 0.f;	mat[2][2] = 1.f;	mat[2][3] = 0.f;
	mat[3][0] = v.x;	mat[3][1] = v.y;	mat[3][2] = v.z;	mat[3][3] = 1.f;
}

Bool Mat4::operator == (const Mat4& m)
{
	for (uint row = 0; row < 4; ++row)
	{
		for (uint column = 0; column < 4; ++column)
		{
			if (Math::IsEqual(mat[row][column], m.mat[row][column]) == false)
				return false;
		}
	}
	return true;
}

Mat4 Mat4::operator + (const Mat4& m)
{
	Mat4 resultM;
	for (uint row = 0; row < 4; ++row)
	{
		for (uint column = 0; column < 4; ++column)
		{
			resultM[row][column] = mat[row][column] + m.mat[row][column];
		}
	}
	return resultM;
}

Mat4 Mat4::operator - (const Mat4& m)
{
	Mat4 resultM;
	for (uint row = 0; row < 4; ++row)
	{
		for (uint column = 0; column < 4; ++column)
		{
			resultM[row][column] = mat[row][column] - m.mat[row][column];
		}
	}
	return resultM;
}

Mat4 Mat4::operator - ()
{
	Mat4 resultM;
	for (uint row = 0; row < 4; ++row)
	{
		for (uint column = 0; column < 4; ++column)
		{
			resultM[row][column] = -mat[row][column];
		}
	}
	return resultM;
}

Mat4 Mat4::operator * (const Mat4& m)
{
	Mat4 resultM;
	for (uint row = 0; row < 4; ++row)
	{
		for (uint column = 0; column < 4; ++column)
		{
			resultM[row][column] = mat[row][0] * m.mat[0][column] +
				mat[row][1] * m.mat[1][column] +
				mat[row][2] * m.mat[2][column] +
				mat[row][3] * m.mat[3][column];
		}
	}
	return resultM;
}

Vec4 Mat4::operator * (const Vec4& v)
{
	Vec4 resultV;
	for (uint row = 0; row < 4; ++row)
	{
		resultV[row] = mat[row][0] * v[0] +
			mat[row][1] * v[1] +
			mat[row][2] * v[2] +
			mat[row][3] * v[3];
	}
	return resultV;
}

Mat4 Mat4::operator * (const f32 fv)
{
	Mat4 resultM;
	for (uint row = 0; row < 4; ++row)
	{
		for (uint column = 0; column < 4; ++column)
		{
			resultM[row][column] = mat[row][0] * fv;
		}
	}
	return resultM;
}
Mat4 operator * (const f32 fv, const Mat4& m)
{
	Mat4 resultM;
	for (uint row = 0; row < 4; ++row)
	{
		for (uint column = 0; column < 4; ++column)
		{
			resultM[row][column] = fv * m.mat[row][column];
		}
	}
	return resultM;
}
Vec4 operator * (const Vec4& v, const Mat4& m)
{
	Vec4 resultV;
	for (uint column = 0; column < 4; ++column)
	{
		resultV[column] = m.mat[0][column] * v[0] +
			m.mat[1][column] * v[1] +
			m.mat[2][column] * v[2] +
			m.mat[3][column] * v[3];
	}
	return resultV;
}
Mat4 Mat4::Transpose()
{
	Mat4 resultM;
	for (uint row = 0; row < 4; ++row)
	{
		for (uint column = 0; column < 4; ++column)
		{
			resultM[column][row] = mat[row][column];
		}
	}
	return resultM;
}
Mat4& Mat4::Translation(const Vec3& v)
{
	return Translation(v.x, v.y, v.z);
}
Mat4& Mat4::Translation(f32 x, f32 y, f32 z)
{
	mat[3][0] = mat[3][0] + x;//x*mat[0][0]+y*mat[1][0]+z*mat[2][0];
	mat[3][1] = mat[3][1] + y;//x*mat[0][1]+y*mat[1][1]+z*mat[2][1];
	mat[3][2] = mat[3][2] + z;//x*mat[0][2]+y*mat[1][2]+z*mat[2][2];
	//mat[3][3]=mat[3][3]+x*mat[0][3]+y*mat[1][3]+z*mat[2][3];

	return *this;
}

Mat4 Mat4::Inverse()
{
	Mat4 resultM;
	resultM = *this;
	uint is[4];
	uint js[4];

	for (s32 k = 0; k < 4; ++k)
	{
		f32 fMax = 0.0f;
		for (uint i = k; i < 4; i++)
		{
			for (uint j = k; j < 4; j++)
			{
				const f32 f = Math::Abs<f32>(resultM[i][j]);
				if (f > fMax)
				{
					fMax = f;
					is[k] = i;
					js[k] = j;
				}
			}
		}
		if (Math::IsZero(fMax))
			return ZERO;

		if (is[k] != k)
		{
			for (uint i = 0; i < 4; ++i)
			{
				f32 tmp = resultM[k][i];
				resultM[k][i] = resultM[is[k]][i];
				resultM[is[k]][i] = tmp;
			}
		}
		if (js[k] != k)
		{
			for (uint i = 0; i < 4; ++i)
			{
				f32 tmp = resultM[i][k];
				resultM[i][k] = resultM[i][js[k]];
				resultM[i][js[k]] = tmp;
			}
		}
		resultM[k][k] = 1.0f / resultM[k][k];
		for (uint j = 0; j < 4; j++)
		{
			if (j != k)
				resultM[k][j] *= resultM[k][k];
		}
		for (uint i = 0; i < 4; i++)
		{
			if (i != k)
			{
				for (uint j = 0; j < 4; j++)
				{
					if (j != k)
						resultM[i][j] = resultM[i][j] - resultM[i][k] * resultM[k][j];
				}
			}
		}
		for (uint i = 0; i < 4; i++)
		{
			if (i != k)
				resultM[i][k] *= -resultM[k][k];
		}
	}

	for (s32 k = 3; k >= 0; k--)
	{
		if (js[k] != k)
		{
			for (uint i = 0; i < 4; ++i)
			{
				f32 tmp = resultM[k][i];
				resultM[k][i] = resultM[js[k]][i];
				resultM[js[k]][i] = tmp;
			}
		}
		if (is[k] != k)
		{
			for (uint i = 0; i < 4; ++i)
			{
				f32 tmp = resultM[i][k];
				resultM[i][k] = resultM[i][is[k]];
				resultM[i][is[k]] = tmp;
			}
		}
	}
	return resultM;
}

Mat4& Mat4::operator *=(const Mat4 &m)
{
	Mat4 resultM;
	for (uint row = 0; row < 4; ++row)
	{
		for (uint column = 0; column < 4; ++column)
		{
			resultM[row][column] = mat[row][0] * m.mat[0][column] +
				mat[row][1] * m.mat[1][column] +
				mat[row][2] * m.mat[2][column] +
				mat[row][3] * m.mat[3][column];
		}
	}
	*this = resultM;
	return *this;
}
Mat4& Mat4::Rotation(const Quat& q)
{
	f32 x, y, z;

	Mat3 r(q);

	x = mat[0][0]; y = mat[1][0]; z = mat[2][0];
	mat[0][0] = x * r[0][0] + y * r[0][1] + z * r[0][2];
	mat[1][0] = x * r[1][0] + y * r[1][1] + z * r[1][2];
	mat[2][0] = x * r[2][0] + y * r[2][1] + z * r[2][2];

	x = mat[0][1]; y = mat[1][1]; z = mat[2][1];
	mat[0][1] = x * r[0][0] + y * r[0][1] + z * r[0][2];
	mat[1][1] = x * r[1][0] + y * r[1][1] + z * r[1][2];
	mat[2][1] = x * r[2][0] + y * r[2][1] + z * r[2][2];

	x = mat[0][2]; y = mat[1][2]; z = mat[2][2];
	mat[0][2] = x * r[0][0] + y * r[0][1] + z * r[0][2];
	mat[1][2] = x * r[1][0] + y * r[1][1] + z * r[1][2];
	mat[2][2] = x * r[2][0] + y * r[2][1] + z * r[2][2];

	x = mat[0][3]; y = mat[1][3]; z = mat[2][3];
	mat[0][3] = x * r[0][0] + y * r[0][1] + z * r[0][2];
	mat[1][3] = x * r[1][0] + y * r[1][1] + z * r[1][2];
	mat[2][3] = x * r[2][0] + y * r[2][1] + z * r[2][2];

	return *this;
}
Mat4& Mat4::Scale(const f32 x, const f32 y, const f32 z)
{
	mat[0][0] *= x; mat[0][1] *= x; mat[0][2] *= x; mat[0][3] *= x;
	mat[1][0] *= y; mat[1][1] *= y; mat[1][2] *= y; mat[1][3] *= y;
	mat[2][0] *= z; mat[2][1] *= z; mat[2][2] *= z; mat[2][3] *= z;
	return *this;
}
