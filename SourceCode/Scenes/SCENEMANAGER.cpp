#include "SceneManager.h"
//#include "SceneDemo.h"
#include "SceneGame1.h"



/*--------------------------------------------------SceneManager Initialize()-------------------------------------*/

HRESULT SceneManager::Initialize()
{
    Insert(ScenesEnum::Scene_Game1, std::make_shared<SceneGame1>());
    ChangeScene(ScenesEnum::Scene_Game1);
    return S_OK;
}

/*--------------------------------------------------SceneManager Execute()-------------------------------------*/

void SceneManager::Execute()
{
    if (!cur_Scene)
        return;
    cur_Scene->Execute();
}

/*--------------------------------------------------SceneManager Render()-------------------------------------*/

void SceneManager::Render()
{
    if (!cur_Scene)
        return;
    cur_Scene->Render();
}

/*--------------------------------------------------SceneManager Finalize()-------------------------------------*/

void SceneManager::Finalize()
{
    if (!cur_Scene)
        return;
    cur_Scene->Finalize();
    cur_Scene = nullptr;
}

/*--------------------------------------------------SceneManager ChangeScene()-------------------------------------*/

void SceneManager::ChangeScene(ScenesEnum name)
{
    if (cur_Scene)
        Finalize();
    cur_Scene = scenes.find(name)->second;
    cur_Scene->Initialize();
    current_Enum = name;
}

/*--------------------------------------------------SceneManager Insert()-------------------------------------*/

void SceneManager::Insert(ScenesEnum name, std::shared_ptr<Scene>s)
{
    scenes.emplace(name, s);
}

/*--------------------------------------------------SceneManager Play()-------------------------------------*/
/// <summary>
/// Transition into SceneDemo
/// </summary>
void SceneManager::Play()
{
    // Changes the scene if in UI
    //if (current_Enum == ScenesEnum::Scene_UI)
    //    ChangeScene(ScenesEnum::Scene_Demo);

    // Resumes the scene if demo scene is paused
    if (current_Enum == ScenesEnum::Scene_Game1 && ((SceneGame1*)cur_Scene.get())->GetState() == false)
    {
        ((SceneGame1*)cur_Scene.get())->Resume();
    }
}

/*--------------------------------------------------SceneManager Pause()-------------------------------------*/
/// <summary>
/// Pauses the demo scene
/// </summary>
void SceneManager::Pause()
{
    if (current_Enum == ScenesEnum::Scene_Game1 && ((SceneGame1*)cur_Scene.get())->GetState() == true)
        ((SceneGame1*)cur_Scene.get())->Pause();
}

/*--------------------------------------------------SceneManager Stop()-------------------------------------*/
/// <summary>
/// Stops the demo scene and transition back into SceneUI
/// </summary>
void SceneManager::Stop()
{
    //if (current_Enum == ScenesEnum::Scene_Game1)
    //    ChangeScene(ScenesEnum::Scene_UI);
}




/*--------------------------------------------------SceneManager Retrieve()-------------------------------------*/

std::shared_ptr<Scene>SceneManager::Retrieve(ScenesEnum name)
{
    return scenes.find(name)->second;
}

/*--------------------------------------------------SceneManager CurrentSceneEnum()-------------------------------------*/
/// <summary>
/// Returns the enum of this current scene
/// </summary>
/// <returns></returns>
ScenesEnum SceneManager::CurrentSceneEnum()
{
    return current_Enum;
}

