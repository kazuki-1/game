#include "Graphics.h"
#include "DirectX11.h"
#include "Sprite.h"
#include "Model.h"
#include "Input.h"
#include "Camera.h"
#include "BlendMode.h"
#include "MODEL.h"
#include "../PLAYER.h"
#include "../SCENEMANAGER.h"
#include "../SCENEGAME.h"
#include "../Components/Base Classes/COMPONENT_CREATOR.h"
#include "Audio.h"
#include "IMGUI.h"

using namespace DirectX;


std::shared_ptr<MODEL>Stage;

HRESULT Graphics::Initialize(int Width, int Height, HWND hwnd)
{
#pragma region SETTING INITIALIZATION
    DirectX11* DX = DirectX11::Instance();
    if (FAILED(DirectX11::Instance()->Initialize(Width, Height, true, hwnd, false, 100.0f, 0.01f)))
        assert(!"Failed to Initilize DirectX11 Class");

    D3D11_BUFFER_DESC cbd{};
    cbd.ByteWidth = sizeof(SCENE_CONSTANT_DATA);
    cbd.Usage = D3D11_USAGE_DEFAULT;
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    HRESULT hr = DX->Device()->CreateBuffer(&cbd, nullptr, dxSceneConstantBuffer.ReleaseAndGetAddressOf());
    if (FAILED(hr))
        assert(!"Failed to create constant buffer");
    // stage.reset(new Model(DX->Device(), "./resources/ExampleStage.fbx"));
#pragma endregion

    SHADERMANAGER::Instance()->Initialize();
    AUDIOENGINE::Instance()->Initialize();

    BLENDMODE::Instance()->Create(BLENDMODE::BLEND_MODE::ALPHA, DirectX11::Instance()->Device());
    COMPONENT_CREATOR::Instance()->Initialize();
    SCENEMANAGER::Instance()->Initialize();
    Camera::Instance()->Initialize({ 0, 0, 1 }, {});
    Camera::Instance()->SetRange(10);
    return S_OK;
}


bool Graphics::Frame()
{

    SCENEMANAGER::Instance()->Execute();
    INPUTMANAGER::Instance()->Execute();



#pragma region CALLS RENDER (DO NOT PUT FUNCTIONS BELOW HERE)
    if (Render())
        return false;
    return true;
#pragma endregion
}

bool Graphics::Render()
{

#pragma region BASE SETTINGS
    ID3D11DeviceContext* dc{ DirectX11::Instance()->DeviceContext() };
    DirectX11::Instance()->Begin({ 0.0f, 0.3f, 0.3f, 1.0f });

#pragma endregion
#pragma region SCENE_CONSTANTS

    // Scene Constant buffer update (Camera Settings and Light Directions)
    SCENE_CONSTANT_DATA data;
    XMMATRIX v{ Camera::Instance()->ViewMatrix() }, pr{ DirectX11::Instance()->ProjectionMatrix() };
    DirectX::XMStoreFloat4x4(&data.view_proj, v * pr);


    // Camera Position
    data.camera_position.x = Camera::Instance()->Eye().x;
    data.camera_position.y = Camera::Instance()->Eye().y;
    data.camera_position.z = Camera::Instance()->Eye().z;
    data.camera_position.w = 1;
    data.ambientLightColour = {0.2f, 0.2f, 0.2f ,1 };
    int pLightCount{}, sLightCount{};;
    for (auto& d : LIGHTINGMANAGER::Instance()->Dataset())
    {
        switch (d.second->Type())
        {
        case LIGHTING::L_TYPE::DIRECTIONAL:
            d.second->WriteBuffer<DLIGHT_DATA>(&data.directional);
            break;
        case LIGHTING::L_TYPE::POINT:
            d.second->WriteBuffer<PLIGHT_DATA>(&data.pointlights[pLightCount]);
            ++pLightCount;
            break;
        case LIGHTING::L_TYPE::SPOT:
            d.second->WriteBuffer<SLIGHT_DATA>(&data.spotlights[sLightCount]);
            ++sLightCount;
            break;
        }
    }
    data.pLightCount = pLightCount;
    data.sLightCount = sLightCount;
    dc->UpdateSubresource(dxSceneConstantBuffer.Get(), 0, 0, &data, 0, 0);
    dc->VSSetConstantBuffers(0, 1, dxSceneConstantBuffer.GetAddressOf());
    dc->PSSetConstantBuffers(0, 1, dxSceneConstantBuffer.GetAddressOf());
#pragma endregion

#pragma region PUT RENDER FUNCTIONS HERE 
    


    SCENEMANAGER::Instance()->Render();



#pragma endregion


    DirectX11::Instance()->End();
    return true;
}

void Graphics::Finalize()
{
    SCENEMANAGER::Instance()->Finalize();
}