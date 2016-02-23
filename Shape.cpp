#include "Shape.h"
#include "Matrix2D.h"
#include "Matrix3D.h"

AABB operator*(const Matrix3D &m, const AABB &a)
{
	Vector2D omin = a.minv();
	Vector2D omax = a.maxv();

	Vector2D rmin = m[2].xy;
	Vector2D rmax = m[2].xy;

	float p, q;

	for (unsigned j = 0; j < 2; ++j)
		for (unsigned i = 0; i < 2; ++i)
		{
			p = omin[i] * m[i][j];
			q = omax[i] * m[i][j];

			if (p < q) std::swap(p, q);
			rmin[j] += p;
			rmax[j] += q;
		}
	return{ (rmin + rmax) / 2, (rmin - rmax) / 2 };
}


Circle operator*(const Matrix3D &m, const Circle &a)
{
	Circle ret;
	ret.p = (m * Vector3D(a.p.x, a.p.y, 1)).xy;

	Vector3D xrad(a.r, 0, 0);
	Vector3D yrad(0, a.r, 0);

	ret.r = fmaxf((m * xrad).magnitude(), (m * yrad).magnitude());

	return ret;
}


Ray operator*(const Matrix3D &m, const Ray &a)
{
	Vector3D dir = Vector3D(a.d.x, a.d.y, 0) * a.l;
	Vector3D pos(a.p.x, a.p.y, 1);

	return{ (m * pos).xy, Vector2D::Normal((m * dir).xy), dir.Magnitude() };
}

Plane operator*(const Matrix3D &m, const Plane &a)
{
	Vector3D nor(a.n.x, a.n.y, 0);
	Vector3D pos(a.p.x, a.p.y, 1);

	return{ (m * pos).xy,(m * nor).xy };
}

ConvexHull operator*(const Matrix3D &m, const ConvexHull &a)
{
	ConvexHull ret;
	for each(Vector2D p in ret.verts)
		ret.verts.push_back((m * Vector3D(p.x, p.y, 1)).xy);

	return ret;
}