#include "Engine.h"

#include "Renderer.h"
#include "System.h"
#include "Game.h"
#include "Window.h"
#include "Graphics.h"
#include "GameLogic.h"
#include "EngineTimer.h"

#include "GraphicsDeviceManager.h"
#include "WorldSettings.h"

#include "Logger.h"

#ifndef _DELETEMACRO_H
	#include "deletemacros.h"
#endif // !_DELETEMACRO_H
#ifndef _STRING_H
	#define _STRING_H
#endif // !_STRING_H

EngineState Engine::m_EngineState = EngineState::Invalid;

Engine::Engine() { m_EngineState = EngineState::Constructing; }
Engine::~Engine() { m_EngineState = EngineState::Destroying; }

//Public Methods

int Engine::RunLoop()
{
	// Create the context
	Context context;
	// Set the context renderer
	context.pRenderer = new Renderer();

	// Init the engine
	if (!this->Initialize()) { return 0; }
	Logger::Log(_T("Engine Initialize succeded"), LOGTYPE_INFO, false);

	// Get a random number
	srand(GetTickCount());

	// Set a new MSG to empty
	MSG msg = {};

	// Change the Engine state
	m_EngineState = EngineState::Running;

	// Start the run loop
	while (msg.message != WM_QUIT && m_EngineState == EngineState::Running)
	{
		// Check if the user is trying to change the window size
		CheckResize();

		// Check the message and remove the message from the queue
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// Update and draw
		this->Update(context);
		this->Draw(context);
	}

	Logger::Log(_T("Ending program"), LOGTYPE_INFO, false);
	Logger::WriteLogFile();

	// Shut down the engine
	if (!this->ShutDown()) { return 0; }

	// End the program with the msg param
	return (int)msg.wParam;
}

//Private Methods
int Engine::Initialize()
{
	// Set the engine to Initializing
	m_EngineState = EngineState::Initializing;

	// Create the WorldSettings singleton
	Singleton<WorldSettings>::CreateInstance();

	// Create a new point to a new game
	Game* game = CreateGame();

	// Break if the new game failed
	if (!game) { return false; }

	// Add systems

	// Adding the Window system
#if defined(DEBUG) | defined(_DEBUG)
	if (!AddSystem(new Window(WindowData(Singleton<WorldSettings>::GetInstance()->getWindowWidth(),
										 Singleton<WorldSettings>::GetInstance()->getWindowHeight(),
										 Singleton<WorldSettings>::GetInstance()->getWindowTitle()))))
		return false;
#else
	AddSystem(new Window(WindowData(Singleton<WorldSettings>::GetInstance()->getWindowWidth(),
									Singleton<WorldSettings>::GetInstance()->getWindowHeight(),
									Singleton<WorldSettings>::GetInstance()->getWindowTitle())));
#endif
	// Adding the Graphics system
#if defined(DEBUG) | defined(_DEBUG)
	if (!AddSystem(new Graphics(GraphicsData(GetSystem<Window>(SystemType::Sys_Window)))))
		return false;
#else
	AddSystem(new Graphics(GraphicsData(GetSystem<Window>(SystemType::Sys_Window))));
#endif
	// Adding the Engine Timer system
#if defined(DEBUG) | defined(_DEBUG)
	if (!AddSystem(new EngineTimer(EngineTimerData())))
		return false;
#else
	AddSystem(new EngineTimer(EngineTimerData()));
#endif
	// Adding the Game Logic Data system
#if defined(DEBUG) | defined(_DEBUG)
	if (!AddSystem(new GameLogic(GameLogicData())))
		return false;
#else
	AddSystem(new GameLogic(GameLogicData()));
#endif

	// Initialize the system

	// Window Init Block
#if defined(DEBUG) | defined(_DEBUG)
	if (!m_mapSystems[SystemType::Sys_Window]->Initialize())
		return false;
#else
	m_mapSystems[SystemType::Sys_Window]->Initialize();
#endif

		// Graphics Init Block
#if defined(DEBUG) | defined(_DEBUG)
		if (!m_mapSystems[SystemType::Sys_Graphics]->Initialize())
			return false;
#else
	m_mapSystems[SystemType::Sys_Graphics]->Initialize();
#endif

		// Engine Timer Init Block
#if defined(DEBUG) | defined(_DEBUG)
		if (!m_mapSystems[SystemType::Sys_EngineTimer]->Initialize())
			return false;
#else
	m_mapSystems[SystemType::Sys_EngineTimer]->Initialize();
#endif

		// Game Logic Init Block
#if defined(DEBUG) | defined(_DEBUG)
		if (!m_mapSystems[SystemType::Sys_Logic]->Initialize())
			return false;
#else
	m_mapSystems[SystemType::Sys_Logic]->Initialize();
#endif

	// Create the singleton of the graphics device manager
	Singleton<GraphicsDeviceManager>::CreateInstance();
	// Set that to the system we created
	Singleton<GraphicsDeviceManager>::GetInstance()->SetGraphics(GetSystem<Graphics>(SystemType::Sys_Graphics));

	return true;
}

