#include "Matrix3D.h"

#ifndef _UNORDERED_SET_
#include <unordered_set>
#endif

Matrix3D::Matrix3D() { Identity(); }

Matrix3D::Matrix3D(float m0, float m1, float m2, float m3, 
				   float m4, float m5, float m6, float m7, 
				   float m8, float m9, float m10, float m11, 
				   float m12, float m13, float m14, float m15)
{
	m[0]  = m0;	 m[1]  = m1;  m[2]  = m2;  m[3]  = m3;
	m[4]  = m4;	 m[5]  = m5;  m[6]  = m6;  m[7]  = m7;
	m[8]  = m8;	 m[9]  = m9;  m[10] = m10; m[11] = m11;
	m[12] = m12; m[13] = m13; m[14] = m14; m[15] = m15;
}

Matrix3D::Matrix3D(const Matrix3D & other) {
	*this = other;
}

// WIP
float Matrix3D::GetDeterminant()
{
	return 0.0f;
}

Matrix3D & Matrix3D::Identity()
{
	m[0] = m[5] = m[10] = m[15] = 1.0f;
	m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.0f;
	return *this;
}
Matrix3D Matrix3D::Transpose()
{
	Matrix3D matTranspose = *this;

	std::swap(matTranspose[1], matTranspose[4]);
	std::swap(matTranspose[2], matTranspose[8]);
	std::swap(matTranspose[6], matTranspose[9]);
	std::swap(matTranspose[3], matTranspose[12]);
	std::swap(matTranspose[7], matTranspose[13]);
	std::swap(matTranspose[11], matTranspose[14]);

	return matTranspose;
}
Matrix3D Matrix3D::Invert()
{
	float determinant, invDeterminant;
	float tmp[16];

	#pragma region Math

	tmp[0]  =  m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
	tmp[1]  = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
	tmp[2]  =  m[1] * m[6]  * m[15] - m[1] * m[7]  * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[7]  - m[13] * m[3] * m[6];
	tmp[3]  = -m[1] * m[6]  * m[11] + m[1] * m[7]  * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[9]  * m[2] * m[7]  + m[9]  * m[3] * m[6];
	tmp[4]  = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
	tmp[5]  =  m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
	tmp[6]  = -m[0] * m[6]  * m[15] + m[0] * m[7]  * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[7]  + m[12] * m[3] * m[6];
	tmp[7]  =  m[0] * m[6]  * m[11] - m[0] * m[7]  * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[8]  * m[2] * m[7]  - m[8]  * m[3] * m[6];
	tmp[8]  =  m[4] * m[9]  * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
	tmp[9]  = -m[0] * m[9]  * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
	tmp[10] =  m[0] * m[5]  * m[15] - m[0] * m[7]  * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[7]  - m[12] * m[3] * m[5];
	tmp[11] = -m[0] * m[5]  * m[11] + m[0] * m[7]  * m[9]  + m[4] * m[1] * m[11] - m[4] * m[3] * m[9]  - m[8]  * m[1] * m[7]  + m[8]  * m[3] * m[5];
	tmp[12] = -m[4] * m[9]  * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
	tmp[13] =  m[0] * m[9]  * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
	tmp[14] = -m[0] * m[5]  * m[14] + m[0] * m[6]  * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[6]  + m[12] * m[2] * m[5];
	tmp[15] =  m[0] * m[5]  * m[10] - m[0] * m[6]  * m[9]  - m[4] * m[1] * m[10] + m[4] * m[2] * m[9]  + m[8]  * m[1] * m[6]  - m[8]  * m[2] * m[5];

#pragma endregion

	// check determinant if it is 0
	determinant = m[0] * tmp[0] + m[1] * tmp[4] + m[2] * tmp[8] + m[3] * tmp[12];
	if (fabs(determinant) <= EPSILON)
		return Identity(); // cannot inverse, make it idenety matrix

    // divide by the determinant
	invDeterminant = 1.0f / determinant;

	Matrix3D matInverse = Matrix3D(
		invDeterminant * tmp[0],
		invDeterminant * tmp[1],
		invDeterminant * tmp[2],
		invDeterminant * tmp[3],
		invDeterminant * tmp[4],
		invDeterminant * tmp[5],
		invDeterminant * tmp[6],
		invDeterminant * tmp[7],
		invDeterminant * tmp[8],
		invDeterminant * tmp[9],
		invDeterminant * tmp[10],
		invDeterminant * tmp[11],
		invDeterminant * tmp[12],
		invDeterminant * tmp[13],
		invDeterminant * tmp[14],
		invDeterminant * tmp[15]);

	return matInverse;
}

