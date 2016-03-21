#ifndef _MATRIX4_H
#define _MATRIX4_H

//Additional Include Files
//------------------------
#ifndef _VECTOR4D_H
#include "Vector4D.h"
#endif
#include "Vector3D.h"
#ifndef _2DUTILL_H
#include "d2dutill.h"
#endif
#include "Quaternion.h"

/*__declspec(align(32))*/ class Matrix4
{
public:
	union
	{
		float m[16];
		Vector4D  c[4];
		float mm[4][4];
		struct
		{
			union { Vector4D c1; Vector3D right; };
			union { Vector4D c2; Vector3D up; };
			union { Vector4D c3; Vector3D forward; };
			union { Vector4D c4; Vector3D position; };
		};
	};
public:
	// constructors
	Matrix4();  // init with identity
	Matrix4(
		float m0, float m1, float m2, float m3,              // 1st column
		float m4, float m5, float m6, float m7,              // 2nd column
		float m8, float m9, float m10, float m11,
		float m12, float m13, float m14, float m15);             // 3rd column
	Matrix4(const Matrix4& other);
	~Matrix4() {}

	float        GetDeterminant();

	Matrix4&   Identity();
	Matrix4    Transpose();                            // transpose itself and return reference
	Matrix4    Invert();

	Vector3D GetTranslation() const;
	Vector3D GetScale() const;
	double GetRotation() const;

	// operators
	Matrix4     operator+(const Matrix4& rhs) const;      // add rhs
	Matrix4     operator-(const Matrix4& rhs) const;      // subtract rhs
	Matrix4&    operator+=(const Matrix4& rhs);           // add rhs and update this object
	Matrix4&    operator-=(const Matrix4& rhs);           // subtract rhs and update this object
	Matrix4     operator*(const Matrix4& a) const;		// multiplication: M3 = M1 * M2
	Matrix4&    operator*=(const Matrix4& rhs);           // multiplication: M1' = M1 * M2

	bool        operator==(const Matrix4& rhs) const;      // exact compare, no epsilon
	bool        operator!=(const Matrix4& rhs) const;      // exact compare, no epsilon

	float       operator[](int index) const;            // subscript operator v[0], v[1]
	float&      operator[](int index);                  // subscript operator v[0], v[1]

	Matrix4&   operator=(const Matrix4& other);       //set matrix equal to another matrix

														//static methods
	static Matrix4 CreateIdentityMatrix();                                 // Instantiate an identity matrix
	static Matrix4 CreateRotationMatrix(double radians);                   // Instantiate a rotation matrix
	static Matrix4 CreateScalingMatrix(double scale);                      // Instantiate a scale matrix
	static Matrix4 CreateScalingMatrix(double scaleX, double scaleY, double scaleZ);      // Instantiate a scale matrix
	static Matrix4 CreateScalingMatrix(const Vector3D& scaleXYZ);           // Instantiate a scale matrix
	static Matrix4 CreateTranslationMatrix(const Vector3D& origin);        // Instantiate a translation matrix
	static Matrix4 CreateTranslationMatrix(double tx, double ty, double tz);          // Instantiate a translation matrix

	const D2D1_MATRIX_3X2_F& Matrix4::ToMatrix3x2F();

	static Matrix4 toMatrix4(Quaternion q, Vector3D v, float scale)
	{
		Matrix3 rotation;

		q.toRotationMatrix(rotation);

		rotation *= scale;

		return Matrix4(rotation[0], rotation[1], rotation[2], v[0],
			rotation[3], rotation[4], rotation[5], v[1],
			rotation[6], rotation[7], rotation[8], v[2],
			0, 0, 0, 1);
	}
	static Matrix4 toMatrix4(Quaternion q, Vector3D v, Matrix3 scale)
	{
		Matrix3 rotation;

		q.toRotationMatrix(rotation);

		rotation *= scale;

		return Matrix4(rotation[0], rotation[1], rotation[2], v[0],
			rotation[3], rotation[4], rotation[5], v[1],
			rotation[6], rotation[7], rotation[8], v[2],
			0, 0, 0, 1);
	}
private:
	static const int MAXNUMBER = 16;

	const float EPSILON = 0.00001f;
};

#endif