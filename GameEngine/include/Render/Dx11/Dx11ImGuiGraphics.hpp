#pragma once

#include "Render/ImGuiGraphics.hpp"


class Dx11ImGuiGraphics : public ImGuiGraphics {
public:
	Dx11ImGuiGraphics() = default;
	Dx11ImGuiGraphics(const Dx11ImGuiGraphics&) = default;
	~Dx11ImGuiGraphics() = default;

	bool Init(DeviceVariant device, DeviceContextVariant device_context) const;
	void Shutdown() const;

	void NewFrame() const;
	void RenderDrawData(struct ImDrawData* draw_data) const;
};