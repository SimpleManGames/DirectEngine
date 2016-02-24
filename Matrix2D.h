#ifndef _MATRIX2D_H
#define _MATRIX2D_H

//Additional Include Files
//------------------------
#ifndef _VECTOR3D_H
#include "Vector3D.h"
#endif

#ifndef _2DUTILL_H
#include "d2dutill.h"
#endif

/*__declspec(align(32))*/ class Matrix2D
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
	Matrix2D();  // init with identity
	Matrix2D(float m0, float m1, float m2,              // 1st column
			 float m3, float m4, float m5,              // 2nd column
			 float m6, float m7, float m8);             // 3rd column
	Matrix2D(const Matrix2D& other);
	~Matrix2D();

	float        GetDeterminant();

	Matrix2D&    Identity();
	Matrix2D    Transpose();                            // transpose itself and return reference
	Matrix2D    Invert();

	Vector2D GetTranslation() const;
	Vector2D GetScale() const;
	double GetRotation() const;

	// operators
	Matrix2D     operator+(const Matrix2D& rhs) const;      // add rhs
	Matrix2D     operator-(const Matrix2D& rhs) const;      // subtract rhs
	Matrix2D&    operator+=(const Matrix2D& rhs);           // add rhs and update this object
	Matrix2D&    operator-=(const Matrix2D& rhs);           // subtract rhs and update this object
	Matrix2D     operator*(const Matrix2D& rhs) const;      // multiplication: M3 = M1 * M2
	Matrix2D&    operator*=(const Matrix2D& rhs);           // multiplication: M1' = M1 * M2

	bool        operator==(const Matrix2D& rhs) const;      // exact compare, no epsilon
	bool        operator!=(const Matrix2D& rhs) const;      // exact compare, no epsilon

	float       operator[](int index) const;            // subscript operator v[0], v[1]
	float&      operator[](int index);                  // subscript operator v[0], v[1]

	Matrix2D&   operator=(const Matrix2D& other);       //set matrix equal to another matrix

														//static methods
	static Matrix2D CreateIdentityMatrix();                                 // Instantiate an identity matrix
	static Matrix2D CreateRotationMatrix(double radians);                   // Instantiate a rotation matrix
	static Matrix2D CreateScalingMatrix(double scale);                      // Instantiate a scale matrix
	static Matrix2D CreateScalingMatrix(double scaleX, double scaleY);      // Instantiate a scale matrix
	static Matrix2D CreateScalingMatrix(const Vector2D& scaleXY);           // Instantiate a scale matrix
	static Matrix2D CreateTranslationMatrix(const Vector2D& origin);        // Instantiate a translation matrix
	static Matrix2D CreateTranslationMatrix(double tx, double ty);          // Instantiate a translation matrix

	const D2D1_MATRIX_3X2_F& Matrix2D::ToMatrix3x2F();
private:
	static const int MAXNUMBER = 9;

	const float EPSILON = 0.00001f;
};

#endif