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
		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::W)) {
			currentRunSpeed = -runSpeed;
		}
		else if (Window::GetKeyboard()->KeyDown(KeyboardKeys::S)) {
			currentRunSpeed = runSpeed;
		}
		else {
			currentRunSpeed = 0;
		}

		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::A)) {
			currentTurnSpeed = turnSpeed;
		}
		else if (Window::GetKeyboard()->KeyDown(KeyboardKeys::D)) {
			currentTurnSpeed = -turnSpeed;
		}
		else {
			currentTurnSpeed = 0;
		}

		transform.IncreaseRotation(Vector3(0, 1, 0), currentTurnSpeed * dt);
		float distance = currentRunSpeed * dt;
		float dx = distance * sin(Maths::DegreesToRadians(transform.GetOrientation().ToEuler().y));
		float dz = distance * cos(Maths::DegreesToRadians(transform.GetOrientation().ToEuler().y));

		transform.IncreasePosition(Vector3(dx, 0 , dz));
		
		renderObject->frameTime -= dt;
		while (renderObject->frameTime < 0.0f) {
			renderObject->currentFrame = (renderObject->currentFrame + 1) % renderObject->animation->GetFrameCount();
			renderObject->frameTime += 1.0f / renderObject->animation->GetFrameRate();
		}
	}
	~Animal() {}
protected:
	float runSpeed = 10;	// unit: m/s
	float turnSpeed = 10.0f; // unit: degrees/s
	float currentRunSpeed = 0.0f; 
	float currentTurnSpeed = 0.0f;
};