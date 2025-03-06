
#include "Render/Renderer.hpp"
#include "Components/MeshRenderer.hpp"
#include "Components/Transform.hpp"

#include "Resources/Mesh.hpp"


MeshRenderer::MeshRenderer() {

	mesh = new Mesh();
}

void MeshRenderer::Render() const {

	mesh->Render(renderer->GetDeviceContext(), Transform()->GetMatrix());
}

void MeshRenderer::OnDestroy() {
	delete mesh;
	mesh = nullptr;
}

void MeshRenderer::LoadMesh(const std::string& fileName) {
	mesh->Load(fileName);
}

Mesh* MeshRenderer::GetMesh() const {
	return mesh;
}
