#include "Shape.h"
#include "Matrix2D.h"
#include "Matrix3D.h"

AABB operator*(const Matrix2D &m, const AABB &a)
{
	Vector2D omin = a.minv();
	Vector2D omax = a.maxv();

	Vector2D rmin = m.c[2].xy;
	Vector2D rmax = m.c[2].xy;

	float p, q;

	for (unsigned j = 0; j < 2; ++j)
		for (unsigned i = 0; i < 2; ++i)
		{
			p = omin[i] * m.mm[i][j];
			q = omax[i] * m.mm[i][j];

			if (p < q) std::swap(p, q);
			rmin[j] += p;
			rmax[j] += q;
		}
	return{ (rmin + rmax) / 2, (rmin - rmax) / 2 };
}

Circle operator*(const Matrix2D & m, const Circle & a)
{
	Circle ret;
	ret.p = (Vector3D(a.p.x, a.p.y, 1) * m).xy;

	Vector3D xrad(a.r, 0, 0);
	Vector3D yrad(0, a.r, 0);

	ret.r = fmaxf((xrad * m).Magnitude(), (yrad * m).Magnitude());

	return ret;
}

Ray operator*(const Matrix2D &m, const Ray &a)
{
	Vector3D dir = Vector3D(a.d.x, a.d.y, 0) * a.l;
	Vector3D pos(a.p.x, a.p.y, 1);

	return{ (pos * m).xy, Vector2D::Normal((dir * m).xy), dir.Magnitude() };
}

Plane operator*(const Matrix2D &m, const Plane &a)
{
	Vector3D nor(a.n.x, a.n.y, 0);
	Vector3D pos(a.p.x, a.p.y, 1);

	return{ (pos * m).xy, (nor * m).xy };
}

ConvexHull operator*(const Matrix2D &m, const ConvexHull &a)
{
	ConvexHull ret;
	for each(Vector2D p in ret.verts)
		ret.verts.push_back((Vector3D(p.x, p.y, 1) * m).xy);

	return ret;
}

Vector2D AABB::minv() const { return Vector2D(p - e); }

Vector2D AABB::maxv() const { return Vector2D(p + e); }
