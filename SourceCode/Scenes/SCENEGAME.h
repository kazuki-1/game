#pragma once
#include "SCENE.h"



class SCENEGAME : public SCENE
{
    HRESULT Initialize() override;
    void Execute() override;
    void Render()override;
    void Finalize()override;
};