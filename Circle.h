#ifndef _CIRCLE_H
#define _CIRCLE_H

#include "Vector2D.h"
struct Circle
{
public:
	Circle()
		: position(0, 0)
		, radius(0) { }
	Circle(const Vector2D& v, float r)
		: position(v)
		, radius(r) { }
	Circle(double _x, double _y, float r)
		: position(_x, _y)
		, radius(r) { }

	Circle(const Circle& c)
		: position(c.position)
		, radius(c.radius) {  }
	~Circle() {  }


	Vector2D position;
	
	float radius;

	static const Circle empty;

	Circle operator= (const Circle other)
	{
		Circle c;
		
		c.position = other.position;
		c.radius = other.radius;

		return c;
	}
	bool operator== (const Circle& other)
	{
		if (this->position == other.position &&
			this->radius == other.radius)
			return true;

		return false;
	}

	bool IsEqual(Circle& other) 
	{
		if (this->position == other.position &&
			this->radius == other.radius)
			return true;

		return false;
	}

	bool vsCircle(Circle c)
	{
		float r = this->radius + c.radius;
		r *= r;
		return r > sqrtf((this->position.x - c.position.x) * (this->position.x - c.position.x) + (this->position.y - c.position.y) * (this->position.y - c.position.y));
	}
	bool vsCircle(const Vector2D& p, float r) { return vsCircle({ p, r }); }
	bool vsCircle(float x, float y, float r) { return vsCircle({ { x, y }, r }); }
};

inline bool operator== (const Circle c1, const Circle& c2)
{
	return (c1.position == c2.position && c1.radius == c2.radius);
}
inline bool operator!= (const Circle c1, const Circle& c2)
{
	return !(c1 == c2);
}

#endif
