#include "SceneGame1.h"
#include "../GAMEOBJECT.h"
#include "../Audio/AudioController.h"
#include "../Components\Base Classes\DataManager.h"
#include "../DialogueController.h"
#include "../Engine/IMGUI.h"
#include "../DialogueController.h"

/*--------------------------------------------------SceneDemo Insert()-------------------------------------*/

HRESULT SceneGame1::Initialize()
{
    DialogueController::Instance()->Initialize(L"./Data/Images/text_box.png", {50, 600}, {800, 200});
    DataManager::Instance()->InsertAndInitialize();
    AudioController::Instance()->Initialize();
    return S_OK;
}

/*--------------------------------------------------SceneDemo Execute()-------------------------------------*/

void SceneGame1::Execute()
{
    IMGUI::Instance()->Execute();
    AudioController::Instance()->Execute();
    if(state)
        GAMEOBJECTS->Execute();;
}

/*--------------------------------------------------SceneDemo Render()-------------------------------------*/

void SceneGame1::Render()
{
    GAMEOBJECTS->Render();  
    AudioController::Instance()->DebugUI();
    DialogueController::Instance()->Render();
    IMGUI::Instance()->Render();

}

/*--------------------------------------------------SceneDemo Finalize()-------------------------------------*/

//void SceneDemo::Finalize()
//{
//    GAMEOBJECTS->Finalize();
//}
//
/*--------------------------------------------------SceneDemo Pause()-------------------------------------*/

void SceneGame1::Pause()
{
    state = false;
}

/*--------------------------------------------------SceneDemo Resume()-------------------------------------*/

void SceneGame1::Resume()
{
    state = true;
}

/*--------------------------------------------------SceneDemo GetState()-------------------------------------*/

bool SceneGame1::GetState()
{
    return state;
}

