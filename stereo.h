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
protected:
	/// Override to specify contents of scene.
	/// By default, draws a cube
	virtual void drawScene();

public:
	/// Called to perform stereoscopic rendering.  The nature of c++
	/// pointers may require that implementors create a static function
	/// that just calls this and give that to glutDisplayFunc.
	void display();
};

#endif // STEREO_H_

