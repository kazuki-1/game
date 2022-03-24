#include "ENEMY.h"
#include "Components/Headers/TRANSFORM_3D.h"
#include "S_MACHINE.h"  
#include "PLAYER.h"

#pragma region UNUSED


#pragma region MAIN FUNCTIONS
ENEMY::ENEMY(std::shared_ptr<OBJECT_DATA>d)
{
    data = d;
}



HRESULT ENEMY::Initialize()
{
    GAMEOBJECT::Initialize();
    //srand(time(NULL));
    //model = std::make_shared<MODEL>();
    //model->SetTake(data->AnimationTake());
    //start_position = GetComponent<TRANSFORM_3D>()->Translation();
    //SetSamplingRate(60);
    //SetScale(data->Scale().XMF3());
    //SetPosition(data->Translation().XMF3());
    ////CreateCapsule(0.3f);
    ////collider = std::make_shared<OBB>(VECTOR3{ -0.5, 0, -0.5 }, VECTOR3{ 0.5, 2, 0.5 });
    ////weaponCollider = std::make_shared<OBB>(VECTOR3{ -0.1f, -0.1f, -0.1f }, VECTOR3{ 0.1f, 10.0f, 100.0f });
    //for (auto& cd : data->ColliderDataset())
    //{
    //    colliders.emplace(cd->Name(), std::make_shared<COLLIDER>(cd));
    //}

    //stateMachine = std::make_shared<S_MACHINE>(this);
    //stateMachine->Change(E_STATE::IDLE);
    //isAlive = true;
    return S_OK;

    //return model->Initialize(data->ModelPath());
}

void ENEMY::Execute()
{
    GAMEOBJECT::Execute();
    //UpdateNextMovement();
    //Move();
    ////Movement();
    //VelocityControl();


    //if (isAlive)
    //{
    //    CheckForTarget();
    //    AnimationSetting();
    //    Attack();
    //    collider->UpdateQ(XMMatrixRotationQuaternion(Model()->Quaternion().XMV()) * XMMatrixTranslationFromVector(Model()->Translation().XMV()));
    //    capsule->UpdatePosition(position);
    //    FitWeaponOBBToBoneQ("mixamorig:RightHand");
    //}
    //else
    //    DeathAnimation();
    //if (isAlive) {
    //    stateMachine->Execute();
    //    //UpdateColliders();
    //}
    //else
    //    DeathAnimation();
    //UpdateTransform();

}

void ENEMY::UpdateNextMovement()
{

    canMove = true;
    nextRotation = Math::ToRadians((float)(rand() % 360));
    
}

void ENEMY::Move()
{
    //isMoving = false;
    //VECTOR3 F{ GetComponent<TRANSFORM_3D>()->Forward() };

    //F = { F.x, 0, F.z};
    //F.Normalize();
    //if (!canMove)
    //{
    //    velocity = {};
    //    return;
    //}
    //move += FRAMETIME;
    //move = Math::Clamp(move, -1.5f, 1.5f);
    //F *= move;
    //velocity = F;
    //isMoving = true;
}


#pragma endregion

#pragma region SUBFUNCTIONS

void ENEMY::CheckForTarget()
{
  
    //VECTOR3 Cur_Pos{ position }, Tar_Pos{ PLAYERMANAGER::Instance()->Get()->Position() };
    //VECTOR3 dist{ Cur_Pos - Tar_Pos };

    //float length{ Math::Length(Cur_Pos, Tar_Pos) };
    //length < 3.0f ? hasTarget = true : hasTarget = false;
    //if (!hasTarget)
    //    return;
    //length < 3.0f ? SetTarget(Tar_Pos.XMF3()) : ClearTarget();

    //length < 1.0f ? canMove = false : canMove = true;

}

void ENEMY::SetForwardToTarget()
{

    //if (fabs((target - position).Length()) < 0.1f)
    //    return;
    //nextRotation = Math::GetAngle(position, target);

    

}

void ENEMY::AnimationSetting()
{
    //XMVECTOR v{ XMLoadFloat3(&velocity) };
    //
    //if (!isAlive)
    //    return;
    //{
    //    if (isAttacking)
    //    {
    //        if (Model()->FinishedAnim())
    //        {
    //            SetAnimation(0);
    //            isAttacking = false;
    //        }
    //        return;
    //    }
    //}
    //float length{ velocity.Length() };
    //if (length > 0)
    //    SetAnimation(1);
    //else
    //    SetAnimation(0);
}

void ENEMY::SetTarget(XMFLOAT3 p)
{
    target = p;
    hasTarget = true;
    SetForwardToTarget();
}

void ENEMY::ClearTarget()
{
    //target = start_position;
    //if (Math::Length(position, target) < 0.3f || !hasTarget)
    //{
    //    hasTarget = false;
    //    return;
    //}
    //SetForwardToTarget();
}

void ENEMY::Attack()
{
    //static float at_timer{};
    //if (hasTarget)
    //{

    //    if (Length(position, target) < 1.5f)
    //    {
    //        ++at_timer;
    //        if (at_timer > 180)
    //        {
    //            at_timer = 0;
    //            SetAnimation(2);
    //            isAttacking = true;
    //            
    //        }
    //    }
    //}
    //SetAnimation(4);
    //weaponCollider->Activate();
    //isAttacking = true;
}

void ENEMY::UpdateRotation()
{
    //XMVECTOR temp{ XMQuaternionRotationAxis(Model()->Up().XMV(), nextRotation) };
    //quaternion.Load(XMQuaternionSlerp(quaternion.XMV(), temp, 0.1f));
}

#pragma endregion






HRESULT ENEMYMANAGER::Add(std::shared_ptr<OBJECT_DATA>d)
{
    enemies.push_back(std::make_shared<ENEMY>(d));
    return enemies.back()->Initialize();
}


#pragma endregion