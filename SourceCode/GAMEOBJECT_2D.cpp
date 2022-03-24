#include "GAMEOBJECT_2D.h"
//#include "GAMEOBJECT.h"
#include "Components\Headers\TRANSFORM_2D.h"
#include "Components\Headers\TRANSFORM_3D.h"

GAMEOBJECT_2D::GAMEOBJECT_2D(std::shared_ptr<OBJECT_DATA>d) 
{
    data = d;
    //name_buffer = (char*)data->name.c_str();
    for (int a = 0; a < data->name.size(); ++a)
        name_buffer[a] = data->name[a];
}
HRESULT GAMEOBJECT_2D::Initialize()
{
    if (data->Dataset().size() <= 0)
        __InternalAddComponent(COMPONENT_TYPE::TRANSFORM_2D);
    else
        for (auto& d : data->Dataset())
            __InternalAddComponent(d->type, d);
    return S_OK;

}

void GAMEOBJECT_2D::Execute()
{
    for (auto& c : components)
    {
        if(dynamic_cast<TRANSFORM_2D*>(c.get()))
            continue;
        c->Execute();
            
    }
    GetComponent<TRANSFORM_2D>()->Execute();
}

void GAMEOBJECT_2D::Render()
{
    for(auto& c : components)
    {
        if (dynamic_cast<TRANSFORM_2D*>(c.get()))
            continue;
        c->Render();
    }
    GetComponent<TRANSFORM_2D>()->Execute();
}