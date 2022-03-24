#include "DATAMANAGER.h"
#include "../../GAMEOBJECT.h"
#include <filesystem>
#include <fstream>
//#include <cereal/archives/json.hpp>

void DATAMANAGER::Load(std::string n)
{
    if (dataset.size() > 0)
        dataset.clear();
    if (GAMEOBJECT_MANAGER::Instance()->GameObjects().size() >= 0)
        GAMEOBJECT_MANAGER::Instance()->Clear();
    std::filesystem::path path(n);
    if (!std::filesystem::exists(n))
        assert(!"No file found");

    std::ifstream ifs(path, std::ios::in | std::ios::binary);
    cereal::BinaryInputArchive bin(ifs);
    bin(dataset);
    ifs.close();
    InsertAndInitialize();
}

void DATAMANAGER::InsertAndInitialize()
{
    GAMEOBJECT_MANAGER::Instance()->GameObjects().clear();
    for (auto& d : dataset)
    {
        //GAMEOBJECT_MANAGER::Instance()->Insert(d->Name(), d);
        GAMEOBJECT_MANAGER::Instance()->Insert(d->Name(), d);
    }
}

void DATAMANAGER::OutputFile(std::string output_path)
{
    std::string dir{ "./Generated/Stage Data/" };
    if (!std::filesystem::exists(dir))
        std::filesystem::create_directories(dir);
    dir += output_path.c_str();
    std::filesystem::path path(dir);
    path.replace_extension(".stg");
    if (std::filesystem::exists(path))
        std::filesystem::remove(path);
    std::stringstream oss(std::ios::in | std::ios::out | std::ios::binary);
    std::ofstream ofs(path, std::ios::out | std::ios::binary);
    cereal::BinaryOutputArchive out(ofs);
    out(dataset);
    std::string temp{ oss.str() };
    std::stringstream ss(std::ios::in | std::ios::out | std::ios::binary);
    {
        cereal::BinaryOutputArchive  o_archive(ss);
        o_archive(dataset);
    }
    std::string dummy = ss.str();
    ofs.close();
}

std::vector<std::shared_ptr<OBJECT_DATA>>DATAMANAGER::Dataset()
{
    return dataset;
}

void DATAMANAGER::Insert(std::shared_ptr<OBJECT_DATA>d)
{
    dataset.push_back(d);
}