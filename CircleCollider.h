#ifndef _CIRCLE_COLLIDER_H
#define _CIRCLE_COLLIDER_H

#include "GameObject.h"
#include "Component.h"
#include "TransformComponent.h"
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
	CircleCollider(const CircleCollider& other)
	{
		pos = other.pos;
		r = other.r;
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

	CircleCollider* setCircle(float x, float y, float r);
	CircleCollider* setCircle(Vector2D pos, float r);
	CircleCollider* setCircle(Vector3D all);

	bool vs(Circle _c)
	{
		float r = this->r + _c.radius;
		r *= r;
		//return r >= sqrtf((this->pos.x - _c.position.x) * (this->pos.x - _c.position.x) + (this->pos.y - _c.position.y) * (this->pos.y - _c.position.y));
		return r >= Dot(this->pos - _c.position, this->pos - _c.position);
	}
	bool vs(const Vector2D& p, float r) { return vs({ p, r }); }
	bool vs(float x, float y, float r) { return vs({ { x, y }, r }); }
	
	bool vs(Rect2D r)
	{
		Vector2D pc(Vector2D::clampv(this->pos, r.min, r.max));
		return (Dot((this->pos - pc), (this->pos - pc)) <= this->r * this->r);
	}
	bool vs(double l, double t, double r, double b) { return vs(Rect2D{ l, t, r, b }); }
	bool vs(const Vector2D& v1, const Vector2D& v2) { return vs(Rect2D{ v1, v2 }); }
	bool vs(Ray r);
	bool vs(Plane p);

	void DrawCollider(Context & context, Color _c)
	{
		RENDERER->SetColor(_c);
		RENDERER->DrawCircle(this->m_gameObject->FindComponentByType<TransformComponent>()->getPosition().xy, c.radius, 2.f);
	}
};

#endif //!_CIRCLE_COLLIDER_H