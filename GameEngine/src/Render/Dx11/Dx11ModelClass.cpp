#ifdef _WINDOWS

#include "Render/Dx11/Dx11ModelClass.hpp"

#include <vector>

#include "Render/Vertex.hpp"


bool Dx11ModelClass::Initialize(DeviceVariant device, const unsigned int verticesCount, Vertex* vertices, const unsigned int indicesCount, unsigned int* indices) {
    ID3D11Device** ptr = std::get_if<ID3D11Device*>(&device);
    if (ptr != nullptr) {
		return InitializeBuffers(*ptr, verticesCount, vertices, indicesCount, indices);
	}

    throw std::runtime_error("Wrong API Device Variant");
}

void Dx11ModelClass::Shutdown() {
	// Shutdown the vertex and index buffers.
	ShutdownBuffers();
}

void Dx11ModelClass::Render(DeviceContextVariant deviceContext) {
    ID3D11DeviceContext** ptr = std::get_if<ID3D11DeviceContext*>(&deviceContext);
    if (ptr != nullptr) {
        // Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
        return RenderBuffers(*ptr);
    }

    throw std::runtime_error("Wrong API Device Context Variant");
}

bool Dx11ModelClass::InitializeBuffers(ID3D11Device* device, const unsigned int verticesCount, Vertex* vertices, const unsigned int indicesCount, unsigned int* indices) {

    // Vertex Buffer
    D3D11_BUFFER_DESC vertexBufferDesc{
        .ByteWidth = sizeof(Vertex) * verticesCount,
        .Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT,
        .BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER,
        .CPUAccessFlags = 0,
        .MiscFlags = 0,
        .StructureByteStride = 0,
    };

    D3D11_SUBRESOURCE_DATA vertexData{
        .pSysMem = vertices,
        .SysMemPitch = 0,
        .SysMemSlicePitch = 0,
    };

    HRESULT result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);
    if (FAILED(result)) { return false; }

    // Index Buffer
    D3D11_BUFFER_DESC indexBufferDesc{
        .ByteWidth = sizeof(unsigned int) * indicesCount,
        .Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT,
        .BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER,
        .CPUAccessFlags = 0,
        .MiscFlags = 0,
        .StructureByteStride = 0,
    };

    D3D11_SUBRESOURCE_DATA indexData{
        .pSysMem = indices,
        .SysMemPitch = 0,
        .SysMemSlicePitch = 0,
    };

    result = device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);
    return !FAILED(result);
}

void Dx11ModelClass::ShutdownBuffers() {
	// Release the index buffer.
	if (indexBuffer != nullptr)
	{
		indexBuffer->Release();
		indexBuffer = nullptr;
	}

	// Release the vertex buffer.
	if (vertexBuffer != nullptr)
	{
		vertexBuffer->Release();
		vertexBuffer = nullptr;
	}
}

void Dx11ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext) {
	// Set vertex buffer stride and offset.
	unsigned int stride = sizeof(Vertex);
	unsigned int offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

#endif