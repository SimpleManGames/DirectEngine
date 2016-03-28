#ifndef _GAMELOGIC_H
#define _GAMELOGIC_H

// Addition Include files
#include "System.h"

struct GameLogicData : public SystemData
{
public:
	// Default constructor for Game Data Logic
	GameLogicData();
};
// GameLogic class that inherits from System
class GameLogic :
	public System
{
	// Define for the gameobject instance
	TYPE_INIT(GameLogic);
	friend class Engine;

private:
	GameLogic(const GameLogicData& data);
	virtual ~GameLogic();

	//void* operater new(size_t size);
	//void* operater delete(void* pDelete);

	// Overridable Methods

	// Initialition of the Game Logic class
	virtual bool Initialize();
	// Updates the game logic
	// Takes in the current context
	virtual bool Update(Context& context);
	// Draws the game logic
	// Takes in the current context
	virtual bool Draw(Context& context);
	// Shut down the game logic
	virtual bool ShutDown();

};

#endif // !_GAMELOGIC_H