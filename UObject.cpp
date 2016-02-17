#include "UObject.h"

int UObject::m_ObjAmount = 0;

UObject::UObject()
	:m_Name(_T("")),

	m_ID(m_ObjAmount),
	m_bIsInitialized(false),
	m_bIsPostContentLoaded(false),
	m_bIsContentLoaded(false),
	m_bIsDestoryed(false),

	m_bCanDraw(true),
	m_bCanTick(true)
{
	m_Name = _T("Object_") + TOSTRING(m_ID);
	++m_ObjAmount;
}

UObject::UObject(const std::tstring& name)
	:m_Name(name),
	m_ID(m_ObjAmount),
	m_bIsInitialized(false),
	m_bIsPostContentLoaded(false),
	m_bIsContentLoaded(false),
	m_bIsDestoryed(false),

	m_bCanDraw(true),
	m_bCanTick(true)
{
	++m_ObjAmount;
}


UObject::~UObject()
{
	--m_ObjAmount;
}

void UObject::Reset()
{

}
