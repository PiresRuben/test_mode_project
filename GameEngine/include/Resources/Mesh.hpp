#pragma once

#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Core/Maths/mat4x4.hpp"
#include "Render/APIsVariant.hpp"

#include "Resources/Resource.hpp"

class Mesh : public Resource {

public:
    static Assimp::Importer importer;

    Mesh();
    ~Mesh();


    bool Load(const std::string& filePath) override;
    void Cleanup() override;

    //PoolVector<struct Vertex> vertices;
    struct Vertex* vertices = nullptr;
    unsigned int verticesCount = 0;

    //PoolVector<unsigned int> indices;
    unsigned int* indices = nullptr;
    unsigned int indicesCount = 0;

    class ModelClass* modelClass = nullptr;
    class ColorShaderClass* shaderClass = nullptr;

    void Render(DeviceContextVariant deviceContext, const glm::mat4x4& transformMatrix);
private:
    // returns wether successful
    bool PrepareVertices(const int verticesCount_);
    // returns wether successful
    bool PrepareIndices(const int indicesCount_);

    void Initialize();

    class RenderModule* renderModule = nullptr;
};