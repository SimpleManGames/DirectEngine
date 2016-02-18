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

//Forward Declaration
enum SystemType;

class System;
class Game;

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
	Engine();
	~Engine();

	int RunLoop();

	//void* operater new(size_t size);
	//void* operater delete(void* pDelete);

	static EngineState GetEngineState() { return m_EngineState; }

private:
	int Intialize();
	int Draw(Context& context);
	int Update(Context& context);
	int ShutDown();

	// Check if we need to resize
	void CheckResize();
	//Add a core system to the engine
	int AddSystem(System* psys);
	// Retrieve a core system from the engine
	template<typename T>
	T* GetSystem(SystemType systype)
	{
		T* psys = static_cast<T*>(m_mapSystems[systype]);
		if (!psys)
		{
			//Logger::Log("System is not valid")
			return nullptr;
		}
		return psys;
	}

	// Create the game instance
	Game* CreateGame();

	std::map<SystemType, System*> m_mapSystems;

	static EngineState m_EngineState;
};

#endif
