/*
 * WorldObject.h
 *
 *  Created on: 30 nov 2015
 *      Author: potatissoppa
 */

#ifndef WORLDOBJECT_H_
#define WORLDOBJECT_H_

#include "main.h"

#define TYPE_MYSHIP 1
#define TYPE_ASTEROID 2
#define TYPE_BULLET 3

enum plyTypes {
	LINE_LOOP,
	VERTEX
};

class WorldObject {
public:

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
	plyTypes plyType ;
	Vector ** lineLoop;
	unsigned short nLine;
	int reserved[4];
};


class MyShip: public WorldObject {

	public:
		MyShip();
		void Kill();
		void FireBullet();
	};

class Asteroid: public WorldObject {
	public:
		Asteroid();
};

class Bullet: public WorldObject{
	public:
		Bullet(WorldObject* parent);
};

class Schrapnel: public WorldObject{
public:
	Schrapnel(Point start, WorldObject parent);
};

class Explosion: public WorldObject{
	public:
		Explosion(Point start, WorldObject parent);
};

#endif /* WORLDOBJECT_H_ */

