#pragma once

#include <iostream>

#include <d3d11.h>
#include <directxmath.h>

#include "Core/Renderer.hpp"
#include "Vertex.hpp"

#define DO_TRY_IMPL



class Model {
#ifndef DO_TRY_IMPL
struct VertexType {

public:
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT4 color;
};
#endif

public:
	bool Initialize(const unsigned int verticesSize, struct Vertex* vertices, const unsigned int indicesSize, unsigned int* indices);
	void Shutdown();
	void Render();

private:
	bool InitializeBuffers(const unsigned int verticesSize, Vertex* vertices, const unsigned int indicesSize, unsigned int* indices);
	void ShutdownBuffers();
	void RenderBuffers();

private:
	ID3D11Buffer* vertexBuffer = nullptr;
	ID3D11Buffer* indexBuffer = nullptr;
	int vertexCount = 0;
	int indexCount = 0;
};


