// File: targets.h
//
// ////////////////////////////////////////////////////////////////////// 

#ifndef TARGETS_H_
#define TARGETS_H_

#include "scene.h"

/// Base class for geometry objects which can be targeted
class Target : public Geometry {
	// TODO: methods appropriate for targetable things
};

/// Stationary enemy emplacements with rotating dish
class Radar : public Target {
private:
	/// current rotation of dish
	int rotation;

public:
	Radar();

	/// Implementations over abstract
	virtual void render();
	virtual void animate();
};

#endif
