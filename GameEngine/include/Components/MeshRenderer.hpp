#pragma once

#include "Components/Renderable.hpp"

class MeshRenderer : public Renderable {

public:
	MeshRenderer();
	void Render() const override;
	void OnDestroy();

	void LoadMesh(const std::string& fileName);
	class Mesh* GetMesh() const;
	Mesh* mesh;
private:

};