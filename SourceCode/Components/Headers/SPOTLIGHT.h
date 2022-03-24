#pragma once
#include "../Base Classes/COMPONENT.h"

class SPOTLIGHT_DATA : public COMPONENT_DATA
{
public:
    SPOTLIGHT_DATA();
    VECTOR3 position{};
    VECTOR3 direction{};
    VECTOR4 colour{};
    float range{};
    float innerCorner{};
    float outerCorner{};
    float placeholder{};
    template <class T>
    void serialize(T& t)
    {
        t(position, direction, colour, range, innerCorner, outerCorner, placeholder);
    }
};


class SPOTLIGHT : public COMPONENT
{
    std::shared_ptr<LIGHTING>light;
    SPOTLIGHT_DATA* data;
public:
    SPOTLIGHT(GAMEOBJECT* t, COMPONENT_DATA* data);


    /// <summary>
    /// <para>Called when component is created. Initializes the component with the component data of its matching type (OBB_COLLIDER_DATA)</para>
    /// <para> �������ɌĂяo���B�Ώۂ̃f�[�^���g���ď��������� (OBB_COLLIDER_DATA) </para>
    /// </summary>
    /// <returns></returns>
    HRESULT Initialize() override;
    /// <summary>
    /// <para> Called each frame </para>
    /// <para> ���t���[���ɌĂяo�� </para>
    /// </summary>
    void Execute() override;
    /// <summary>
    /// <para> Called after Execute() to perform any render functions </para>
    /// <para> Execute()��Ƀ����_�[�֐������s����悤�ɖ��t���[���ɌĂяo�� </para>
    /// </summary>
    void Render() override;
    /// <summary>
    /// <para> Renders the UI for this component </para>
    /// <para> UI��`�� </para>
    /// </summary>
    void UI() override;

    VECTOR3 Position();
    VECTOR3 Direction();
    VECTOR4 Colour();
    float Range();
    float InnerCorner();
    float OuterCorner();
};

CEREAL_REGISTER_TYPE(SPOTLIGHT_DATA)