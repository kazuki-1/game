#pragma once
#include "CHARACTER.h"
#include "S_MACHINE.h"
#include "Engine/Singleton.h"
#include "Engine/DXMath.h"




class ENEMY : public CHARACTER
{
    int timer{};
    float nextRotation;
    bool canMove{};
    bool hasTarget{};

    VECTOR3 start_position{};
    VECTOR3 target{};


    std::shared_ptr<S_MACHINE>stateMachine;

public:
#pragma region MAIN FUNCTIONS
    ENEMY() {};
    ENEMY(std::shared_ptr<OBJECT_DATA>d);
    HRESULT Initialize() override;
    void Execute() override;
    void Move();
    void UpdateNextMovement();
    void UpdateRotation();

#pragma endregion
#pragma region SUBFUNCTIONS

    void Attack();
    void NotAttacking()
    {
        isAttacking = false;
    }
    void AnimationSetting() override;
    void ResetTimer()
    {
        timer = 0;
    }
    void UpdateTimer()
    {
        timer++;
    }
    void CheckForTarget();
    void SetForwardToTarget();
    void SetTarget(XMFLOAT3 p);
    void ClearTarget();
    void Kill() override
    {
        SetStatus(false);
    }

    std::shared_ptr<S_MACHINE>StateMachine()
    {
        return stateMachine;
    }
    VECTOR3 Target()
    {
        return target;
    }
    bool HasTarget()
    {
        return hasTarget;
    }
    bool IsCloseToTarget()
    {
        if (!hasTarget)
            return false;
        return (target - position).Length() < 1.0f;
    }
    int Timer()
    {
        return timer;
    }
#pragma endregion
};

class ENEMYMANAGER : public SINGLETON<ENEMYMANAGER>
{
    std::vector<std::shared_ptr<ENEMY>>enemies;
public:
    HRESULT Add(std::string model_path, XMFLOAT3 start_pos)
    {
        //enemies.push_back(std::make_shared<ENEMY>());
        //return enemies.back()->Initialize();
        
        return S_OK;
    }
    HRESULT Add(std::shared_ptr<OBJECT_DATA>d);
    void AddAnimation(std::string path)
    {
        for (auto& e : enemies)
            e->AddAnimation(path);
    }
    void Execute()
    {

    }
    void Render()
    {
        for (auto& e : enemies)
            e->Render({1, 0, 0, 1});
    }

    std::shared_ptr<ENEMY>GetEnemy(int it)
    {
        return enemies.at(it);
    }
    std::vector<std::shared_ptr<ENEMY>>GetVector()
    {
        return enemies;
    }


};