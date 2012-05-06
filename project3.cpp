// File: project3.cpp
// 
// Author: Matthew MacEwan
//
// ///////////////////////////////////////////////////////////////////// 

#include <cstdlib>
#include <GL/glut.h>
#include "scene.h"
#include "stereo.h"
#include "camera.h"
#include "targets.h"

class StereoSceneViewport : public StereoViewport {
public:
	Scene& scene;

	StereoSceneViewport(Scene& s) : StereoViewport(), scene(s) {
	}

	virtual void drawScene() {
		scene.render();
	}
};

static StereoSceneViewport* sv;
///////////////////////
// OpenGL callbacks
///////////////////////
static void gldisplay() {
	sv->display();
}

static void glkeyboard(unsigned char key, int x, int y) {
	sv->cam.wasdKeyboard(key);
	glutPostRedisplay();

	switch (key) {
	case'q': 
		exit(0);
		break;
	case 0x1b:
		sv->cam.uncaptureMouse();
		break;
	}
}

static void glpassivemouse(int x, int y) {
	sv->cam.mouseMove(x,y);
}

static void glmouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		sv->cam.captureMouse();
	}
}

static void gltimer(int value) {
	sv->scene.animate();
	glutPostRedisplay();
	// aiming for 50 fps
	glutTimerFunc(20, gltimer, 0);
}

/////////////////////////
// Other functions
/////////////////////////

/// Populates the given Scene with stuff
void populateScene(Scene& scene) {
	scene.addGeometry(*(new Radar()));
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

	// create scene
	Scene theScene;
	populateScene(theScene);
	
	sv = new StereoSceneViewport(theScene);
	sv->initProjection();
	sv->cam.updateScreenCenter();
	glClearColor(0,0,0,0);
	glutDisplayFunc(gldisplay);
	glutKeyboardFunc(glkeyboard);
	glutPassiveMotionFunc(glpassivemouse);
	glutMouseFunc(glmouse);
	glutTimerFunc(20, gltimer, 0);
	glutMainLoop();
}
