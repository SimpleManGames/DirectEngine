#include "GameObject.h"
#include "Find_All.h"

GameObject::GameObject()
	: m_name("GameObject")
	, m_tags("")
	, m_transform(NULL)
	, m_parent(NULL)
{
	HRESULT l_result = CoCreateGuid(&m_guid);
}

GameObject::GameObject(std::string l_name)
	: m_name(l_name)
	, m_tags("")
	, m_transform(NULL)
	, m_parent(NULL)
{
	HRESULT l_result = CoCreateGuid(&m_guid);
}

GameObject::~GameObject() { }

void GameObject::Create() {
	TransformComponent* l_transform = new TransformComponent();
	l_transform->m_gameObject = this;
	this->m_transform = (TransformComponent*)ComponentManager::getInstance()->AddComponent(l_transform);
	this->AddComponents(this->m_transform);
}
void GameObject::Destory() {
	ComponentManager::getInstance()->RemoveComponentWithGameObj(this);

	for (gameObj_vector_itr itr = m_children.begin();
	itr != m_children.end(); ++itr) {
		(*itr)->Destory();
		delete *itr;
	}

	for (comp_vector_itr itr = m_components.begin();
	itr != m_components.end(); ++itr) {
		delete *itr;
	}

	m_children.clear();
	m_components.clear();
}

void GameObject::AddComponents(Component * l_component) {
	l_component->m_gameObject = this;
	m_components.push_back(l_component);
	l_component->Start();
}

void GameObject::AddChild(GameObject * l_gameObj) {
	l_gameObj->m_parent = this;
	l_gameObj->Create();
	this->m_children.push_back(l_gameObj);
}

GameObject * GameObject::FindChildByName(std::string l_name)
{
	gameObj_vector_itr itr = std::find_if(m_children.begin(), m_children.end(), GameObjectComparer(l_name));
	if (itr != m_children.end()) { return *itr; }
	return NULL;
}

std::vector<GameObject*> GameObject::FindAllChildrenByName(std::string l_name)
{
	std::vector<GameObject*> l_objects;
	std::vector<gameObj_vector_itr> itr_list = find_all(m_children.begin(), m_children.end(), GameObjectComparer(l_name));
	for (std::vector<gameObj_vector_itr>::iterator itr = itr_list.begin(); itr != itr_list.end(); ++itr) {
		l_objects.push_back(**itr);
	}
	return l_objects;
}
