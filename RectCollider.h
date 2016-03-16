#pragma once
#include "Component.h"
#include "Rect2D.h"
#include "Circle.h"
#include "Ray.h"
//#include "Polygon.h"

#include "Context.h"
#include "Renderer.h"

class RectCollider :
	public Component
{
public:
	RectCollider()
		: left(0)
		, top(0)
		, right(0)
		, bottom(0)
	{
		m_name = "RECTCOLLIDER";
		m_gameObject = NULL;
		m_isEnabled = true;

		width = right - left;
		height = bottom - top;
		min = { top, left };
		max = { bottom, right };
	}
	RectCollider(const Rect2D& r, std::string name = "RECTCOLLIDER")
		: left(r.left)
		, top(r.top)
		, right(r.right)
		, bottom(r.bottom)
	{
		m_name = name;
		m_gameObject = NULL;
		m_isEnabled = true;

		width = r.width;
		height = r.height;
		pos = { top + (width / 2), right + (height / 2) };
		min = { top, left };
		max = { bottom, right };
	}
	RectCollider(double l, double t, double r, double b, std::string name = "RECTCOLLIDER")
		: left(l)
		, top(t)
		, right(r)
		, bottom(b)
	{
		m_name = name;
		m_gameObject = NULL;
		m_isEnabled = true;

		width = right - left;
		height = bottom - top;
		pos = { top + (width / 2), right + (height / 2) };
		min = { top, left };
		max = { bottom, right };
	}
	RectCollider(const Vector2D& v1, const Vector2D& v2, std::string name = "RECTCOLLIDER")
		: top(v1.y)
		, left(v1.x)
		, bottom(v2.y)
		, right(v2.x)
	{
		m_name = name;
		m_gameObject = NULL;
		m_isEnabled = true;

		width = right - left;
		height = bottom - top;
		pos = { top + (width / 2), left + (height / 2) };
		min = { top, left };
		max = { bottom, right };
	}
	~RectCollider() { }

	union
	{
		Rect2D r;
		struct
		{
			double top;
			double left;
			double bottom;
			double right;

			double width;
			double height;

		};
	};

	Vector2D pos;
	Vector2D min;
	Vector2D max;

	bool vs(Rect2D b)
	{
		// Exit with no intersection if found separated along an axis
		if (this->max.x < b.min.x || this->min.x > b.max.x) return false;
		if (this->max.y < b.min.y || this->min.y > b.max.y) return false;

		// No separating axis found, therefor there is at least one overlapping axis
		return true;
	}
	bool vs(double l, double t, double r, double b) { return vs({ l, t, r, b }); }
	bool vs(const Vector2D& v1, const Vector2D& v2) { return vs({ v1, v2 }); }

	bool vs(Circle c)
	{
		Vector2D pc = Vector2D::clampv(c.position, this->min, this->max);
		return (Dot((c.position - pc), (c.position - pc)) <= c.radius * c.radius);
	}
	bool vs(const Vector2D& p, float r) { vs({ p, r }); }
	bool vs(float x, float y, float r) { vs({ x, y }, r); }

	void DrawCollider(Context & context, Color c)
	{
		RENDERER->SetColor(c);
		RENDERER->DrawRect(r, 2.f);
	}
};

