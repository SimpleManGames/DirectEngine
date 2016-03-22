#include "CircleCollider.h"

CircleCollider * CircleCollider::setCircle(float x, float y, float r)
{
	this->pos = { x, y };
	this->r = r;

	return this;
}

CircleCollider * CircleCollider::setCircle(Vector2D pos, float r)
{
	this->pos = pos;
	this->r = r;

	return this;
}

CircleCollider * CircleCollider::setCircle(Vector3D all)
{
	this->pos = all.xy;
	this->r = all.z;

	return this;
}
