#include "ENEMY.h"
#include "S_MACHINE.h"


void S_MACHINE::Change(E_STATE es)
{
    if (cur_State)
        cur_State->Finalize(host);
    cur_State = STATEMANAGER::Instance()->Get(es);
    cur_State->Initialize(host);
}

void S_MACHINE::Initialize()
{
    cur_State->Initialize(host);
}

void S_MACHINE::Execute()
{
    cur_State->Execute(host);
}

void S_MACHINE::Finalize()
{
    cur_State->Finalize(host);
}