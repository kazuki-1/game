#pragma once
#include "ENEMY.h"
#include "PLAYER.h"
#include "STAGE_ITEMS.h"
#include "Engine/Singleton.h"



class COLLISIONMANAGER : public SINGLETON<COLLISIONMANAGER>
{
public:
    bool CapsuleToCapsule()
    {
        PLAYER* p{PLAYERMANAGER::Instance()->Get().get()  };
        for (auto& e : ENEMYMANAGER::Instance()->GetVector())
        {
            //if (e->Capsule()->HasCollided(PLAYERMANAGER::Instance()->Get()->Capsule().get()))
            //    return true;

            //if (RAYCAST::OBBCollision(PLAYERMANAGER::Instance()->Get()->WeaponCollider().get(), e->Collider().get()) && PLAYERMANAGER::Instance()->Get()->IsAttacking())
            //{
            //    e->Kill();
            //}

            //if (RAYCAST::OBBCollision(e->WeaponCollider().get(), p->Collider().get()) && e->IsAttacking())
            //{
            //    p->Hit();
            //}

        }
        return false;
    }
    bool OBBToObb()
    {
        //std::shared_ptr<PLAYER> p{ PLAYERMANAGER::Instance()->Get() };
        //for (auto& i : STAGE_ITEM_MANAGER::Instance()->Items())
        //{
        //    OBB* pl, * tar;
        //    pl = p->Colliders().begin()->second->Obb();
        //    bool noOBB{true};
        //    for (auto& c : i->Colliders())
        //    {
        //        if (c.second->Dataset()->Type() != COLLIDER_TYPE::OBB)
        //            continue;
        //        tar = c.second->Obb();
        //        bool val = RAYCAST::OBBCollision(pl, tar);
        //        ImGui::Begin("Collision");
        //        ImGui::Text(i->Data()->Name().c_str());
        //        ImGui::Checkbox("Hit ? ", &val);
        //        ImGui::End();
        //        if (val)
        //            return true;


        //    }

        ////return false;
        //}
        return false;
    }
    bool ObbToObb(COLLIDERS::OBB* ori, COLLIDERS::OBB* tar)
    {
        //return RAYCAST::OBBCollision(ori, tar);
    }


    void RenderDebug()
    {
        bool temp{ CapsuleToCapsule() };
        ImGui::Begin("Collision Check");
        int check{ temp };
        ImGui::InputInt("Collided ? ", &check);
        ImGui::End();
    }
};