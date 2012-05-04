//
// File: scene.cpp
//
// ///////////////////////////////////////////////////////////////////// 

#include "scene.h"
#include <GL/glut.h>

Geometry::Geometry() : solid(false) {
}

Scene::Scene() : children() {
}

void Scene::render() {
	// store current matrix
	glPushMatrix();

	for (vector<Geometry&>::iterator iter(children.begin());
			iter != children.end(); iter++) {
		glPopMatrix();
		glPushMatrix();
		iter->render();
	}

	glPopMatrix();
}
