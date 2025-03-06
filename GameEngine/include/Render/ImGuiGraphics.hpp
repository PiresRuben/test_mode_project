#pragma once

#include "Render/APIsVariant.hpp"


class ImGUIGraphics {
public:
	ImGUIGraphics() = default;
	ImGUIGraphics(const ImGUIGraphics&) = default;
	~ImGUIGraphics() = default;

	virtual bool Init(DeviceVariant device, DeviceContextVariant device_context) const = 0;
	virtual void Shutdown() const = 0;

	virtual void NewFrame() const = 0;
	virtual void RenderDrawData() const = 0;

};