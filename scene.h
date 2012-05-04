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
private:
	/// if true, the Geometry should render solid instead of wireframe
	bool solid;

protected:
	Geometry();	// protected to make class abstract

public:
	virtual ~Geometry() {}

	/// render as implementor sees fit
	virtual void render() = 0;
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
};

#endif
