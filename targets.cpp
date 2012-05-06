// File: targets.cpp
//
// Author: Matthew MacEwan
//
// ////////////////////////////////////////////////////////////////////// 

#include <GL/glut.h>
#include "targets.h"

Target::Target() : Geometry() {}
Target::Target(float _x, float _y, float _z) : Geometry(_x, _y, _z) {
}

Radar::Radar() : rotation(0), dR(5) {
}

Radar::Radar(float _x, float _y, float _z) : Target(_x, _y, _z), rotation(0), dR(5) {
}

void Radar::doRender() {
	glPushMatrix();
	// Blender helped with the modeling

	// draw base
	glPushMatrix();
	glTranslatef(0, 0.371, 0);
	glScalef(1, 0.371, 1);
	if(solid) {
		glutSolidCube(2.0);
	} else {
		glutWireCube(2.0);
	}
	glPopMatrix();

	// rotate LCS for dish
	glRotatef(rotation, 0, 1, 0);

	// draw arm
	glPushMatrix();
	glTranslatef(0, 0.742, 0.393);
	glScalef(0.557, 1.023, 0.557);
	glRotatef(-90, 1, 0, 0);
	if (solid) {
		glutSolidCone(1.0, 1.0, 4, 1);
	} else {
		glutWireCone(1.0, 1.0, 4, 1);
	}
	glPopMatrix();

	// draw dish
	glPushMatrix();
	glTranslatef(0, 2.038, -0.127);
	glRotatef(-118.9, 1, 0, 0);
	glRotatef(-90, 0, 1, 0);
	glScalef(1.019, 1.019, 0.590);
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
