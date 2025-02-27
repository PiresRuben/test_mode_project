#ifdef _WINDOWS

#include "Render/Dx11/Dx11ModelClass.hpp"

#include <vector>

#include "Render/Vertex.hpp"
#include "Utilities/PoolAllocator.hpp"


bool Dx11ModelClass::Initialize(DeviceVariant device) {

	if (auto ptr = std::get_if<ID3D11Device*>(&device)) {
		return InitializeBuffers(*ptr);
	}

    throw std::runtime_error("Wrong API Device Variant");
}

void Dx11ModelClass::Shutdown() {
	// Shutdown the vertex and index buffers.
	ShutdownBuffers();
}

void Dx11ModelClass::Render(DeviceContextVariant deviceContext) {

    if (auto ptr = std::get_if<ID3D11DeviceContext*>(&deviceContext)) {
        // Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
        return RenderBuffers(*ptr);
    }

    throw std::runtime_error("Wrong API Device Context Variant");
}

int Dx11ModelClass::GetIndexCount() const {
	return indexCount;
}

bool Dx11ModelClass::InitializeBuffers(ID3D11Device* device) {
    HRESULT result;

	vertexCount = 3;
	indexCount = 3;

    std::vector<Vertex, PoolAllocator<Vertex>> vertices(vertexCount);
    std::vector<ULONG, PoolAllocator<ULONG>> indices(indexCount);

    // Load vertex data
    vertices[0].SetPosition(-1.0f, -1.0f, 0.0f);
    vertices[0].SetColor(1.0f, 0.0f, 0.0f, 1.0f);

    vertices[1].SetPosition(0.0f, 1.0f, 0.0f);
    vertices[1].SetColor(0.0f, 1.0f, 0.0f, 1.0f);

    vertices[2].SetPosition(1.0f, -1.0f, 0.0f);
    vertices[2].SetColor(0.0f, 0.0f, 1.0f, 1.0f);

    indices = { 0, 1, 2 };

    // Vertex Buffer
    D3D11_BUFFER_DESC vertexBufferDesc{};
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = static_cast<UINT>(sizeof(Vertex) * vertices.size());
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA vertexData{};
    vertexData.pSysMem = vertices.data();

    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);
    if (FAILED(result)) return false;

    // Index Buffer
    D3D11_BUFFER_DESC indexBufferDesc{};
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = static_cast<UINT>(sizeof(ULONG) * indices.size());
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA indexData{};
    indexData.pSysMem = indices.data();

    result = device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);
    if (FAILED(result)) return false;

    // Clear vectors (not strictly necessary, but for cleanup)
    vertices.clear();
    indices.clear();

    return true;
}

void Dx11ModelClass::ShutdownBuffers() {
	// Release the index buffer.
	if (indexBuffer)
	{
		indexBuffer->Release();
		indexBuffer = nullptr;
	}

	// Release the vertex buffer.
	if (vertexBuffer)
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
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

#endif