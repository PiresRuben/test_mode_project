#include "Modules/RenderModule.hpp"

#include <iostream>

#include "Engine.hpp"
#include "Modules/Window.hpp"
#include "Render/CameraClass.hpp"
#include "Render/Dx11/Dx11ColorShaderClass.hpp"
#include "Render/Dx11/Dx11ModelClass.hpp"
#include "Render/Dx11/Dx11Renderer.hpp"
#include "Render/Dx11/Dx11ImGuiGraphics.hpp"

#include "Utilities/ImGUI.hpp"


enum class APIs {
	Dx11,
	Dx12,
	Vulkan,
	OpenGL,

	UNKNOW
};

static APIs SelectAPI() {
	static APIs selectedAPI(APIs::UNKNOW);

	if (selectedAPI != APIs::UNKNOW) return selectedAPI;

	/* Actual selection code instead */
	selectedAPI = APIs::Dx11;

	return selectedAPI;
}

static Renderer* CreateRenderer(const APIs selectedAPI) {
	switch (selectedAPI) {
	case APIs::Dx12:
	case APIs::Vulkan:
	case APIs::OpenGL:
	case APIs::Dx11:
		return new Dx11Renderer();
	default:
		throw std::runtime_error("UNKNOW Graphics API");
	}
}

static ModelClass* CreateModelClass(const APIs selectedAPI) {
	switch (selectedAPI) {
	case APIs::Dx12:
	case APIs::Vulkan:
	case APIs::OpenGL:
	case APIs::Dx11:
		return new Dx11ModelClass();
	default:
		throw std::runtime_error("UNKNOW Graphics API");
	}
}

static ColorShaderClass* CreateColorShaderClass(const APIs selectedAPI) {
	switch (selectedAPI) {
	case APIs::Dx12:
	case APIs::Vulkan:
	case APIs::OpenGL:
	case APIs::Dx11:
		return new Dx11ColorShaderClass();
	default:
		throw std::runtime_error("UNKNOW Graphics API");
	}
}

static ImGuiGraphics* CreateImGuiGraphics(const APIs selectedAPI) {
	switch (selectedAPI) {
	case APIs::Dx12:
	case APIs::Vulkan:
	case APIs::OpenGL:
	case APIs::Dx11:
		return new Dx11ImGuiGraphics();
	default:
		throw std::runtime_error("UNKNOW Graphics API");
	}
}


void RenderModule::Init() {

	Window* window = Engine::GetInstance()->GetModule<Window>();

	renderer = CreateRenderer(SelectAPI());
	if (!renderer->Init(window, window->GetSize().x, window->GetSize().y)) {
		MessageBox(*window, L"Could not initialize Direct3D", L"Error", MB_OK);
		throw std::runtime_error("Couldn't Initialize Renderer");
	}

	camera = new CameraClass();
	camera->SetPosition(0.0f, 0.0f, -5.0f);

	model = CreateModelClass(SelectAPI());
	if (!model->Initialize(renderer->GetDevice())) {
		MessageBox(*window, L"Could not initialize the model object.", L"Error", MB_OK);
		throw std::runtime_error("Couldn't Initialize Model Object");
	}

	colorShader = CreateColorShaderClass(SelectAPI());
	if (!colorShader->Initialize(renderer->GetDevice(), window)) {
		MessageBox(*window, L"Could not initialize the color shader object.", L"Error", MB_OK);
		throw std::runtime_error("Couldn't Initialize Color Shader Object");
	}

	InitImGUI(window);
}

void RenderModule::Update() { // prepare window in order to draw on it later in RenderModule::Render()

	imGuiGraphics->NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	renderer->Clear(0.2f, 0.3f, 0.8f);
}

void RenderModule::Render() {
	camera->Render();

	glm::mat4x4 worldMatrix = renderer->GetWorldMatrix();
	glm::mat4x4 viewMatrix = camera->GetViewMatrix();
	glm::mat4x4 projectionMatrix = renderer->GetProjectionMatrix();

	// Dessiner le modèle
	model->Render(renderer->GetDeviceContext());

	if (!colorShader->Render(renderer->GetDeviceContext(), model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix)) {
		throw std::runtime_error("IDK");
	}

	ImGui::Render();
	imGuiGraphics->RenderDrawData(ImGui::GetDrawData());

	renderer->Present();
}

void RenderModule::Shutdown() {

	if (colorShader != nullptr) {
		colorShader->Shutdown();
		delete colorShader;
		colorShader = nullptr;
	}

	if (model != nullptr) {
		model->Shutdown();
		delete model;
		model = nullptr;
	}

	if (camera != nullptr) {
		delete camera;
		camera = nullptr;
	}

	if (renderer != nullptr) {
		renderer->Shutdown();
		delete renderer;
		renderer = nullptr;
	}

	if (imGuiGraphics != nullptr) {
		delete imGuiGraphics;
		imGuiGraphics = nullptr;
	}
}

void RenderModule::InitImGUI(Window* window) {

	ImGui::CreateContext();

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOther(window->GetWindow(), true);

	imGuiGraphics = CreateImGuiGraphics(SelectAPI());
	if (!imGuiGraphics->Init(renderer->GetDevice(), renderer->GetDeviceContext())) {
		MessageBox(*window, L"Could not initialize ImGuiGraphics.", L"Error", MB_OK);
		throw std::runtime_error("Couldn't Initialize ImGuiGraphics");
	}
}

void RenderModule::CleanupImGUI() {

	imGuiGraphics->Shutdown();
	ImGui_ImplGlfw_Shutdown();

	ImGui::DestroyContext();
}
