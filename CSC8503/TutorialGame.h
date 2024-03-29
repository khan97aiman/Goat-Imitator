#pragma once
#include "GameTechRenderer.h"
#ifdef USEVULKAN
#include "GameTechVulkanRenderer.h"
#endif
#include "PhysicsSystem.h"

#include "StateGameObject.h"
#include <MeshMaterial.h>
#include <MeshAnimation.h>
#include "Animal.h"
#include <NavigationGrid.h>
#include <StateMachine.h>
#include "Door.h"

//enum class GameState {
//	SPLASH,
//	INIT,
//	RUNNING,
//	PAUSED,
//	LOST,
//	WON,
//};
namespace NCL {
	namespace CSC8503 {
		class TutorialGame		{
		public:
			TutorialGame();
			~TutorialGame();

			virtual void UpdateGame(float dt);

		protected:
			void InitialiseAssets();

			void InitCamera();
			void UpdateKeys();

			void InitWorld();

			/*
			These are some of the world/object creation functions I created when testing the functionality
			in the module. Feel free to mess around with them to see different objects being created in different
			test scenarios (constraints, collision types, and so on). 
			*/
			void InitGameExamples();

			void InitSphereGridWorld(int numRows, int numCols, float rowSpacing, float colSpacing, float radius);
			void InitMixedGridWorld(int numRows, int numCols, float rowSpacing, float colSpacing);
			void InitCubeGridWorld(int numRows, int numCols, float rowSpacing, float colSpacing, const Vector3& cubeDims);

			void InitDefaultFloor();

			bool SelectObject();
			void MoveSelectedObject();
			void DebugObjectMovement();
			void LockedObjectMovement();

			GameObject* AddFloorToWorld(const Vector3& position);
			GameObject* AddSphereToWorld(const Vector3& position, float radius, float inverseMass = 10.0f);
			GameObject* AddCubeToWorld(const Vector3& position, Vector3 dimensions, float inverseMass = 10.0f);

			GameObject* AddPlayerToWorld(const Vector3& position, NavigationGrid* grid);
			void AddEnemyToWorld(const Vector3& position, NavigationGrid* grid);
			void AddDoorToWorld(const Vector3& position);

			//void AddCoinsToWorld(const Vector3& position);
			void AddNavigationGrid();

#ifdef USEVULKAN
			GameTechVulkanRenderer*	renderer;
#else
			GameTechRenderer* renderer;
#endif
			PhysicsSystem*		physics;
			GameWorld*			world;

			bool useGravity;
			bool inSelectionMode;

			float		forceMagnitude;

			GameObject* selectionObject = nullptr;

			std::map<std::string, MeshGeometry*> meshes;
			std::map<std::string, MeshMaterial*> meshMaterials;
			std::map<std::string, MeshAnimation*> meshAnimations;
			
			std::map<std::string, TextureBase*> textures;
			std::map<std::string, ShaderBase*> shaders;
			NavigationGrid* hedgeMaze;

			//Coursework Additional functionality	
			GameObject* lockedObject	= nullptr;
			Vector3 lockedOffset		= Vector3(0, 14, 20);
			void LockCameraToObject(GameObject* o) {
				lockedObject = o;
			}

			GameObject* objClosest = nullptr;
			Animal* player = nullptr;
			Door* door = nullptr;

			//GameState gameState = GameState::SPLASH;
			float remainingTime = 30;
			vector <Vector3 > testNodes;

		public:
			StateMachine menuSystem;
			//StateGameObject* AddStateObjectToWorld(const Vector3& position);
			//StateGameObject * testStateObject;
		};
	}
}

