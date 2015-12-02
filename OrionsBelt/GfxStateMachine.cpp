/*
 * GfxStateMachine.cpp
 *
 *  Created on: 2 dec 2015
 *      Author: potatissoppa
 */

#include "GfxStateMachine.h"
#include "globals.h"

GfxStateMachine::GfxStateMachine() {
	// TODO Auto-generated constructor stub
	gameState = STARTSCREEN;
}

GfxStateMachine::~GfxStateMachine() {
	// TODO Auto-generated destructor stub
}

GameState GfxStateMachine::GetGamestate() {
	return gameState;
}

void GfxStateMachine::SetGamestate(GameState enumGameState) {
	gameState = enumGameState;
}

void GfxStateMachine::InitGlut(int argc, char** argcv) {
	glutInit(&argc, argcv);
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
}

void GfxStateMachine::RenderObjects(void){



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

void GfxStateMachine::Render() {

	glMatrixMode(GL_MODELVIEW);

	RenderObjects();

	if(GetGamestate()==DEAD)
		RenderDeadScreen();

}

void GfxStateMachine::RenderDeadScreen() {
	glPushMatrix();
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBegin(GL_QUADS);
		glColor4f(1,1,1,1.0);
		glTexCoord2f(0.0, 1.0);glVertex2f(GLB::w*0.4, GLB::h*0.5+GLB::w*0.1);//upper left
		glTexCoord2f(0.0, 0.0); glVertex2f(GLB::w*0.4,  GLB::h*0.5-GLB::w*0.1);//lower left
		glTexCoord2f(1.0, 0.0);glVertex2f(GLB::w*0.6, GLB::h*0.5-GLB::w*0.1); //lower right
		glTexCoord2f(1.0, 1.0);glVertex2f(GLB::w*0.6, GLB::h*0.5+GLB::w*0.1);///upper right

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


}
