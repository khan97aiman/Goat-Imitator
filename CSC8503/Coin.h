#pragma once
#include <GameObject.h>
#include <SphereVolume.h>
#include <Vector3.h>
#include <ShaderBase.h>
#include <MeshGeometry.h>
#include <RenderObject.h>
#include <MeshMaterial.h>
#include <PhysicsObject.h>
#include <MeshAnimation.h>

using namespace NCL;
using namespace CSC8503;
using namespace Maths;
using namespace Rendering;

class Coin : public GameObject {
public:
	Coin(const Vector3& position, MeshGeometry* mesh, TextureBase* texture, ShaderBase* shader) : GameObject() {
		float meshSize = 0.25f;
		float inverseMass = 1.0f;

		SphereVolume* volume = new SphereVolume(meshSize * 5);

		boundingVolume = (CollisionVolume*)volume;

		transform
			.SetScale(Vector3(meshSize, meshSize, meshSize))
			.SetPosition(position);

		renderObject = new RenderObject(&transform, mesh, texture, shader);
		renderObject->SetColour(Vector4(1, 1, 0, 1));
		physicsObject = new PhysicsObject(&transform, boundingVolume);

		physicsObject->SetInverseMass(inverseMass);
		physicsObject->InitSphereInertia();
		layer = Layer::OtherObjects;
	}
	void Update(float dt) {
		transform.IncreaseRotation(Vector3(0, 1, 0), rotation * dt);
	}
	~Coin() {}
protected:
	float rotation = 50;
};