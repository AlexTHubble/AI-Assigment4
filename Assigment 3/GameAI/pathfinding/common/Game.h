#pragma once

/* Game - base class for actual application class

	Dean Lawson
	Champlain College
	2011
*/
#include <Trackable.h>
#include <Timer.h>
#include "Defines.h"

class MemoryTracker;
class PerformanceTracker;
class GraphicsSystem;
class GraphicsBuffer;
class GraphicsBufferManager;
class SpriteManager;
class Game;
class Font;
class ComponentManager;
class UnitManager;

extern PerformanceTracker* gpPerformanceTracker;
extern Game* gpGame;


const IDType BACKGROUND_SPRITE_ID = 0;
const IDType TARGET_SPRITE_ID = 3;
const IDType AI_ICON_SPRITE_ID = 2;

const float LOOP_TARGET_TIME = 33.3f;//how long should each frame of execution take? 30fps = 33.3ms/frame

class Game:public Trackable
{
public:
	Game();
	virtual ~Game();

	virtual bool init();
	virtual void cleanup();

	//game loop
	virtual void beginLoop();
	virtual void processLoop();
	virtual bool endLoop();

	inline GraphicsSystem* getGraphicsSystem() const { return mpGraphicsSystem; };
	inline GraphicsBufferManager* getGraphicsBufferManager() const { return mpGraphicsBufferManager; };
	inline SpriteManager* getSpriteManager() const { return mpSpriteManager; };
	inline Timer* getMasterTimer() const { return mpMasterTimer; };
	inline double getCurrentTime() const { return mpMasterTimer->getElapsedTime(); };
	inline Font* getFont() const { return mpFont; };
	inline void markForExit() { mShouldExit = true; };
	inline ComponentManager* getComponentManager() { return mpComponentManager; };
	inline UnitManager* getUnitManager() { return mpUnitManager; };

protected:
	GraphicsSystem* mpGraphicsSystem;
	GraphicsBufferManager* mpGraphicsBufferManager;
	SpriteManager* mpSpriteManager;
	ComponentManager* mpComponentManager;
	UnitManager* mpUnitManager;
	Timer* mpLoopTimer;
	Timer* mpMasterTimer;
	float mLoopTargetTime;
	bool mShouldExit;

	//should be somewhere else
	Font* mpFont;

	GraphicsBufferID mBackgroundBufferID = "background";
	GraphicsBufferID mEnemyIconBufferID = "enemy";

};

float genRandomBinomial();//range -1:1 from "Artificial Intelligence for Games", Millington and Funge
float genRandomFloat();//range 0:1 from "Artificial Intelligence for Games", Millington and Funge
float mapRotationToRange( float rotation, float low, float high );

const double PI = std::atan(1.0)*4;//could proved useful!
