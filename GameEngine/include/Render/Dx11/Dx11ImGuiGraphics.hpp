#pragma once

#include "Render/ImGuiGraphics.hpp"


class Dx11ImGuiGraphics : public ImGUIGraphics {
public:
	Dx11ImGuiGraphics() = default;
	Dx11ImGuiGraphics(const Dx11ImGuiGraphics&) = default;
	~Dx11ImGuiGraphics() = default;

	bool Init(DeviceVariant device, DeviceContextVariant device_context) const override;
	void Shutdown() const override;

	void NewFrame() const override;
	void RenderDrawData() const override;
};