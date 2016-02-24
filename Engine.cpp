#include "Engine.h"

#include "Renderer.h"

#include "System.h"
#include "Game.h"
#include "Window.h"
#include "Graphics.h"

#include "EngineTimer.h"

#include "GraphicsDeviceManager.h"

#include "Shape.h" // TESTING
#include "Transform.h"
#include "Collider.h"

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

	//Logger::Log("Ending program");
	//Logger::WriteLogToFile();

	if (!this->ShutDown()) { return 0; }

	return msg.wParam;
}

//Private Methods
int Engine::Intialize()
{
	m_EngineState = EngineState::Initializing;

	Game* game = CreateGame();

	if (!game) { return false; }

	// Add systems
	if (!AddSystem(new Window(WindowData(640, 480))))
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

	GRAPHICSDEVICEMANAGER->SetGraphics(GetSystem<Graphics>(SystemType::Sys_Graphics));

	return true;
}
int Engine::Draw(Context& context)
{
	Graphics* graph = GetSystem<Graphics>(SystemType::Sys_Graphics);
	if (graph == nullptr) return false;

	graph->BeginDraw();

	// Draw Game
	
	RENDERER->SetColor(Color(0, 0, 0, 1));

	Vector2D pos1(150, 150);
	Vector2D pos2(235, 235);

	Transform p1;
	Transform p2;

	Circle c1 = { { 0, 0 }, (float)50 };
	AABB c2 =	{ { 0, 0 }, { 50, 50 } };

	p1.setPosition(pos1);
	//p1.setScale({ 1.0f, 1.0f });
	p2.setPosition(pos2);
	//p2.setScale({ 1.0f, 1.0f});
	
	Collider cc1 = Collider(Collider::e_CIRCLE);
	Collider cc2 = Collider(Collider::e_AABB);
	cc1.SetCircle(Vector2D(0, 0), c1.r);
	cc2.SetAABB(Vector2D(0, 0), Vector2D(50, 50));

	if (EvaluateCollision(p1, cc1, p2, cc2).isOverlap) { RENDERER->SetColor(Color(0, 1, 0, 1)); }
	else RENDERER->SetColor(Color(1, 0, 0, 1));

	RENDERER->FillCircle(p1.getGlobalTransform() * c1);
	RENDERER->FillRect(p2.getGlobalTransform() * c2);

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
		//if (!psys.second->ShutDown())
		{
			//Logger::Log("Failed to shutdown systems" + psys->GetSystemType());
			continue;
		}
		SafeDelete(psys.second);
	}
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
