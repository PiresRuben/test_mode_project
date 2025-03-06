#pragma once

#include "Render/APIsVariant.hpp"
#include "Common.hpp"


class ModelClass {
public:
	ModelClass() = default;
	ModelClass(const ModelClass&) = default;
	~ModelClass() = default;
	virtual bool Initialize(DeviceVariant device, const unsigned int verticesCount, struct Vertex* vertices, const unsigned int indicesSCount, unsigned int* indices) = 0;
	virtual void Render(DeviceContextVariant deviceContext) = 0;
	virtual void Shutdown() = 0;
};