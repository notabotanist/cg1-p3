// File: targets.cpp
//
// Author: Matthew MacEwan
//
// ////////////////////////////////////////////////////////////////////// 

#include <GL/glut.h>
#include "targets.h"

Radar::Radar() : rotation(0), dR(5) {
}

void Radar::doRender() {
	glPushMatrix();
	// Blender helped with the modeling

	// draw base
	glPushMatrix();
	glTranslatef(0, 0.371, 0);
	glScalef(1, 0.371, 1);
	if(solid) {
		glutSolidCube(1.0);
	} else {
		glutWireCube(1.0);
	}
	glPopMatrix();

	// rotate LCS for dish
	glRotatef(rotation, 0, 1, 0);

	// draw arm
	glPushMatrix();
	glTranslatef(0, 1.256, 0.393);
	glScalef(0.557, 1.023, 0.557);
	if (solid) {
		glutSolidCone(1.0, 1.0, 4, 1);
	} else {
		glutWireCone(1.0, 1.0, 4, 1);
	}
	glPopMatrix();

	// draw dish
	glPushMatrix();
	glTranslatef(0, 1.909, 0.126);
	glScalef(1.019, 0.590, 1.019);
	glRotatef(-118.9, 1, 0, 0);
	if (solid) {
		glutSolidCone(1.0, 1.0, 8, 2);
	} else {
		glutWireCone(1.0, 1.0, 8, 2);
	}
	glPopMatrix();

	glPopMatrix();
}

void Radar::animate() {
	rotation = (rotation + dR) % 360;
}
