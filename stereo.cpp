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
StereoViewport::StereoViewport() : width(1000), height(500), x(0), y(0), eyeoff(0.2) {
}

/// rendering callback
void StereoViewport::display() {
	// set up projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, width / (2 * height), 0.1, 10);
	glMatrixMode(GL_MODELVIEW);

	// setup left viewport (right eye view)
	glViewport(x, y, width/2, height);
	glLoadIdentity();
	glTranslatef(-eyeoff, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	drawScene();
	// setup right viewport (left eye view)
	glViewport(x+width/2, y, width/2, height);
	glLoadIdentity();
	glTranslatef(eyeoff, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	drawScene();

	glFlush();
}

/// default scene
void StereoViewport::drawScene() {
	glTranslatef(0.0, 0.0, 5);
	glColor3f(1, 1, 1);
	glutWireCube(1.0);
}

// } // end namespace TODO_OPTIONAL_

// (main function is NEVER in a namespace)
/////////////////////////// main // TODO_ // DELETE section if not needed

static StereoViewport sv;
static void gldisplay() {
	sv.display();
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
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(1000, 500);
	glutCreateWindow(argv[0]);

	glClearColor(0,0,0,0);
	glutDisplayFunc(gldisplay);
	glutMainLoop();
}

