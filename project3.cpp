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
#include "hud.h"

class StereoSceneViewport : public StereoViewport {
public:
	Scene& scene;

	StereoSceneViewport(Scene& s) : StereoViewport(), scene(s) {
	}

	virtual void drawScene() {
		scene.render();
	}
};

class Building : public Geometry {
public:
	float height;
	// length of both sides of building base
	float base;

protected:
	virtual void doRender() {
		glPushMatrix();

		glColor3ub(127, 127, 127);
		// Align base of building with floor
		glTranslatef(0, height/2, 0);
		glScalef(base, height, base);
		if (solid) {
			glutSolidCube(1.0);
		} else {
			glutWireCube(1.0);
		}

		glPopMatrix();
	}

public:
	/// Constructor
	/// Specify xyz location, height, and base
	Building(float x, float y, float z, float h, float b) :
		Geometry(x, y, z), height(h), base(b) {
		setBound(b/2);
	}
};

/// Globals and prototypes
static StereoSceneViewport* sv;
static Hud* hud;
void resetCamera();

///////////////////////
// OpenGL callbacks
///////////////////////
static void gldisplay() {
	sv->display();
}

static void glkeyboard(unsigned char key, int x, int y) {
	sv->cam.wasdKeyboard(key);
	hud->fixLCS();

	switch (key) {
	case 'r':
		resetCamera();
		break;
	case 'q': 
		exit(0);
		break;
	case 0x1b:
		sv->cam.uncaptureMouse();
		break;
	case '1':
		sv->scene.setAllSolid(false);
		break;
	case '2':
		sv->scene.setAllSolid(true);
		break;
	}

	glutPostRedisplay();
}

static void glpassivemouse(int x, int y) {
	sv->cam.mouseMove(x,y);
	hud->fixLCS();
}

static void glmouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (sv->cam.isMouseCaptured()) {
			hud->startWarning();
		} else {
			sv->cam.captureMouse();
		}
	}
	if (state == GLUT_DOWN) {
		glpassivemouse(x, y);
	}
}

static void gltimer(int value) {
	sv->scene.animate();
	glutPostRedisplay();
	// aiming for 50 fps
	glutTimerFunc(20, gltimer, 0);
}

static void glreshape(int width, int height) {
	sv->setDimensions(width, height);
	sv->cam.updateScreenCenter();
}

/////////////////////////
// Other functions
/////////////////////////

/// Populates the given Scene with stuff
void populateScene(Scene& scene) {
	// add hud
	scene.addGeometry(*hud);

	// add radar installations
	float alleySize = 3.5; // distance between buildings
	float halfAlley = alleySize / 2;

	scene.addGeometry(*(new Radar(0*alleySize+halfAlley, 0, 0)));
	scene.addGeometry(*(new Radar(0, 0, 1*alleySize+halfAlley)));

	// add buildings
	for (float x(-4*alleySize); x <= 4*alleySize; x += alleySize) {
		for (float z(-4*alleySize); z <= 4*alleySize; z += alleySize) {
			scene.addGeometry(*(new Building(x, 0, z, abs((int)(x+z)%4)+1, 1.5)));
		}
	}
}

/// Moves sv's camera to its set original position
void resetCamera() {
	sv->cam.x = 0;
	sv->cam.y = 2;
	sv->cam.z = 3;
	sv->cam.pitch = 0;
	sv->cam.yaw = 0;
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
	
	sv = new StereoSceneViewport(theScene);
	sv->initProjection(60, 1, 40);
	sv->cam.updateScreenCenter();
	resetCamera();
	hud = new Hud(sv->cam);

	populateScene(theScene);

	// Final setup, including callbacks
	glClearColor(0,0,0,0);
	glutDisplayFunc(gldisplay);
	glutKeyboardFunc(glkeyboard);
	glutPassiveMotionFunc(glpassivemouse);
	glutMouseFunc(glmouse);
	glutTimerFunc(20, gltimer, 0);
	glutReshapeFunc(glreshape);
	glutMainLoop();
}
