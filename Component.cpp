#include "Component.h"
#include "GameObject.h"

Component::Component(void)
	: m_name("Component")
	, m_isEnabled(true)
	, m_gameObject(NULL)
{
	this->Awake();
	HRESULT l_result = CoCreateGuid(&m_guid);
}

Component::Component(std::string l_name)
	: m_name(l_name)
	, m_isEnabled(true)
	, m_gameObject(NULL) {

	this->Awake();
	HRESULT l_result = CoCreateGuid(&m_guid);
}
Component::~Component(void) {

}
void Component::Destory() {

}
void Component::Awake() {

}
void Component::Start() {

}
void Component::FixedUpdate() {

}
void Component::Update() {

}
void Component::LateUpdate() {

}