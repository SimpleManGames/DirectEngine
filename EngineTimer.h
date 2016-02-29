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
struct EngineTimerData : public SystemData {
	EngineTimerData() :
		SystemData(_T("Engine Timer"), SystemType::Sys_EngineTimer) { }

};

class EngineTimer :
	public System
{
	friend class Engine;
public:
	// Destructor
	virtual ~EngineTimer();

	Timer* GetWorldTimer() { return m_pWorldTimer; }
	void AddTimer(const std::tstring& name);
	Timer* GetTimer(const std::tstring& name);

	/*void* operator new(size_t size);
	void operator delete(void* pdelete);*/

	// Methods
	bool Initialize();
	bool Update(Context& context);
	bool ShutDown();

protected:
	// Constructor
	EngineTimer(const EngineTimerData& data);

private:
	// Members
	Timer* m_pWorldTimer;
	std::vector<Timer*> m_vecTimers;
};

#endif // !_ENGINETIMER_H