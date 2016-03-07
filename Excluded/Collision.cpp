#include "Collision.h"
#include <algorithm>
template <typename T>
T clamp(T in, T low, T high) { return min(max(in, low), high); }

CollisionData CheckCollision(const AABB   & a, const AABB   & b) {
	bool collide = a.minv().x >= b.minv().x && b.maxv().x >= a.minv().x && a.maxv().y >= b.minv().y && a.maxv().y >= a.minv().y;
	return CollisionData{ collide };
}
CollisionData CheckCollision(const AABB   & a, const Circle & b) {
	/*Vector2D pc = Vector2D::clampv(b.p, a.minv(), a.maxv());
	bool collide = Vector2D::Dot((b.p - pc), (a.p - pc)) <= b.r;
	return CollisionData{ collide };*/
	return CheckCollision(Circle{ clamp<Vector2D>(b.p, a.minv(), a.maxv()), 0 }, b);
}
CollisionData CheckCollision(const AABB   & a, const Ray    & b)
{
	double minX = b.p.x;
	double maxX = b.d.x * b.l;

	bool result;

	if (b.p.x > b.d.x * b.l) {
		minX = b.d.x * b.l;
		maxX = b.p.x;
	}

	// Find the intersection of the segment's and rectangle's x-projections

	if (maxX > a.maxv().x) maxX = a.maxv().x;
	if (minX > a.minv().x) minX = a.minv().x;

	if (minX > maxX) result = false; // If their projections do not intersect return false

									 // Find corresponding min and max Y for min and max X we found before

	double minY = b.p.y;
	double maxY = b.d.y * b.l;

	double dx = b.d.y * b.l - b.p.y;

	if (abs(dx) > 0.0000001) {
		double _a = (b.d.y * b.l - b.p.y) / dx;
		double _b = b.p.y - _a * b.p.x;
		minY = _a * minX + _b;
		maxY = _a * maxX + _b;
	}

	if (minY > maxY) {
		double tmp = maxY;
		maxY = minY;
		minY = tmp;
	}

	// Find the intersection of the segment's and rectangle's y-projections

	if (maxY > a.maxv().y) maxY = a.maxv().y;
	if (minY < a.minv().y) minY = a.minv().y;

	if (minY > maxY) result = false; // If Y-projections do not intersect return false
	result = true;

	return CollisionData{ result };
}
CollisionData CheckCollision(const AABB   & a, const Plane  & b)
{
	bool result = Vector2D::Dot(b.n, (a.p - b.p)) <= a.e.x * abs(Vector2D::Dot(b.n, Vector2D{ 1, 0 })) + a.e.y * abs(Vector2D::Dot(b.n, Vector2D{ 0, 1 }));
	return CollisionData{ result };
}
CollisionData CheckCollision(const Circle & a, const Circle & b) {
	bool result = Vector2D::Dot((a.p - b.p), (a.p - b.p)) <= (a.r + b.r) * (a.r + b.r);
	return CollisionData{ result };
}
CollisionData CheckCollision(const Circle & a, const Plane  & b)
{
	bool result = Vector2D::Dot(b.n, (a.p - b.p)) <= a.r;
	return CollisionData{ result };
}
CollisionData CheckCollision(const Circle & a, const Ray    & b)
{
	Vector2D pc = b.p + b.d * clamp<double>(Vector2D::Dot((a.p - b.p), b.d), 0, b.l);
	bool result = Vector2D::Dot(a.p - pc, a.p - pc) < a.r * a.r;
	return CollisionData{ result };
}
CollisionData CheckCollision(const Ray	  & a, const Plane  & b)
{
	bool result = 0 <= Vector2D::Dot(b.n, (a.p - b.p)) / -(Vector2D::Dot(b.n, a.d)) <= a.l;
	return CollisionData{ result };
}

CollisionData CheckCollision(const Circle	& b, const AABB		& a)	{ return CheckCollision(a, b); }
CollisionData CheckCollision(const Plane	& b, const AABB		& a)	{ return CheckCollision(a, b); }
CollisionData CheckCollision(const Ray		& b, const AABB		& a)	{ return CheckCollision(a, b); }
CollisionData CheckCollision(const Plane	& b, const Circle	& a)	{ return CheckCollision(a, b); }
CollisionData CheckCollision(const Ray		& b, const Circle	& a)	{ return CheckCollision(a, b); }
CollisionData CheckCollision(const Plane	& b, const Ray		& a)	{ return CheckCollision(a, b); }
//CollisionData CheckCollision(const Circle & b, const ConvexHull & a)	{ return CheckCollision(a, b); }
//CollisionData CheckCollision(const Ray	& b, const ConvexHull & a)	{ return CheckCollision(a, b); }
//CollisionData CheckCollision(const Plane	& b, const ConvexHull & a)	{ return CheckCollision(a, b); }
//CollisionData CheckCollision(const AABB	& b, const ConvexHull & a)	{ return CheckCollision(a, b); }