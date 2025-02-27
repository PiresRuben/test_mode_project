#pragma once

#include "Core/Maths/vec3.hpp"
#include "Core/Maths/vec4.hpp"
#include "Core/Maths/mat4x4.hpp"
#include "Core/Maths/ext/matrix_transform.hpp"


class CameraClass
{
public:
	CameraClass() = default;
	CameraClass(const CameraClass&) = default;
	~CameraClass() = default;

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;
	glm::mat4x4 GetViewMatrix() const;

	void Render();

private:
	glm::vec3 position{};
	glm::vec3 rotation{};

	glm::mat4x4 viewMatrix = glm::identity<glm::mat4x4>();
};