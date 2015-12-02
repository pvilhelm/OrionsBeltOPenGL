/*
 * WorldObject.h
 *
 *  Created on: 30 nov 2015
 *      Author: potatissoppa
 */

#ifndef WORLDOBJECT_H_
#define WORLDOBJECT_H_

#include "main.h"



class WorldObject {
public:
	WorldObject(float x,float y,float psi,float vx,float vy,float dpsi);
	WorldObject();
	virtual ~WorldObject();
	void SetGeometry(GLfloat* points, int nPointPairs);
	int objType;
	float x;
	float y;
	float psi;
	float vx;
	float vy;
	float dpsi;
	float colRad;
	unsigned int plyType ;
	Vector ** lineLoop;
	unsigned short nLine;
	int reserved[4];
};







class MyShip: public WorldObject {

	public:
		MyShip();
	};

class Asteroid: public WorldObject {
	public:
		Asteroid();
};

#endif /* WORLDOBJECT_H_ */

