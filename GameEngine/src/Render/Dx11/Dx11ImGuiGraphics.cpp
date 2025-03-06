#include "Render/Dx11/Dx11ImGuiGraphics.hpp"

#include <d3d11.h>
#include <stdexcept>

#include "Utilities/ImGUI.hpp"


bool Dx11ImGuiGraphics::Init(DeviceVariant device, DeviceContextVariant device_context) const {
	ID3D11Device** ptrDevice = std::get_if<ID3D11Device*>(&device);
	ID3D11DeviceContext** ptrDeviceContext = std::get_if<ID3D11DeviceContext*>(&device_context);

	if (ptrDevice != nullptr && ptrDeviceContext != nullptr) {
		return ImGui_ImplDX11_Init(*ptrDevice, *ptrDeviceContext);
	}

	throw std::runtime_error("Wrong API Device or Device Context Variant");
}

void Dx11ImGuiGraphics::Shutdown() const {
	ImGui_ImplDX11_Shutdown();
}

void Dx11ImGuiGraphics::NewFrame() const {
	ImGui_ImplDX11_NewFrame();
}

void Dx11ImGuiGraphics::RenderDrawData() const {
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}