#include "GAMEOBJECT.h"
#include "GAMEOBJECT_2D.h"
#include "Engine/DROPMANAGER.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Components/Headers/MESH.h"
#include "Components/Headers/TRANSFORM_3D.h"
#include "Components/Headers/TRANSFORM_2D.h"
#include "Components/Base Classes/COMPONENT.h"
#include "Components/Base Classes/COMPONENT_CREATOR.h"
#define INSTANTIATE COMPONENT_CREATOR::Instance()->Instantiate
bool popup{};


#pragma region MAIN_FUNCTIONS


/*------------------------------------------GAMEOBJECT Constructor--------------------------------------------*/

GAMEOBJECT::GAMEOBJECT(std::shared_ptr<OBJECT_DATA>d)
{
    data = d;
    for (int a = 0; a < data->name.size(); ++a)
        name_buffer[a] = data->name[a];
}

/*------------------------------------------GAMEOBJECT Initialize()--------------------------------------------*/

/// <summary>
/// <para> virtual function. Initializes the gameObject by creating components from the data member</para>
/// <para>　仮想関数。データを使ってゲームオブジェクトのコンポネントを生成
/// </summary>
/// <returns></returns>
HRESULT GAMEOBJECT::Initialize()
{
    if (data->Dataset().size() <= 0)
        __InternalAddComponent(COMPONENT_TYPE::TRANSFORM_3D);
    else
    {
        for (auto& d : data->Dataset())
        {
            __InternalAddComponent(d->type, d);

        }
    }
    return S_OK;
}

/*------------------------------------------GAMEOBJECT Execute()--------------------------------------------*/

/// <summary>
/// <para> Virtual function. Performs the Execute() function in each component </para>
/// <para> 仮想関数。各コンポネントのExecute()関数を呼び出す
/// </summary>
void GAMEOBJECT::Execute()
{
    for (auto& c : components) {
        c->Execute();
    }

}

/*------------------------------------------GAMEOBJECT Render()--------------------------------------------*/

/// <summary>
/// <para> Virtual function. Calls the Render() function in each component </para>
/// <para> 仮想関数。各コンポネントのRender()関数を呼び出す。</para>
/// </summary>
void GAMEOBJECT::Render()
{
    for (auto& c : components)
    {
        if (dynamic_cast<TRANSFORM_3D*>(c.get()))
            continue;
        c->Render();
    }
    GetComponent<TRANSFORM_3D>()->Render();
}



#pragma endregion
#pragma region COMPONENT INSERTION

/*------------------------------------------GAMEOBJECT __InternalAddComponent()----------------------------*/

void GAMEOBJECT::__InternalAddComponent(COMPONENT_TYPE t)
{
    data->dataset.push_back(COMPONENT_CREATOR::Instance()->Instantiate(t));
    components.push_back(INSTANTIATE(this, data->dataset.back()));
    components.back()->Initialize();

}


void GAMEOBJECT::__InternalAddComponent(COMPONENT_TYPE t, std::shared_ptr<COMPONENT_DATA>d)
{
    components.push_back(INSTANTIATE(this, d));
    components.back()->Initialize();

}

/*------------------------------------------GAMEOBJECT AddComponent()--------------------------------------------*/

void GAMEOBJECT::AddComponent(COMPONENT_TYPE t)
{
    data->dataset.push_back(COMPONENT_CREATOR::Instance()->Instantiate(t));
    components.push_back(INSTANTIATE(this, data->dataset.back()));
    components.back()->Initialize();

}

/*------------------------------------------GAMEOBJECT RemoveComponent()----------------------------------------*/

/// <summary>
/// <para> Adds a component to the gameObject </para>
/// <para> ゲームオブジェクトにコンポネントを追加</para>
/// </summary>
void GAMEOBJECT::RemoveComponent(int id)
{
    components.erase(components.begin() + id);
    data->Remove(id);
}

/*------------------------------------------GAMEOBJECT RemoveComponent()--------------------------------------------*/


#pragma endregion
#pragma region GETTERS

/*------------------------------------------GAMEOBJECT Data()--------------------------------------------*/

std::shared_ptr<OBJECT_DATA>GAMEOBJECT::Data()
{
    return data;
}

/*------------------------------------------GAMEOBJECT Components()--------------------------------------------*/

std::vector<std::shared_ptr<COMPONENT>>GAMEOBJECT::Components()
{
    return components;
}

#pragma endregion
#pragma region GAMEOBJECT MANAGER

/*------------------------------------------GAMEOBJECT_MANAGER Initialize()--------------------------------------------*/

/// <summary>
/// <para> Initializes all the gameObjects in the map </para>
/// <para> マップ内すべてのゲームオブジェクトをリセットする </para>
/// </summary>
void GAMEOBJECT_MANAGER::Initialize()
{
    for (auto& g : gameObjects)
        g.second->Initialize();
}

