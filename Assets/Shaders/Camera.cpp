#include "Shader/CameraClass.hpp"

Camera* Camera::instance = nullptr;

void Camera::SetPosition(const float x, const float y, const float z) {
	positionX = x;
	positionY = y;
	positionZ = z;
}


void Camera::SetRotation(const float x, const float y, const float z) {
	rotationX = x;
	rotationY = y;
	rotationZ = z;
}

DirectX::XMFLOAT3 Camera::GetPosition() const {
	return DirectX::XMFLOAT3(positionX, positionY, positionZ);
}

DirectX::XMFLOAT3 Camera::GetRotation() const {
	return DirectX::XMFLOAT3(rotationX, rotationY, rotationZ);
}

void Camera::Render() { // how tf is that a render ? 
	DirectX::XMFLOAT3 up(.0f, 1.0, .0f);
	DirectX::XMVECTOR upVector = XMLoadFloat3(&up);

	DirectX::XMFLOAT3 pos(positionX, positionY, positionZ);
	DirectX::XMVECTOR positionVector = XMLoadFloat3(&pos);

	DirectX::XMFLOAT3 lookAt(.0f, .0f, 1.0f);
	DirectX::XMVECTOR lookAtVector = XMLoadFloat3(&lookAt);

	// Create the rotation matrix from the yaw, pitch, and roll values.
	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(
		rotationX * 0.0174532925f,
		rotationY * 0.0174532925f,
		rotationZ * 0.0174532925f
	);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAtVector = DirectX::XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAtVector = DirectX::XMVectorAdd(positionVector, lookAtVector);

	// Finally create the view matrix from the three updated vectors.
	viewMatrix = DirectX::XMMatrixLookAtLH(positionVector, lookAtVector, upVector);
}