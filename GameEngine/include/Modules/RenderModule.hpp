#pragma once

#include "Module.hpp"
#include "Resources/Mesh.hpp"


class RenderModule : public Module {
public:

	enum class RenderingAPI {
		Dx11,
		Dx12,
		Vulkan,
		OpenGL,

		Unknown
	};

	RenderModule() {
		instance = this;
	}
	~RenderModule() = default;

	static RenderingAPI SelectAPI();
	static class Renderer* CreateRenderer();
	static class ImGUIGraphics* CreateImGuiGraphics();
	static class ModelClass* CreateModelClass();
	static class ColorShaderClass* CreateColorShaderClass();


	void Init() override;
	void Update() override;
	void Render() override;
	void Shutdown() override;

	void InitImGUI(class Window* window);
	void CleanupImGUI();

	static void SubscribeCamera(class Camera* camera);
	static void UnSubscribeCamera(Camera* camera);
	static void MakeMainCamera(Camera* camera);

	class Renderer* renderer = nullptr;
	Camera* mainCamera = nullptr;
private:

	std::vector<Camera*> availableCameras;
	class ImGUIGraphics* imGUIGraphics = nullptr;
	static RenderModule* instance;
};