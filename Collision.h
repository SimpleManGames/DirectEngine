#pragma once

#include "GameObject.h"
#include "PhysicsComponent.h"

#include "CircleCollider.h"

#include "Vector2D.h"

struct Manifold
{
	Manifold()
		: A(nullptr)
		, B(nullptr)
		, penDepth(0)
		, normal({})
	{

	}
	Manifold(GameObject *a, GameObject *b)
		: A(a)
		, B(b)
		, penDepth(0)
		, normal({})
	{
	
	}

	GameObject *A;
	GameObject *B;
	float penDepth;
	Vector2D normal;
};

void ResolveCollision(Manifold *m)
{
	// Set up the pointers
	GameObject *a = m->A;
	GameObject *b = m->B;

	PhysicsComponent *aPhys = a->FindComponentByType<PhysicsComponent>();
	PhysicsComponent *bPhys = b->FindComponentByType<PhysicsComponent>();

	// Error Check : See if the component exists
	if (bPhys == NULL || aPhys == NULL)
		return;

	// Calculate relative veolcity
	Vector2D rv = bPhys->vel.xy - aPhys->vel.xy;

	// Calculate relative velocity in terms of the normal direction
	float velAlongNormal = Dot(rv, m->normal);

	// Do not resolve if velocities are separating
	if (velAlongNormal > 0)
		return;

	// Calclate restitution
	float e = min(aPhys->restitution, bPhys->restitution);

	// Calculate impulse
	float j = -(1 + e) * velAlongNormal;
	j /= 1 / aPhys->mass + 1 / bPhys->mass;

	// Apply
	Vector2D impulse = m->normal * j;
	aPhys->vel.xy -= impulse * (1 / aPhys->mass);
	bPhys->vel.xy += impulse * (1 / bPhys->mass);
}

bool Manifold_CC(Manifold *m)
{
	// Setup the pointers into the Manifold
	GameObject *a = m->A;
	GameObject *b = m->B;

	// Vector from A to B
	Vector2D n = b->FindComponentByType<TransformComponent>()->getPosition().xy - a->FindComponentByType<TransformComponent>()->getPosition().xy;

	float r = a->FindComponentByType<CircleCollider>()->r + b->FindComponentByType<CircleCollider>()->r;
	r *= r;

	if (n.Length() * n.Length() > r)
		return false;

	// Collided, do the manifold math
	float d = n.Length();

	// If distance between circles is not zero
	if (d != 0)
	{
		// Distance is difference between radius and distance;
		m->penDepth = r - d;

		// Calc the collision normal
		m->normal = n / d;

		return true;
	}
	// Circles are on the same position
	else
	{
		m->penDepth = a->FindComponentByType<CircleCollider>()->r;
		m->normal = Vector2D(1, 0);
		return true;
	}
}