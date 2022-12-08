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
		name = "Player";
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
			currentRunSpeed = runSpeed;
			//physicsObject->AddForce(transform.GetOrientation() * Vector3(0, 0, currentRunSpeed));
		}
		else if (Window::GetKeyboard()->KeyDown(KeyboardKeys::S)) {
			currentRunSpeed = -runSpeed;
			//physicsObject->AddForce(transform.GetOrientation() * Vector3(0, 0, currentRunSpeed));
		}
		else {
			currentRunSpeed = 0;
		}

		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::A)) {
			currentTurnSpeed = turnSpeed;
			//physicsObject->AddForce(transform.GetOrientation() * Vector3(currentRunSpeed, 0, 0));
		}
		else if (Window::GetKeyboard()->KeyDown(KeyboardKeys::D)) {
			currentTurnSpeed = -turnSpeed;
			//physicsObject->AddForce(transform.GetOrientation() * Vector3(currentRunSpeed, 0, 0));
		}
		else {
			currentTurnSpeed = 0;
		}

		//physicsObject->AddTorque(Vector3(0, currentTurnSpeed, 0));
		transform.IncreaseRotation(Vector3(0, 1, 0), currentTurnSpeed * dt);
		transform.IncreasePosition(currentRunSpeed * dt);

		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::SPACE)) {
			physicsObject->AddForce(Vector3(0, 20, 0));
		}
		
		renderObject->frameTime -= dt;
		while (renderObject->frameTime < 0.0f) {
			renderObject->currentFrame = (renderObject->currentFrame + 1) % renderObject->animation->GetFrameCount();
			renderObject->frameTime += 1.0f / renderObject->animation->GetFrameRate();
		}
	}
	~Animal() {}
	virtual void OnCollisionBegin(GameObject* otherObject) {
		if ((otherObject->IsActive() && otherObject->GetName() == "Coin")) {
			points++;
		}
	}

	virtual void OnCollisionEnd(GameObject* otherObject) {
		if (otherObject->GetName() == "Coin") {
			otherObject->SetActive(false);
		}
	}
protected:
	float runSpeed = 50;	// unit: m/s
	float turnSpeed = 50.0f; // unit: degrees/s
	float currentRunSpeed = 0.0f; 
	float currentTurnSpeed = 0.0f;
	int points = 0;
};