#include "EngineTimer.h"

//#include "MemoryManager.h"
#include "Logger.h"

#include "Timer.h"

// Constructor for the engine timer
// Takes a ref to Engine Timer Data
EngineTimer::EngineTimer(const EngineTimerData& data) 
	: System(data)
	, m_pWorldTimer(nullptr) { }

// Destructor for Engine Timer
EngineTimer::~EngineTimer() { }

// Inits the Engine timer
bool EngineTimer::Initialize() 
{
	// Inits the system for engine timer
	System::Initialize();
	// Gets the world timer and sets it to a new timer
	m_pWorldTimer = new Timer(_T("WorldTimer"));


#if defined(DEBUG) | defined(_DEBUG)
	if (!m_pWorldTimer->Initialize())
		return false;
	//m_pWorldTimer->SetInitialized();
	//if (!m_pWorldTimer->PostInitialized())
		//return false;
	//m_pWorldTimer->SetPostInitialized();
#else
	//m_pWorldTimer->Initialize();
	//m_pWorldTimer->SetInitialized();
	//m_pWorldTimer->PostInitialized();
	//m_pWorldTimer->SetPostInitialized();
#endif

	Logger::Log(_T("Engine timer initialized"), LOGTYPE_INFO, false);
	return true;
}

// Update for the Engine timer
// Takes in the current context
bool EngineTimer::Update(Context & context) 
{
	// Update the system for the engine timer
	System::Update(context);

	// Update the world timer
	if (m_pWorldTimer) {
		m_pWorldTimer->Update(context);
		// Set the delta time
		context.dTime = m_pWorldTimer->GetDeltaTime();
	}
	// Update all other timers
	for (Timer* timer : m_vecTimers) timer->Update(context);

	return true;
}

// Shut down for the engine timer
bool EngineTimer::ShutDown() 
{
	// Shut down the system for the engine timer
	System::ShutDown();
	// Delete the pointer
	SafeDelete(m_pWorldTimer);
	// Delete all other timers
	for (Timer* timer : m_vecTimers) SafeDelete(timer);

	return true;
}
