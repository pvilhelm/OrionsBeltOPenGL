
/**
 * Copyright 1993-2012 NVIDIA Corporation.  All rights reserved.
 *
 * Please refer to the NVIDIA end user license agreement (EULA) associated
 * with this source code for terms and conditions that govern your use of
 * this software. Any use, reproduction, disclosure, or distribution of
 * this software and related documentation outside the terms of the EULA
 * is strictly prohibited.
 */

#include <stdlib.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#define FPS 50
#define PERIOD (1/50)
float h, w;

struct KeyboardState{
	int w = 0;
	int s = 0;
	int a = 0;
	int d = 0;
	int spc = 0;

};

KeyboardState keyboardState;

struct MyShip {
		float x = 0;
		float y = 0;
		float psi = 0;
		float vx = 0;
		float vy = 0;
		float dpsi = 0;
	};

struct Asteroid {
	float x = 0;
	float y = 0;
	float psi = 0;
	float vx = 0;
	float vy = 0;
	float dpsi = 0;
};

struct WorldObjects{
	MyShip myShip;
	Asteroid* asteroids;
	int nAsteroids = 0;
};

WorldObjects theWorld;

void renderShip(float x, float y, float psi){

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(x,y,0);
	glRotatef(psi,0,0,1); //rotera kring z-axeln

	glBegin(GL_LINE_LOOP);
		glColor3f(1.0f, 1.0f, 1.0);

		glVertex2f(0, -10);
		glVertex2f(40, 0);
		glVertex2f(0, 10);
	glEnd();

	glPopMatrix();

}

void renderAsteroids(){

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	for(int i = 0; i<theWorld.nAsteroids;i++){
		float x = theWorld.asteroids[i].x;
		float y = theWorld.asteroids[i].y;
		float psi  = theWorld.asteroids[i].psi;
		glLoadIdentity();
		glTranslatef(x,y,0);
		glRotatef(psi,0,0,1); //rotera kring z-axeln

		glBegin(GL_LINE_LOOP);
			glColor3f(1.0f, 1.0f, 1.0);

			glVertex2f(0, -30);
			glVertex2f(40, 0);
			glVertex2f(65,8);
			glVertex2f(23,18);
			glVertex2f(0, 10);
			glVertex2f(2,3);
		glEnd();


	}
	glPopMatrix();
}

void drawDisplay(void){
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, w, 0.0, h);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderShip(theWorld.myShip.x,theWorld.myShip.y,theWorld.myShip.psi);
	renderAsteroids();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	//glEnable(GL_TEXTURE_2D);



	//glFlush();
	glutSwapBuffers();
}

void changeShipVelocity() {
	if (keyboardState.w) {
		theWorld.myShip.vx += cos(theWorld.myShip.psi / 57.3) * 20.0f;
		theWorld.myShip.vy += sin(theWorld.myShip.psi / 57.3) * 20.0f;

	}
	if (keyboardState.a) {
		theWorld.myShip.dpsi += 20;

	}
	if (keyboardState.d) {
		theWorld.myShip.dpsi -= 20;

	}
	if (keyboardState.s) {
		theWorld.myShip.vx -= cos(theWorld.myShip.psi / 57.3) * 20.0f;
		theWorld.myShip.vy -= sin(theWorld.myShip.psi / 57.3) * 20.0f;

	}
	if (keyboardState.spc) {
		theWorld.myShip.vx *= 0.9;
		theWorld.myShip.vy *= 0.9;
		theWorld.myShip.dpsi *= 0.8;

	} else {
		theWorld.myShip.vx *= 0.98;
		theWorld.myShip.vy *= 0.98;
		theWorld.myShip.dpsi *= 0.97;
	}


}

void checkBorders() {
	if (theWorld.myShip.x > w)
		theWorld.myShip.x = 0;

	if (theWorld.myShip.y > h)
		theWorld.myShip.y = 0;

	if (theWorld.myShip.x < 0)
		theWorld.myShip.x = w;

	if (theWorld.myShip.y < 0)
		theWorld.myShip.y = h;

	for(int i = 0; i< theWorld.nAsteroids; i++){
		if (theWorld.asteroids[i].x > w)
			theWorld.asteroids[i].x = 0;

		if (theWorld.asteroids[i].y > h)
			theWorld.asteroids[i].y = 0;

		if (theWorld.asteroids[i].x < 0)
			theWorld.asteroids[i].x = w;

		if (theWorld.asteroids[i].y < 0)
			theWorld.asteroids[i].y = h;

	}

}

void changeShipPosition() {
	theWorld.myShip.x += theWorld.myShip.vx / FPS;
	theWorld.myShip.y += theWorld.myShip.vy / FPS;
	theWorld.myShip.psi += theWorld.myShip.dpsi / FPS;
}

void updateFrame(int data){
	glutTimerFunc(1000/FPS,updateFrame,0);

	changeShipVelocity();
	changeShipPosition();

	for(int i = 0; i< theWorld.nAsteroids;i++){
		theWorld.asteroids[i].x += theWorld.asteroids[i].vx/FPS;
		theWorld.asteroids[i].y += theWorld.asteroids[i].vy/FPS;
		theWorld.asteroids[i].psi += theWorld.asteroids[i].dpsi/FPS;
	}

	checkBorders();

	glutPostRedisplay();

}

void keyboardFunc(unsigned char key, int x, int y){
	switch(key){
		case 'w':
			keyboardState.w = 1;
			break;
		case 'a':
			keyboardState.a = 1;
			break;
		case 'd':
			keyboardState.d = 1;
			break;
		case 's':
			keyboardState.s = 1;
			break;
		case ' ':
			keyboardState.spc = 1;
			break;
		default:
			break;
		}
}

void keyboardUpFunc(unsigned char key, int x, int y){
	switch(key){
		case 'w':
			keyboardState.w = 0;
			break;
		case 'a':
			keyboardState.a = 0;
			break;
		case 'd':
			keyboardState.d = 0;
			break;
		case 's':
			keyboardState.s = 0;
			break;
		case ' ':
			keyboardState.spc = 0;
			break;
		default:
			break;
		}
}

int main(int argc, char **argv)
{
// Init glut and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(1000,1000);
	glutCreateWindow("Orion's Belt");
	glutFullScreen();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
	// Set the correct perspective.
	gluOrtho2D(0.0, w, 0.0, h);
	//glDisableClientState( GL_VERTEX_ARRAY );
	w = glutGet(GLUT_SCREEN_WIDTH);
	h = glutGet(GLUT_SCREEN_HEIGHT);

	// Set glut and opengl options:
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glEnable(GL_DEPTH_TEST);

	//
	theWorld.myShip.vx = 100;
	theWorld.myShip.vy = 50;

	theWorld.asteroids = (Asteroid*)calloc(sizeof(Asteroid),100);
	theWorld.asteroids[0].x = 300;
	theWorld.asteroids[0].y = 555;
	theWorld.asteroids[0].vx = 45;
	theWorld.asteroids[0].vy = 11;
	theWorld.asteroids[0].dpsi = 123;
	theWorld.nAsteroids = 1;

	glutKeyboardUpFunc(keyboardUpFunc);
	glutKeyboardFunc(keyboardFunc);
	glutDisplayFunc(drawDisplay);
	glutTimerFunc(0,updateFrame,0); // The frame update function (all the work is carried out here)


	// Enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
