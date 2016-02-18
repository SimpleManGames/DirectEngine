#ifndef _TIMER_H
#define _TIMER_H

// Include Files
#include "UObject.h"

class Timer :
	public UObject
{
public:
	// Constructor
	Timer(const std::tstring& name);
	
	// Destructor
	virtual ~Timer();

	// Copy Constructor & Assignment Operator
	Timer(const Timer& other);
	Timer& operator=(const Timer& other);

	/*void* operator new(size_t size);
	void operator delete(void* pdelete);*/

	bool Initialize();
	bool PostInitialize();
	bool Update(Context& context);
	bool ShutDown();

	float GetTotalTimer();
	float GetDeltaTime();

	void Reset();

private:
	// Methods
	void Start();
	void Stop();

	// Members
	double m_SecondsPerCount;
	double m_DeltaTime;

	__int64 m_BaseTime;
	__int64 m_PauseTime;
	__int64 m_StopTime;
	__int64 m_PrevTime;
	__int64 m_CurrTime;

	bool m_bStopped;
};

#endif