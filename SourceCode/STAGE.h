#pragma once
#include "Engine/MODEL.h"


class STAGE 
{
    std::shared_ptr<MODEL>stageModel;

public:
    HRESULT Initialize(std::string model_path);
    void Execute();
    void Render(float SamplingRate = 0, XMFLOAT4 colour = { 1.0f, 1.0f, 1.0f, 1.0f });
    void Finalize();

    ~STAGE();
    // Parameter Retrieval
    std::shared_ptr<MODEL>Stage();

};


class STAGEMANAGER : public SINGLETON <STAGEMANAGER>
{
    std::shared_ptr<STAGE>Stage;
public:

    HRESULT Initialize(std::string model_path);
    void Execute();
    void Render();
    void Finalize();
    std::shared_ptr<STAGE>Get();


};