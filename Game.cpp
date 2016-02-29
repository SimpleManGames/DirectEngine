#include "Game.h"



Game::Game(const GameData& data)
	: System(data)
{
}


Game::~Game()
{
}

GameData::GameData()
	: SystemData(_T("Game"), SystemType::Sys_Game)
{
}

GameData::GameData(const std::tstring & name)
	: SystemData(name, SystemType::Sys_Game)
{
}
