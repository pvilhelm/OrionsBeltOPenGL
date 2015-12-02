/*
 * WorldObject.cpp
 *
 *  Created on: 30 nov 2015
 *      Author: potatissoppa
 */

#include "WorldObject.h"
#include "math.h"
#include "globals.h"

#define RANDZ(x) (rand()%x)
#define RANDZM(x) (rand()%x-x/2)


WorldObject::WorldObject(float x,float y,float psi,float vx,float vy,float dpsi){
			this->x = x;
			this->y = y;
			this->psi = psi;
			this->vx = vx;
			this->vx = vy;
			this->dpsi = dpsi;
}

WorldObject::WorldObject() {
			this->x = 0;
			this->y = 0;
			this->psi = 0;
			this->vx = 0;
			this->vx = 0;
			this->dpsi = 0;
}

void WorldObject::SetGeometry(GLfloat* points, int nPointPairs){

		}

WorldObject::~WorldObject() {
	// TODO Auto-generated destructor stub

	for(unsigned short i = 0; i < this->nLine;i++){
		delete this->lineLoop[i];
	}
	delete this->lineLoop;
}

Asteroid::Asteroid(){
	//{Vector(0, -10), Vector(40,0), Vector(0,10)}
	this->lineLoop = new Vector*[8];
	this->lineLoop[0] = new Vector(50+RANDZM(7),0+RANDZM(7));
	this->lineLoop[1] = new Vector(40+RANDZM(7),40+RANDZM(7));
	this->lineLoop[2] = new Vector(0+RANDZM(7),50+RANDZM(7));
	this->lineLoop[3] = new Vector(-40+RANDZM(7),40+RANDZM(7));
	this->lineLoop[4] = new Vector(-50+RANDZM(7),0+RANDZM(7));
	this->lineLoop[5] = new Vector(-40+RANDZM(7),-40+RANDZM(7));
	this->lineLoop[6] = new Vector(0+RANDZM(7),-50+RANDZM(7));
	this->lineLoop[7] = new Vector(40+RANDZM(7),-40+RANDZM(7));
	this->nLine = 8;
	this->x = rand()%GLB::w;
	this->y = rand()%GLB::h;
	this->vx = +RANDZM(20);
	this->vy = +RANDZM(30);
	this->dpsi = +RANDZM(50);
	objType = TYPE_ASTEROID;
	colRad = 55;
}

MyShip::MyShip(){
	this->lineLoop = new Vector*[3];
	this->lineLoop[0] = new Vector(-40/3,-10);
	this->lineLoop[1] = new Vector(40*2/3,-0);
	this->lineLoop[2] = new Vector(-40/3,10);
	this->nLine = 3;
	this->objType = TYPE_MYSHIP;
	colRad = 30;
}



