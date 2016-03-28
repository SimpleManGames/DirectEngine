#ifndef _ENGINETIMER_H
#define _ENGINETIMER_H

// Include Files
#include "System.h"

// Additional Include Files
#ifndef _VECTOR_
	#include <vector>
#endif
#ifndef _STRING_
	#include "string.h"
#endif
#ifndef _DELETEMACROS_H
	#include "deletemacros.h"
#endif

#include <iostream>

// Foward Declaration
class Timer;

// Struct

// Engine Timer Data struct which inherits from SystemData
struct EngineTimerData : public SystemData
{
	// Default constructor for Engine timer Data
	// Sets the default values for System Data
	// Name is "Engine Timer"
	// SystemType is set to Sys_EngineTimer
	EngineTimerData() 
		:	SystemData(_T("Engine Timer")
		, SystemType::Sys_EngineTimer) { }
};

// Engine Timer class that inherits from System
class EngineTimer : public System
{
	friend class Engine;
public:
	// Virtual Default Destructor
	virtual ~EngineTimer();

	// Returns the World Timer for the engine
	Timer* GetWorldTimer() { return m_pWorldTimer; }
	// TODO: Implement
	// Adds a timer to a vector
	// Takes in a name for the timer
	void AddTimer(const std::tstring& name);
	// TODO:
	// Returns a timer with name
	// Takes in the name of the timer you want
	Timer* GetTimer(const std::tstring& name);

	/*void* operator new(size_t size);
	void operator delete(void* pdelete);*/

	// Methods

	// Initialization of the timer
	bool Initialize();
	// Update for the timer
	// Takes in a the current context
	bool Update(Context& context);
	// Shut down for the engine timer
	bool ShutDown();

protected:
	// Constructor for engine timer
	// Takes a ref to Engine Timer Data
	EngineTimer(const EngineTimerData& data);

private:
	// Members

	// Holds a pointer to the World Timer
	Timer* m_pWorldTimer;
	// Vector of pointers to new Timers
	std::vector<Timer*> m_vecTimers;
};

#endif // !_ENGINETIMER_H