#ifndef _TIMER_H
#define _TIMER_H

// Include Files
#include "BaseObject.h"

// Timer class that inherits from BaseObject
class Timer :
	public BaseObject
{
public:
	// Constructor for Timer
	// Takes in name for BaseObject
	Timer(const std::tstring& name);
	
	// Default Destructor for Timer
	virtual ~Timer();

	// Copy Constructor & Assignment Operator
	Timer(const Timer& other);

	// TODO
	// Sets two timers equal
	//Timer& operator=(const Timer& other);

	/*void* operator new(size_t size);
	void operator delete(void* pdelete);*/

	// Initialization of the Timer
	bool Initialize();
	// Post Initiazlization of the Timer
	bool PostInitialize();
	// Update the timer
	// Takes in the current context
	bool Update(Context& context);
	// Shut down for the timer
	bool ShutDown();

public:
	// Return the total time the program has been running
	float GetTotalTimer();
	// Return the deltatime
	float GetDeltaTime();
	// Holds the value for Delta time
	double m_DeltaTime;
	// Reset the timer
	void Reset();

private:
	// Methods

	// Start method for the timer
	void Start();
	// Stop method for the timer
	void Stop();

	// Members

	double m_SecondsPerCount;

	__int64 m_BaseTime;
	__int64 m_PauseTime;
	__int64 m_StopTime;
	__int64 m_PrevTime;
	__int64 m_CurrTime;

	bool m_bStopped;
};

#endif