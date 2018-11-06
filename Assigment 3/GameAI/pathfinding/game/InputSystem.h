#pragma once
#include <sstream>
#include <SDL.h>


#include "GameMessageManager.h"
#include "GraphicsBufferManager.h"
#include "GraphicsSystem.h"
#include "GameMessageManager.h"
#include "PathToMessage.h"
#include "Game.h"

class InputSystem : public Trackable
{
public:
	InputSystem();
	~InputSystem();

	void init();
	void cleanup();
	void update();

	//void setFlockSteering(Flock *theSteering) { mpFlockSteering = theSteering; };
	

private:
	GameMessageManager * mpMessageManager;
	SpriteManager * mpSpriteManager;
	IDType mAiSpriteID;
};