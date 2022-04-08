#include "Engine/Camera.h"
#include "Engine/IMGUI.h"
#include "Engine/ResourceManager.h"
#include "Engine/LIGHTING.h"
#include "Engine/Input.h"
#include "SCENEGAME.h"
#include "Components/Base Classes/DATAMANAGER.h"
#include "GAMEOBJECT.h"
#include "Engine/Audio.h"
#include "Audio/AUDIO_STATE_MACHINE.h"
std::shared_ptr<AUDIO>test_audio;




HRESULT SCENEGAME::Initialize()
{
    HRESULT hr{ S_OK };
    // Data loading
    DATAMANAGER::Instance()->Load("terrain_2.stg");

    //AUDIOENGINE::Instance()->Insert("Idle", L"./Data/Audio/Idle.wav");
    //AUDIOENGINE::Instance()->Insert("Tension", L"./Data/Audio/Tension.wav");
    //AUDIOENGINE::Instance()->Insert("Cooldown", L"./Data/Audio/Cooldown.wav");
    //AUDIOENGINE::Instance()->Insert("Climax", L"./Data/Audio/Climax.wav");
    AUDIO_STATE_MACHINE::Instance()->Initialize();
    return hr;
}

void SCENEGAME::Execute()
{
    IMGUI::Instance()->Execute();
    Camera::Instance()->Execute();
    AUDIO_STATE_MACHINE::Instance()->Execute();
    GAMEOBJECT_MANAGER::Instance()->Execute();
}

void SCENEGAME::Render()
{
    GAMEOBJECT_MANAGER::Instance()->Render();
    AUDIO_STATE_MACHINE::Instance()->DebugUI();
    IMGUI::Instance()->Render();
}

void SCENEGAME::Finalize()
{


}