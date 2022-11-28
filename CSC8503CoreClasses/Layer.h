#pragma once
#include <vector>
#include <map>

enum class Layer {
	Camera,
	Spheres,
	Cubes,
	OtherObjects
};


static std::map<Layer, int> COLLISION_LAYER_MASK = {
	std::make_pair(Layer::Camera, (1 << (int)Layer::Spheres)),
	std::make_pair(Layer::Spheres, (1 << (int)Layer::Cubes) | (1 << (int)Layer::OtherObjects)),
	std::make_pair(Layer::Cubes, (1 << (int)Layer::Spheres) | (1 << (int)Layer::OtherObjects)),
	std::make_pair(Layer::OtherObjects, 1 << (int)Layer::Spheres) // ~(1 << (int)Layer::Camera)),
};