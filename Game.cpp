#include "Game.h"

// Game Construtor
Game::Game(const GameData& data)
	: System(data)
{
}

// Default Game Deconstrutor
// Empty
Game::~Game()
{
}

// Game Data construtor
GameData::GameData()
	: SystemData(_T("Game"), SystemType::Sys_Game)
{
}

// Game Data Construtor
GameData::GameData(const std::tstring & name)
	: SystemData(name, SystemType::Sys_Game)
{
}
