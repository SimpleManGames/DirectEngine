#ifndef _MATRIX3_H
#define _MATRIX3_H

//Additional Include Files
//------------------------
#ifndef _VECTOR3D_H
#include "Vector3D.h"
#endif

#ifndef _2DUTILL_H
#include "d2dutill.h"
#endif

/*__declspec(align(32))*/ class Matrix3
{
public:
	union
	{
		float m[9];
		float mm[3][3];
		Vector3D c[3];
		struct
		{
			union { Vector3D c1; Vector2D right; };
			union { Vector3D c2; Vector2D up; };
			union { Vector3D c3; Vector2D position; };
		};
	};
public:
	// constructors
	Matrix3();  // init with identity
	Matrix3(float m0, float m1, float m2,              // 1st column
			 float m3, float m4, float m5,              // 2nd column
			 float m6, float m7, float m8);             // 3rd column
	Matrix3(const Matrix3& other);
	~Matrix3();

	float        GetDeterminant();

	Matrix3&    Identity();
	Matrix3    Transpose();                            // transpose itself and return reference
	Matrix3    Invert();

	Vector2D GetTranslation() const;
	Vector2D GetScale() const;
	double GetRotation() const;

	// operators
	Matrix3     operator+(const Matrix3& rhs) const;      // add rhs
	Matrix3     operator-(const Matrix3& rhs) const;      // subtract rhs
	Matrix3&    operator+=(const Matrix3& rhs);           // add rhs and update this object
	Matrix3&    operator-=(const Matrix3& rhs);           // subtract rhs and update this object
	Matrix3     operator*(const Matrix3& rhs) const;      // multiplication: M3 = M1 * M2
	Matrix3&    operator*=(const Matrix3& rhs);           // multiplication: M1' = M1 * M2

	bool        operator==(const Matrix3& rhs) const;      // exact compare, no epsilon
	bool        operator!=(const Matrix3& rhs) const;      // exact compare, no epsilon

	float       operator[](int index) const;            // subscript operator v[0], v[1]
	float&      operator[](int index);                  // subscript operator v[0], v[1]

	Matrix3&   operator=(const Matrix3& other);       //set matrix equal to another matrix

														//static methods
	static Matrix3 CreateIdentityMatrix();                                 // Instantiate an identity matrix
	static Matrix3 CreateRotationMatrix(double radians);                   // Instantiate a rotation matrix
	static Matrix3 CreateScalingMatrix(double scale);                      // Instantiate a scale matrix
	static Matrix3 CreateScalingMatrix(double scaleX, double scaleY);      // Instantiate a scale matrix
	static Matrix3 CreateScalingMatrix(const Vector2D& scaleXY);           // Instantiate a scale matrix
	static Matrix3 CreateTranslationMatrix(const Vector2D& origin);        // Instantiate a translation matrix
	static Matrix3 CreateTranslationMatrix(double tx, double ty);          // Instantiate a translation matrix

	const D2D1_MATRIX_3X2_F& Matrix3::ToMatrix3x2F();
private:
	static const int MAXNUMBER = 9;

	const float EPSILON = 0.00001f;
};

#endif