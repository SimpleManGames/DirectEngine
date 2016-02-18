#ifndef _VECTOR2D_H
#pragma once
#define _VECTOR2D_H

//C Runtime Header Files
#ifndef _INC_MATH
#include <math.h>
#endif

__declspec(align(32)) struct Vector2D
{
public:
	Vector2D()
		: x(0.0)
		, y(0.0)
	{}
	Vector2D(const Vector2D& other)
	{
		x = other.x;
		y = other.y;
	}
	Vector2D(double xPos, double yPos)
		: x(xPos)
		, y(yPos)
	{}
	~Vector2D()
	{}

	double x;
	double y;

	static Vector2D ZeroVector;

	double       Length() const;                            // length of a vector
	double       Distance(const Vector2D& vec) const;       // distance between two vectors
	double       Dot(const Vector2D& vec) const;            // dot product
	Vector2D&    Normalize();                               // normalized vector
	float		 Magnitude();
															// operators
	Vector2D     operator-()const;                          // unary operator (negate)
	Vector2D     operator+(const Vector2D& rhs) const;      // add rhs
	Vector2D     operator-(const Vector2D& rhs) const;      // subtract rhs
	Vector2D&    operator+=(const Vector2D& rhs);           // add rhs and update this object
	Vector2D&    operator-=(const Vector2D& rhs);           // subtract rhs and update this object
	Vector2D     operator*(const double scale) const;       // scale
	Vector2D     operator*(const Vector2D& rhs) const;      // multiply each element
	Vector2D&    operator*=(const double scale);            // scale and update this object
	Vector2D&    operator*=(const Vector2D& rhs);           // multiply each element and update this object
	Vector2D     operator/(const double scale) const;       // inverse scale
	Vector2D&    operator/=(const double scale);            // scale and update this object

	bool        operator==(const Vector2D& rhs) const;      // exact compare, no epsilon
	bool        operator!=(const Vector2D& rhs) const;      // exact compare, no epsilon
	bool        operator<(const Vector2D& rhs) const;        // comparison for sort
};

#endif