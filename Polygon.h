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


};


#endif // !_POLYGON_H
