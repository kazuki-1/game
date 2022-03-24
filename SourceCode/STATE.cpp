#include "ENEMY.h"
#include "STATE.h"


#pragma region I_STATE

void I_STATE::Initialize(ENEMY* host)
{
    //host->SetAnimation(0);
    //host->ResetTimer();
    //host->WeaponCollider()->Deactivate();
}

void I_STATE::Execute(ENEMY* host)
{
    //host->CheckForTarget();
    //host->UpdateRotation();
    //host->UpdateTimer();
    //if (host->HasTarget())
    //    host->StateMachine()->Change(E_STATE::CHASE);
    //if (host->Timer() > 180)
    //    host->StateMachine()->Change(E_STATE::WANDER);
}

void I_STATE::Finalize(ENEMY* host)
{

}

#pragma endregion
#pragma region W_STATE

void W_STATE::Initialize(ENEMY* host)
{
    //host->SetAnimation(1);
    //host->ResetTimer();
    //host->UpdateNextMovement();
    //host->WeaponCollider()->Deactivate();


}

void W_STATE::Execute(ENEMY* host)
{
    //host->CheckForTarget();
    //host->UpdateRotation();
    //host->Movement();
    //host->Move();
    //host->VelocityControl();
    //host->UpdateTimer();

    //if (host->HasTarget())
    //    host->StateMachine()->Change(E_STATE::CHASE);
    //if (host->Timer() > 180)
    //    host->StateMachine()->Change(E_STATE::IDLE);
}

void W_STATE::Finalize(ENEMY* host)
{
    //host->ResetTimer();
}

#pragma endregion
#pragma region C_STATE

void C_STATE::Initialize(ENEMY* host)
{
    //host->ResetTimer();
    //host->SetAnimation(1);
    //host->WeaponCollider()->Deactivate();

}


void C_STATE::Execute(ENEMY* host)
{
    //host->UpdateRotation();
    //host->CheckForTarget();
    //host->SetForwardToTarget();
    //host->Move();
    //host->Movement();
    //if (!host->HasTarget())
    //    host->StateMachine()->Change(E_STATE::WANDER);
    //if (host->IsCloseToTarget())
    //    host->StateMachine()->Change(E_STATE::ATTACK);
}

void C_STATE::Finalize(ENEMY* host)
{
    //host->ResetTimer();
}

#pragma endregion
#pragma region A_STATE

void A_STATE::Initialize(ENEMY* host)
{
    //host->ResetTimer();
    //host->Attack();
    //timer = 0;
}


void A_STATE::Execute(ENEMY* host)
{
    //++timer;
    //if(host->Model()->CurrentFrame() > 30)
    //    //host->WeaponCollider()->Activate();

    //if ((host->Target() - host->Position()).Length() > 1.0f || host->Model()->FinishedAnim())
    //{
    //    host->NotAttacking();
    //    host->SetAnimation(0);
    //    //host->WeaponCollider()->Deactivate();
    //    if(timer > 150)
    //       host->StateMachine()->Change(E_STATE::CHASE);
    //}

}

void A_STATE::Finalize(ENEMY* host)
{
    //host->ResetTimer();
    //host->WeaponCollider()->Deactivate();

}

#pragma endregion

