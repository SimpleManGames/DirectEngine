#ifndef _POLYGON_H
#define _POLYGON_H

#include <vector>
#include "Vector2D.h"

struct Polygon
{
public:
	Polygon()
		: points(NULL) { }
	Polygon(const Polygon& p)
		: points(p.points) { }
	Polygon(std::vector<Vector2D> _points)
		: points(_points) { }
	~Polygon() { };

	std::vector<Vector2D> points;

	static const Polygon empty;

	Polygon operator=(const Polygon& other)
	{
		Polygon p;

		p.points = other.points;

		return p;
	}
	bool operator==(const Polygon& other)
	{
		if (this->points.size() == other.points.size())
			for (int i = 0; i < this->points.size(); ++i)
				if (this->points[i] == other.points[i])
					continue;
				else
					return false;

		return true;
	}
	Vector2D operator[](int index)
	{
		return this->points[index];
	}

	int vsPolygon(Polygon& a, Polygon& b);
};

inline bool operator==(const Polygon p1, const Polygon p2)
{
	return (p1 == p2);
}
inline bool operator!=(const Polygon p1, const Polygon p2)
{
	return !(p1 == p2);
}

#endif // !_POLYGON_H
