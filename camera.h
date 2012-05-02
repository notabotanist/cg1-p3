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

/// Camera object plus functions for handling input
class InputCamera : public Camera {
private:
	/// distance moved at each keypress
	float dp;
	/// mouse cursor will be trapped in window if true
	bool mouseCaptured;
	/// center coords of screen
	int centerX;
	int centerY;

public:
	InputCamera() : Camera(), dp(0.1), mouseCaptured(false) {}

	/// Translates camera given keyboard input based on common FPS
	/// wasd controls
	void wasdKeyboard(unsigned char key);

	/// Rotate camera based on mouse movement, if it is captured
	void mouseMove(int x, int y);

	/// Capture mouse
	void captureMouse();

	/// uncapture mouse
	void uncaptureMouse();

	void updateScreenCenter();
};

#endif
