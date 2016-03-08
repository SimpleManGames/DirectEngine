#ifndef _PLANE_H
#define _PLANE_H

#include "Vector2D.h"

struct Plane
{
public:
	Plane()
		: pos(0, 0)
		, normal(0, 0) { }
	Plane(const Plane& p)
		: pos(p.pos)
		, normal(p.normal) { }
	Plane(Vector2D& _pos, Vector2D& _normal)
		: pos(_pos)
		, normal(_normal) { }
	Plane(double x, double y, Vector2D& _normal)
		: pos(x, y)
		, normal(_normal) { }
	Plane(Vector2D& _pos, double nx, double ny)
		: pos(_pos)
		, normal(nx, ny) { }
	Plane(double x, double y, double nx, double ny)
		: pos(x, y)
		, normal(nx, ny) { }
	~Plane() { }

	Vector2D pos;
	Vector2D normal;

	static const Plane empty;
	Plane operator=(const Plane& other)
	{
		Plane p;

		p.pos = other.pos;
		p.normal = other.normal;

		return p;
	}
	bool operator==(const Plane& other)
	{
		return (this->pos == other.pos &&
				this->normal == other.normal);
	}

	bool IsEqual(Plane& other)
	{
		return (this->pos == other.pos &&
				this->normal == other.normal);
	}
};

inline bool operator==(const Plane& p1, const Plane& p2)
{
	return (p1.pos == p2.pos &&
			p1.normal == p2.normal);
}
inline bool operator!=(const Plane& p1, const Plane& p2)
{
	return !(p1 == p2);
}

#endif // !_PLANE_H