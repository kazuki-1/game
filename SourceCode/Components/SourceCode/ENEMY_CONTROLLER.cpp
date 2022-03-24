#include "../Headers/ENEMY_CONTROLLER.h"

ENEMY_CONTROLLER::ENEMY_CONTROLLER(GAMEOBJECT* g, COMPONENT_DATA* d)
{
    parent = g;
    data = static_cast<ENEMY_CONTROLLER_DATA*>(d);
}
HRESULT ENEMY_CONTROLLER::Initialize()
{
    return S_OK;
}
void ENEMY_CONTROLLER::Execute()
{

}
void ENEMY_CONTROLLER::UI()
{
    if (ImGui::TreeNode("Player Controller"))
    {
        ImGui::InputText("Name : ", data->name, 256);
        ImGui::TreePop();
    }
}
void ENEMY_CONTROLLER::Render()
{

}
