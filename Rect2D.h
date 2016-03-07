#ifndef _RECT2D_H
#define _RECT2D_H

#include "Vector2D.h"
#include "Circle.h"

template <typename T>
T clamp(T in, T low, T high) { return min(max(in, low), high); }

struct Rect2D
{
public:
	Rect2D()
		: left(0)
		, top(0)
		, right(0)
		, bottom(0)
	{
		width = right - left;
		height = bottom - top;
		min = { top, left };
		max = { bottom, right };
	}
	Rect2D(const Rect2D& r)
		: left(r.left)
		, top(r.top)
		, right(r.right)
		, bottom(r.bottom)
	{
		width = r.width;
		height = r.height;
		pos = { top + (width / 2), right + (height / 2) };
		min = { top, left };
		max = { bottom, right };
	}
	Rect2D(double l, double t, double r, double b)
		: left(l)
		, top(t)
		, right(r)
		, bottom(b)
	{
		width = right - left;
		height = bottom - top;
		pos = { top + (width / 2), right + (height / 2) };
		min = { top, left };
		max = { bottom, right };
	}
	Rect2D(const Vector2D& v1, const Vector2D& v2)
		: top(v1.y)
		, left(v1.x)
		, bottom(v2.y)
		, right(v2.x)
	{
		width = right - left;
		height = bottom - top;
		pos = { top + (width / 2), left + (height / 2) };
		min = { top, left };
		max = { bottom, right };
	}
	~Rect2D() {  }

	double top;
	double left;
	double bottom;
	double right;

	double width;
	double height;

	Vector2D pos;
	// Represents the lower bounds
	Vector2D min;
	// Represents the higher bounds
	Vector2D max;

	static const Rect2D empty;

	Rect2D operator= (const Rect2D other)
	{
		Rect2D r;

		r.left = other.left;
		r.right = other.right;
		r.bottom = other.bottom;
		r.top = other.top;

		r.width = other.width;
		r.height = other.height;

		r.min = other.min;
		r.max = other.max;

		return r;
	}
	bool operator== (const Rect2D& other)
	{
		if (this->left == other.left && 
			this->right == other.right && 
			this->top == other.top && 
			this->bottom == other.bottom)
			return true;

		return false;
	}

	bool IsEqual(Rect2D& other)
	{
		if (this->left == other.left && this->right == other.right && this->top == other.top && this->bottom == other.bottom)
			return true;

		return false;
	}
	// Checks collision with another Rect2D
	bool vsRect2D(Rect2D b)
	{
		// Exit with no intersection if found separated along an axis
		if (this->max.x < b.min.x || this->min.x > b.max.x) return false;
		if (this->max.y < b.min.y || this->min.y > b.max.y) return false;

		// No separating axis found, therefor there is at least one overlapping axis
		return true;
	}
	bool vsRect2D(double l, double t, double r, double b) { return this->vsRect2D({ l, t, r, b }); }
	bool vsRect2D(const Vector2D& v1, const Vector2D& v2) { return this->vsRect2D({ v1, v2 }); }

	bool vsCircle(Circle c)
	{
		Vector2D pc = Vector2D::clampv(c.position, this->min, this->max);
		return (Dot((c.position - pc), (c.position - pc)) <= c.radius * c.radius);
		//return Circle(Vector2D::clampv(c.position, this->min, this->max), 0).vsCircle(c);
	}
	bool vsCircle(const Vector2D& p, float r);
	bool vsCircle(float x, float y, float r);
};

inline bool operator== (const Rect2D r1, const Rect2D& r2)
{
	return (r1.left == r2.left && r1.right == r2.right && r1.top == r2.top && r1.bottom == r2.bottom);
}
inline bool operator!= (const Rect2D r1, const Rect2D& r2)
{
	return !(r1 == r2);
}

#endif