/*------------------------------------------GAMEOBJECT_MANAGER Execute()--------------------------------------------*/

/// <summary>
/// <para> Called every frame to perform Execute() of all gameObjects and its components </para>
/// <para> ゲームオブジェクト及びそのコンポネントのExecute()関数を呼び出すように毎フレームに呼び出す </para>
/// </summary>
void GAMEOBJECT_MANAGER::Execute()
{
    for (auto& g : gameObjects)
        g.second->Execute();
}

/*------------------------------------------GAMEOBJECT_MANAGER Render()--------------------------------------------*/

/// <summary>
/// <para> Called every frame to perform Render() of all gameObjects and its components </para>
/// <para> ゲームオブジェクト及びそのコンポネントのRender()関数を呼び出すように毎フレームに呼び出す </para>
/// </summary>
void GAMEOBJECT_MANAGER::Render()
{
    //VECTOR3 cam_forward = Camera::Instance()->Forward();
    //cam_forward.Normalize();
    //VECTOR3 cam_position = Camera::Instance()->Eye();
    //VECTOR3 dist{};
    //VECTOR3 gameObject_Dist{};
    for (auto& g : gameObjects)
    {
        //if (dynamic_cast<GAMEOBJECT_2D*>(g.second.get()))
        //{
        //    g.second->Render();
        //    continue;
        //}
        //gameObject_Dist = g.second->GetComponent<TRANSFORM_3D>()->Translation();
        //gameObject_Dist.y = 0.0f;
        //dist = gameObject_Dist -cam_position;
        //dist.Normalize();
        //float dot = Math::GetDirection(cam_forward, dist);
        //if (dot > 1.56)
        //    continue;
        g.second->Render();
    }
}

/*------------------------------------------GAMEOBJECT_MANAGER Finalize()--------------------------------------------*/

/// <summary>
/// <para> Generally unneeded. Called when closing to finalize all gameObjects</para>
/// <para> 基本的に必要ない。ゲームを終了時にゲームオブジェクトを終了処理するように呼び出す。</para>
/// </summary>
void GAMEOBJECT_MANAGER::Finalize()
{
    gameObjects.clear();
}

/*------------------------------------------GAMEOBJECT_MANAGER Insert()--------------------------------------------*/

/// <summary>
/// <para> Create a gameObject and insert it into the map </para>
/// <para> ゲームオブジェクトを生成してマップに登録する </para>
/// </summary>
/// <param name="n"> : Name of gameObject</param>
/// <param name="d"> : Dataset of gameObject with data of components</param>
void GAMEOBJECT_MANAGER::Insert(std::string n, std::shared_ptr<OBJECT_DATA>d)
{
    COMPONENT_DATA* base{ d->Dataset().begin()->get() };
    TRANSFORM_2D_DATA* data = dynamic_cast<TRANSFORM_2D_DATA*>(base);
    if (data)
        gameObjects.insert(std::make_pair(n, std::make_shared<GAMEOBJECT_2D>(d)));
    else
        gameObjects.insert(std::make_pair(n, std::make_shared<GAMEOBJECT>(d)));
    gameObjects.find(n)->second->Initialize();

}

/*------------------------------------------GAMEOBJECT_MANAGER Remove()--------------------------------------------*/

/// <summary>
/// <para> Remove the gameObject from the map, and from the game </para>
/// <para> ゲームオブジェクトをマップ及びゲームから削除する </para>
/// </summary>
/// <param name="name"> : name of gameObject to remove</param>
void GAMEOBJECT_MANAGER::Remove(std::string n)
{
    gameObjects.erase(n);
}
void GAMEOBJECT_MANAGER::Remove(std::shared_ptr<GAMEOBJECT>gameObject)
{
    std::string target{ RetrieveName(gameObject) };
    Remove(target);
}

/*------------------------------------------GAMEOBJECT_MANAGER Retrieve()--------------------------------------------*/

std::shared_ptr<GAMEOBJECT> GAMEOBJECT_MANAGER::Retrieve(std::string n)
{
    return gameObjects.find(n)->second;
}

/*------------------------------------------GAMEOBJECT_MANAGER RetrieveName()--------------------------------------------*/

std::string GAMEOBJECT_MANAGER::RetrieveName(std::shared_ptr<GAMEOBJECT>go)
{
    for (auto& g : gameObjects)
        if (g.second == go)
            return g.first;
    assert("Not Found");
    return "";
}


/*------------------------------------------GAMEOBJECT_MANAGER Clear()--------------------------------------------*/

void GAMEOBJECT_MANAGER::Clear()
{
    gameObjects.clear();
}

/*------------------------------------------GAMEOBJECT_MANAGER GameObjects()--------------------------------------------*/

std::map<std::string, std::shared_ptr<GAMEOBJECT>>GAMEOBJECT_MANAGER::GameObjects()
{
    return gameObjects;
}

#pragma endregion
