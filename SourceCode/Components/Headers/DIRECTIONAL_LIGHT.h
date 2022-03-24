#pragma once
#include "../Base Classes/COMPONENT.h"
class DIRECTIONAL_LIGHT_DATA : public COMPONENT_DATA
{
public:
    DIRECTIONAL_LIGHT_DATA();
    VECTOR3 direction{};
    VECTOR4 colour{};
    template <class T>
    void serialize(T& t)
    {
        t(direction, colour);
    }
};


class DIRECTIONAL_LIGHT : public COMPONENT
{
    std::shared_ptr<LIGHTING>light;
    DIRECTIONAL_LIGHT_DATA* data;
public:
    DIRECTIONAL_LIGHT(GAMEOBJECT* t, COMPONENT_DATA* data);

    HRESULT Initialize() override;
    void Execute() override;
    void Render() override;
    void UI() override;

    VECTOR3 Direction();
    VECTOR4 Colour();


};

CEREAL_REGISTER_TYPE(DIRECTIONAL_LIGHT_DATA)
