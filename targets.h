// File: targets.h
//
// ////////////////////////////////////////////////////////////////////// 

#ifndef TARGETS_H_
#define TARGETS_H_

#include "scene.h"

/// @author mrm4677
/// Base class for geometry objects which can be targeted
class Target : public Geometry {
private:
	int ttl;

public:
	enum TState { T_IDLE, T_TARGETED, T_EXPLODING, T_DEAD };
	TState state;

protected:
	void doRender();

	virtual void renderIdle() = 0;
	virtual void renderReticle() = 0;

public:
	Target();
	Target(float _x, float _y, float _z);

	virtual void animate();

	void lockOn();
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
	virtual void renderIdle();
	virtual void renderReticle();

public:
	Radar();
	Radar(float _x, float _y, float _z);

	/// Implementations over abstract
	virtual void animate();
};

#endif
