#include "PLAYER.h"
#include "Engine/Camera.h"
#include "Engine/ResourceManager.h"
#include "Engine/DXMath.h"
#include "Engine/COLLISION.h"
#include "Components\Headers/TRANSFORM_3D.h"
#include "CollisionManager.h"

#pragma region UNUSED


#pragma region MAIN FUNCTIONS

PLAYER::PLAYER(std::shared_ptr<OBJECT_DATA>d)
{
    data = d;
}


HRESULT PLAYER::Initialize()
{
    SetSamplingRate(60);
    
    //colliders.resize(data->ColliderDataset().size());
    //CreateCapsule(0.3f);
    //collider = std::make_shared<OBB>(VECTOR3{ -0.5, 0, -0.5 }, VECTOR3{ 0.5, 2, 0.5 });
    //weaponCollider = std::make_shared<OBB>(VECTOR3{ -0.1, -0.1, -0.1 }, VECTOR3{ 0.1, 0.1, 100.0 });
    return S_OK;

}

void PLAYER::Execute()
{
    GAMEOBJECT::Execute();
    if (!isHit)
    {
        Move();
        Movement();
        UpdateRotation();
        Collision();
        GravityControl();
    }
    VelocityControl();
    AnimationSetting();
    UpdateTransform();
}

void PLAYER::Move()
{
    //static VECTOR3 d_Rot{ Camera::Instance()->Rotation() };
    //isMoving = false;
    //VECTOR2 k_Axis{ INPUTMANAGER::Instance()->Keyboard()->AxisX() };
    //if (isAttacking || isDodging)
    //{
    //    move = 0;
    //    return;

    //}
    //if (!k_Axis.x && !k_Axis.y)
    //{
    //    move = 0;
    //    return;
    //}
    //VECTOR2 limit{ -20.0f, 20.0f };
    //move = Math::Clamp(move, limit.x, limit.y);
    //VECTOR3 ROT{ Camera::Instance()->Rotation() };
    //if (d_Rot != ROT)
    //{
    //    d_Rot = ROT;
    //    next_Rotation = ROT.y;
    //}
    //if (k_Axis.x || k_Axis.y)
    //    move += 0.01667 * 10.0f;
    //Math::Clamp(move, 0, 0.6f);

    //fabs(move) < 0.01f ? move = 0 : move = move;
    //VECTOR3 f;
    //f = GetComponent<TRANSFORM_3D>()->Forward();
    //f = { f.x, 0, f.z };
    //f.Normalize();
    //if (isRunning)
    //    move *= 3;
    //velocity.x = (f * move).x;
    //velocity.z = (f * move).z;
    //isMoving = true;
}

void PLAYER::GravityControl()
{
    //if (!onGround)
    //    velocity.y -= 0.5f;
    //else
    //    velocity.y = 0.0f;
    //velocity.y = (std::max)(velocity.y, -100.0f);
}


void PLAYER::VelocityControl()
{
    //CHARACTER::VelocityControl();
    //if (isDodging || !move)
    //{
    //    velocity.x *= 0.9f;
    //    velocity.z *= 0.9f;
    //}
}

void PLAYER::UpdateRotation()
{
    //VECTOR2 ax{ INPUTMANAGER::Instance()->Keyboard()->AxisX() };
    //float temp{ Rotation().y };
    //if (!ax.x && !ax.y)
    //{
    //    isRotating = false;
    //    return;
    //}
    //float y_ax{ Camera::Instance()->Rotation().y };

    //

    //VECTOR3 d_Front{ 0, 0, 1 }, d_Right{ 1, 0, 0 };
    //VECTOR3 input{ ax.x, 0, ax.y };
    //float t_Angle{ Math::GetDirection(d_Front, input) };
    //if (d_Right.Dot(input) < 0)
    //    t_Angle *= -1;
    //float new_Angle = y_ax + t_Angle ;
    //next_Rotation = new_Angle;
    //

    //XMVECTOR Normal{ GetComponent<TRANSFORM_3D>()->Up().XMV() };

    //XMVECTOR cur_q{ Model()->Quaternion().XMV() }, next_q;
    //VECTOR4 v4;
    //v4.Load(XMQuaternionRotationAxis(Normal, next_Rotation));
    //GetComponent<TRANSFORM_3D>()->SlerpRotation(v4)


    //isRotating = true;



}

void PLAYER::Render(XMFLOAT4 colour)
{
    for (auto& c : components)
        c->Render();
    // model->Render(samplingRate, colour);
    // int take{ GetComponent<MESH>()->Model()->CurrentTake() };
    //ImGui::Begin("Velocity");
    //ImGui::InputFloat3("Velocity : ", &velocity.x);
    //ImGui::TreeNode("Rotation");
    //ImGui::InputFloat("Next Rotation : ", &next_Rotation);
    //ImGui::End();
    //model->DebugText();
}

#pragma endregion
#pragma region INPUT RELATED FUNCTIONS




void PLAYER::MovementInput()
{
    //if (isAttacking || isDodging || isJumping)
    //    return;
    //VECTOR2 v{ velocity.x, velocity.z };
    //v.Length() >= 1.5f ? SetAnimation((int)PLAYER_ANIM_2::WALK) : SetAnimation((int)PLAYER_ANIM_2::IDLE);
}

void PLAYER::AttackInput()
{
    //if (isDodging)
    //    return;
    //if (INPUTMANAGER::Instance()->Mouse()->LButton().Triggered())
    //{
    //    SetAnimation((int)PLAYER_ANIM::ATTACK);
    //    isAttacking = true;
    //}
    //if (model->FinishedAnim() && Model()->CurrentTake() == (int)PLAYER_ANIM::ATTACK)
    //{
    //    SetAnimation((int)PLAYER_ANIM::IDLE);

    //    isAttacking = false;
    //}
}

