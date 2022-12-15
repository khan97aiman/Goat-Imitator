#pragma once
#include <GameObject.h>
#include <AABBVolume.h>
#include <Vector3.h>
#include <Vector4.h>
#include <ShaderBase.h>
#include <MeshGeometry.h>
#include <RenderObject.h>
#include <MeshMaterial.h>
#include <PhysicsObject.h>
#include <MeshAnimation.h>
#include <NavigationGrid.h>

using namespace NCL;
using namespace CSC8503;
using namespace Maths;
using namespace Rendering;

class Wall : public GameObject {
public:
	Wall(const Vector3& position, MeshGeometry* mesh, TextureBase* texture, ShaderBase* shader) : GameObject() {
		name = "Wall";
		Vector3 cubeDims = Vector3(1, 1, 1);
		float inverseMass = 0.0f;

		AABBVolume* volume = new AABBVolume(cubeDims * 10);

		boundingVolume = (CollisionVolume*)volume;

		transform
			.SetScale(cubeDims * 20)
			.SetPosition(position);

		renderObject = new RenderObject(&transform, mesh, texture, shader);
		renderObject->SetColour(Vector4(55, 94, 39, 255) / 255);
		physicsObject = new PhysicsObject(&transform, boundingVolume);

		physicsObject->SetInverseMass(inverseMass);
		physicsObject->InitSphereInertia();
		layer = Layer::StaticObjects;
	}
	~Wall() {}
protected:
};