Vector3D Matrix3D::GetTranslation() const { return Vector3D(m[3], m[7], m[11]); }
Vector3D Matrix3D::GetScale() const { return Vector3D(m[0], m[5], m[10]); }
double Matrix3D::GetRotation() const {
	if ((m[1] != (-1 * m[4])) || (m[5] != m[0]))
		return -1.0;
	else
	{
		double scale_factor = sqrt((m[0] * m[5] - m[4] * m[1]));
		return acos(m[0] / scale_factor); // For radians
	}
}

Matrix3D Matrix3D::operator+(const Matrix3D & rhs) const
{
	return Matrix3D(
		m[0] + rhs[0], m[1] + rhs[1], m[2] + rhs[2], m[3] + rhs[3], 
		m[4] + rhs[4], m[5] + rhs[5], m[6] + rhs[6], m[7] + rhs[7], 
		m[8] + rhs[8], m[9] + rhs[9], m[10] + rhs[10], m[11] + rhs[11],
		m[12] + rhs[12], m[13] + rhs[13], m[14] + rhs[14], m[15] + rhs[15]);
}

Matrix3D Matrix3D::operator-(const Matrix3D & rhs) const
{
	return Matrix3D(
		m[0] - rhs[0], m[1] - rhs[1], m[2] - rhs[2], m[3] - rhs[3],
		m[4] - rhs[4], m[5] - rhs[5], m[6] - rhs[6], m[7] - rhs[7],
		m[8] - rhs[8], m[9] - rhs[9], m[10] - rhs[10], m[11] - rhs[11],
		m[12] - rhs[12], m[13] - rhs[13], m[14] - rhs[14], m[15] - rhs[15]);
}

Matrix3D & Matrix3D::operator+=(const Matrix3D & rhs)
{
		m[0] += rhs[0]; m[1] += rhs[1]; m[2] += rhs[2]; m[3] += rhs[3];
		m[4] += rhs[4]; m[5] += rhs[5]; m[6] += rhs[6]; m[7] += rhs[7];
		m[8] += rhs[8]; m[9] += rhs[9]; m[10] += rhs[10]; m[11] += rhs[11];
		m[12] += rhs[12]; m[13] += rhs[13]; m[14] += rhs[14]; m[15] += rhs[15];
		return *this;
}

Matrix3D & Matrix3D::operator-=(const Matrix3D & rhs)
{
	m[0] -= rhs[0]; m[1] -= rhs[1]; m[2] -= rhs[2]; m[3] -= rhs[3];
	m[4] -= rhs[4]; m[5] -= rhs[5]; m[6] -= rhs[6]; m[7] -= rhs[7];
	m[8] -= rhs[8]; m[9] -= rhs[9]; m[10] -= rhs[10]; m[11] -= rhs[11];
	m[12] -= rhs[12]; m[13] -= rhs[13]; m[14] -= rhs[14]; m[15] -= rhs[15];
	return *this;
}

Matrix3D Matrix3D::operator*(const Matrix3D & a) const
{
	return Matrix3D(
		m[0]  * a[0] + m[1]  * a[4] + m[2]  * m[8]  + m[3]  * a[12], 
		m[0]  * a[1] + m[1]  * a[5] + m[2]  * a[9]  + m[3]  * a[13], 
		m[0]  * a[2] + m[1]  * a[6] + m[2]  * a[10] + m[3]  * a[14], 
		m[0]  * a[3] + m[1]  * a[7] + m[2]  * a[11] + m[3]  * a[15],

		m[4]  * a[0] + m[5]  * a[4] + m[6]  * a[8]  + m[7]  * a[12], 
		m[4]  * a[1] + m[5]  * a[5] + m[6]  * a[9]  + m[7]  * a[13], 
		m[4]  * a[2] + m[5]  * a[6] + m[6]  * a[10] + m[7]  * a[14], 
		m[4]  * a[3] + m[5]  * a[7] + m[6]  * a[11] + m[7]  * a[15],

		m[8]  * a[0] + m[9]  * a[4] + m[10] * a[8]  + m[11] * a[12],
		m[8]  * a[1] + m[9]  * a[5] + m[10] * a[9]  + m[11] * a[13],
		m[8]  * a[2] + m[9]  * a[6] + m[10] * a[10] + m[11] * a[14],
		m[8]  * a[3] + m[9]  * a[7] + m[10] * a[11] + m[11] * a[15],

		m[12] * a[0] + m[13] * a[4] + m[14] * a[8]  + m[15] * a[12],
		m[12] * a[1] + m[13] * a[5] + m[14] * a[9]  + m[15] * a[13],
		m[12] * a[2] + m[13] * a[6] + m[14] * a[10] + m[15] * a[14],
		m[12] * a[3] + m[13] * a[7] + m[14] * a[11] + m[15] * a[15]);
}

