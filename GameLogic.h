#ifndef _GAMELOGIC_H
#define _GAMELOGIC_H

// Addition Include files
#include "System.h"

struct GameLogicData : public SystemData
{
public:
	GameLogicData();

};
class GameLogic :
	public System
{
	TYPE_INIT(GameLogic);
	friend class Engine;

private:
	GameLogic(const GameLogicData& data);
	virtual ~GameLogic();

	//void* operater new(size_t size);
	//void* operater delete(void* pDelete);

	// Overridable Methods
	virtual bool Initialize();
	virtual bool Update(Context& context);
	virtual bool Draw(Context& context);
	virtual bool ShutDown();

};

#endif // !_GAMELOGIC_H