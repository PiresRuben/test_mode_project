#include "Shader/ModelClass.hpp"

#include "Vertex.hpp"

bool Model::Initialize(const unsigned int verticesSize, Vertex* vertices, const unsigned int indicesSize, unsigned int* indices) {

    return InitializeBuffers(verticesSize, vertices, indicesSize, indices);
}

void Model::Shutdown() {
    ShutdownBuffers(); // Shutdown the vertex and index buffers.
}

void Model::Render() {
    RenderBuffers(); // Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
}

#if false
bool Model::InitializeBuffers() {

#ifndef DO_TRY_IMPL
    // Create the vertex array.
    vertexCount = 3;
    VertexType* vertices = new VertexType[vertexCount];
    if (vertices == nullptr) { return false; }

    // Create the index array.
    indexCount = 3;
    unsigned long* indices = new unsigned long[indexCount];
    if (indices == nullptr) {
        delete[] vertices;
        return false;
    }

    // Load the vertex array with data.
    vertices[0].position = DirectX::XMFLOAT3(-1.0f, -1.0f, 0.0f);  // Bottom left.
    vertices[0].color = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

    vertices[1].position = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);  // Top middle.
    vertices[1].color = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

    vertices[2].position = DirectX::XMFLOAT3(1.0f, -1.0f, 0.0f);  // Bottom right.
    vertices[2].color = DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

    // Load the index array with data.
    indices[0] = 0;  // Bottom left.
    indices[1] = 1;  // Top middle.
    indices[2] = 2;  // Bottom right.
#endif
    // Set up the description of the static vertex buffer.
    D3D11_BUFFER_DESC vertexBufferDesc{};
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
#ifdef DO_TRY_IMPL
    vertexBufferDesc.ByteWidth = sizeof(Vertex) * mesh.verticesCount;
#else
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * vertexCount;
#endif
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
    vertexBufferDesc.StructureByteStride = 0;

    // Give the subresource structure a pointer to the vertex data.
    D3D11_SUBRESOURCE_DATA vertexData{
#ifdef DO_TRY_IMPL
        .pSysMem = mesh.vertices,
#else
        .pSysMem = vertices,
#endif
        .SysMemPitch = 0,
        .SysMemSlicePitch = 0 ,
    };

    // Now create the vertex buffer.
    if (FAILED(device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer))) { return false; }

    // Set up the description of the static index buffer.
    D3D11_BUFFER_DESC indexBufferDesc{};
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
#ifdef DO_TRY_IMPL
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * mesh.indicesCount;
#else
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * indexCount;
#endif
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
    indexBufferDesc.StructureByteStride = 0;

    // Give the subresource structure a pointer to the index data.
    D3D11_SUBRESOURCE_DATA indexData{
        #ifdef DO_TRY_IMPL
        .pSysMem = mesh.indices,
#else
        .pSysMem = indices,
#endif
        .SysMemPitch = 0,
        .SysMemSlicePitch = 0,
    };

    // Create the index buffer.
    if (FAILED(device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer))) { return false; }

    // Release the arrays now that the vertex and index buffers have been created and loaded.
#ifndef DO_TRY_IMPL
    delete[] vertices;
    delete[] indices;
#endif

    return true;
}
#else
bool Model::InitializeBuffers(const unsigned int verticesSize, Vertex* vertices, const unsigned int indicesSize, unsigned int* indices) {

    // Set up the description of the static vertex buffer.
    D3D11_BUFFER_DESC bufferDesc{
        //.ByteWidth = sizeof(Vertex) * mesh.verticesCount,
        .ByteWidth = verticesSize,
        .Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT,
        .BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER,
        .CPUAccessFlags = 0,
        .MiscFlags = 0,
        .StructureByteStride = 0,
    };

    // Give the subresource structure a pointer to the vertex data.
    D3D11_SUBRESOURCE_DATA subresourceData{
        //.pSysMem = mesh.vertices,
        .pSysMem = vertices,
        .SysMemPitch = 0,
        .SysMemSlicePitch = 0 ,
    };

    // Now create the vertex buffer.
    if (FAILED(Renderer::device->CreateBuffer(&bufferDesc, &subresourceData, &vertexBuffer))) { return false; }

    // Set up the description of the static index buffer.
    //bufferDesc.ByteWidth = sizeof(unsigned long) * mesh.indicesCount;
    bufferDesc.ByteWidth = indicesSize;
    bufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;

    // Give the subresource structure a pointer to the index data.
    //subresourceData.pSysMem = mesh.indices;
    subresourceData.pSysMem = indices;

    // Create the index buffer.
    if (FAILED(Renderer::device->CreateBuffer(&bufferDesc, &subresourceData, &indexBuffer))) { return false; }

    return true;
}
#endif

#if false
bool Model::InitializeBuffers() {

    // generic buffer setup
    D3D11_BUFFER_DESC bufferDesc{
        .Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT,
        .CPUAccessFlags = 0,
        .MiscFlags = 0,
        .StructureByteStride = 0,
    };


    // generic subresource data
    D3D11_SUBRESOURCE_DATA subresourceData{
        .SysMemPitch = 0,
        .SysMemSlicePitch = 0,
    };


    // specify for vertex buffer
    bufferDesc.ByteWidth = sizeof(Vertex) * mesh->verticesCount;
    bufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;

    subresourceData.pSysMem = mesh->vertices;

    // create Vertex buffer
    if (FAILED(device->CreateBuffer(&bufferDesc, &subresourceData, &vertexBuffer))) { return false; }

    // specify for index buffer
    bufferDesc.ByteWidth = sizeof(unsigned long) * mesh->indicesCount;
    bufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;

    subresourceData.pSysMem = mesh->indices;

    // create Index buffer
    if (FAILED(device->CreateBuffer(&bufferDesc, &subresourceData, &indexBuffer))) { return false; }

    return true;
}
#endif

void Model::ShutdownBuffers() {

    // Release the index buffer.
    if (indexBuffer != nullptr) {

        indexBuffer->Release();
        indexBuffer = nullptr;
    }

    // Release the vertex buffer.
    if (vertexBuffer != nullptr) {

        vertexBuffer->Release();
        vertexBuffer = nullptr;
    }
}

void Model::RenderBuffers() {
    // Set vertex buffer stride and offset.
#if defined(DO_TRY_IMPL)
    unsigned int stride = sizeof(Vertex);
#else
    unsigned int stride = sizeof(VertexType);
#endif
    unsigned int offset = 0;

    // Set the vertex buffer to active in the input assembler so it can be rendered.
    Renderer::deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
    Renderer::deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
    Renderer::deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
