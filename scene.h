//
// File: scene.h
//
// Classes for organizing and drawing a scene
// ///////////////////////////////////////////////////////////////////// 

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
using namespace std;

/// @author mrm4677
/// Abstract base class for objects renderable in Scenes
class Geometry {
protected:
	/// if true, the Geometry should render solid instead of wireframe
	bool solid;

public:
	/// Location of local coordinate system
	float x, y, z;
	/// Rotation of local coordinate system
	float roll, pitch, yaw;

protected:
	Geometry();	// protected to make class abstract

	/// Implement to create actual geometry with respect to local
	/// coordinate system set up by render()
	/// The current modelview matrix should be identical before and after.
	virtual void doRender() = 0;

public:
	virtual ~Geometry() {}

	/// Set up local coordinate system, in which the implementor's
	/// definition of doRender will place the geometry.
	void render();

	/// Call at invervals to perform animation based on implementor
	/// Default implementation: do nothing
	virtual void animate() {}

	/// setter
	inline void setSolid(bool s) {
		solid = s;
	}
};

/// @author mrm4677
/// Container for Geometries.
class Scene {
private:
	/// can't instantiate Geometry objects.  Keep pointers for polymorphism
	std::vector<Geometry*> children;

public:
	Scene();
	virtual ~Scene();

	/// Iterates over all child Geometries and renders them in turn
	void render();

	/// Add geometry to scene.  This object takes ownership of the geometry.
	void addGeometry(Geometry& geom);

	/// Sets solid flag for all children
	void setAllSolid(bool s);
};

#endif
