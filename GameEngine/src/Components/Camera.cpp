#include "Components/Camera.hpp"

#include "Core/Maths/trigonometric.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "Core/Maths/gtx/euler_angles.hpp"
#include "Modules/RenderModule.hpp"
#include "Components/Transform.hpp"
#include "Engine.hpp"
#include "Modules/RenderModule.hpp"
#include "Modules/InputManager.hpp"
#include "Modules/Time.hpp"


void Camera::Awake() {
	RenderModule::SubscribeCamera(this);
}

void Camera::MakeMainCamera() {
	RenderModule::MakeMainCamera(this);
}

void Camera::OnDestroy() {
	RenderModule::UnSubscribeCamera(this);
}

void Camera::Update() {
	Move();

	if (InputManager::IsCursorEnabled() && !InputManager::GetMouseButton(GLFW_MOUSE_BUTTON_2)) { return; }

	glm::vec2 mouseDelta = InputManager::GetMouseDelta();
	Yaw += mouseDelta.x * MouseSensitivity * Time::deltaTime;
	Pitch -= mouseDelta.y * MouseSensitivity * Time::deltaTime;

	// calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	// also re-calculate the Right and Up vector
	Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up = glm::normalize(glm::cross(Right, Front));
}

glm::mat4x4 Camera::GetViewMatrix() const {
	return glm::lookAt(Transform()->position, Front + Transform()->position, Up);
}

void Camera::Move() {
	int value;

	if ((value = InputManager::GetKey(GLFW_KEY_W) - InputManager::GetKey(GLFW_KEY_S)) != 0) {
#ifdef DEBUG
		std::cout << "Moved On the target vector\n";
#endif
		Transform()->position += Front * (MovementSpeed * Time::deltaTime * value);
	}
	
	if ((value = InputManager::GetKey(GLFW_KEY_D) - InputManager::GetKey(GLFW_KEY_A)) != 0) {
#ifdef DEBUG
		std::cout << "Moved perpendicularly to the target vector\n";
#endif
		Transform()->position += Right * (MovementSpeed * Time::deltaTime * value);
	}

	if ((value = InputManager::GetKey(GLFW_KEY_SPACE) - InputManager::GetKey(GLFW_KEY_LEFT_SHIFT)) != 0) {
		Transform()->position += Up * (MovementSpeed * Time::deltaTime * value);
	}
}
