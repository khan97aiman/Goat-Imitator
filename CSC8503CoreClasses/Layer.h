#pragma once
#include <vector>
#include <map>

enum class Layer {
	Camera,
	Spheres,
	Cubes,
	OtherObjects
};

std::map<Layer, int> collisionMatrix = {
	std::make_pair(Layer::Camera, ~(1 << (int)Layer::Camera)),
	std::make_pair(Layer::Spheres, 1 << (int)Layer::Cubes),
	std::make_pair(Layer::Cubes, 1 << (int)Layer::Spheres),
	std::make_pair(Layer::OtherObjects, ~(1 << (int)Layer::Camera)),
}