//
// File: scene.cpp
//
// ///////////////////////////////////////////////////////////////////// 

#include <GL/glut.h>
#include "scene.h"

Geometry::Geometry() {
}

Scene::Scene() : children() {
}

Scene::~Scene() {
	// Free memory of owned Geometry objects
	for (vector<Geometry*>::iterator iter(children.begin());
			iter != children.end(); iter++) {
		delete (*iter);
	}
}

void Scene::render() {
	// store current matrix
	glPushMatrix();

	for (vector<Geometry*>::iterator iter(children.begin());
			iter != children.end(); iter++) {
		glPopMatrix();
		glPushMatrix();
		(*iter)->render();
	}

	// restore matrix
	glPopMatrix();
}

void Scene::addGeometry(Geometry& geom) {
	children.push_back(&geom);
}
