/*
 * GameStateMachine.cpp
 *
 *  Created on: 1 dec 2015
 *      Author: tomatsoppa
 */

#include <math.h>

#include "GameStateMachine.h"
#include "globals.h"
#include "WorldObject.h"
#include "TheUniverse.h"

void changeShipVelocity() {
	MyShip *myShip = theWorld->GetMyShip();
	if(myShip == NULL)
		return;

	if (keyboardState.w) {
		myShip->vx += cos(myShip->psi / 57.3) * 20.0f;
		myShip->vy += sin(myShip->psi / 57.3) * 20.0f;

	}
	if (keyboardState.a) {
		myShip->dpsi += 20;

	}
	if (keyboardState.d) {
		myShip->dpsi -= 20;

	}
	if (keyboardState.s) {
		myShip->vx -= cos(myShip->psi / 57.3) * 20.0f;
		myShip->vy -= sin(myShip->psi / 57.3) * 20.0f;

	}
	if (keyboardState.spc) {
		myShip->vx *= 0.9;
		myShip->vy *= 0.9;
		myShip->dpsi *= 0.8;

	} else {
		myShip->vx *= 0.98;
		myShip->vy *= 0.98;
		myShip->dpsi *= 0.97;
	}


}

void checkBorders() {

	for(int i = 0; i< theWorld->nObjects; i++){
		if(theWorld->worldObjects[i]->objType == TYPE_BULLET)
			continue;

		if (theWorld->worldObjects[i]->x >GLB::w)
			theWorld->worldObjects[i]->x = 0;

		if (theWorld->worldObjects[i]->y >GLB::h)
			theWorld->worldObjects[i]->y = 0;

		if (theWorld->worldObjects[i]->x < 0)
			theWorld->worldObjects[i]->x =GLB::w;

		if (theWorld->worldObjects[i]->y < 0)
			theWorld->worldObjects[i]->y =GLB::h;

	}

}


float euclDist(Vector* p1, Vector* p2){
	return sqrt(pow(p2->x-p1->x,2)+pow(p2->y-p1->y,2));

}

void changeObjectPosition(){
	for(int i=0;i<theWorld->nObjects;i++){
		WorldObject* tmp = theWorld->worldObjects[i];
		tmp->x += tmp->vx/FPS;
		tmp->y += tmp->vy/FPS;
		tmp->psi += tmp->dpsi/FPS;
	}
}

int checkCollision(WorldObject* worldObject){
	if (worldObject == NULL)
		return 0;

	Vector* p0 = (Vector*)&(worldObject->x);
	for(int i=0;i<theWorld->nObjects;i++){
		if(worldObject == theWorld->worldObjects[i])
			continue;
		Vector* p1 = (Vector*)&(theWorld->worldObjects[i]->x);
		float d = euclDist(p0,p1);
		if(d<worldObject->colRad+theWorld->worldObjects[i]->colRad)
			return 1;
	}
	return 0;
}

int checkFineCollision(WorldObject* worldObject){




}

GameStateMachine::GameStateMachine() {
	// TODO Auto-generated constructor stub

	theWorld = new TheUniverse();

}

GameStateMachine::~GameStateMachine() {
	// TODO Auto-generated destructor stub
}

void GameStateMachine::UpdateObjects(){
	MyShip* myShip = theWorld->GetMyShip();
	if(myShip!=NULL & keyboardState.ent)
		myShip->FireBullet();

}

void GameStateMachine::UpdateStates() {

	if((!isLive) & keyboardState.spc  ){
		theWorld->~TheUniverse();
		theWorld = new TheUniverse();
		theWorld->AddMyShip();
		for(int i=0;i<4;i++)
			theWorld->AddObject(new Asteroid());
		isLive = true;
		gfxStateMachine.SetGamestate(PLAYING);
	}


	changeObjectPosition();
	checkBorders();


	if(isLive){
		changeShipVelocity();
		UpdateObjects();
		if(checkCollision(theWorld->GetMyShip())){
			KillGame();
		}
	}
}

void GameStateMachine::KillGame() {
	MyShip* myShip = theWorld->GetMyShip();
	myShip->Kill();
	isLive = false;
	gfxStateMachine.SetGamestate(DEAD);
}


