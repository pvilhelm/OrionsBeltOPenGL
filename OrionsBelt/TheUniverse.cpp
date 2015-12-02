/*
 * TheUniverse.cpp
 *
 *  Created on: 1 dec 2015
 *      Author: potatissoppa
 */

#include "TheUniverse.h"

TheUniverse::TheUniverse(){
	worldObjects = new WorldObject*[100];
}

TheUniverse::~TheUniverse() {
	// TODO Auto-generated destructor stub
	for(unsigned short i=0;i<this->nObjects;i++){
		delete this->worldObjects[i];
	}
	delete worldObjects;
}

MyShip* TheUniverse::GetMyShip() {
	return myShip;
}
