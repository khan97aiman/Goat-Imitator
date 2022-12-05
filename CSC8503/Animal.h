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

class Animal : public GameObject {
public:
	Animal(const Vector3& position, MeshGeometry* mesh, MeshMaterial* material, MeshAnimation* animation, ShaderBase* shader) : GameObject() {
		float meshSize = 3.0f;
		float inverseMass = 0.5f;

		SphereVolume* volume = new SphereVolume(1.0f);

		boundingVolume = (CollisionVolume*)volume;

		transform
			.SetScale(Vector3(meshSize, meshSize, meshSize))
			.SetPosition(position);

		renderObject = new RenderObject(&transform, mesh, nullptr, shader);
		renderObject->SetRigged(true);
		int meshLayers = mesh->GetSubMeshCount();
		for (int i = 0; i < meshLayers; i++) {
			renderObject->AddTexture(material->GetMaterialForLayer(i)->GetEntry("Diffuse"));
		}
		physicsObject = new PhysicsObject(&transform, boundingVolume);

		physicsObject->SetInverseMass(inverseMass);
		physicsObject->InitSphereInertia();
		layer = Layer::OtherObjects;
		renderObject->animation = animation;
	}
	void Update(float dt) {
		renderObject->frameTime -= dt;
		while (renderObject->frameTime < 0.0f) {
			renderObject->currentFrame = (renderObject->currentFrame + 1) % renderObject->animation->GetFrameCount();
			renderObject->frameTime += 1.0f / renderObject->animation->GetFrameRate();
		}
	}
	~Animal() {}
protected:
};