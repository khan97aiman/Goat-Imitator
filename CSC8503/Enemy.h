#pragma once
#include "StateGameObject.h"
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
#include <StateTransition.h>

using namespace NCL;
using namespace CSC8503;
using namespace Maths;
using namespace Rendering;

class Enemy : public StateGameObject {
public:
	Enemy(const Vector3& position, MeshGeometry* mesh, TextureBase* texture, ShaderBase* shader, NavigationGrid* grid, GameObject* player) : StateGameObject() {
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
		this->grid = grid;
		this->player = player;

		bool found = grid->FindPath(transform.GetPosition(), player->GetTransform().GetPosition(), outPath);
		outPath.PopWaypoint(currentPos);
		outPath.PopWaypoint(nextPos);

		State* chasePlayer = new State([&](float dt)-> void {
			/*std::cout << "In chase state" << std::endl;
			std::cout << transform.GetPosition();
			std::cout << nextPos;
			std::cout << abs(Vector3(nextPos - transform.GetPosition()).Length()) << std::endl;
			std::cout << "end\n" << std::endl;*/

			this->Move(dt);
		});
		State* shootPlayer = new State([&](float dt)-> void {
			//std::cout << "In shoot state" << std::endl;
		});
		State* idleState = new State([&](float dt)-> void {
			std::cout << "In idle state" << std::endl;
			//counter += dt;
		});
		stateMachine->AddState(chasePlayer);
		//stateMachine->AddState(shootPlayer);
		stateMachine->AddState(idleState);

		stateMachine->AddTransition(new StateTransition(chasePlayer, idleState, [&]()-> bool {
			return abs(Vector3(nextPos - transform.GetPosition()).Length()) < 10;
		}));
		stateMachine->AddTransition(new StateTransition(idleState, chasePlayer, [&]()-> bool {
			Vector3 pos; 
			if (outPath.PopWaypoint(pos)) {
				currentPos = nextPos;
				nextPos = pos;
				std::cout << "transitioning from idle to chase" << std::endl;
				return true;
			}
			return false;
		}));
	}
	void Move(float dt) {
		Vector3 direction = nextPos - currentPos;
		//float turnSpeed = -10;
		//float runSpeed = -10;
		//if (direction.x > 0) {		//move left
		//}
		//else if (direction.x < 0) { //move right
		//	turnSpeed = -turnSpeed;
		//}
		//else if (direction.z > 0) { //move down
		//}
		//else if (direction.z < 0) { //move up
		//	runSpeed = -runSpeed;
		//}
		GetPhysicsObject()->AddForce(direction.Normalised() * 4);
		//transform.IncreaseRotation(Vector3(0, 1, 0), turnSpeed * dt);
		//transform.IncreasePosition(runSpeed * dt);
		counter -= dt;
	}
	~Enemy() {}
protected:
	NavigationGrid* grid;
	GameObject* player;
	vector<Vector3> testNodes;
	int index = 1;
	Vector3 currentPos;
	Vector3 nextPos;
	NavigationPath outPath;
};