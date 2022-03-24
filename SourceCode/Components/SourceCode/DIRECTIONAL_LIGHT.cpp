#include "../Base Classes/COMPONENT.h"
#include "../Headers/DIRECTIONAL_LIGHT.h"
#include "../../Engine/LIGHTING.h"
#include "../../GAMEOBJECT.h"

DIRECTIONAL_LIGHT_DATA::DIRECTIONAL_LIGHT_DATA()
{
    type = COMPONENT_TYPE::DIRECTIONAL_LIGHT;
}


DIRECTIONAL_LIGHT::DIRECTIONAL_LIGHT(GAMEOBJECT* t, COMPONENT_DATA* data)
{
    parent = t;
    this->data = static_cast<DIRECTIONAL_LIGHT_DATA*>(data);

}
HRESULT DIRECTIONAL_LIGHT::Initialize()
{
    
    light = std::make_shared<LIGHTING>(LIGHTING::L_TYPE::DIRECTIONAL);
    LIGHTINGMANAGER::Instance()->Insert(Parent()->Data()->Name(), light);
    return S_OK;
}
void DIRECTIONAL_LIGHT::Execute()
{

}
void DIRECTIONAL_LIGHT::Render()
{
    light->WriteToData(this);
}
void DIRECTIONAL_LIGHT::UI()
{
    if (ImGui::TreeNode("Directional Light"))
    {
        ImGui::DragFloat3("Direction", &data->direction.x, 0.05f, -1.0f, 1.0f);
        ImGui::ColorEdit4("Colour", &data->colour.x);
        ImGui::TreePop();
    }
}
VECTOR3 DIRECTIONAL_LIGHT::Direction()
{
    return data->direction;
}
VECTOR4 DIRECTIONAL_LIGHT::Colour()
{
    return data->colour;
}
