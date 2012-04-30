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

protected:
	/// Override to specify contents of scene.
	/// By default, draws a cube
	virtual void drawScene();

public:
	/// parameterless constructor
	StereoViewport();
	// default destructor should be ok

	/// Called to perform stereoscopic rendering.  The nature of c++
	/// pointers may require that implementors create a static function
	/// that just calls this and give that to glutDisplayFunc.
	void display();
};

#endif // STEREO_H_

