#include "Engine/Camera.h"
#include "Engine/IMGUI.h"
#include "Engine/ResourceManager.h"
#include "Engine/LIGHTING.h"
#include "Engine/Input.h"
#include "SCENEGAME.h"
#include "Components/Base Classes/DATAMANAGER.h"
#include "GAMEOBJECT.h"
#include "Engine/Audio.h"
#include "Audio/AudioController.h"
std::shared_ptr<AUDIO>test_audio;




HRESULT SCENEGAME::Initialize()
{
    HRESULT hr{ S_OK };
    // Data loading
    DATAMANAGER::Instance()->Load("terrain_2.stg");
    AudioController::Instance()->Initialize();
    return hr;
}

void SCENEGAME::Execute()
{
    IMGUI::Instance()->Execute();
    Camera::Instance()->Execute();
    AudioController::Instance()->Execute();
    GAMEOBJECT_MANAGER::Instance()->Execute();
}

void SCENEGAME::Render()
{
    GAMEOBJECT_MANAGER::Instance()->Render();
    AudioController::Instance()->DebugUI();
    IMGUI::Instance()->Render();
}

void SCENEGAME::Finalize()
{


}