int Engine::Draw(Context& context)
{
	// Create a graphics and set it to our system
	Graphics* graph = GetSystem<Graphics>(SystemType::Sys_Graphics);
	if (graph == nullptr) return false;

	// Create the game logic and set it to our system
	GameLogic* logic = GetSystem<GameLogic>(SystemType::Sys_Logic);
	if (logic == nullptr)
		return false;

	// Begin the Draw
	graph->BeginDraw();

	// Draw the game logic
	logic->Draw(context);

	Rect2D r(100, 100, 200, 200);
	RENDERER->DrawRect(r, 2.f);

	// End the Draw
	graph->EndDraw();

	return true;
}
int Engine::Update(Context& context)
{
	// Update all our system in our map of systems
	for (std::pair<SystemType, System*> pSys : m_mapSystems)
	{
		if (!pSys.second)
			continue;

		pSys.second->Update(context);
	}
	
	return true;
}
int Engine::ShutDown()
{
	// Set the engine to shutting down
	m_EngineState = EngineState::ShuttingDown;

	// Shut down each system in our map of systems
	for (std::pair<SystemType, System*> psys : m_mapSystems)
	{
		if (!psys.second->ShutDown())
		{
			// Output if we failed to notify the user
			Logger::Log(_T("Failed to shutdown system: " + psys.second->GetName()), LOGTYPE_WARNING, false);
			continue;
		}
		// If they didn't fail, delete the pointer to the system
		SafeDelete(psys.second);
	}
	// Destory the Instance of world settings in our singleton handler
	Singleton<WorldSettings>::DestoryInstance();
	Logger::Log(_T("Succeded in shuting down the engine"), LOGTYPE_INFO, false);

	return true;
}

void Engine::CheckResize() {
	// Get wnd pointer and set it to our window system
	Window* wnd = GetSystem<Window>(SystemType::Sys_Window);
	// See if the user is trying to resize
	if (wnd && wnd->GetResizeData().mustResize) {
		// Get a pointer to our graphics and set it to the system
		Graphics* graph = GetSystem<Graphics>(SystemType::Sys_Graphics);
		if (graph) {
			// Resize the window
			graph->OnResize(wnd->GetResizeData().newWidth, wnd->GetResizeData().newHeight);
			wnd->GetResizeData().mustResize = false;
		}
	}
}

int Engine::AddSystem(System* psys)
{
	// Add the system pointer to our map of systems
	auto element = m_mapSystems.insert(std::make_pair(psys->GetType(), psys));
	if (element.second) { return true; }
	else return false;
}

Game* Engine::CreateGame()
{
	// Create a new game
	if (!AddSystem(new Game(GameData()))) { return nullptr; }
	Game* game = GetSystem<Game>(SystemType::Sys_Game);
	if (!game) { return nullptr; }
	if (!game->Initialize()) { return nullptr; }

	return game;
}
