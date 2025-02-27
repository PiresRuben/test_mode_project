#pragma once

#include "Core/Maths/mat4x4.hpp"
#include "Render/APIsVariant.hpp"


class ColorShaderClass {
public :
	ColorShaderClass() = default;
	ColorShaderClass(const ColorShaderClass&) = default;
	~ColorShaderClass() = default;

	//Init & ShutDown
	virtual bool Initialize(DeviceVariant device, class Window* window) = 0;
	virtual void Shutdown() = 0;

	virtual bool Render(DeviceContextVariant deviceContext, int indexCount, glm::mat4x4 worldMatrix, glm::mat4x4 viewMatrix, glm::mat4x4 projectionMatrix) = 0;

protected:

	struct MatrixBufferType {
		glm::mat4x4 world;
		glm::mat4x4 view;
		glm::mat4x4 projection;
	};

};