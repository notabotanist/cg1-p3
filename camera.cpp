//
// File: camera.cpp
// ///////////////////////////////////////////////////////////////////// 

#include "camera.h"
#include <GL/glut.h>

void Camera::applyXform() {
	glTranslatef(-x, -y, -z);
	glRotatef(pitch, 1.0, 0, 0);
	glRotatef(yaw, 0, 1.0, 0);
}

void InputCamera::wasdKeyboard(unsigned char key) {
	// TODO: these wasd update rules don't take facing into account.
	switch (key) {
		case 'w':
			z -= dp;
			break;
		case 'a':
			x -= dp;
			break;
		case 's':
			z += dp;
			break;
		case 'd':
			x += dp;
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

	float pitchoff = -1.0f * (y - centerY);
	float yawoff = -1.0f * (x - centerX);

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
	// TODO: hide pointer
}

void InputCamera::uncaptureMouse() {
	mouseCaptured = false;
}
