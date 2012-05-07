// 
// File: stereo.cpp 
// 
// @author matthew: TODO_AUTHOR_FULL_NAME_
// 
// Version: 
// $Id$ 
// 
// Revisions: 
// $Log$ 
// 
// //////////////////////////////////////////////////////////////////// 

// include files, system headers first
#include <GL/glut.h>

#include "stereo.h"          // local header include

/// namespace TODO_OPTIONAL_ is optional
// namespace TODO_OPTIONAL_ {

/// ctor: basic default values
StereoViewport::StereoViewport() : width(1000), height(500), x(0), y(0),
	eyeoff(0.2), fov(60.f), pnear(1.f), pfar(20.f) {
}

/// init projection matrix
void StereoViewport::initProjection(float viewangle, float nearplane, float farplane) {
	fov = viewangle;
	pnear = nearplane;
	pfar = farplane;
	// set up projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, (GLfloat)width / (GLfloat)(2 * height), pnear, pfar);
	glMatrixMode(GL_MODELVIEW);
}

/// change viewport dimensions
void StereoViewport::setDimensions(int w, int h) {
	width = w;
	height = h;
	// update perspective projection for new aspect ratio
	initProjection(fov, pnear, pfar);
}

/// rendering callback
void StereoViewport::display() {
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT);

	// setup left viewport (right eye view)
	glViewport(x, y, width/2.0, height);
	glClear(GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-eyeoff, 0, 0);
	cam.applyXform();
	drawScene();

	// setup right viewport (left eye view)
	glViewport(x+width/2.0, y, width/2.0, height);
	glClear(GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(eyeoff, 0, 0);
	cam.applyXform();
	drawScene();

	glutSwapBuffers();
}

/// default scene
void StereoViewport::drawScene() {
	glTranslatef(0.0, 0.0, -5);
	glColor3f(1, 1, 1);
	glutWireCube(1.0);
}

// } // end namespace TODO_OPTIONAL_

// (main function is NEVER in a namespace)
/////////////////////////// main // TODO_ // DELETE section if not needed

/*
static StereoViewport sv;
static void gldisplay() {
	sv.display();
}

static void glkeyboard(unsigned char key, int x, int y) {
	sv.cam.wasdKeyboard(key);
	glutPostRedisplay();

	switch (key) {
	case'q': 
		// exit(0);
		break;
	case 0x1b:
		sv.cam.uncaptureMouse();
		break;
	}
}

static void glpassivemouse(int x, int y) {
	sv.cam.mouseMove(x,y);
}

static void glmouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		sv.cam.captureMouse();
	}
}

///
/// main function TODO_DOCS_
/// @author matthew: TODO_AUTHOR_FULL_NAME_
///
/// @param argc  number of command line arguments, including program name
/// @param argv  supplied command line arguments, including program name
/// @returns errorCode  the error Code; 0 if no error
///
int main( int argc, char* argv[] ) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1000, 500);
	glutCreateWindow(argv[0]);

	sv.initProjection();
	sv.cam.updateScreenCenter();
	glClearColor(0,0,0,0);
	glutDisplayFunc(gldisplay);
	glutKeyboardFunc(glkeyboard);
	glutPassiveMotionFunc(glpassivemouse);
	glutMouseFunc(glmouse);
	glutMainLoop();
}
*/

