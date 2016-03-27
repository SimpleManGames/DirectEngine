#include "SceneManager.h"

#include "Logger.h"

//#include "SceneFactory.h"
//#include "Scene.h"
//#include "LoadingScene.h"

//#ifndef _CONSTANTS_H
//#include "constants.h"
//#endif

SceneManager::SceneManager()
	: m_pActiveScene(nullptr)
	, m_pLoadingScene(nullptr)
{

}


SceneManager::~SceneManager() { }

bool SceneManager::Initialize()
{
	if(m_pActiveScene)
	{
		
	}

	return true;
}

bool SceneManager::LoadContent()
{
	if (m_pActiveScene)
	{
		
	}

	return true;
}

bool SceneManager::Update(Context & context)
{
	if (m_pActiveScene)
	{

	}

	return true;
}

bool SceneManager::Draw(Context & context)
{
	if (m_pActiveScene)
	{

	}

	return true;
}

bool SceneManager::ShutDown()
{
	if (m_pActiveScene)
	{

	}

	return true;
}

bool SceneManager::AddScene(Scene * scene)
{
	return true;
}

bool SceneManager::RemoveScene(const std::tstring & name)
{
	return true;
}

Scene * SceneManager::FindScene(const std::tstring & name)
{
	return nullptr;
}

Scene * SceneManager::GetActiveScene()
{
	if(m_pActiveScene)
	{
	
	}

	return nullptr;
}

void SceneManager::ClearScenes()
{

}

void SceneManager::SetActiveScene(const std::tstring & name)
{

}
