#pragma once
#include "Component.h"
#include "Vector3D.h"

class PhysicsComponent
	: public Component
{
public:
	PhysicsComponent()
		: vel({})
		, restitution(0)
		, mass(0)
	{
		m_name = "PHYSICS";
		m_gameObject = NULL;
		m_isEnabled = true;
	}
	PhysicsComponent(Vector3D _vel = {}, float _restitution = 0, float _mass = 0, std::string name = "PHYSICS")
		: vel(_vel)
		, restitution(_restitution)
		, mass(_mass)
	{
		m_name = name;
		m_gameObject = NULL;
		m_isEnabled = true;
	}
	~PhysicsComponent() { }

	Vector3D vel;
	float restitution;
	float mass;
};

