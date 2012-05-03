//
// File: scene.h
//
// Classes for organizing and drawing a scene
// ///////////////////////////////////////////////////////////////////// 

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

/// @author mrm4677
/// Abstract base class for objects renderable in Scenes
class Geometry {
protected:
	Geometry();	// protected to make class abstract
public:
	virtual ~Geometry() {}

	/// render as implementor sees fit
	virtual void render() = 0;
};

/// @author mrm4677
/// Container for Geometries
class Scene {
private:
	/// can't instantiate Geometry objects. Does STL work with refs?
	std::vector<Geometry&> children;

public:
	Scene();
	virtual ~Scene() {}

	/// Iterates over all child Geometries and renders them in turn
	void render();
}

#endif
