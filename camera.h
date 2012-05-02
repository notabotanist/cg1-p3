//
// File: camera.h
//
// ////////////////////////////////////////////////////////////////////// 

#ifndef CAMERA_H_
#define CAMERA_H_

/// @author mrm4677:
/// Encapsulates properties of a simple camera to later apply to Modelview
/// matrix.
/// The roll of this camera is constrained to 0.
struct Camera {
	/// location of camera
	float x;
	float y;
	float z;
	/// rotation of camera
	float pitch;
	float yaw;

	/// Applies view transformation represented by this camera.
	/// Be sure we are in GL_MODELVIEW mode
	void applyXform();
};

#endif
