#pragma once
#include "StateGameObject.h"
#include <StateTransition.h>
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
#include <State.h>
#include <StateMachine.h>

using namespace NCL;
using namespace CSC8503;
using namespace Maths;
using namespace Rendering;

class Door : public StateGameObject {
public:
	Door(const Vector3& position, MeshGeometry* mesh, TextureBase* texture, ShaderBase* shader, Animal* player) : StateGameObject() {
		name = "Wall";
		Vector3 cubeDims = Vector3(0.1, 2, 1);
		float inverseMass = 0.0f;

		OBBVolume* volume = new OBBVolume(cubeDims * 10);

		boundingVolume = (CollisionVolume*)volume;

		transform
			.SetScale(cubeDims * 20)
			.SetPosition(position);

		renderObject = new RenderObject(&transform, mesh, texture, shader);
		//renderObject->SetColour(Vector4(55, 94, 39, 255) / 255);
		physicsObject = new PhysicsObject(&transform, boundingVolume);

		physicsObject->SetInverseMass(inverseMass);
		physicsObject->InitSphereInertia();
		layer = Layer::StaticObjects;
		this->player = player;

		State* openState = new State([&](float dt)-> void {
			transform.SetOrientation(Quaternion::AxisAngleToQuaterion(Vector3(0, 0, 1), 90));
			isDoorOpen = true;
		});

		State* closedState = new State([&](float dt)-> void {
			
		});

		stateMachine->AddState(closedState);
		stateMachine->AddState(openState);

		stateMachine->AddTransition(new StateTransition(closedState, openState, [&]()-> bool {
			return HasPlayerCollectedAllCoins();
		}));
	}
	~Door() {}

	bool HasPlayerCollectedAllCoins() {
		return player->GetPoints() == 10;
	}

	bool IsDoorOpen() {
		return isDoorOpen;
	}
protected:
	Animal* player;
	bool isDoorOpen = false;
};