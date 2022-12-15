#pragma once
#include <State.h>
#include <StateMachine.h>
#include <StateTransition.h>
#include <Window.h>
#include "TutorialGame.h"

using namespace NCL;
using namespace CSC8503;

class MenuSystem : public StateMachine {
public:
	MenuSystem(TutorialGame* g) : StateMachine() {
		
		State* splash = new State([&](float dt)-> void {
			Debug::Print("Collect 10 coins, then go to Don Duck for survival", Vector2(5, 30), Vector4(1, 1, 0, 1));
			Debug::Print("Going to Don without enough coins will get you killed", Vector2(0, 45), Vector4(1, 1, 0, 1));
			Debug::Print("Hide from enemies or shoot them", Vector2(25, 60), Vector4(1, 1, 0, 1));
			Debug::Print("Press Space to Continue", Vector2(30, 75), Vector4(1, 0, 0, 1));
			g->Render();
		});
		State* init = new State([&](float dt)-> void {
		});
		State* running = new State([&](float dt)-> void {
		});
		State* paused = new State([&](float dt)-> void {
		});
		State* lost = new State([&](float dt)-> void {
		});
		State* won = new State([&](float dt)-> void {
		});
		AddState(splash);
		AddState(init);
		AddState(running);
		AddState(paused);
		AddState(lost);
		AddState(won);


		AddTransition(new StateTransition(splash, init, [&]()-> bool {
			return Window::GetKeyboard()->KeyPressed(KeyboardKeys::SPACE);
		}));
		AddTransition(new StateTransition(init, running, [&]()-> bool {
			return Window::GetKeyboard()->KeyPressed(KeyboardKeys::N);
		}));
		AddTransition(new StateTransition(running, paused, [&](float time)-> bool {
			if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::P)) {

			}
			return Window::GetKeyboard()->KeyPressed(KeyboardKeys::P);
		}));
		AddTransition(new StateTransition(paused, running, [&]()-> bool {
			return Window::GetKeyboard()->KeyPressed(KeyboardKeys::P);
		}));
		AddTransition(new StateTransition(running, lost, [&]()-> bool {
			return g->remainingTime == 0;
		}));
		AddTransition(new StateTransition(running, won, [&]()-> bool {
			return false;
		}));
		AddTransition(new StateTransition(won, running, [&]()-> bool {
			return false;
		}));
		AddTransition(new StateTransition(lost, running, [&]()-> bool {
			return false;
		}));
	}
	
	
	~MenuSystem() {}
protected:
};