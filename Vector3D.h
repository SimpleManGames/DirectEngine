#ifndef _VECTOR3D_H
#define _VECTOR3D_H

#include "Vector2D.h"

/*__declspec(align(32))*/ class Vector3D
{
public:
	union
	{
		float v[3];
		Vector2D xy;
		Vector2D st;
		struct { float x, y, z; };
		struct { float r, g, b; };
		struct { float s, t, p; };
	};
public:
	Vector3D()
		: x(0.0)
		, y(0.0)
		, z(0.0) {}
	Vector3D(const Vector3D& other) {
		x = other.x;
		y = other.y;
		z = other.z;
	}
	Vector3D(double xPos, double yPos, double zPos)
		: x((float)xPos)
		, y((float)yPos)
		, z((float)zPos) {}
	~Vector3D() {}

	static Vector3D ZeroVector();

	double       Length() const;                            // length of a vector
	double       Distance(const Vector3D& vec) const;       // distance between two vectors
	double       Dot(const Vector3D& vec) const;            // dot product
	static double Dot(const Vector3D& a, const Vector3D& b);
	Vector3D&    Normalize();                               // normalized vector
	static Vector3D	 Normal(const Vector3D &a);
	float		 Magnitude();
	Vector3D	 Reflect(const Vector3D &v, const Vector3D &a);
	Vector3D	 Project(const Vector3D &b);
															// operators
	Vector3D     operator-()const;                          // unary operator (negate)
	Vector3D     operator+(const Vector3D& rhs) const;      // add rhs
	Vector3D     operator-(const Vector3D& rhs) const;      // subtract rhs
	Vector3D&    operator+=(const Vector3D& rhs);           // add rhs and update this object
	Vector3D&	 operator+=(const float rhs);
	Vector3D&    operator-=(const Vector3D& rhs);           // subtract rhs and update this object
	Vector3D     operator*(const double scale) const;       // scale
	Vector3D     operator*(const Vector3D& rhs) const;      // multiply each element
	Vector3D&    operator*=(const double scale);            // scale and update this object
	Vector3D&    operator*=(const Vector3D& rhs);           // multiply each element and update this object
	Vector3D     operator/(const double scale) const;       // inverse scale
	Vector3D&    operator/=(const double scale);            // scale and update this object
	Vector3D	 operator*(const class Matrix4 & a);
	Vector3D	 operator*(const class Matrix3 & a);

	bool        operator==(const Vector3D& rhs) const;      // exact compare, no epsilon
	bool        operator!=(const Vector3D& rhs) const;      // exact compare, no epsilon
	bool        operator<(const Vector3D& rhs) const;       // comparison for sort
	bool        operator>(const Vector3D& rhs) const;
	float& operator [](unsigned int i) { return v[i]; }
	float operator [](unsigned int i) const { return v[i]; }
	Vector3D Cross(const Vector3D &a, const Vector3D &b);

	static Vector3D minv(const Vector3D &a, const Vector3D &b);
	static Vector3D maxv(const Vector3D &a, const Vector3D &b);
	static Vector3D clampv(const Vector3D &a, const Vector3D &a_min, const Vector3D &a_max);
};


#endif // !_VECTOR3D_H