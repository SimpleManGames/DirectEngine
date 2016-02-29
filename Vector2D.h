#ifndef _VECTOR2D_H
#define _VECTOR2D_H

//C Runtime Header Files
#ifndef _INC_MATH
#include <cmath>
#endif


/*__declspec(align(32))*/ struct Vector2D
{
	union
	{
		struct { float x, y; };
		float v[2];
	};
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
		: x((float)xPos)
		, y((float)yPos)
	{}
	~Vector2D()
	{}

	static Vector2D ZeroVector;

	double       Length() const;                            // length of a vector
	double       Distance(const Vector2D& vec) const;       // distance between two vectors
	double       Dot(const Vector2D& vec) const;            // dot product
	static double Dot(const Vector2D &a, const Vector2D &b);
	Vector2D&    Normalize();                               // normalized vector
	static Vector2D	 Normal(const Vector2D &a);
	float		 Magnitude();
	float		 Angle();
	Vector2D	 Reflect(const Vector2D &v, const Vector2D &a);
	Vector2D	 Project(const Vector2D &b);
	static Vector2D	 Perp(const Vector2D &a);

	static Vector2D fromAngle(float a);
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
	bool        operator>(const Vector2D& rhs) const;        // comparison for sort

	float &operator[](unsigned idx) { return v[idx]; }
	float  operator[](unsigned idx) const { return v[idx]; }

	static Vector2D minv(const Vector2D &a, const Vector2D &b);
	static Vector2D maxv(const Vector2D &a, const Vector2D &b);
	static Vector2D clampv(const Vector2D &a, const Vector2D &a_min, const Vector2D &a_max);
};

#endif