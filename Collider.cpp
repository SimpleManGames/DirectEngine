#include "Collider.h"
#include "Transform.h"

Collider::Collider() : shape(e_CIRCLE), circle({ { 0,0 },1 }) { }

Collider::Collider(SHAPE s) : shape(s) { }

Collider::Collider(const Collider & other) {
	*this = other;
}

CollisionData EvaluateCollision(const Transform &at, const Collider &ac,
	const Transform &bt, const Collider &bc)
{
	Transform t_lhs = at;
	Transform t_rhs = bt;
	Collider lhs = ac;
	Collider rhs = bc;
	if (lhs.shape > rhs.shape)
	{
		std::swap(lhs, rhs);
		std::swap(t_lhs, t_rhs);
	}

	switch (lhs.shape | rhs.shape)
	{
	case Collider::e_CIRCLE:
		return CheckCollision(t_lhs.getGlobalTransform() * lhs.circle,
			t_rhs.getGlobalTransform() * rhs.circle);

	case Collider::e_CIRCLE | Collider::e_AABB:
		return CheckCollision(t_lhs.getGlobalTransform() * lhs.circle,
			t_rhs.getGlobalTransform() * rhs.aabb);

	case Collider::e_CIRCLE | Collider::e_RAY:
		return CheckCollision(t_lhs.getGlobalTransform() * lhs.circle,
			t_rhs.getGlobalTransform() * rhs.ray);

	case Collider::e_CIRCLE | Collider::e_PLANE:
		return CheckCollision(t_lhs.getGlobalTransform() * lhs.circle,
			t_rhs.getGlobalTransform() * rhs.plane);

	case Collider::e_AABB:
		return CheckCollision(t_lhs.getGlobalTransform() * lhs.aabb,
			t_rhs.getGlobalTransform() * rhs.aabb);

	case Collider::e_AABB | Collider::e_RAY:
		return CheckCollision(t_lhs.getGlobalTransform() * lhs.aabb,
			t_rhs.getGlobalTransform() * rhs.ray);

	case Collider::e_AABB | Collider::e_PLANE:
		return CheckCollision(t_lhs.getGlobalTransform() * lhs.aabb,
			t_rhs.getGlobalTransform() * rhs.plane);

	case Collider::e_RAY | Collider::e_PLANE:
		return CheckCollision(t_lhs.getGlobalTransform() * lhs.ray,
			t_rhs.getGlobalTransform() * rhs.plane);
	}
}