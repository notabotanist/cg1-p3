// File: hud.h
//
// ////////////////////////////////////////////////////////////////////// 

#ifndef HUD_H_
#define HUD_H_

#include "scene.h"

class Camera;

/// @author: Matthew MacEwan
/// Class responsible for rendering a heads-up display.
/// To accomplish this, it moves itself right up to the
/// camera whenever animate() is called
class Hud : public Geometry {
private:
	/// reference to camera that should be oriented to
	Camera& head;

	/// length of reticle segment
	float reticleLength;

	/// distance from center of screen to start reticle segments
	float reticleOffset;

	/// if true, render 'invalid target' warning
	bool warn;

	/// countdown to warn expiry
	int ttl;

protected:
	/// draw reticle in local coordinate system
	void doRender();

	/// draw 'invalid target' warning
	void drawWarn();

public:
	Hud(Camera& cam, float retlen = 0.1, float retoff = 0.1);

	/// Moves local coordinate system to near plane of camera
	void fixLCS();

	/// Override to keep the hud in position in front of the camera
	/// and to animate the warning
	void animate();

	/// Indicates that a warning should be displayed
	void startWarning();
};

#endif
