/*
 * GfxStateMachine.h
 *
 *  Created on: 2 dec 2015
 *      Author: potatissoppa
 */

#ifndef GFXSTATEMACHINE_H_
#define GFXSTATEMACHINE_H_


#include "FreeImage/FreeImagePlus.h"
#include "WorldObject.h"
#include "main.h"
#include "TheUniverse.h"
#include "GameStateMachine.h"

enum GameState {
	PLAYING,
	STARTSCREEN,
	DEAD
};

class GfxStateMachine {
public:
	GfxStateMachine();
	virtual ~GfxStateMachine();
	GameState GetGamestate();
	void SetGamestate(GameState);
	void RenderObjects();
	void InitGlut(int argc, char** argcv);
	GameState gameState;
	void Render();
	void RenderDeadScreen();
};


#endif /* GFXSTATEMACHINE_H_ */
