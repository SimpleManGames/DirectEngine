#include "Engine.h"

#include "Renderer.h"

#include "System.h"
#include "Game.h"
#include "Window.h"
#include "Graphics.h"

#include "EngineTimer.h"

#include "GraphicsDeviceManager.h"

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

	return (int)msg.wParam;
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

	Singleton<GraphicsDeviceManager>::CreateInstance();
	Singleton<GraphicsDeviceManager>::GetInstance()->SetGraphics(GetSystem<Graphics>(SystemType::Sys_Graphics));

	return true;
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

int Engine::Draw(Context& context)
{
	Graphics* graph = GetSystem<Graphics>(SystemType::Sys_Graphics);
	if (graph == nullptr) return false;

	graph->BeginDraw();

	// Draw Game

	CircleCollider c({ 0, 0, 25 });
	RectCollider r({ 100, 100 }, { 200, 200 });

	if (c.vs(r.r))
	{
		RENDERER->DrawCircle(c.pos, c.r); RENDERER->DrawRect(r.r);
	}

	GameObject topWall = { "Top Wall" };
	RectCollider tr({ 0.0 , 0.0 }, { 1.0, (double)GETWINDOW->GetWidth() });
	topWall.AddComponents(&tr);
	tr.DrawCollider(context, { 0,0,0,1 });

	GameObject bottomWall = { "Bottom Wall" };
	RectCollider br({ (double)WINDOW->GetWidth(), (double)WINDOW->GetHeight() }, { (double)WINDOW->GetWidth() - 1.0, (double)WINDOW->GetHeight() });
	bottomWall.AddComponents(&br);
	br.DrawCollider(context, { 0, 0, 0, 1 });

	GameObject a = { "a" };
	TransformComponent ta;
	static Vector3D p = {};
	static Vector3D d = { 1, 1, 1 };
	ta.setPosition(p += d);
	CircleCollider ca;
	ca.setCircle(ta.getPosition().xy, 25);

	a.AddComponents(&ta);
	a.AddComponents(&ca);
	Color c_ = { 0,0,0,1 };
	RENDERER->SetColor(c_);
	RENDERER->DrawLine({br.top, br.left}, { br.top, br.right }, 2.f);

	if (ca.vs(br.r)) 
		d = Vector3D::Reflect(d, { br.top, br.right, 0 });

	a.FindComponentByType<CircleCollider>()->DrawCollider(context, { 0, 0, 0, 1 });

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