#define SMALL_NUM   0.00000001 // anything that avoids division overflow
#define perp(u,v)  ((u).x * (v).y - (u).y * (v).x)  // perp product  (2D)

// Copyright 2001 softSurfer, 2012 Dan Sunday
// This code may be freely used, distributed and modified for any purpose
// providing that this copyright notice is included with it.
// SoftSurfer makes no warranty for this code, and cannot be held
// liable for any real or imagined damage resulting from its use.
// Users of this code must verify correctness for their application.

// Assume that classes are already given for the objects:
//    Point and Vector with
//        coordinates {float x, y, z;}
//        operators for:
//            == to test  equality
//            != to test  inequality
//            Point   = Point ± Vector
//            Vector =  Point - Point
//            Vector =  Scalar * Vector    (scalar product)
//            Vector =  Vector * Vector    (3D cross product)
//    Line and Ray and Segment with defining  points {Point P0, P1;}
//        (a Line is infinite, Rays and  Segments start at P0)
//        (a Ray extends beyond P1, but a  Segment ends at P1)
//    Plane with a point and a normal {Point V0; Vector  n;}
//===================================================================
// intersect2D_2Segments(): find the 2D intersection of 2 finite segments
//    Input:  two finite segments S1 and S2
//    Output: *I0 = intersect point (when it exists)
//            *I1 =  endpoint of intersect segment [I0,I1] (when it exists)
//    Return: 0=disjoint (no intersect)
//            1=intersect  in unique point I0
//            2=overlap  in segment from I0 to I1
/*int intersect2D_2Segments( Segment S1, Segment S2, Point* I0, Point* I1 )
{


	Vector    u = S1.P1 - S1.P0;
    Vector    v = S2.P1 - S2.P0;
    Vector    w = S1.P0 - S2.P0;
    float     D = perp(u,v);

    // test if  they are parallel (includes either being a point)
    if (fabs(D) < SMALL_NUM) {           // S1 and S2 are parallel
        if (perp(u,w) != 0 || perp(v,w) != 0)  {
            return 0;                    // they are NOT collinear
        }
        // they are collinear or degenerate
        // check if they are degenerate  points
        float du = dot(u,u);
        float dv = dot(v,v);
        if (du==0 && dv==0) {            // both segments are points
            if (S1.P0 !=  S2.P0)         // they are distinct  points
                 return 0;
            *I0 = S1.P0;                 // they are the same point
            return 1;
        }
        if (du==0) {                     // S1 is a single point
            if  (inSegment(S1.P0, S2) == 0)  // but is not in S2
                 return 0;
            *I0 = S1.P0;
            return 1;
        }
        if (dv==0) {                     // S2 a single point
            if  (inSegment(S2.P0, S1) == 0)  // but is not in S1
                 return 0;
            *I0 = S2.P0;
            return 1;
        }
        // they are collinear segments - get  overlap (or not)
        float t0, t1;                    // endpoints of S1 in eqn for S2
        PosVector w2 = S1.P1 - S2.P0;
        if (v.x != 0) {
                 t0 = w.x / v.x;
                 t1 = w2.x / v.x;
        }
        else {
                 t0 = w.y / v.y;
                 t1 = w2.y / v.y;
        }
        if (t0 > t1) {                   // must have t0 smaller than t1
                 float t=t0; t0=t1; t1=t;    // swap if not
        }
        if (t0 > 1 || t1 < 0) {
            return 0;      // NO overlap
        }
        t0 = t0<0? 0 : t0;               // clip to min 0
        t1 = t1>1? 1 : t1;               // clip to max 1
        if (t0 == t1) {                  // intersect is a point
            *I0 = S2.P0 +  t0 * v;
            return 1;
        }

        // they overlap in a valid subsegment
        *I0 = S2.P0 + t0 * v;
        *I1 = S2.P0 + t1 * v;
        return 2;
    }

    // the segments are skew and may intersect in a point
    // get the intersect parameter for S1
    float     sI = perp(v,w) / D;
    if (sI < 0 || sI > 1)                // no intersect with S1
        return 0;

    // get the intersect parameter for S2
    float     tI = perp(u,w) / D;
    if (tI < 0 || tI > 1)                // no intersect with S2
        return 0;

    *I0 = S1.P0 + sI * u;                // compute S1 intersect point
    return 1;
}
*/
