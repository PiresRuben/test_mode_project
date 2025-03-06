	#pragma once

#include "Core/Maths/vec3.hpp"
#include "Core/Maths/vec4.hpp"
#include "Core/Maths/mat4x4.hpp"
#include "Core/Maths/ext/matrix_transform.hpp"

#include "Component.hpp"

class Camera : public Component
{
public:
	Camera() = default;

	void Awake() override;
	void Update() override;
	void MakeMainCamera();

	void OnDestroy() override;
	glm::mat4x4 GetViewMatrix() const;

private:
	glm::vec3 Front{ .0f, .0f, 1.f };
	glm::vec3 Up{ .0f, 1.f, .0f };
	glm::vec3 Right{ 1.f, .0f, .0f };
	glm::vec3 WorldUp{ .0f, 1.f, .0f };
	// euler Angles
	float Yaw{ -270.f };
	float Pitch{ .0f };
	// camera options
	float MovementSpeed{ 2.f };
	float MouseSensitivity{ 2.f };

	void Move();
};