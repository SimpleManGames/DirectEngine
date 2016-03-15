#ifndef _RENDER_COMPONENT_H
#define _RENDER_COMPONENT_H

#include "Component.h"

class RenderComponent
	: public Component
{
public:
	RenderComponent();
	~RenderComponent();

	void Render();
};

#endif