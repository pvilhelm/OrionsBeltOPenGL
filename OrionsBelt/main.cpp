
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

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "globals.h"


#include "FreeImage/FreeImagePlus.h"
#include "WorldObject.h"
#include "main.h"
#include "TheUniverse.h"
#include "GameStateMachine.h"



void renderObjects(void){
	glMatrixMode(GL_MODELVIEW);


	for(int i=0;i<theWorld->nObjects;i++){
		glPushMatrix();
		float x = theWorld->worldObjects[i]->x;
		float y = theWorld->worldObjects[i]->y;
		float psi  = theWorld->worldObjects[i]->psi;
		glLoadIdentity();
		glTranslatef(x,y,0);
		glRotatef(psi,0,0,1); //rotera kring z-axeln

		glBegin(GL_LINE_LOOP);
		glColor3f(1.0f, 1.0f, 1.0);
		unsigned short tmp = theWorld->worldObjects[i]->nLine;
		for(unsigned short k=0;k<tmp;k++){

			glVertex2f(theWorld->worldObjects[i]->lineLoop[k]->x,theWorld->worldObjects[i]->lineLoop[k]->y);
		}
		glEnd();
		glPopMatrix();

	}

}



void drawDisplay(void){
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0,GLB::w, 0.0,GLB::h);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*renderShip(theWorld->myShip.x,theWorld->myShip.y,theWorld->myShip.psi);
	renderAsteroids();*/
	renderObjects();

	//glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc (GL_ONE, GL_ONE);
	//glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS);
		glColor4f(1,1,1,1.0);
		glTexCoord2f(0.0, 1.0);glVertex2f(100, 300);//upper left
		glTexCoord2f(0.0, 0.0); glVertex2f(100, 100);//lower left
		glTexCoord2f(1.0, 0.0);glVertex2f(300, 100); //lower right
		glTexCoord2f(1.0, 1.0);glVertex2f(300, 300);///upper right

	glEnd();
	glDisable(GL_TEXTURE_2D);


	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	//glEnable(GL_TEXTURE_2D);



	glFlush();
	glutSwapBuffers();
}




void updateFrame(int data){
	glutTimerFunc(1000/FPS,updateFrame,0);

	gameStateMachine.UpdateStates();

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
	srand(time(NULL));
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
	gluOrtho2D(0.0,GLB::w, 0.0,GLB::h);
	//glDisableClientState( GL_VERTEX_ARRAY );
	GLB::w = glutGet(GLUT_SCREEN_WIDTH);
	GLB::h = glutGet(GLUT_SCREEN_HEIGHT);

	if(GLB::w==3600)
		GLB::w=1920;


	GLuint tempTextureID;
	glGenTextures(1, &tempTextureID);
	glBindTexture(GL_TEXTURE_2D, tempTextureID);
	fipImage* texImg = new fipImage();
	texImg->load("./died.png");

    int width = texImg->getWidth();
    int height= texImg->getHeight();
    printf("kk %d\n",width);
    BYTE* bDataPtr = texImg->accessPixels();
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, width, height,0,GL_RGBA,GL_UNSIGNED_BYTE,bDataPtr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glActiveTexture(tempTextureID);



	glutKeyboardUpFunc(keyboardUpFunc);
	glutKeyboardFunc(keyboardFunc);
	glutDisplayFunc(drawDisplay);
	glutTimerFunc(0,updateFrame,0); // The frame update function (all the work is carried out here)


	// Enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
