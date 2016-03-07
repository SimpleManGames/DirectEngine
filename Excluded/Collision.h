#ifndef _COLLISION_H
#define _COLLISION_H

#include "Shape.h"
#include "Vector2D.h"

struct CollisionData // Wrapper for Minimum Translation Vector
{
	bool     isOverlap;         // Did we collide?
	float    PenetrationDepth;
	Vector2D  CollisionNormal;   // CollisionNormal * PenetrationDepth = Minimum Translation Vector, also called the impulse vector, very important! 
	Vector2D  PointOfContact;    // optional.
};

// Some distance formula
float point_plane_dist(const Vector2D &a, const Plane &b);
float ray_plane_dist(const Ray &a, const Plane &b);


// All of the basic tests
CollisionData CheckCollision(const AABB &a, const AABB &b);
CollisionData CheckCollision(const AABB &a, const Circle &b);
CollisionData CheckCollision(const AABB &a, const Ray &b);
CollisionData CheckCollision(const AABB &a, const Plane &b);

CollisionData CheckCollision(const Circle &a, const Circle &b);
CollisionData CheckCollision(const Circle &a, const Plane &b);
CollisionData CheckCollision(const Circle &a, const Ray &b);

CollisionData CheckCollision(const Ray &a, const Plane &b);


// Convex Hull vs remaining shapes
//CollisionData CheckCollision(const ConvexHull &A, const ConvexHull &B);
//CollisionData CheckCollision(const ConvexHull &A, const Circle &b);
//CollisionData CheckCollision(const ConvexHull &A, const Ray &b);
//CollisionData CheckCollision(const ConvexHull &A, const Plane &b);
//CollisionData CheckCollision(const ConvexHull &A, const AABB &b);



// flip overloads for lhs/rhs
CollisionData CheckCollision(const Circle &b, const AABB   &a);
CollisionData CheckCollision(const Plane  &b, const AABB   &a);
CollisionData CheckCollision(const Ray    &b, const AABB   &a);

CollisionData CheckCollision(const Plane  &b, const Circle &a);
CollisionData CheckCollision(const Ray    &b, const Circle &a);

CollisionData CheckCollision(const Plane  &b, const Ray    &a);

//CollisionData CheckCollision(const Circle &b, const ConvexHull &A);
//CollisionData CheckCollision(const Ray    &b, const ConvexHull &A);
//CollisionData CheckCollision(const Plane  &b, const ConvexHull &A);
//CollisionData CheckCollision(const AABB   &b, const ConvexHull &A);

#endif // !_COLLISION_H