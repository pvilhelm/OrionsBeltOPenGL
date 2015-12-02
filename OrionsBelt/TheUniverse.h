/*
 * TheUniverse.h
 *
 *  Created on: 1 dec 2015
 *      Author: potatissoppa
 */

#ifndef THEUNIVERSE_H_
#define THEUNIVERSE_H_

#include "WorldObject.h"

class TheUniverse {
public:
	WorldObject** worldObjects;
	MyShip* myShip;
	int nObjects = 0;
	TheUniverse();
	void AddObject(WorldObject* theObject){
		worldObjects[nObjects++]= theObject;
	}
	void AddMyShip(){
		myShip = new MyShip();
		worldObjects[nObjects++] = myShip;
	}
	virtual ~TheUniverse();
	MyShip* GetMyShip();
};


#endif /* THEUNIVERSE_H_ */
