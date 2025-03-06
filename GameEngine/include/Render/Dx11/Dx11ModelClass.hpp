#pragma once
#ifdef _WINDOWS

#include <d3d11.h>

#include "Render/ModelClass.hpp"
#include "Common.hpp"


class Dx11ModelClass : public ModelClass {
public:
	Dx11ModelClass() = default;
	Dx11ModelClass(const Dx11ModelClass&) = default;
	~Dx11ModelClass() = default;

	bool Initialize(DeviceVariant device, const unsigned int verticesCount, struct Vertex* vertices, const unsigned int indicesCount, unsigned int* indices) override;

	void Render(DeviceContextVariant deviceContext) override;
	void Shutdown() override;

private:
	ID3D11Buffer* vertexBuffer = nullptr;
	ID3D11Buffer* indexBuffer = nullptr;

	bool InitializeBuffers(ID3D11Device* device, const unsigned int verticesSize, struct Vertex* vertices, const unsigned int indicesSize, unsigned int* indices);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext* deviceContext);
};

#endif