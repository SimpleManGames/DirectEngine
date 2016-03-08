#ifndef _RAY_H
#define _RAY_H

#include "Vector2D.h"

struct Ray
{
public:
	Ray()
		: pos(0, 0)
		, dir(0, 0)
		, len(0) { }
	Ray(const Ray& r) 
		: pos(r.pos)
		, dir(r.dir)
		, len(r.len) { }
	Ray(Vector2D &_pos, Vector2D &_dir, float l)
		: pos(_pos)
		, dir(_dir)
		, len(l) { }
	Ray(float x, float y, Vector2D &_dir, float l)
		: pos(x, y)
		, dir(_dir)
		, len(l) { }
	Ray(Vector2D &_pos, float dx, float dy, float l)
		: pos(_pos)
		, dir(dx, dy)
		, len(l) { }
	Ray(float x, float y, float dx, float dy, float l)
		: pos(x, y)
		, dir(dx, dy)
		, len(l) { }
	~Ray() { }

	Vector2D pos;
	Vector2D dir;
	float len;

	static const Ray empty;

	Ray operator=(const Ray& other) 
	{
		Ray r;

		r.pos = other.pos;
		r.dir = other.dir;
		r.len = other.len;

		return r;
	}
	bool operator==(const Ray& other)
	{
		if (this->pos == other.pos &&
			this->dir == other.dir &&
			this->len == other.len)
			return true;

		return false;
	}

	bool IsEqual(const Ray& other)
	{
		return (this->pos == other.pos && 
				this->dir == other.dir &&	
				this->len == other.len);
	}
};

inline bool operator== (const Ray& r1, const Ray& r2) 
{
	return (r1.pos == r2.pos &&
			r1.dir == r2.dir &&
			r1.len == r2.len);
}
inline bool operator!= (const Ray& r1, const Ray& r2)
{
	return !(r1 == r2);
}


#endif // !_RAY_H