#pragma once

#include <directxmath.h>

struct Vertex {

public:
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT3 normal;
    DirectX::XMFLOAT2 texCoord;
};