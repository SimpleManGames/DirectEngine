#ifndef _SHAPE_H
#define _SHAPE_H

#include "Matrix2D.h"
#include "Vector2D.h"
#include <vector>

// Undef

struct ConvexHull { std::vector<Vector2D> verts; };
struct Ray
{
	Vector2D  p, // Position
			  d; // Direction
	float	  l; // length (possibly infinite?) Just use a big value...
};
struct Plane
{
	Vector2D p, // Position
			 n; // Normal
};
struct Circle
{
	Vector2D  p;  // position
	float	  r; // radius
};
struct AABB
{
	Vector2D p, e; // position and half-extents 
	Vector2D minv() const; // p - e
	Vector2D maxv() const; // p + e
};

//Useful for taking a gameobject's transform and applying it
// to a shape for collision detection
AABB        operator*(const Matrix2D &m, const AABB       &a);
Circle      operator*(const Matrix2D &m, const Circle     &a);
Ray         operator*(const Matrix2D &m, const Ray        &a);
Plane       operator*(const Matrix2D &m, const Plane      &a);
ConvexHull  operator*(const Matrix2D &m, const ConvexHull &a);

#endif // !_SHAPE_H


// Redef
