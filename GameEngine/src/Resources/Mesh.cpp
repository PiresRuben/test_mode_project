#pragma once


#include <iostream>
#include <d3d11.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Engine.hpp"

#include "Modules/Window.hpp"
#include "Modules/RenderModule.hpp"

#include "Render/Dx11/Dx11ModelClass.hpp"
#include "Render/Dx11/Dx11ColorShaderClass.hpp"

#include "Render/Renderer.hpp"

#include "Components/Camera.hpp"

#include "Resources/Mesh.hpp"
#include "Render/Vertex.hpp"

#include "Core/Maths/vec3.hpp"

Assimp::Importer Mesh::importer;

Mesh::Mesh() { }
Mesh::~Mesh() {

    Cleanup();
}


bool Mesh::Load(const std::string& filePath) {

    const aiScene* scene = importer.ReadFile(filePath,
        aiPostProcessSteps::aiProcess_Triangulate |             // Ensures triangles only
        aiPostProcessSteps::aiProcess_JoinIdenticalVertices |   // Merges duplicate vertices
        aiPostProcessSteps::aiProcess_GenNormals |              // Generates normals if missing
        aiPostProcessSteps::aiProcess_CalcTangentSpace          // Generates tangents and bitangents
    );

    if (scene == nullptr) {

        std::cerr << "Couldn t load .obj: " << filePath << std::endl;
        return false;
    }


    const aiMesh* mesh_ = scene->mMeshes[0]; // Assuming single-mesh OBJ else just loop through the array


    if (!PrepareVertices(mesh_->mNumVertices)) { return false; }

    for (unsigned int i = 0; i < mesh_->mNumVertices; i++) {

        vertices[i] = Vertex(
            glm::vec3(
                mesh_->mVertices[i].x,
                mesh_->mVertices[i].y,
                mesh_->mVertices[i].z
            ),
            Color::Red,



            mesh_->HasTextureCoords(0) ?
            glm::vec2(mesh_->mTextureCoords[0][i].x, mesh_->mTextureCoords[0][i].y) :
            glm::vec2(.0f, .0f)


            /*.normal = mesh_->HasNormals() ?
                glm::vec3(mesh_->mNormals[i].x, mesh_->mNormals[i].y, mesh_->mNormals[i].z) :
                glm::vec3(.0f, 0.f, .0f*/
        );

    }

    std::vector<unsigned int> indices_;

    // Extract indices
    for (unsigned int i = 0; i < mesh_->mNumFaces; i++) {

        if (mesh_->mFaces[i].mNumIndices == 3) { // Ensure that the face is not malformed unlike my brain

            indices_.push_back(mesh_->mFaces[i].mIndices[0]);
            indices_.push_back(mesh_->mFaces[i].mIndices[1]);
            indices_.push_back(mesh_->mFaces[i].mIndices[2]);
        }
    }

    if (!PrepareIndices((int)indices_.size())) { return false; }

    _ = std::move(indices_.begin(), indices_.end(), indices);

    std::cout <<
        "Loaded " << verticesCount <<
        " vertices and " << indicesCount <<
        " triangles from " << filePath
        << std::endl;

    Initialize();

    return true;
}

void Mesh::Cleanup() {

    //vertices.clear();
    //indices.clear();

    if (modelClass != nullptr) {
        delete modelClass;
        modelClass = nullptr;
    }

    if (shaderClass != nullptr) {
        delete shaderClass;
        shaderClass = nullptr;
    }
}


void Mesh::Render(DeviceContextVariant deviceContext, const glm::mat4x4& transformMatrix) {
    modelClass->Render(deviceContext);
    _ = shaderClass->Render(deviceContext, indicesCount, transformMatrix, renderModule->mainCamera->GetViewMatrix(), renderModule->renderer->GetProjectionMatrix());
}


//bool Mesh::PrepareVertices(const int verticesCount_) { return (vertices = PoolVector<Vertex>(verticesCount = verticesCount_)).empty(); }
bool Mesh::PrepareVertices(const int verticesCount_) { return (vertices = new Vertex[verticesCount = verticesCount_]) != nullptr; }
//bool Mesh::PrepareIndices(const int indicesCount_) { return (indices = PoolVector<unsigned int>(indicesCount = indicesCount_)).empty(); }
bool Mesh::PrepareIndices(const int indicesCount_) { return (indices = new unsigned int[indicesCount = indicesCount_]) != nullptr; }


void Mesh::Initialize() {
    Window* window = Engine::GetModule<Window>();
    renderModule = Engine::GetModule<RenderModule>();

    modelClass = RenderModule::CreateModelClass();
    if (!modelClass->Initialize(renderModule->renderer->GetDevice(), verticesCount, vertices, indicesCount, indices)) {
        _ = MessageBox(*window, L"Could not initialize the model object.", L"Error", MB_OK);
        throw std::runtime_error("Couldn't Initialize Model Object");
    }

    shaderClass = RenderModule::CreateColorShaderClass(); // move that to be shared at some point
    if (!shaderClass->Initialize(renderModule->renderer->GetDevice(), window)) {
        _ = MessageBox(*window, L"Could not initialize the color shader object.", L"Error", MB_OK);
        throw std::runtime_error("Couldn't Initialize Color Shader Object");
    }
}