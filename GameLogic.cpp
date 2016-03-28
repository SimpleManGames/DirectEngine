#include "GameLogic.h"

#include "Logger.h"
#include "SceneManager.h"
#include "WorldSettings.h"

#include "deletemacros.h"

// Default constructor for Game Logic Data
GameLogicData::GameLogicData()
	: SystemData(_T("GameLogic"), SystemType::Sys_Logic)
{
}

// Constructor for Game Logic
// Takes in a ref to Game Logic Data
GameLogic::GameLogic(const GameLogicData & data)
	: System(data)
{
	TYPE_REGISTER(GameLogic);
}

// Destructor for Game Logic
GameLogic::~GameLogic()
{
}

// Initialition of the Game Logic class
bool GameLogic::Initialize()
{
	System::Initialize();

	Singleton<SceneManager>::CreateInstance();
	Singleton<SceneManager>::GetInstance()->SetActiveScene(Singleton<WorldSettings>::GetInstance()->getStartSceneName());

#if defined(DEBUG) | defined(_DEBUG)
	if (!Singleton<SceneManager>::GetInstance()->Initialize())
		return false;
	if (!Singleton<SceneManager>::GetInstance()->LoadContent())
		return false;
#else
	Singleton<SceneManager>::GetInstance()->Initialize();
	Singleton<SceneManager>::GetInstance()->LoadContent();
#endif

	Logger::Log(_T("GameLogic Initialized"), LOGTYPE_INFO, false);

	return true;
}

// Updates the game logic
// Takes in the current context
bool GameLogic::Update(Context & context)
{
	System::Update(context);

#if defined(DEBUG) | defined(_DEBUG)
	if (!Singleton<SceneManager>::GetInstance()->Update(context))
		return false;
#else
	Singleton<SceneManager>::GetInstance()->Update(context);
#endif

	return true;
}

// Draws the game logic
// Takes in the current context
bool GameLogic::Draw(Context & context)
{
	System::Draw(context);

#if defined(DEBUG) | defined(_DEBUG)
	if (!Singleton<SceneManager>::GetInstance()->Draw(context))
		return false;
#else
	Singleton<SceneManager>::GetInstance()->Draw(context);
#endif

	return true;
}

bool GameLogic::ShutDown()
{
	System::ShutDown();

#if defined(DEBUG) | defined(_DEBUG)
	if (!Singleton<SceneManager>::GetInstance()->ShutDown())
	{
		Singleton<SceneManager>::DestoryInstance();
		return false;
	}
#else
	Singleton<SceneManager>::GetInstance()->ShutDown();
	Singleton<SceneManager>::DestoryInstance();
#endif

	return true;
}
