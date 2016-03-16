#ifndef _TRANSFORM_COMPONENT_H
#define _TRANSFORM_COMPONENT_H

#include "Component.h"
#include "Vector3D.h"

class TransformComponent
	: public Component
{
public:
	TransformComponent(void)
		: pos(0, 0, 0)
		, rot(0, 0, 0)
		, scale(1)
	{
		m_name = "TRANSFORM";
		m_gameObject = NULL;
		m_isEnabled = true;
	}
	TransformComponent(Vector3D _pos, Vector3D _rot, float _scale, std::string _name = "TRANSFORM")
		: pos(_pos)
		, rot(_rot)
		, scale(_scale) 
	{ 
		m_name = _name;
		m_gameObject = NULL;
		m_isEnabled = true;
	}
	~TransformComponent(void) {} 

	Vector3D pos;
	Vector3D rot;
	float scale;
};

#endif