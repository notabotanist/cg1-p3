//
// File: scene.cpp
//
// ///////////////////////////////////////////////////////////////////// 

#include <cmath>
#include <GL/glut.h>
#include "scene.h"
#include "vecmath.h"

Geometry::Geometry() : solid(false), x(0), y(0), z(0),
		roll(0), pitch(0), yaw(0),
		scale(1), bRadius(0) {
}

Geometry::Geometry(float _x, float _y, float _z) : solid(false),
		x(_x), y(_y), z(_z),
		roll(0), pitch(0), yaw(0),
		scale(1), bRadius(0) {
}

void Geometry::getBoundingSphere(float& cx, float& cy, float& cz, float& r) {
	cx = x;
	cy = y;
	cz = z;
	r = bRadius * scale;
}

// set up local coords
void Geometry::render() {
	// store current matrix
	glPushMatrix();

	glTranslatef(x, y, z);
	glRotatef(roll, 0, 0, 1);
	glRotatef(pitch, 1, 0, 0);
	glRotatef(yaw, 0, 1, 0);
	glScalef(scale, scale, scale);

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

/// adapted from p700 of Eberly's '3D Game Engine Design'
bool testRaySphere(Vector3 raydir, Point3 raysrc, Point3 spheresrc, float rad) {
	Vector3 delta(raysrc - spheresrc);
	float a0 = delta * delta - rad * rad;
	if (a0 <= 0) {
		// ray source is inside or on the sphere
		return true;
	}
	// else: ray source is outside the sphere

	float a1 = raydir * delta;
	if (a1 >= 0) {
		// ray is directed away from sphere.
		return false;
	}

	float discr = a1 * a1 - a0;
	return discr >= 0;
}

/// adapted from p699 of Eberly's '3D Game Engine Design'
bool findRaySphere(Vector3 raydir, Point3 raysrc, Point3 spheresrc, float rad,
		int& quantity, float tvalue[2]) {
	Vector3 delta(raysrc - spheresrc);
	float a0 = delta * delta - rad * rad;
	float a1 = raydir * delta;
	float discr = a1 * a1 - a0;

	quantity = 0;
	if (discr < 0) {
		// two complex-valued roots, no intersections
		quantity = 0;
	} else if (discr >= /*epsilon*/0.0001) {
		// two distinct real-valued roots, two intersections if this
		// were a line
		float root = sqrt(discr);
		// since we're intersecting with a ray, do not include
		// intersections where t < 0
		float r1 = -a1 - root;
		if (r1 >= 0) {
			tvalue[quantity] = r1;
			quantity++;
		}
		float r2 = -a1 + root;
		if (r2 >= 0) {
			tvalue[quantity] = r2;
			quantity++;
		}
	} else {
		// discr is effectively 0.
		// one repeated real-valued root, one intersection
		if (-a1 >= 0) {
			tvalue[0] = -a1;
			quantity = 1;
		}
	}
	return quantity > 0;
}

// pick
Geometry* Scene::pickRay(float cx, float cy, float cz,
			 float nx, float ny, float nz) {
	// Attributes to determine which object in the scene is picked
	Geometry* closepick;
	int minT = 1000;

	// Pack arguments
	Vector3 raydir(nx, ny, nz);
	Point3 raysrc(cx, cy, cz);

	// Iterate over children, perform ray-sphere intersection test
	// keep minimum t.
	for (vector<Geometry*>::iterator iter(children.begin());
			iter != children.end(); iter++) {
		Geometry* candidate = *iter;
		// Construct bounding sphere
		float sx, sy, sz, r;	// sphere properties
		candidate->getBoundingSphere(sx, sy, sz, r);
		Point3 spheresrc(sx, sy, sz);
		if (testRaySphere(raydir, raysrc, spheresrc, r)) {
			// An intersection! find minimum t
			int quant;
			float tval[2];
			findRaySphere(raydir, raysrc, spheresrc, r,
				      quant, tval);
			for (int i = 0; i < quant; i++) {
				if (tval[i] < minT) {
					minT = tval[i];
					closepick = candidate;
				}
			}
		}
	}

	return closepick;
}
