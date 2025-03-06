#pragma once
#ifdef _WINDOWS

#include <d3d11.h>

#include "Render/ColorShaderClass.hpp"


class Dx11ColorShaderClass : public ColorShaderClass {
public:
	Dx11ColorShaderClass() = default;
	Dx11ColorShaderClass(const Dx11ColorShaderClass&) = default;
	~Dx11ColorShaderClass() = default;

	//Init & ShutDown
	bool Initialize(DeviceVariant device, class Window* window) override;
	void Shutdown() override;

	bool Render(DeviceContextVariant deviceContext, const int indicesCount, glm::mat4x4 worldMatrix, glm::mat4x4 viewMatrix, glm::mat4x4 projectionMatrix) override;

private:
	ID3D11VertexShader* vertexShader = nullptr;
	ID3D11PixelShader* pixelShader = nullptr;
	ID3D11InputLayout* inputLayout = nullptr;
	ID3D11Buffer* matrixBuffer = nullptr;

	bool InitializeShader(ID3D11Device* device, const HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob* errorMessage, const HWND hwnd, WCHAR* shaderFilename);

	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, glm::mat4x4 worldMatrix, glm::mat4x4 viewMatrix, glm::mat4x4 projectionMatrix);
	void RenderShader(ID3D11DeviceContext* deviceContext, const int indicesCount);

};

#endif