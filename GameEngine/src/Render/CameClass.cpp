#include "Render/CameraClass.hpp"

#include "Core/Maths/trigonometric.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "Core/Maths/gtx/euler_angles.hpp"


void CameraClass::SetPosition(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;
}

void CameraClass::SetRotation(float x, float y, float z) {
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
}

glm::vec3 CameraClass::GetPosition() const {
	return position;
}


glm::vec3 CameraClass::GetRotation() const {
	return rotation;
}

void CameraClass::Render() {
	// Convert degrees to radians
	float pitch = glm::radians(rotation.x);
	float yaw = glm::radians(rotation.y);
	float roll = glm::radians(rotation.z);

	// Create the rotation matrix from yaw, pitch, and roll
	glm::mat4 rotationMatrix = glm::yawPitchRoll(yaw, pitch, roll);

	glm::vec3 upVector{ .0f, 1.f, .0f};
	glm::vec3 lookAtVector{ .0f, .0f, 1.f};

	// Transform the lookAt and up vectors by the rotation matrix
	lookAtVector = rotationMatrix * glm::vec4(lookAtVector, 1.f);
	upVector = rotationMatrix * glm::vec4(upVector, .0f);

	// Translate the rotated camera position to the location of the viewer
	lookAtVector = position + lookAtVector;

	// Create the view matrix
	viewMatrix = glm::lookAt(position, lookAtVector, upVector);
}

glm::mat4x4 CameraClass::GetViewMatrix() const {
	return viewMatrix;
}
