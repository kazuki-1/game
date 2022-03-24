#pragma once
#include <d3dcompiler.h>
#include <string>
#include <memory>
#include <map>
#include "DirectX11.h"
#include "Singleton.h"
#include <filesystem>
class SHADERS
{
    ComPtr<ID3D11PixelShader>dxPixelShader;
    ComPtr<ID3D11VertexShader>dxVertexShader;
    ComPtr<ID3D11InputLayout>dxInputLayout;
    ComPtr<ID3D11SamplerState>dxSamplerState;
public:
    // Pixel Shader Retriever
    ComPtr<ID3D11PixelShader>PSS()
    {
        return dxPixelShader;
    }
    // Vertex Shader Retriever
    ComPtr<ID3D11VertexShader>VSS()
    {
        return dxVertexShader;
    }
    // Sampler State Retriever
    ComPtr<ID3D11SamplerState>SamplerState()
    {
        return dxSamplerState;
    }
    ComPtr<ID3D11InputLayout>InputLayout()
    {
        return dxInputLayout;
    }
    SHADERS(std::wstring shader_path, ID3D11Device* dv, D3D11_INPUT_ELEMENT_DESC* ied, UINT ied_count);
    void SetShaders(ID3D11DeviceContext* dc)
    {
        dc->VSSetShader(dxVertexShader.Get(), 0, 0);
        dc->PSSetShader(dxPixelShader.Get(), 0, 0);
        dc->IASetInputLayout(dxInputLayout.Get());
        dc->PSSetSamplers(0, 1, dxSamplerState.GetAddressOf());
    }
};

class SHADERMANAGER : public SINGLETON<SHADERMANAGER>
{
    std::map<std::wstring, std::shared_ptr<SHADERS>>shaders;

public:
    HRESULT Insert(std::wstring shader_path, D3D11_INPUT_ELEMENT_DESC* ied, UINT ied_count);
    std::shared_ptr<SHADERS>Retrieve(std::wstring name);

    std::map<std::wstring, std::shared_ptr<SHADERS>>Shaders();
    void Clear();
    ~SHADERMANAGER()
    {
        Clear();
    }
    HRESULT Initialize();


};