#ifndef _MATRIX3D_H
#define _MATRIX3D_H

//Additional Include Files
//------------------------
#ifndef _VECTOR4D_H
#include "Vector4D.h"
#endif
#ifndef _2DUTILL_H
#include "d2dutill.h"
#endif

__declspec(align(32)) class Matrix3D
{
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
	Matrix3D();  // init with identity
	Matrix3D(
		float m0, float m1, float m2, float m3,              // 1st column
		float m4, float m5, float m6, float m7,              // 2nd column
		float m8, float m9, float m10, float m11,
		float m12, float m13, float m14, float m15);             // 3rd column
	Matrix3D(const Matrix3D& other);
	~Matrix3D() {}

	float        GetDeterminant();

	Matrix3D&   Identity();
	Matrix3D    Transpose();                            // transpose itself and return reference
	Matrix3D    Invert();

	Vector3D GetTranslation() const;
	Vector3D GetScale() const;
	double GetRotation() const;

	// operators
	Matrix3D     operator+(const Matrix3D& rhs) const;      // add rhs
	Matrix3D     operator-(const Matrix3D& rhs) const;      // subtract rhs
	Matrix3D&    operator+=(const Matrix3D& rhs);           // add rhs and update this object
	Matrix3D&    operator-=(const Matrix3D& rhs);           // subtract rhs and update this object
	Matrix3D     operator*(const Matrix3D& a) const;		// multiplication: M3 = M1 * M2
	Matrix3D&    operator*=(const Matrix3D& rhs);           // multiplication: M1' = M1 * M2

	bool        operator==(const Matrix3D& rhs) const;      // exact compare, no epsilon
	bool        operator!=(const Matrix3D& rhs) const;      // exact compare, no epsilon

	float       operator[](int index) const;            // subscript operator v[0], v[1]
	float&      operator[](int index);                  // subscript operator v[0], v[1]

	Matrix3D&   operator=(const Matrix3D& other);       //set matrix equal to another matrix

														//static methods
	static Matrix3D CreateIdentityMatrix();                                 // Instantiate an identity matrix
	static Matrix3D CreateRotationMatrix(double radians);                   // Instantiate a rotation matrix
	static Matrix3D CreateScalingMatrix(double scale);                      // Instantiate a scale matrix
	static Matrix3D CreateScalingMatrix(double scaleX, double scaleY, double scaleZ);      // Instantiate a scale matrix
	static Matrix3D CreateScalingMatrix(const Vector3D& scaleXYZ);           // Instantiate a scale matrix
	static Matrix3D CreateTranslationMatrix(const Vector3D& origin);        // Instantiate a translation matrix
	static Matrix3D CreateTranslationMatrix(double tx, double ty, double tz);          // Instantiate a translation matrix

	//const D2D1_MATRIX_3X2_F& Matrix3D::ToMatrix3x2F();
private:
	static const int MAXNUMBER = 16;

	const float EPSILON = 0.00001f;
};

#endif