void PLAYER::DodgeInput()
{

    //if (INPUTMANAGER::Instance()->Keyboard()->Triggered(VK_SPACE))
    //    Dodge();
    //if (isDodging)
    //{
    //    if (Model()->InAnim(15, 45))
    //        int temp{};
    //        //collider->Deactivate();
    //    if (Model()->FinishedAnim())
    //    {
    //        SetAnimation((int)PLAYER_ANIM::IDLE);
    //        //collider->Activate();
    //        isDodging = false;
    //    }
    //}
}

void PLAYER::RunInput()
{
    //if (INPUTMANAGER::Instance()->Keyboard()->Held(VK_SHIFT))
    //{
    //    SetAnimation((int)PLAYER_ANIM::RUN);
    //    isRunning = true;
    //    return;
    //}
    //if (Model()->CurrentTake() != (int)PLAYER_ANIM::RUN && isRunning)
    //{
    //    SetAnimation((int)PLAYER_ANIM::IDLE);
    //    isRunning = false;
    //}
}

void PLAYER::JumpInput()
{
    //if (INPUTMANAGER::Instance()->Keyboard()->Triggered('Z'))
    //    Jump();
    //if (!isJumping)
    //    return;
    //if (velocity.y != 0)
    //    model->PauseAnimAt(24);
    //else
    //    model->ResumeAnim();
    //if ((model->CurrentTake() == (int)PLAYER_ANIM_2::JUMP && model->FinishedAnim()) || !onGround)
    //{
    //    model->SetTake((int)PLAYER_ANIM_2::IDLE);
    //    isJumping = false;
    //}
}

#pragma endregion
#pragma region SUB FUNCTIONS

void PLAYER::Dodge()
{
    //if (isDodging)
    //    return;
    //SetAnimation((int)PLAYER_ANIM::DIVE);
    //isDodging = true;
    //VECTOR3 forward{ Model()->Forward() };
    //forward.Normalize();
    //velocity = forward * 20.0f;

}

void PLAYER::Slerp()
{
    //if (!isRotating)
    //    return;
    //VECTOR3 r{ Rotation() };
    //float y{ r.y };
    //if (fabs(y - next_Rotation) > 0.01f)
    //{
    //    float cor{ next_Rotation - r.y };
    //    cor *= 0.1f;
    //    SetRotation({ r.x, r.y + cor, r.z });
    //}
    //else
    //{
    //    isRotating = false;
    //    r.y = next_Rotation;
    //}
}

void PLAYER::AnimationSetting()
{
    //if (!isHit)
    //{
    //    MovementInput();
    //    JumpInput();
    //}
    //else
    //{
    //}
}

void PLAYER::Collision()
{
    //for (auto& c : colliders)
    //{
    //    OBB* ori, * tar;
    //    if (c.second->Dataset()->Type() != COLLIDER_TYPE::OBB)
    //        continue;
    //    ori = c.second->Obb();
    //    for (auto& i : STAGE_ITEM_MANAGER::Instance()->Items())
    //    {
    //        switch (i->Data()->Type())
    //        {
    //        case OBJECT_TYPE::WALL:
    //        case OBJECT_TYPE::BACKDROP:
    //        {
    //            for (auto& i_c : i->Colliders())
    //            {
    //                if (i_c.second->Dataset()->Type() != COLLIDER_TYPE::OBB)
    //                    continue;
    //                tar = i_c.second->Obb();
    //                if (RAYCAST::OBBCollision(ori, tar))
    //                {
    //                     position.x -= velocity.x * 0.019;
    //                     position.z -= velocity.z * 0.019;
    //                    //velocity.x = velocity.z = 0.0f;
    //                    position.y -= velocity.y * 0.016;
    //                    velocity.y = 0;
    //                    //velocity.y = 0.0f;

    //                    //move = 0;

    //                }
    //            }
    //            break;
    //        }
    //        case OBJECT_TYPE::FLOOR:
    //        {
    //            for (auto& i_c : i->Colliders())
    //            {
    //                if (i_c.second->Dataset()->Type() != COLLIDER_TYPE::OBB)
    //                    continue;
    //                tar = i_c.second->Obb();
    //                if (RAYCAST::OBBCollision(ori, tar))
    //                {
    //                    onGround = true;
    //                    position.y -= velocity.y * 0.02;
    //                    velocity.y = 0.0f;

    //                }
    //                else
    //                    onGround = false;
    //            }

    //        }
    //        }
            //for (auto& i_c : i->Colliders())
            //{
            //    if (i_c.second->Dataset()->Type() != COLLIDER_TYPE::OBB)
            //        continue;
            //    tar = i_c.second->Obb();
            //    if (RAYCAST::OBBCollision(ori, tar))
            //    {
            //        switch (i->Data()->Type())
            //        {
            //        case OBJECT_TYPE::BACKDROP:
            //        {
            //            //position.x -= velocity.x * 0.04;
            //            //position.y -= velocity.z * 0.04;
            //            //velocity.x = velocity.z = 0.0f;
            //            break;
            //        }
            //        case OBJECT_TYPE::FLOOR:
            //        {
            //            onGround = true;
            //            position.y -= velocity.y * 0.05;
            //            velocity.y = 0.0f;
            //        }
            //        }
            //    }
            //}
    //    }
    //}

}

void PLAYER::Jump()
{
    //model->SetTake((int)PLAYER_ANIM_2::JUMP);
    //velocity.y += 30.0f;
    //position.y += velocity.y * 0.1f;
    //isJumping = true;

}

void PLAYER::Hit()
{

}

void PLAYER::Kill()
{

}

#pragma endregion


#pragma endregion