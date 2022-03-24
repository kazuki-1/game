#pragma once
#include "CHARACTER.h"
#include "Engine/Input.h"
class PLAYERMANAGER;
//enum class PLAYER_ANIM
//{
//    IDLE, 
//    WALK, 
//    RUN, 
//    DIVE, 
//    ATTACK, 
//    HIT, 
//    DIE
//};
//
//enum class PLAYER_ANIM_2
//{
//    T_POSE, 
//    WALK, 
//    IDLE, 
//    JUMP, 
//    LANDING
//};


class PLAYER : public CHARACTER
{
    //bool isMoving{};
    bool isRotating{};
    bool isDodging{};
    bool isRunning{};
    bool isJumping{};
    bool onGround{};
    float next_Rotation;
public:
#pragma region MAIN FUNCTIONS

    friend class PLAYERMANAGER;
    PLAYER() {}
    PLAYER(std::shared_ptr<OBJECT_DATA>d);
    HRESULT Initialize() override;
    void Execute() override;
    void Render(XMFLOAT4 colour = { 1.0f, 1.0f, 1.0f, 1.0f }) override;
    void Move();
    void Jump();
    void VelocityControl() override;
    void GravityControl();
    void UpdateRotation();
    void Collision();
    void MovementInput();
    void AttackInput();
    void DodgeInput();
    void RunInput();
    void JumpInput();
#pragma endregion

#pragma region SUBFUNCTIONS
    void Dodge();
    void Slerp();
    void Hit() override;
    void Kill() override;
    void AnimationSetting() override;
#pragma endregion



};


class PLAYERMANAGER : public SINGLETON<PLAYERMANAGER>
{
    std::shared_ptr<PLAYER>Player;
public:
    HRESULT Initialize(std::shared_ptr<PLAYER> p)
    {
        Player = p;
        Player->Initialize();
        return Player ? S_OK : E_FAIL;
    }

    void Execute()
    {
        Player->Execute();
    }

    void Render()
    {
        Player->Render();
    }

    void Finalize()
    {
        Player.reset();
    }


    std::shared_ptr<PLAYER>Get()
    {
        return Player;
    };
};