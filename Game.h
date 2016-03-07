#ifndef _GAME_H
	#define _GAME_H

#include "System.h"

/// Structs
// GameData inherits from SystemData
struct GameData : public SystemData
{
	/// Construtors & Deconstrutors

	// Default GameData Construtor
	GameData();
	// GameData Construtor
	// param: name = Name of the SystemData
	GameData(const std::tstring& name);
};
// Game class
class Game : public System
{
public:
	/// Construtors & Deconstrutors

	// Game Construtor
	Game(const GameData& data);
	// Default Game Deconstrutor
	// Empty
	virtual ~Game();
};

#endif // !_GAME_H