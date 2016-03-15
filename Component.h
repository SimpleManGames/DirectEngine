#ifndef _COMPONENT_H
#define _COMPONENT_H

#include <string>

#include <objbase.h>
#include <guiddef.h>

class GameObject;
class Component {
public:
	std::string m_name;
	GameObject* m_gameObject;
	bool m_isEnabled;

	GUID m_guid;

	Component(void);
	Component(std::string l_name);
	virtual ~Component(void);

	virtual void Destory();
	virtual void Awake();
	virtual void Start();
	virtual void FixedUpdate();
	virtual void Update();
	virtual void LateUpdate();
};

struct ComponentComparer {
	std::string m_name;

	ComponentComparer(std::string l_name)
		: m_name(l_name) {

	}
	bool operator()(Component* l_object) { return (l_object->m_name == m_name ? true : false); }
};

#endif