#pragma once

#include "Render/APIsVariant.hpp"


class ImGuiGraphics {
public:
	ImGuiGraphics() = default;
	ImGuiGraphics(const ImGuiGraphics&) = default;
	~ImGuiGraphics() = default;

	virtual bool Init(DeviceVariant device, DeviceContextVariant device_context) const = 0;
	virtual void Shutdown() const = 0;

	virtual void NewFrame() const = 0;
	virtual void RenderDrawData(struct ImDrawData* draw_data) const = 0;

};