Matrix3D & Matrix3D::operator*=(const Matrix3D & rhs)
{
	m[0] *= rhs[0]; m[1] *= rhs[1]; m[2] *= rhs[2]; m[3] *= rhs[3];
	m[4] *= rhs[4]; m[5] *= rhs[5]; m[6] *= rhs[6]; m[7] *= rhs[7];
	m[8] *= rhs[8]; m[9] *= rhs[9]; m[10] *= rhs[10]; m[11] *= rhs[11];
	m[12] *= rhs[12]; m[13] *= rhs[13]; m[14] *= rhs[14]; m[15] *= rhs[15];
	return *this;
}

bool Matrix3D::operator==(const Matrix3D & rhs) const
{
	return ((m[0] == rhs[0]) && (m[1] == rhs[1]) && (m[2] == rhs[2]) && (m[3] == rhs[3]) &&
		(m[4] == rhs[4]) && (m[5] == rhs[5]) && (m[6] == rhs[6]) && (m[7] == rhs[7]) &&
		(m[8] == rhs[8]) && (m[9] == rhs[9]) && (m[10] == rhs[10]) && (m[11] == rhs[11]) &&
		(m[12] == rhs[12]) && (m[13] == rhs[13]) && (m[14] == rhs[14]) && (m[15] == rhs[15]));
}

bool Matrix3D::operator!=(const Matrix3D & rhs) const
{
	return ((m[0] != rhs[0]) && (m[1] != rhs[1]) && (m[2] != rhs[2]) && (m[3] != rhs[3]) &&
		(m[4] != rhs[4]) && (m[5] != rhs[5]) && (m[6] != rhs[6]) && (m[7] != rhs[7]) &&
		(m[8] != rhs[8]) && (m[9] != rhs[9]) && (m[10] != rhs[10]) && (m[11] != rhs[11]) &&
		(m[12] != rhs[12]) && (m[13] != rhs[13]) && (m[14] != rhs[14]) && (m[15] != rhs[15]));

}

float Matrix3D::operator[](int index) const { return m[index]; }
float & Matrix3D::operator[](int index) { return m[index]; }

Matrix3D & Matrix3D::operator=(const Matrix3D & other)
{
	for (int i = 0; i < MAXNUMBER; ++i)
		this->m[i] = other.m[i];

	return *this;
}

Matrix3D Matrix3D::CreateIdentityMatrix() { return Matrix3D(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1); }
Matrix3D Matrix3D::CreateRotationMatrix(double radians)
{
	return Matrix3D((float)cos(radians), (float)-sin(radians), 0.0f, 0.0f,
					(float)sin(radians), (float)cos(radians), 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
}
Matrix3D Matrix3D::CreateScalingMatrix(double scale) { return CreateScalingMatrix(scale, scale, scale); }
Matrix3D Matrix3D::CreateScalingMatrix(double scaleX, double scaleY, double scaleZ)
{
	return Matrix3D((float)scaleX, 0.0f, 0.0f, 0.0f,
					0.0f, (float)scaleY, 0.0f, 0.0f,
					0.0f, 0.0f, (float)scaleZ, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
}
Matrix3D Matrix3D::CreateScalingMatrix(const Vector3D & scaleXYZ) { return CreateScalingMatrix(scaleXYZ.x, scaleXYZ.y, scaleXYZ.z); }
Matrix3D Matrix3D::CreateTranslationMatrix(const Vector3D & origin) { return CreateTranslationMatrix((double)origin.x, (double)origin.y, (double)origin.z); } 
Matrix3D Matrix3D::CreateTranslationMatrix(double tx, double ty, double tz)
{
	return Matrix3D(1.0f, 0.0f, 0.0f, (float)tx,
		0.0f, 1.0f, 0.0f, (float)ty,
		0.0f, 0.0f, 1.0f, (float)tz,
		0.0f, 0.0f, 0.0f, 1.0f);
}
