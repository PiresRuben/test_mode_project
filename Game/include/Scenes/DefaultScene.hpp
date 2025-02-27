#pragma once
#include <iostream>

#include "Scene.hpp"
#include "Component.hpp"
#include "GameObject.hpp"
#include "Modules/Time.hpp"


class SomeComponent : public Component {

public:
	void Awake() override {

		std::cout << "I have awoken" << std::endl;
	}

	void Update() override {

		//std::cout << "I was updated\n";

		//std::cout << Time::time << "\n";
		/*StartTimedExecution("LowkeyLengthy");
		for (int i = 0; i < 1'000'000'000; i++) {
			double var = Time::deltaTime / Time::deltaTime;
		}
		EndTimedExecution("LowkeyLengthy");*/

		//std::cout << 1 / Time::deltaTime << "\n";
	}

private:

};


class DefaultScene : public Scene {

public:
	DefaultScene(bool startActive) : Scene(startActive) { }

	void Init() override {

		AddGameObjectUntracked(true)->AddComponent<SomeComponent>();

	}

private:

};