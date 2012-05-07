//
// File: scene.cpp
//
// ///////////////////////////////////////////////////////////////////// 

#include <GL/glut.h>
#include "scene.h"

Geometry::Geometry() : solid(false), x(0), y(0), z(0),
		roll(0), pitch(0), yaw(0) {
}

Geometry::Geometry(float _x, float _y, float _z) : solid(false),
		x(_x), y(_y), z(_z),
		roll(0), pitch(0), yaw(0) {
}

// set up local coords
void Geometry::render() {
	// store current matrix
	glPushMatrix();

	glTranslatef(x, y, z);
	glRotatef(roll, 0, 0, 1);
	glRotatef(pitch, 1, 0, 0);
	glRotatef(yaw, 0, 1, 0);

	// go go gadget implementor
	doRender();

	// restore matrix
	glPopMatrix();
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
		(*iter)->render();
	}

	// restore matrix
	glPopMatrix();
}

void Scene::animate() {
	for (vector<Geometry*>::iterator iter(children.begin());
			iter != children.end(); iter++) {
		(*iter)->animate();
	}
}

void Scene::addGeometry(Geometry& geom) {
	children.push_back(&geom);
}

void Scene::setAllSolid(bool s) {
	for (vector<Geometry*>::iterator iter(children.begin());
			iter != children.end(); iter++) {
		(*iter)->setSolid(s);
	}
}
