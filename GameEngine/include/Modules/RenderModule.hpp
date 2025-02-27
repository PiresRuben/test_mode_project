#pragma once

#include "Module.hpp"


class RenderModule : public Module {
public:
	RenderModule() = default;
	RenderModule(const RenderModule&) = default;
	~RenderModule() = default;

	void Init() override;
	void Update() override;
	void Render() override;
	void Shutdown() override;

	void InitImGUI(class Window* window);
	void CleanupImGUI();

private:
	class Renderer* renderer = nullptr;
	class CameraClass* camera = nullptr;
	class ModelClass* model = nullptr;
	class ColorShaderClass* colorShader = nullptr;

	class ImGuiGraphics* imGuiGraphics = nullptr;
};