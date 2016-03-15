#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include <string>
#include <algorithm>
#include <typeinfo>
#include <vector>

#include <objbase.h>
#include <guiddef.h>

#include "Component.h"
#include "ComponentManager.h"
#include "TransformComponent.h"

class GameObject {
public:
	std::string m_name; // Non-Unqiue
	std::string m_tags;
	GameObject* m_parent;
	TransformComponent* m_transform;

	GUID m_guid;

	typedef std::vector<Component*> comp_vector;
	typedef comp_vector::iterator comp_vector_itr;
	typedef comp_vector::const_iterator comp_vector_const_itr;

	typedef std::vector<GameObject*> gameObj_vector;
	typedef gameObj_vector::iterator gameObj_vector_itr;
	typedef gameObj_vector::const_iterator gameObj_vector_const_itr;

	comp_vector m_components;
	gameObj_vector m_children;

	GameObject();
	GameObject(std::string l_name);
	~GameObject();

	void Create();
	void Destory();

	void AddComponents(Component* l_Component);

	template<typename T>
	T* FindComponentByType() {
		for (comp_vector_itr itr = m_components.begin(); itr != m_components.end(); ++itr) {
			if (T* l_type = dynamic_cast<T*>(*itr)) { return l_type; }
		}
		return NULL;
	};

	void AddChild(GameObject* l_gameObj);

	GameObject* FindChildByName(std::string l_name);
	std::vector<GameObject*> FindAllChildrenByName(std::string l_name);
};

struct GameObjectComparer {
	std::string m_name;

	GameObjectComparer(std::string l_name)
		: m_name(l_name) {

	}
	bool operator()(GameObject* l_object) { return (l_object->m_name == m_name ? true : false); }
};

#endif // !_GAMEOBJECT_H