#pragma once
#include "../../OBJECT_DATA.h"
#include "../../Engine/Singleton.h"
#include <vector>
#include <memory>




class DATAMANAGER : public SINGLETON<DATAMANAGER>
{
    std::vector<std::shared_ptr<OBJECT_DATA>>dataset;

public:
    void Insert(std::shared_ptr<OBJECT_DATA>d);
    void Load(std::string file_path);
    void InsertAndInitialize();
    void OutputFile(std::string output_path);
    std::vector<std::shared_ptr<OBJECT_DATA>>Dataset();
};