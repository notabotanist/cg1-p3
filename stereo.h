// 
// File: stereo.h 
// 
// stereo.h TODO_DOCS_
// 
// Version: 
// $Id$ 
// 
// Revisions: 
// $Log$ 
// 
// //////////////////////////////////////////////////////////////////// 

#ifndef STEREO_H_
#define STEREO_H_

#include "camera.h"

/// @author matthew:
/// Uses 2 viewports to render a scene with stereoscopic output
class StereoViewport {
private:
	/// class fields
	/// dimensions of total viewport
	int width;
	int height;
	/// location of lower-left of viewport
	int x;
	int y;
	/// offset of right eye from center of 'camera'
	float eyeoff;
	/// gluPerspective settings
	float fov;
	float pnear;
	float pfar;

public:
	InputCamera cam;

protected:
	/// Override to specify contents of scene.
	/// By default, draws a cube
	virtual void drawScene();

public:
	/// parameterless constructor
	StereoViewport();
	// default destructor is not ok for anything that gets overridden
	virtual ~StereoViewport() {}

	/// Called to perform stereoscopic rendering.  The nature of c++
	/// pointers may require that implementors create a static function
	/// that just calls this and give that to glutDisplayFunc.
	void display();

	/// Initializes projection matrix
	/// Not needed to run every display cycle
	void initProjection(float viewangle, float nearplane, float farplane);

	/// Call to update viewport dimensions.
	/// Automatically rectifies the projection matrix
	void setDimensions(int w, int h);
};

#endif // STEREO_H_

