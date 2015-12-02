/*
 * main.h
 *
 *  Created on: 30 nov 2015
 *      Author: potatissoppa
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <GL/freeglut.h>



#define TYPE_MYSHIP 1
#define TYPE_ASTEROID 2

struct KeyboardState{
	int w = 0;
	int s = 0;
	int a = 0;
	int d = 0;
	int spc = 0;

};

class Point {
public:
	float x;
	float y;
};

class Segment{
public:
	Point P0;
	Point P1;
};

class Vector {
	public:
		GLfloat x = 0;
		GLfloat y = 0;
		Vector(GLfloat x,GLfloat y){
			this->x=x;
			this->y=y;
		}
		Vector(){
			x=0;
			y=0;
		}
		void Set(GLfloat x,GLfloat y){
			this->x=x;
			this->y=y;
		}
};

#endif /* MAIN_H_ */
