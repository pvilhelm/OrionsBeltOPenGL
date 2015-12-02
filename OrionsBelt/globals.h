/*
 * globals.h
 *
 *  Created on: 1 dec 2015
 *      Author: tomatsoppa
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "WorldObject.h"
#include "main.h"
#include "TheUniverse.h"
#include "GameStateMachine.h"

#define FPS 50
#define PERIOD (1/FPS)

namespace GLB{
extern int w;
extern int h;
}

extern KeyboardState keyboardState;
extern TheUniverse* theWorld;
extern GameStateMachine gameStateMachine;

#endif /* GLOBALS_H_ */
