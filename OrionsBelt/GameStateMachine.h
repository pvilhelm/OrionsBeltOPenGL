/*
 * GameStateMachine.h
 *
 *  Created on: 1 dec 2015
 *      Author: tomatsoppa
 */

#ifndef GAMESTATEMACHINE_H_
#define GAMESTATEMACHINE_H_

class GameStateMachine {
public:
	GameStateMachine();
	virtual ~GameStateMachine();
	bool isLive = false;
	void UpdateStates();
	void KillGame();
	void UpdateObjects();
};

#endif /* GAMESTATEMACHINE_H_ */
