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
