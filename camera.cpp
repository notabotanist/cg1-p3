//
// File: camera.cpp
// ///////////////////////////////////////////////////////////////////// 

#include "camera.h"
#include <GL/glut.h>
#include <cmath>

#define PI_180 0.017453

void Camera::applyXform() {
	glRotatef(pitch, 1.0, 0, 0);
	glRotatef(yaw, 0, 1.0, 0);
	glTranslatef(-x, -y, -z);
}

void Camera::calcView(float& vx, float& vy, float& vz) {
	double pitchR(pitch * PI_180);
	double yawR(yaw * PI_180);

	vx = sin(yawR);
	vz = -cos(yawR);
	vy = -sin(pitchR);
}

void Camera::translate(float tx, float ty, float tz) {
	x += tx;
	y += ty;
	z += tz;
}

void InputCamera::wasdKeyboard(unsigned char key) {
	float vx, vy, vz;
	calcView(vx, vy, vz);
	switch (key) {
		case 'w':
			translate(dp*vx, dp*vy, dp*vz);
			break;
		case 'a':
			translate(dp*vz, 0, -dp*vx);
			break;
		case 's':
			translate(-dp*vx, -dp*vy, -dp*vz);
			break;
		case 'd':
			translate(-dp*vz, 0, dp*vx);
			break;
		case ' ':
			y += dp;
			break;
		case 'z':
			y -= dp;
			break;
	}
}

void InputCamera::mouseMove(int x, int y) {
	if (!mouseCaptured) {
		return;
	}

	float pitchoff = msense * (y - centerY);
	float yawoff = msense * (x - centerX);

	if(pitchoff != 0.0f || yawoff != 0.0f) {
		pitch += pitchoff;
		yaw += yawoff;
		glutPostRedisplay();

		glutWarpPointer(centerX, centerY);
	}
}

void InputCamera::updateScreenCenter() {
	centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
}

void InputCamera::captureMouse() {
	mouseCaptured = true;
	glutWarpPointer(centerX, centerY);
	glutSetCursor(GLUT_CURSOR_NONE);
}

void InputCamera::uncaptureMouse() {
	mouseCaptured = false;
	glutSetCursor(GLUT_CURSOR_INHERIT);
}
