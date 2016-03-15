#ifndef _CIRCLE_COLLIDER_H
#define _CIRCLE_COLLIDER_H

#include "Component.h"
#include "Circle.h"
#include "Ray.h"
#include "Rect2D.h"
#include "Plane.h"

#include "Vector2D.h"

#include "Renderer.h"

#include "Context.h"

class CircleCollider :
	public Component
{
public:
	CircleCollider()
		: pos(0, 0)
		, r(1)
	{
	
	}
	CircleCollider(Circle _c)
		: c(_c)
	{
		
	}
	CircleCollider(const Vector2D& p, float _r)
		: pos(p)
		, r(_r)
	{

	}
	CircleCollider(float x, float y, float _r)
		: pos(x, y)
		, r(_r)
	{
	
	}
	~CircleCollider() { }

	union
	{
		Circle c;
		struct 
		{
			Vector2D pos;
			float r;
		};
	};

	bool vs(Circle c)
	{
		float r = this->r + c.radius;
		r *= r;
		return r > sqrtf((this->pos.x - c.position.x) * (this->pos.x - c.position.x) + (this->pos.y - c.position.y) * (this->pos.y - c.position.y));
	}
	bool vs(const Vector2D& p, float r) { return vs({ p, r }); }
	bool vs(float x, float y, float r) { return vs({ { x, y }, r }); }
	bool vs(Rect2D r);
	bool vs(Ray r);
	bool vs(Plane p);

	void DrawCollider(Context & context, Color _c)
	{
		RENDERER->SetColor(_c);
		RENDERER->DrawCircle(c.position, c.radius);
	}
};

#endif //!_CIRCLE_COLLIDER_H