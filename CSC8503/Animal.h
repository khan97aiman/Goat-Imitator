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
	Animal(const Vector3& position, MeshGeometry* mesh, TextureBase* texture, MeshMaterial* material, MeshAnimation* animation, ShaderBase* shader) : GameObject() {
		name = "Player";
		float meshSize = 3.0f;
		float inverseMass = 0.5f;

		SphereVolume* volume = new SphereVolume(meshSize * 1.1);

		boundingVolume = (CollisionVolume*)volume;

		transform
			.SetScale(Vector3(meshSize, meshSize, meshSize))
			.SetPosition(position);

		renderObject = new RenderObject(&transform, mesh, texture, shader);
		renderObject->SetColour(Vector4(1, 1, 0, 1));
		//renderObject->SetRigged(true);
		/*int meshLayers = mesh->GetSubMeshCount();
		for (int i = 0; i < meshLayers; i++) {
			renderObject->AddTexture(material->GetMaterialForLayer(i)->GetEntry("Diffuse"));
		}*/
		physicsObject = new PhysicsObject(&transform, boundingVolume);

		physicsObject->SetInverseMass(inverseMass);
		physicsObject->InitSphereInertia();
		layer = Layer::Player;
		//renderObject->animation = animation;
		transform.IncreaseRotation(Vector3(0, 1, 0), 180);
	}
	void Update(float dt) {

		if (forceControl) {
			if (Window::GetKeyboard()->KeyDown(KeyboardKeys::W)) {
				currentRunSpeed = -runSpeed;
				physicsObject->AddForce(transform.GetOrientation() * Vector3(0, 0, currentRunSpeed));
			}
			else if (Window::GetKeyboard()->KeyDown(KeyboardKeys::S)) {
				//transform.IncreaseRotation(Vector3(0, 1, 0), 180);
				currentRunSpeed = runSpeed;
				physicsObject->AddForce(transform.GetOrientation() * Vector3(0, 0, currentRunSpeed));
			}
			else {
				currentRunSpeed = 0;
			}

			if (Window::GetKeyboard()->KeyDown(KeyboardKeys::A)) {
				currentTurnSpeed = turnSpeed;
				physicsObject->AddForce(transform.GetOrientation() * Vector3(currentRunSpeed, 0, 0));
			}
			else if (Window::GetKeyboard()->KeyDown(KeyboardKeys::D)) {
				currentTurnSpeed = -turnSpeed;
				physicsObject->AddForce(transform.GetOrientation() * Vector3(currentRunSpeed, 0, 0));
			}
			else {
				currentTurnSpeed = 0;
			}

			physicsObject->AddTorque(Vector3(0, currentTurnSpeed, 0));
			//transform.IncreaseRotation(Vector3(0, 1, 0), currentTurnSpeed * dt);
			//transform.IncreasePosition(currentRunSpeed * dt);
		}
		else {

			if (Window::GetKeyboard()->KeyDown(KeyboardKeys::W)) {
				currentRunSpeed = -runSpeed;
				//physicsObject->AddForce(transform.GetOrientation() * Vector3(0, 0, currentRunSpeed));
			}
			else if (Window::GetKeyboard()->KeyDown(KeyboardKeys::S)) {
				//transform.IncreaseRotation(Vector3(0, 1, 0), 180);
				currentRunSpeed = runSpeed;
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
		}

		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::F)) {
			forceControl = !forceControl;
			if (forceControl) {
				runSpeed = 30;	// unit: m/s
				turnSpeed = 10.0f; // unit: degrees/s
			}
			else {
				runSpeed = 50;	// unit: m/s
				turnSpeed = 100.0f; // unit: degrees/s
			}
		}


		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::SPACE)) {
			if (transform.GetPosition().y < -10) 
				physicsObject->AddForce(Vector3(0, 100, 0));
		}
		
		if (powerUpTime > 0) {
			powerUpTime -= dt;
		}

		/*renderObject->frameTime -= dt;
		while (renderObject->frameTime < 0.0f) {
			renderObject->currentFrame = (renderObject->currentFrame + 1) % renderObject->animation->GetFrameCount();
			renderObject->frameTime += 1.0f / renderObject->animation->GetFrameRate();
		}*/
	}
	~Animal() {}
	virtual void OnCollisionBegin(GameObject* otherObject) {
		if ((otherObject->IsActive() && otherObject->GetName() == "Coin")) {
			points++;
		}

		if ((otherObject->IsActive() && otherObject->GetName() == "PowerUp")) {
			powerUpTime = 5;
		}
	}

	virtual void OnCollisionEnd(GameObject* otherObject) {
		if (otherObject->GetName() == "Coin") {
			otherObject->SetActive(false);
		}
		if (otherObject->GetName() == "PowerUp") {
			otherObject->SetActive(false);
		}
	}

	bool IsInPowerUpState() {
		return powerUpTime > 0;
	}

	int GetPoints() { return points; }
protected:
	float runSpeed = 50;	// unit: m/s
	float turnSpeed = 100.0f; // unit: degrees/s
	float currentRunSpeed = 0.0f; 
	float currentTurnSpeed = 0.0f;
	int points = 0;
	float powerUpTime = 0;
	bool forceControl = false;
};