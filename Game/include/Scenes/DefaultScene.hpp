#pragma once

#include <iostream>
#include "Core/Maths/vec2.hpp"
#include "Core/Maths/vec3.hpp"
#include "Core/Maths/gtc/quaternion.hpp"

#include "Engine.hpp"
#include "Modules/Window.hpp"
#include "Scene.hpp"
#include "Component.hpp"
#include "GameObject.hpp"
#include "Modules/Time.hpp"
#include "Components/MeshRenderer.hpp"
#include "Components/Transform.hpp"
#include "Components/Camera.hpp"
#include "Modules/InputManager.hpp"
#include "Utilities/ImGUI.hpp"


//class CameraMover : public Component {
//
//
//
//public:
//	void Update() override {
//		UpdatePosition();
//		UpdateRotation();
//	}
//
//	void inline UpdatePosition() { // actually separate axis at some point -> x & z in semi local (exclude pitch) and up down as world
//		float speed = InputManager::GetKey(GLFW_KEY_J) ? 10.f : 1.f;
//		speed *= Time::deltaTime;
//
//		Transform()->position +=
//			(
//				glm::vec3(
//					.0f,
//					InputManager::GetKey(GLFW_KEY_SPACE) - InputManager::GetKey(GLFW_KEY_LEFT_SHIFT),
//					.0f
//				)
//
//				+
//
//				Transform::WorldToLocal(
//					glm::vec3(
//						InputManager::GetKey(GLFW_KEY_D) - InputManager::GetKey(GLFW_KEY_A),
//						0,
//						InputManager::GetKey(GLFW_KEY_W) - InputManager::GetKey(GLFW_KEY_S)
//					),
//					glm::angleAxis(glm::eulerAngles(Transform()->rotation).y, glm::vec3(0, 1, 0))
//				)
//			
//			) * speed;
//			
//
//		CameraClass::instance->SetPosition(
//			Transform()->position.x,
//			Transform()->position.y,
//			Transform()->position.z
//		);
//	}
//
//	void inline UpdateRotation() {
//        
//		if (InputManager::GetKeyDown(GLFW_KEY_LEFT_CONTROL)) {
//			Transform()->rotation = glm::quat(1.f, .0f, .0f, .0f);
//		}
//
//		glm::vec mouseDelta = InputManager::GetMouseDelta();
//
//		//glm::quat currentRotation = Transform()->rotation;
//
//		//glm::quat yawRotation = glm::angleAxis(glm::radians(mouseDelta.x * sensitivity), glm::vec3(0, 1, 0));
//
//		//// Apply pitch (vertical rotation)
//		//glm::quat pitchRotation = glm::angleAxis(glm::radians(mouseDelta.y * sensitivity), glm::vec3(1, 0, 0));
//
//		//// Combine rotations
//		//glm::quat newRotation = yawRotation * currentRotation * pitchRotation;
//
//		//// Normalize the quaternion to prevent floating point errors
//		//Transform()->rotation = glm::normalize(newRotation);
//
//		//
//		//glm::quat rotationX = glm::angleAxis(mouseDelta.y * sensitivity, glm::vec3(1, 0, 0));
//		//glm::quat rotationY = glm::angleAxis(mouseDelta.x * sensitivity, glm::vec3(0, 1, 0));
//
//		//glm::vec3 eulerAngle = glm::eulerAngles(Transform()->rotation * rotationY * rotationX); // as rad
//		//glm::quat rotation = rotationX * Transform()->rotation;
//		
//		//glm::vec3 eulerAngle = glm::eulerAngles(glm::normalize( rotationY)); // as rad
//		//eulerAngle.z = 0.f; // kills roll (Z-axis rotation)
//
//		//float halfPi = glm::pi<float>() / 2.f;
//		//eulerAngle.x = glm::clamp(eulerAngle.x, -halfPi, halfPi); // prevents flipping when looking up/down
//
//		//Transform()->rotation = glm::quat(eulerAngle); 
//
//
//		rotationX += mouseDelta.y * sensitivity;
//		rotationY += mouseDelta.x * sensitivity;
//		Transform()->rotation = glm::quat(glm::vec3(rotationX, rotationY, .0f));
//
//		glm::quat qX = glm::angleAxis(glm::radians(rotationX), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotation around X-axis
//		glm::quat qY = glm::angleAxis(glm::radians(rotationY), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotation around Y-axis
//
//		glm::vec3 eulerAngle = glm::eulerAngles(Transform()->rotation);
//		CameraClass::instance->SetRotation(
//			glm::degrees(eulerAngle.x),
//			glm::degrees(eulerAngle.y),
//			.0f
//		);
//    }
//
//private:
//	float sensitivity = .00625f;
//	float rotationX = 0.f;
//	float rotationY = 0.f;
//
//};

class DefaultScene : public Scene {

public:
	DefaultScene(bool startActive) : Scene(startActive) { }

	void Init() override {

		GameObject* camera = AddGameObjectUntracked(true);
		camera->AddComponent<Camera>()->MakeMainCamera();
		camera->transform->position = glm::vec3(.0f, .0f, -5.f);

		GameObject* katana = AddGameObjectUntracked(true);
		katana->AddComponent<MeshRenderer>()->LoadMesh("Assets/katana_V2.obj");
		katana->transform->position += glm::vec3(.0f, 1.5f, 3.0f); // I have the highground
		katana->transform->scale += glm::vec3(.0f, 5.0f, 5.0f); // big boi  
		// katana s default orientation is pointed along the X axis by default so yes the axises don t really make sense
		katana->transform->rotation = glm::quat(0.7071f, 0.0f, 0.0f, 0.7071f); // erect


		GameObject* creature = AddGameObjectUntracked(true);
		creature->AddComponent<MeshRenderer>()->LoadMesh("Assets/Test_Alien-Animal-Blender_2.81.fbx");
		creature->transform->position = glm::vec3(.0f, .0f, .0f);
		creature->transform->rotation = glm::quat(0.7071f, -0.7071f, 0.0f, 0.0f);
		creature->transform->scale = glm::vec3(.1f, .1f, .1f); // smol

	}

private:

};