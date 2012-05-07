// File: targets.cpp
//
// Author: Matthew MacEwan
//
// ////////////////////////////////////////////////////////////////////// 

#include <GL/glut.h>
#include "targets.h"

static const int TIME_TO_IMPACT = 2000; // frames
static const int EXPLOSION_TIME = 25; // frames

Target::Target() : Geometry(), ttl(0), state(T_IDLE) {}
Target::Target(float _x, float _y, float _z) : Geometry(_x, _y, _z), ttl(0), state(T_IDLE) {
}

void Target::doRender() {
	switch (state) {
	case T_TARGETED:
		// TODO: draw incoming orbital strike
		renderReticle();
	case T_IDLE:
		renderIdle();
		break;
	case T_EXPLODING:
		// TODO: draw explosion
		break;
	case T_DEAD:
	default:
		// do nothing
		break;
	}
}

void Target::lockOn() {
	if (state == T_IDLE) {
		state = T_TARGETED;
		ttl = TIME_TO_IMPACT;
	}
}

void Target::animate() {
	if (state == T_IDLE || state == T_DEAD) return;

	ttl--;
	if (ttl < 0) {
		switch (state) {
		case T_TARGETED:
			state = T_EXPLODING;
			ttl = EXPLOSION_TIME;
			break;
		case T_EXPLODING:
			state = T_DEAD;
			ttl = 0;
			break;
		}
	}
}


Radar::Radar() : rotation(0), dR(5) {
}

Radar::Radar(float _x, float _y, float _z) : Target(_x, _y, _z), rotation(0), dR(5) {
}

void Radar::renderIdle() {
	glPushMatrix();
	// Blender helped with the modeling

	// green for 'shoot me!'
	glColor3f(0, 1, 0);
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

void Radar::renderReticle() {
	float minx = -1.05;
	float miny = -0.05;
	float minz = -1.05;
	float maxx = 1.05;
	float maxy = 2.9;
	float maxz = 1.05;
	float ticklen = 0.5;

	// red for ROCK ON
	glColor3f(0.9, 0, 0);
	// draw all corner caps
	glBegin(GL_LINES);
		glVertex3f(minx, miny, minz);
		glVertex3f(minx+ticklen, miny, minz);
		glVertex3f(minx, miny, minz);
		glVertex3f(minx, miny+ticklen, minz);
		glVertex3f(minx, miny, minz);
		glVertex3f(minx, miny, minz+ticklen);

		glVertex3f(minx, miny, maxz);
		glVertex3f(minx+ticklen, miny, maxz);
		glVertex3f(minx, miny, maxz);
		glVertex3f(minx, miny+ticklen, maxz);
		glVertex3f(minx, miny, maxz);
		glVertex3f(minx, miny, maxz-ticklen);

		glVertex3f(minx, maxy, minz);
		glVertex3f(minx+ticklen, maxy, minz);
		glVertex3f(minx, maxy, minz);
		glVertex3f(minx, maxy-ticklen, minz);
		glVertex3f(minx, maxy, minz);
		glVertex3f(minx, maxy, minz+ticklen);

		glVertex3f(minx, maxy, maxz);
		glVertex3f(minx+ticklen, maxy, maxz);
		glVertex3f(minx, maxy, maxz);
		glVertex3f(minx, maxy-ticklen, maxz);
		glVertex3f(minx, maxy, maxz);
		glVertex3f(minx, maxy, maxz-ticklen);

		glVertex3f(maxx, miny, minz);
		glVertex3f(maxx-ticklen, miny, minz);
		glVertex3f(maxx, miny, minz);
		glVertex3f(maxx, miny+ticklen, minz);
		glVertex3f(maxx, miny, minz);
		glVertex3f(maxx, miny, minz+ticklen);

		glVertex3f(maxx, miny, maxz);
		glVertex3f(maxx-ticklen, miny, maxz);
		glVertex3f(maxx, miny, maxz);
		glVertex3f(maxx, miny+ticklen, maxz);
		glVertex3f(maxx, miny, maxz);
		glVertex3f(maxx, miny, maxz-ticklen);

		glVertex3f(maxx, maxy, minz);
		glVertex3f(maxx-ticklen, maxy, minz);
		glVertex3f(maxx, maxy, minz);
		glVertex3f(maxx, maxy-ticklen, minz);
		glVertex3f(maxx, maxy, minz);
		glVertex3f(maxx, maxy, minz+ticklen);

		glVertex3f(maxx, maxy, maxz);
		glVertex3f(maxx-ticklen, maxy, maxz);
		glVertex3f(maxx, maxy, maxz);
		glVertex3f(maxx, maxy-ticklen, maxz);
		glVertex3f(maxx, maxy, maxz);
		glVertex3f(maxx, maxy, maxz-ticklen);
	glEnd();
}

void Radar::animate() {
	Target::animate();

	rotation = (rotation + dR) % 360;
}
