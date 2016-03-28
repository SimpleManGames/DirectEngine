#include "Timer.h"

#ifndef _WINDOW_H
#include <Windows.h>
#endif

//#include "MemoryManager.h"
#include "Logger.h"

#ifndef _CTIME_
#include <ctime>
#endif

// Constructor for Timer
// Takes in a name for the BaseObject
Timer::Timer(const std::tstring& name) 
	: BaseObject(name)
	, m_SecondsPerCount(0.0f)
	, m_DeltaTime(-1.0f)
	, m_BaseTime(0)
	, m_PauseTime(0)
	, m_PrevTime(0)
	, m_CurrTime(0)
	, m_bStopped(false)
{
	__int64 countpersec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countpersec);
	m_SecondsPerCount = 1.0f / (double)countpersec;
}

// Default destructor for Timer
Timer::~Timer()
{
}

// Copy Constructor for Timer
Timer::Timer(const Timer & other) { *this = other; }

//Timer & Timer::operator=(const Timer & other)
//{
//	// TODO: insert return statement here
//}

// Initialization for Timer
bool Timer::Initialize()
{
	// Init baseobject
	BaseObject::Initialize();

	// Start the Timer
	Start();
	
	return true;
}

// Post Initialization for timer
bool Timer::PostInitialize() 
{ 
	// Return the post initialization of baseobject
	return BaseObject::PostInitialize(); 
}

// Update for Timer
// Takes in the current context
bool Timer::Update(Context & context)
{
	// Update the baseobject with context
	BaseObject::Update(context);

	// If the timer is not running...
	if (m_bStopped) {
		// Deltatime should not advance
		m_DeltaTime = 0.0;
		return true;
	}

	// Get the time for this frame
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	m_CurrTime = currTime;

	// Time difference between this frame and the prev one
	m_DeltaTime = (m_CurrTime - m_PrevTime) * m_SecondsPerCount;

	// Prepare the next frame;
	m_PrevTime = m_CurrTime;

	// Force nonnegative
	// The DXSKS's CDXUTTimer metions that if the processor goes into power save mode of we get shuffled to another processer
	// then Delta Time can be negative
	if (m_DeltaTime < 0.0) m_DeltaTime = 0.0;

	return true;
}

// Shut down for Timer
bool Timer::ShutDown()
{
	// Shut down for the base object
	BaseObject::ShutDown();

	// Stop the Timer
	Stop();

	return true;
}

// Get time since the program has been running
float Timer::GetTotalTimer() 
{
	if (m_bStopped) return (float)(m_StopTime - m_BaseTime) * (float)m_SecondsPerCount;
	else return (float)(((m_CurrTime - m_PauseTime) - m_BaseTime) * m_SecondsPerCount);
}

// Returns the Delta Time
float Timer::GetDeltaTime() { return (float)m_DeltaTime; }

// Reset the timer
void Timer::Reset() 
{
	__int64 currtime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currtime);

	m_BaseTime = currtime;
	m_PrevTime = currtime;
	m_StopTime = 0;

	m_bStopped = false;
}

// Start the timer
void Timer::Start() 
{
	__int64 starttime;
	QueryPerformanceCounter((LARGE_INTEGER*)&starttime);
	m_PrevTime = starttime;

	// If we are resuming the timer from a stopped state...
	if (m_bStopped) {
		// then accumulate the passed time
		m_PauseTime += (starttime - m_StopTime);

		// Since we are staring the timer back up,
		// the current previous time is not valid,
		// as it occured while paused,
		// So reset it to the current time
		m_PrevTime = starttime;

		// No longer stopped
		m_StopTime = 0;
		m_bStopped = false;
	}
}

// Stop the timer
void Timer::Stop() 
{
	// IF we are already stopped, then don't do anything
	if (m_bStopped) return;

	__int64 currtime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currtime);

	// Save the time we stopped at
	// and set the boolen flag indication the timer stopped
	m_StopTime = currtime;
	m_bStopped = false;
}
