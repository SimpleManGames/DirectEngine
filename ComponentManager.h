#ifndef _COMPONENTMANAGER_H
#define _COMPONENTMANAGER_H

#include <vector>

#include "Component.h"
#include "RenderComponent.h"
#include "GameObject.h"

class ComponentManager
{
public:
	typedef std::vector<Component*> comp_vector;
	typedef comp_vector::iterator comp_vector_itr;
	typedef comp_vector::const_iterator comp_vector_const_itr;

	typedef std::vector<RenderComponent*> render_comp_vector;
	typedef render_comp_vector::iterator render_comp_vector_itr;
	typedef render_comp_vector::const_iterator render_comp_vector_const_itr;
	
	comp_vector m_components;
	render_comp_vector m_renderComponents;

	int m_componentsSize;
	int m_currentComponentsSize;
	int m_currentComponentCount;

	ComponentManager(void);
	~ComponentManager(void);

	void Create();
	void Clear();
	void Destory();

	Component* AddComponent(Component* l_component);
	bool RemoveComponent(comp_vector_const_itr l_component_itr);
	void RemoveComponentWithGameObj(GameObject* l_objects);

	void FixedUpdate();
	void Update();
	void LateUpdate();

	void Render();

	void ResizeComponents();

	// Singleton Implementation
	static ComponentManager* s_Instance;

	static inline ComponentManager* getInstance(void) {
		if (s_Instance == NULL) { s_Instance = new ComponentManager(); }
		return s_Instance;
	}
	static inline bool exists(void) { return s_Instance != 0; }
};

#endif // !_COMPONENTMANAGER_H