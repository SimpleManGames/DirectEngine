#include "Engine.h"

#include "Renderer.h"

#include "System.h"
#include "Game.h"
#include "Window.h"
#include "Graphics.h"

#include "EngineTimer.h"

#include "GraphicsDeviceManager.h"
#include "WorldSettings.h"

#include "Logger.h"

#include <iostream>

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
	Context context;
	context.pRenderer = new Renderer();

	if (!this->Intialize()) { return 0; }

	srand(GetTickCount());

	MSG msg = {};

	m_EngineState = EngineState::Running;

	while (msg.message != WM_QUIT && m_EngineState == EngineState::Running)
	{
		CheckResize();

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		this->Update(context);
		this->Draw(context);
	}

	Logger::Log(_T("Ending program"), LOGTYPE_INFO, false);
	Logger::WriteLogFile();

	if (!this->ShutDown()) { return 0; }

	return (int)msg.wParam;
}

#include "Circle.h"
#include "Rect2D.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "CircleCollider.h"
#include "RectCollider.h"
#include "Collision.h"
#include "PhysicsComponent.h"
#include "ComponentManager.h"

//Private Methods
int Engine::Intialize()
{
	m_EngineState = EngineState::Initializing;

	Singleton<WorldSettings>::CreateInstance();

	Game* game = CreateGame();

	if (!game) { return false; }

	// Add systems
	if (!AddSystem(new Window(WindowData(Singleton<WorldSettings>::GetInstance()->getWindowWidth(), 
										 Singleton<WorldSettings>::GetInstance()->getWindowHeight(), 
										 Singleton<WorldSettings>::GetInstance()->getWindowTitle()))))
		return false;

	if (!AddSystem(new Graphics(GraphicsData(GetSystem<Window>(SystemType::Sys_Window)))))
		return false;

	if (!AddSystem(new EngineTimer(EngineTimerData())))
		return false;

	// Initialize the system
	if (!m_mapSystems[SystemType::Sys_Window]->Initialize())
		return false;
	if (!m_mapSystems[SystemType::Sys_Graphics]->Initialize())
		return false;
	if (!m_mapSystems[SystemType::Sys_EngineTimer]->Initialize())
		return false;

	Singleton<GraphicsDeviceManager>::CreateInstance();
	Singleton<GraphicsDeviceManager>::GetInstance()->SetGraphics(GetSystem<Graphics>(SystemType::Sys_Graphics));

	return true;
}



int Engine::Draw(Context& context)
{
	Graphics* graph = GetSystem<Graphics>(SystemType::Sys_Graphics);
	if (graph == nullptr) return false;

	graph->BeginDraw();

	// Draw Game

	Ray ray(100, 100, 200, 200, 5);
	Rect2D rect(100, 150, 200, 250);

	RENDERER->DrawLine(ray.pos, ray.dir, 5.f);
	RENDERER->DrawRect(rect, 5.f);

	

	graph->EndDraw();

	return true;
}
int Engine::Update(Context& context)
{
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
	m_EngineState = EngineState::ShuttingDown;

	for (std::pair<SystemType, System*> psys : m_mapSystems)
	{
		if (!psys.second->ShutDown())
		{
			Logger::Log(_T("Failed to shutdown system: " + psys.second->GetName()), LOGTYPE_WARNING, false);
			continue;
		}
		SafeDelete(psys.second);
	}
	Singleton<WorldSettings>::DestoryInstance();

	return true;
}

void Engine::CheckResize() {
	Window* wnd = GetSystem<Window>(SystemType::Sys_Window);
	if (wnd && wnd->GetResizeData().mustResize) {
		Graphics* graph = GetSystem<Graphics>(SystemType::Sys_Graphics);
		if (graph) {
			graph->OnResize(wnd->GetResizeData().newWidth, wnd->GetResizeData().newHeight);
			wnd->GetResizeData().mustResize = false;
		}
	}
}

int Engine::AddSystem(System* psys)
{
	auto element = m_mapSystems.insert(std::make_pair(psys->GetType(), psys));
	if (element.second) { return true; }
	else return false;
}

Game* Engine::CreateGame()
{
	if (!AddSystem(new Game(GameData()))) { return nullptr; }
	Game* game = GetSystem<Game>(SystemType::Sys_Game);
	if (!game) { return nullptr; }
	if (!game->Initialize()) { return nullptr; }

	return game;
}
