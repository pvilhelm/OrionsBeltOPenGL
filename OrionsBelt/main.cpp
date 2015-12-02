
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



#include "FreeImage/FreeImagePlus.h"
#include "WorldObject.h"
#include "main.h"
#include "TheUniverse.h"
#include "GameStateMachine.h"
#include "GfxStateMachine.h"

#include "globals.h"




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
	gfxStateMachine.Render();

	//glEnable(GL_CULL_FACE);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();


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
	gfxStateMachine.InitGlut(argc,argv);


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
