#pragma once
#ifdef _WINDOWS

#include <d3d11.h>

#include "Render/ModelClass.hpp"


class Dx11ModelClass : public ModelClass {
public:
	Dx11ModelClass() = default;
	Dx11ModelClass(const Dx11ModelClass&) = default;
	~Dx11ModelClass() = default;

	bool Initialize(DeviceVariant device) override;
	void Render(DeviceContextVariant deviceContext) override;
	void Shutdown() override;

	int GetIndexCount() const override;

private:
	ID3D11Buffer* vertexBuffer = nullptr;
	ID3D11Buffer* indexBuffer = nullptr;

	int vertexCount = 0;
	int indexCount = 0;

	bool InitializeBuffers(ID3D11Device* device);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext* deviceContext);
};

#endif