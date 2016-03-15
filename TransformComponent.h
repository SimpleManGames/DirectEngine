#ifndef _TRANSFORM_COMPONENT_H
#define _TRANSFORM_COMPONENT_H

#include "Component.h"
#include "Vector2D.h"

class TransformComponent
	: public Component
{
public:
	TransformComponent(void)
		: pos(0, 0)
	{
		m_name = "TRANSFORM";
		m_gameObject = NULL;
		m_isEnabled = true;
	}
	TransformComponent(Vector2D _pos)
		: pos(_pos) { }
	~TransformComponent(void) {} 

	Vector2D pos;
};

#endif