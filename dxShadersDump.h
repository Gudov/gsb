#pragma once
#include <d3d11.h>

void ShaderHook(ID3D11Device* device, const char* type, const void** bytecode, SIZE_T* bytecode_size);