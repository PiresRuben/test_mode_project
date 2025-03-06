#ifdef _WINDOWS

#include "Render/Dx11/Dx11ColorShaderClass.hpp"

#include <d3dcompiler.h>
#include <fstream>
#include <iostream>

#include "Modules/Window.hpp"


bool Dx11ColorShaderClass::Initialize(DeviceVariant device, Window* window)
{
	wchar_t vsFilename[128];
	if (wcscpy_s(vsFilename, 128, L"Assets/Shaders/ColorVS.hlsl") != 0) { return false; }

	wchar_t psFilename[128];
	if (wcscpy_s(psFilename, 128, L"Assets/Shaders/ColorPS.hlsl") != 0) { return false; }

	ID3D11Device** ptr = std::get_if<ID3D11Device*>(&device);
	if (ptr != nullptr) {
		return InitializeShader(*ptr, *window, vsFilename, psFilename);
	}

	throw std::runtime_error("Wrong API Device Variant");
}

void Dx11ColorShaderClass::Shutdown()
{
	ShutdownShader();
}

bool Dx11ColorShaderClass::Render(DeviceContextVariant deviceContext, const int indicesCount, glm::mat4x4 worldMatrix, glm::mat4x4 viewMatrix, glm::mat4x4 projectionMatrix)
{
	if (auto ptr = std::get_if<ID3D11DeviceContext*>(&deviceContext)) {
		// Set the shader parameters that it will use for rendering.
		if (!SetShaderParameters(*ptr, worldMatrix, viewMatrix, projectionMatrix)) { return false; }

		// Now render the prepared buffers with the shader.
		RenderShader(*ptr, indicesCount);
		return true;
	}

	throw std::runtime_error("Wrong API Device Context Variant");
}


bool Dx11ColorShaderClass::InitializeShader(ID3D11Device* device, const HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename)
{
	// If the current shader fail to compile it should have written something to the error message.
	// If there was  nothing in the error message then it simply could not find the shader file itself.

	// Compile the vertex shader code.
	ID3D10Blob* errorMessage = nullptr;
	ID3D10Blob* vertexShaderBuffer = nullptr;
	HRESULT result = D3DCompileFromFile(vsFilename, nullptr, nullptr, "ColorVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &vertexShaderBuffer, &errorMessage);
	if (FAILED(result)) {
		errorMessage != nullptr ? OutputShaderErrorMessage(errorMessage, hwnd, vsFilename) : (void)MessageBox(hwnd, vsFilename, L"Missing Shader File", MB_OK);

		return false;
	}

	// Compile the pixel shader code.
	ID3D10Blob* pixelShaderBuffer = nullptr;
	result = D3DCompileFromFile(psFilename, nullptr, nullptr, "ColorPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &pixelShaderBuffer, &errorMessage);
	if (FAILED(result)) {
		errorMessage != nullptr ? OutputShaderErrorMessage(errorMessage, hwnd, psFilename) : (void)MessageBox(hwnd, psFilename, L"Missing Shader File", MB_OK);

		return false;
	}

	// Create the vertex shader from the buffer.
	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), nullptr, &vertexShader);
	if (FAILED(result)) { return false; }

	// Create the pixel shader from the buffer.
	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), nullptr, &pixelShader);
	if (FAILED(result)) { return false; }

	// Create the vertex input layout description.
	// This setup needs to match the Vertex stucture in the Model and in the shader.
	D3D11_INPUT_ELEMENT_DESC polygonLayout[3] 
	{
		{
			.SemanticName = "POSITION",
			.SemanticIndex = 0,
			.Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,
			.InputSlot = 0,
			.AlignedByteOffset = 0,
			.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,
			.InstanceDataStepRate = 0,
		},

		{
			.SemanticName = "COLOR",
			.SemanticIndex = 0,
			.Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,
			.InputSlot = 0,
			.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT,
			.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,
			.InstanceDataStepRate = 0,
		},

		{
			.SemanticName = "TEXCOORD",
			.SemanticIndex = 0,
			.Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,
			.InputSlot = 0,
			.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT,
			.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,
			.InstanceDataStepRate = 0,
		}
	};

	// Get a count of the elements in the layout.
	unsigned int numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	// Create the vertex input layout.
	result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &inputLayout);
	if (FAILED(result)) { return false; }

	// Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
	vertexShaderBuffer->Release();
	vertexShaderBuffer = nullptr;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = nullptr;

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC matrixBufferDesc {
		.ByteWidth = sizeof(MatrixBufferType),
		.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC,
		.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER,
		.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE,
		.MiscFlags = 0,
		.StructureByteStride = 0,
	};

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	result = device->CreateBuffer(&matrixBufferDesc, nullptr, &matrixBuffer);
	if (FAILED(result)) { return false; }

	return true;
}

void Dx11ColorShaderClass::ShutdownShader()
{
	// Release the matrix constant buffer.
	if (matrixBuffer != nullptr) {
		matrixBuffer->Release();
		matrixBuffer = nullptr;
	}

	// Release the layout.
	if (inputLayout != nullptr) {
		inputLayout->Release();
		inputLayout = nullptr;
	}

	// Release the pixel shader.
	if (pixelShader != nullptr) {
		pixelShader->Release();
		pixelShader = nullptr;
	}

	// Release the vertex shader.
	if (vertexShader != nullptr) {
		vertexShader->Release();
		vertexShader = nullptr;
	}
}

void Dx11ColorShaderClass::OutputShaderErrorMessage(ID3D10Blob* errorMessage, const HWND hwnd, WCHAR* shaderFilename) {
	// Get a pointer to the error message text buffer.
	char* compileErrors = (char*)(errorMessage->GetBufferPointer());

	// Open a file to write the error message to.
	std::ofstream fileOutput;
	fileOutput.open("shader-error.txt");

	// Write out the error message.
	for (int i = 0; i < errorMessage->GetBufferSize(); i++) {
		fileOutput << compileErrors[i];
	}

	// Close the file.
	fileOutput.close();

	// Release the error message.
	errorMessage->Release();
	errorMessage = nullptr;

	// Pop a message up on the screen to notify the user to check the text file for compile errors.
	MessageBox(hwnd, L"Error compiling shader.  Check shader-error.txt for message.", shaderFilename, MB_OK);
}

bool Dx11ColorShaderClass::SetShaderParameters(
	ID3D11DeviceContext* deviceContext, 
	glm::mat4x4 worldMatrix, glm::mat4x4 viewMatrix, glm::mat4x4 projectionMatrix
)
{
	worldMatrix = glm::transpose(worldMatrix);
	viewMatrix = glm::transpose(viewMatrix);
	projectionMatrix = glm::transpose(projectionMatrix);

	// Lock the constant buffer so it can be written to.
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	if (FAILED(deviceContext->Map(matrixBuffer, 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &mappedResource))) { return false; }

	// Get a pointer to the data in the constant buffer.
	MatrixBufferType* dataPtr = (MatrixBufferType*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	// Unlock the constant buffer.
	deviceContext->Unmap(matrixBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	unsigned int bufferNumber = 0;

	// Finally set the constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &matrixBuffer);

	return true;
}

void Dx11ColorShaderClass::RenderShader(ID3D11DeviceContext* deviceContext, const int indicesCount) {
	// Set the vertex input layout.
	deviceContext->IASetInputLayout(inputLayout);

	// Set the vertex and pixel shaders that will be used to render this triangle.
	deviceContext->VSSetShader(vertexShader, nullptr, 0);
	deviceContext->PSSetShader(pixelShader, nullptr, 0);

	// Render the triangle.
	deviceContext->DrawIndexed(indicesCount, 0, 0);
}

#endif