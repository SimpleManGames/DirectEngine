#ifndef _SYSTEM_H
	#define _SYSTEM_H
#include "BaseObject.h"

//Additional Includes
#ifndef _CONTEXT_H
	#include "Context.h"
#endif

/// Enumeration
enum SystemType
{
	Sys_Invalid,
	Sys_Window,
	Sys_Game,
	Sys_Input,
	Sys_Graphics,
	Sys_EngineTimer,

	System_MAX
};

///Structs
struct SystemData : public ObjectData
{
	/// Construtors

	// The Default construtor for SystemData
	SystemData(); 
	// Construtor for SystemData 
	// Takes a tstring for a name for the SystemData to be called 
	// Takes SystemType to set the type of SystemData
	SystemData(const std::tstring& name, const SystemType& type);
	
	/// Varibles

	// Holds the type of the system
	SystemType systemType;
};

class System : public BaseObject
{
	/// Declarations
	friend class Engine;

public:
	/// Getters

	// Returns the type of the system
	SystemType GetType() { return m_SystemType; }

protected:
	// Private Constructors
	System(const SystemData& data);
	virtual ~System();
	// Inits the Base Object
	virtual bool Initialize()				{ return BaseObject::Initialize(); }
	// Updates the Base Object
	virtual bool Update(Context& context)	{ return BaseObject::Update(context); }
	// Shuts down the Base Object
	virtual bool ShutDown()					{ return BaseObject::ShutDown(); }		

protected:
	/// Member varibles
	
	// Holds the System Type
	SystemType m_SystemType;
};

#endif // !_SYSTEM_H
