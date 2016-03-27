#include "GameLogic.h"

#include "Logger.h"
#include "SceneManager.h"
#include "WorldSettings.h"

#include "deletemacros.h"

GameLogicData::GameLogicData()
	: SystemData(_T("GameLogic"), SystemType::Sys_Logic)
{
}

GameLogic::GameLogic(const GameLogicData & data)
	: System(data)
{
	TYPE_REGISTER(GameLogic);
}

GameLogic::~GameLogic()
{
}

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
