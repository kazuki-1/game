#include "SCENEMANAGER.h"
#include "SCENEGAME.h"



HRESULT SCENEMANAGER::Initialize()
{
    Insert("GAME", std::make_shared<SCENEGAME>());
    //Insert("DEMO", std::make_shared<SCENE_DEMO>());
    ChangeScene("GAME");
    return S_OK;
}
void SCENEMANAGER::Execute()
{
    if (!cur_Scene)
        return;
    cur_Scene->Execute();
}
void SCENEMANAGER::Render()
{
    if (!cur_Scene)
        return;
    cur_Scene->Render();
}
void SCENEMANAGER::Finalize()
{
    if (!cur_Scene)
        return;
    cur_Scene->Finalize();
    cur_Scene = nullptr;
}
void SCENEMANAGER::ChangeScene(std::string name)
{
    if (cur_Scene)
        Finalize();
    cur_Scene = scenes.find(name)->second;
    cur_Scene->Initialize();
}
void SCENEMANAGER::Insert(std::string name, std::shared_ptr<SCENE>s)
{
    scenes.emplace(name, s);
}
std::shared_ptr<SCENE>SCENEMANAGER::Retrieve(std::string name)
{
    return scenes.find(name)->second;
}