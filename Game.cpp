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
// Takes in a tstring and sets the name of the system to it
GameData::GameData(const std::tstring & name)
	: SystemData(name, SystemType::Sys_Game)
{
}
