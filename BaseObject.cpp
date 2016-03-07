#include "BaseObject.h"

BaseObject::BaseObject()
	: m_Name(_T(""))

	, m_ID(ObjectCounter<BaseObject>::GetAmount())
	, m_bIsInitialized(false)
	, m_bIsPostContentLoaded(false)
	, m_bIsContentLoaded(false)
	, m_bIsDestoryed(false)

	, m_bCanDraw(true)
	, m_bCanTick(true)
{
	TYPE_REGISTER(BaseObject);
	m_Name = _T("Object_") + TOSTRING(m_ID);
}

BaseObject::BaseObject(ObjectData * data)
	: m_Name(data->name)
	, m_ID(ObjectCounter<BaseObject>::GetAmount())
	, m_bIsInitialized(false)
	, m_bIsPostContentLoaded(false)
	, m_bIsContentLoaded(false)
	, m_bIsDestoryed(false)

	, m_bCanDraw(true)
	, m_bCanTick(true)
{
	TYPE_REGISTER(BaseObject);
}

BaseObject::BaseObject(const std::tstring& name)
	: m_Name(name)
	, m_ID(ObjectCounter<BaseObject>::GetAmount())
	, m_bIsInitialized(false)
	, m_bIsPostContentLoaded(false)
	, m_bIsContentLoaded(false)
	, m_bIsDestoryed(false)

	, m_bCanDraw(true)
	, m_bCanTick(true)
{
	TYPE_REGISTER(BaseObject);
}


BaseObject::~BaseObject() { SafeDelete(m_pdata); }

void BaseObject::Reset() { }

bool BaseObject::isType(const std::tstring & type) { return Singleton<TypeChecker>::GetInstance()->isType(GetID(), type); }
bool BaseObject::isA(const std::tstring & type) { return Singleton<TypeChecker>::GetInstance()->isA(GetID(), type);; }
