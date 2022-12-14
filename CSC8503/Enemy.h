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
	}
	//void Update(float dt) {
	//	/*NavigationPath outPath;
	//	bool found = grid->FindPath(transform.GetPosition(), player->GetTransform().GetPosition(), outPath);
	//	Vector3 pos;
	//	while (outPath.PopWaypoint(pos)) {
	//		testNodes.push_back(pos);
	//	}
	//	for (int i = 1; i < testNodes.size(); ++i) {
	//		Vector3 a = testNodes[i - 1];
	//		Vector3 b = testNodes[i];
	//		Debug::DrawLine(a, b, Vector4(0, 1, 0, 1));
	//	}*/
	//}
	~Enemy() {}
protected:
	NavigationGrid* grid;
	GameObject* player;
};