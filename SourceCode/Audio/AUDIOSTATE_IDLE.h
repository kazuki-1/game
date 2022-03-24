#pragma once
#include "AUDIOSTATE_BASE.h"


class AUDIOSTATE_IDLE : public AUDIOSTATE_BASE
{
    HRESULT Initialize() override;
    void Enter() override;
    void Execute() override;
    void Exit() override;
};