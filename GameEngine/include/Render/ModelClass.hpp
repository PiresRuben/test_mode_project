#pragma once

#include "Render/APIsVariant.hpp"


class ModelClass {
public:
	ModelClass() = default;
	ModelClass(const ModelClass&) = default;
	~ModelClass() = default;

	virtual bool Initialize(DeviceVariant device) = 0;
	virtual void Render(DeviceContextVariant deviceContext) = 0;
	virtual void Shutdown() = 0;

	virtual int GetIndexCount() const = 0;
};