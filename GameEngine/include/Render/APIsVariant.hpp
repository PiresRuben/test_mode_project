#pragma once

#include <variant>


// Add more types when adding RenderingAPI
using DeviceVariant = std::variant<struct ID3D11Device*>;
using DeviceContextVariant = std::variant<struct ID3D11DeviceContext*>;