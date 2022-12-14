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

class Enemy : public GameObject {
public:
	Enemy(const Vector3& position, MeshGeometry* mesh, TextureBase* texture, ShaderBase* shader) : GameObject() {
		name = "Enemy";
		float meshSize = 10.0f;
		float inverseMass = 0.5f;


		AABBVolume* volume = new AABBVolume(Vector3(0.3f, 0.9f, 0.3f) * meshSize);
		SetBoundingVolume((CollisionVolume*)volume);

		transform
			.SetScale(Vector3(meshSize, meshSize, meshSize))
			.SetPosition(position);

		renderObject = new RenderObject(&transform, mesh, texture, shader);
		physicsObject =  new PhysicsObject(&transform, boundingVolume);

		physicsObject->SetInverseMass(inverseMass);
		physicsObject->InitSphereInertia();
		layer = Layer::OtherObjects;
	}
	~Enemy() {}
protected:
};