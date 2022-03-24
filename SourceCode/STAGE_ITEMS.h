#pragma once
#include "Engine/MODEL.h"
#include "Engine/DXMath.h"
#include "Engine/Singleton.h"
//#include "COLLIDERS.h"
#include "GAMEOBJECT.h"
using namespace Math;


/// <summary>
/// Stage items, usage includes but not limited to : Backdrops, stage colliders, invisible barriers
/// </summary>
class STAGE_ITEMS : public GAMEOBJECT
{
protected:
    //std::shared_ptr<MODEL>model;
public:
    STAGE_ITEMS() {}
    STAGE_ITEMS(std::shared_ptr<OBJECT_DATA> d) { data = d; }
    HRESULT Initialize() override;
    void Execute() override;
    //void Render(VECTOR4 colour = { 1.0f, 1.0f, 1.0f, 1.0f }) { model->Render(0.0f, colour.XMF4()); }
    void RenderDebug();

    //std::shared_ptr<MODEL>Model() { return model; }
};

class STAGE_FLOOR : public STAGE_ITEMS
{
public:
    STAGE_FLOOR(std::shared_ptr<OBJECT_DATA> d) { data = d; }
};

class STAGE_WALL : public STAGE_ITEMS
{
public:

    STAGE_WALL(std::shared_ptr<OBJECT_DATA> d) { data = d; }
};

class STAGE_BACKDROP : public STAGE_ITEMS
{
public:
    STAGE_BACKDROP(std::shared_ptr<OBJECT_DATA> d) { data = d; }
};


class STAGE_ITEM_MANAGER : public SINGLETON<STAGE_ITEM_MANAGER>
{
    std::vector < std::shared_ptr<STAGE_ITEMS>>items;
public:
    void Insert(std::shared_ptr<OBJECT_DATA> d);
    void Initialize();
    void Execute();
    void Render();
    void RenderDebug();
    void Finalize();

    std::vector < std::shared_ptr<STAGE_ITEMS>>Items() { return items; }
};