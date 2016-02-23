#ifndef _COLLIDER_H
#define _COLLIDER_H

#include "Shape.h"
#include "Collision.h"
#include "Transform.h"

// Shapes!
class Collider
{
public:
	enum SHAPE { e_CIRCLE = 1, e_AABB = 2, e_RAY = 4, e_PLANE = 8 } shape;
	union
	{
		Circle  circle;
		AABB    aabb;
		Ray     ray;
		Plane   plane;
	};

	Collider();
	Collider(SHAPE s);
	Collider(const Collider& other);
	~Collider() { }
	ConvexHull chull;
};

CollisionData EvaluateCollision(const Transform &at, const Collider &ac,
	const Transform &bt, const Collider &bc);

#endif // !_COLLIDER_H