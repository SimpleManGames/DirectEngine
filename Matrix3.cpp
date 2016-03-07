#include "Matrix3.h"

#ifndef _UNORDERED_SET_
#include <unordered_set>
#endif


Matrix3::Matrix3() { Identity(); }
Matrix3::Matrix3(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8) {
	m[0] = m0; m[1] = m1; m[2] = m2;
	m[3] = m3; m[4] = m4; m[5] = m5;
	m[6] = m6; m[7] = m7; m[8] = m8;
}

Matrix3::Matrix3(const Matrix3 & other) { *this = other; }

Matrix3::~Matrix3() {
	if(this == NULL)
		free(this);
}

float Matrix3::GetDeterminant() { return m[0] * (m[4] * m[8] - m[5] * m[7]) - m[1] * (m[3] * m[8] - m[5] * m[6]) + m[2] * (m[3] * m[7] - m[4] * m[6]); }

inline Matrix3& Matrix3::Identity()
{
	m[0] = m[4] = m[8] = 1.0f;
	m[1] = m[2] = m[3] = m[5] = m[6] = m[7] = 0.0f;
	return *this;
}
Matrix3 Matrix3::Transpose()
{
	Matrix3 matTranspose = *this;

	std::swap(matTranspose[1], matTranspose[3]);
	std::swap(matTranspose[2], matTranspose[6]);
	std::swap(matTranspose[5], matTranspose[7]);

	return matTranspose;
}
Matrix3 Matrix3::Invert()
{
	float determinant, invDeterminant;
	float tmp[9];

	tmp[0] = m[4] * m[8] - m[5] * m[7];
	tmp[1] = m[2] * m[7] - m[1] * m[8];
	tmp[2] = m[1] * m[5] - m[2] * m[4];
	tmp[3] = m[5] * m[6] - m[3] * m[8];
	tmp[4] = m[0] * m[8] - m[2] * m[6];
	tmp[5] = m[2] * m[3] - m[0] * m[5];
	tmp[6] = m[3] * m[7] - m[4] * m[6];
	tmp[7] = m[1] * m[6] - m[0] * m[7];
	tmp[8] = m[0] * m[4] - m[1] * m[3];

	// check determinant if it is 0
	determinant = m[0] * tmp[0] + m[1] * tmp[3] + m[2] * tmp[6];
	if (fabs(determinant) <= EPSILON)
		return Identity(); // cannot inverse, make it idenety matrix

						   // divide by the determinant
	invDeterminant = 1.0f / determinant;

	Matrix3 matInverse = Matrix3(invDeterminant * tmp[0],
		invDeterminant * tmp[1],
		invDeterminant * tmp[2],
		invDeterminant * tmp[3],
		invDeterminant * tmp[4],
		invDeterminant * tmp[5],
		invDeterminant * tmp[6],
		invDeterminant * tmp[7],
		invDeterminant * tmp[8]);

	return matInverse;
}

Vector2D Matrix3::GetTranslation() const { return Vector2D(m[2], m[5]); }
Vector2D Matrix3::GetScale() const { return Vector2D(m[0], m[4]); }
double Matrix3::GetRotation() const
{
	if ((m[1] != (-1 * m[3])) || (m[4] != m[0]))
		return -1.0;
	else
	{
		double scale_factor = sqrt((m[0] * m[4] - m[3] * m[1]));
		return acos(m[0] / scale_factor); // For radians
	}
}

Matrix3 Matrix3::operator+(const Matrix3& rhs) const
{
	return Matrix3(m[0] + rhs[0], m[1] + rhs[1], m[2] + rhs[2],
		m[3] + rhs[3], m[4] + rhs[4], m[5] + rhs[5],
		m[6] + rhs[6], m[7] + rhs[7], m[8] + rhs[8]);
}
Matrix3 Matrix3::operator-(const Matrix3& rhs) const
{
	return Matrix3(m[0] - rhs[0], m[1] - rhs[1], m[2] - rhs[2],
		m[3] - rhs[3], m[4] - rhs[4], m[5] - rhs[5],
		m[6] - rhs[6], m[7] - rhs[7], m[8] - rhs[8]);
}
Matrix3& Matrix3::operator+=(const Matrix3& rhs)
{
	m[0] += rhs[0];  m[1] += rhs[1];  m[2] += rhs[2];
	m[3] += rhs[3];  m[4] += rhs[4];  m[5] += rhs[5];
	m[6] += rhs[6];  m[7] += rhs[7];  m[8] += rhs[8];
	return *this;
}
Matrix3& Matrix3::operator-=(const Matrix3& rhs)
{
	m[0] -= rhs[0];  m[1] -= rhs[1];  m[2] -= rhs[2];
	m[3] -= rhs[3];  m[4] -= rhs[4];  m[5] -= rhs[5];
	m[6] -= rhs[6];  m[7] -= rhs[7];  m[8] -= rhs[8];
	return *this;
}

