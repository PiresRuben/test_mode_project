#ifdef _WINDOWS

#include "Render/Dx11/Dx11Renderer.hpp"

#include <d3d11.h>
#include <dxgi.h>
#include <iostream>

#include "Modules/Window.hpp"
#include "Core/Maths/trigonometric.hpp"
#include "Core/Maths/ext/matrix_clip_space.hpp"


bool Dx11Renderer::Init(Window* window, int width, int height) {
    HWND hwnd = *window;

    DXGI_SWAP_CHAIN_DESC scd{};
    scd.BufferDesc.Width = width;
    scd.BufferDesc.Height = height;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.SampleDesc.Count = 1;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.BufferCount = 1;
    scd.OutputWindow = hwnd;
    scd.Windowed = TRUE;
    scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &scd, &swapChain, &device, nullptr, &context))) {
        return false;
    }

    ID3D11Texture2D* backBuffer = nullptr;
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    device->CreateRenderTargetView(backBuffer, NULL, &renderTarget);
    backBuffer->Release();

    D3D11_RASTERIZER_DESC rsDesc = {};
    rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
    rsDesc.FillMode = D3D11_FILL_SOLID;
    rsDesc.FrontCounterClockwise = false;
    device->CreateRasterizerState(&rsDesc, &rsState);
    context->RSSetState(rsState);

    context->OMSetRenderTargets(1, &renderTarget, NULL);

    D3D11_VIEWPORT viewport{ 0 };
    viewport.Width = (FLOAT)width;
    viewport.Height = (FLOAT)height;
    viewport.MinDepth = 0.f;
    viewport.MaxDepth = 1.0f;
    context->RSSetViewports(1, &viewport);

    // ?? Initialiser la matrice de projection
    float fieldOfView = glm::radians(45.f);
    float screenAspect = (float)width / (float)height;

    projectionMatrix = glm::perspective(fieldOfView, screenAspect, 0.1f, 1000.0f);

    return true;
}

void Dx11Renderer::Clear(float r, float g, float b) {
    float color[] = { r, g, b, 1.0f };
    context->ClearRenderTargetView(renderTarget, color);
}

void Dx11Renderer::Present() {
    if (FAILED(swapChain->Present(1, 0))) {
        std::cout << "Sad T-T\n";
    }
}

void Dx11Renderer::Shutdown() {
    if (rsState) rsState->Release();
    if (swapChain) swapChain->Release();
    if (renderTarget) renderTarget->Release();
    if (context) context->Release();
    if (device) device->Release();
}

DeviceVariant Dx11Renderer::GetDevice() const {
    return device;
}

DeviceContextVariant Dx11Renderer::GetDeviceContext() const {
    return context;
}

#endif