#include "System.h"

// Default SystemData Construtor
SystemData::SystemData()
	: ObjectData()
	, systemType(SystemType::Sys_Invalid)
{}

// SystemData Construtor
// param: name = The name of the system
// param: type = Sets the SystemType
SystemData::SystemData(const std::tstring& name, const SystemType& type)
	: ObjectData(name)
	, systemType(type)
{}

// Default System Construtor
// param: data = Get systemType from this and sets the SystemType
System::System(const SystemData& data)
	:BaseObject(),
	m_SystemType(data.systemType)
{
}

// Default System Deconstrutor
// Empty
System::~System() { }
