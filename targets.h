// File: targets.h
//
// ////////////////////////////////////////////////////////////////////// 

#ifndef TARGETS_H_
#define TARGETS_H_

#include "scene.h"

/// @author mrm4677
/// Base class for geometry objects which can be targeted
class Target : public Geometry {
public:
	Target();
	Target(float _x, float _y, float _z);
	// TODO: methods appropriate for targetable things
};

/// @author mrm4677
/// Stationary enemy emplacements with rotating dish
class Radar : public Target {
private:
	/// current rotation of dish in degrees
	int rotation;
	/// dish rotation rate in degrees/frame
	int dR;

protected:
	/// render implementation
	virtual void doRender();

public:
	Radar();
	Radar(float _x, float _y, float _z);

	/// Implementations over abstract
	virtual void animate();
};

#endif
