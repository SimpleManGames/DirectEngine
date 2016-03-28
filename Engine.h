#ifndef _ENGINE_H
	#define _ENGINE_H

// C Runtime Header Files
#ifndef _WINDOWS_
	#include <Windows.h>
#endif

#ifndef _MAP_
	#include <map>
#endif // !_MAP_

#ifndef _CONTEXT_H
	#include "Context.h"
#endif // !_CONTEXT_H

#include "Logger.h"

//Forward Declaration
enum SystemType;

class System;
class Game;
class GameObject;

// Enumaration
enum EngineState
{
	Invalid,
	Constructing,
	Initializing,
	Running,
	ShuttingDown,
	Destroying
};

class Engine
{
public:
	// Game Engine constructor
	Engine();
	// Game Engine destructor
	~Engine();

	// RunLoop Function
	int RunLoop();

	//void* operater new(size_t size);
	//void* operater delete(void* pDelete);

	// Returns the current engine state
	static EngineState GetEngineState() { return m_EngineState; }

private:
	// Initializion of the engine
	int Initialize();
	// Draws the current scene
	// Takes the current context
	int Draw(Context& context);
	// Updates all the systems
	// Takes the current context
	int Update(Context& context);
	// Shut down the engine and the systems
	int ShutDown();

	// Check if we need to resize
	void CheckResize();
	// Add a core system to the engine
	// Takes a pointer to a system
	int AddSystem(System* psys);
	// Retrieve a core system from the engine
	// Takes in a system type
	template<typename T>
	T* GetSystem(SystemType systype)
	{
		// Create a template pointer and set it as the type we pass in
		T* psys = static_cast<T*>(m_mapSystems[systype]);
		// If failed
		if (!psys)
		{
			// Report to the user
			Logger::Log(_T("System is not valid: " + systype), LOGTYPE_WARNING, false);
			return nullptr;
		}
		// else return the system
		return psys;
	}

	// Create the game instance
	Game* CreateGame();

	// The map that holds the System Type along with its pointer to the system
	std::map<SystemType, System*> m_mapSystems;

	// Holds the current state of the engine
	static EngineState m_EngineState;
};

#endif