Matrix3 Matrix3::operator*(const Matrix3& rhs) const {
	return Matrix3(
		m[0] * rhs[0] + m[3] * rhs[1] + m[6] * rhs[2],
		m[1] * rhs[0] + m[4] * rhs[1] + m[7] * rhs[2],
		m[2] * rhs[0] + m[5] * rhs[1] + m[8] * rhs[2],

		m[0] * rhs[3] + m[3] * rhs[4] + m[6] * rhs[5],
		m[1] * rhs[3] + m[4] * rhs[4] + m[7] * rhs[5],
		m[2] * rhs[3] + m[5] * rhs[4] + m[8] * rhs[5],
		
		m[0] * rhs[6] + m[3] * rhs[7] + m[6] * rhs[8],
		m[1] * rhs[6] + m[4] * rhs[7] + m[7] * rhs[8],
		m[2] * rhs[6] + m[5] * rhs[7] + m[8] * rhs[8]);
}
Matrix3& Matrix3::operator*=(const Matrix3& rhs) {
	*this = *this * rhs;
	return *this;
}

bool Matrix3::operator==(const Matrix3& rhs) const {
	return (m[0] == rhs[0]) && (m[1] == rhs[1]) && (m[2] == rhs[2]) &&
		(m[3] == rhs[3]) && (m[4] == rhs[4]) && (m[5] == rhs[5]) &&
		(m[6] == rhs[6]) && (m[7] == rhs[7]) && (m[8] == rhs[8]);
}
bool Matrix3::operator!=(const Matrix3& rhs) const {
	return (m[0] != rhs[0]) || (m[1] != rhs[1]) || (m[2] != rhs[2]) ||
		(m[3] != rhs[3]) || (m[4] != rhs[4]) || (m[5] != rhs[5]) ||
		(m[6] != rhs[6]) || (m[7] != rhs[7]) || (m[8] != rhs[8]);
}

float Matrix3::operator[](int index) const { return m[index]; }
float& Matrix3::operator[](int index) { return m[index]; }

Matrix3& Matrix3::operator=(const Matrix3& other) {
	for (int i = 0; i < MAXNUMBER; ++i)
		this->m[i] = other.m[i];

	return *this;
}

Matrix3 Matrix3::CreateIdentityMatrix() { return Matrix3(1, 0, 0, 0, 1, 0, 0, 0, 1); }

Matrix3 Matrix3::CreateRotationMatrix(double angle) {
	return Matrix3((float)cos(angle), (float)-sin(angle), 0.0f,
					(float)sin(angle), (float)cos(angle) , 0.0f,
								 0.0f,				 0.0f, 1.0f);
}

Matrix3 Matrix3::CreateScalingMatrix(double scale) { return CreateScalingMatrix(scale, scale); }
Matrix3 Matrix3::CreateScalingMatrix(const Vector2D& scaleXY) { return CreateScalingMatrix(scaleXY.x, scaleXY.y); }
Matrix3 Matrix3::CreateScalingMatrix(double scaleX, double scaleY)
{
	return Matrix3((float)scaleX,          0.0f, 0.0f,
							 0.0f, (float)scaleY, 0.0f,
							 0.0f,			0.0f, 1.0f);
}

Matrix3 Matrix3::CreateTranslationMatrix(const Vector2D& origin)
{
	return Matrix3(		   1.0f,			0.0f, 0.0f,
							   0.0f,			1.0f, 0.0f,
					(float)origin.x, (float)origin.y, 1.0f);
}
Matrix3 Matrix3::CreateTranslationMatrix(double tx, double ty) { return CreateTranslationMatrix(Vector2D(tx, ty)); }

const D2D1_MATRIX_3X2_F& Matrix3::ToMatrix3x2F()
{
	D2D1::Matrix3x2F mat;
	
    mat._11 = (FLOAT)m[0];
	mat._12 = (FLOAT)m[1];
	mat._21 = (FLOAT)m[3];
	mat._22 = (FLOAT)m[4];
	mat._31 = (FLOAT)m[2];
	mat._32 = (FLOAT)m[5];

	return mat;
}