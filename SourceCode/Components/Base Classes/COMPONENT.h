#pragma once
#include "../../Engine/DXMath.h"
#include "../../Engine/CerealHeaders.h"
#include "../../Engine/COLLISION.h"
#include "../../Engine/Sprite.h"
#include "../../Engine/DEBUG_PRIMITIVE.h"
#include "COMPONENT_DATA.h"
#include "EFFECTS.h"
#include "../../Engine/Audio.h"
#include "../../Engine/IMGUI.h"
#include "../../GAMEOBJECT.h"

using namespace Math;
class GAMEOBJECT;
class DEBUG_MANAGER;
class PLAYER_CONTROLLER;

#pragma region BASE_COMPONENT

/// <summary>
/// Base class for components
/// </summary>
class COMPONENT
{
protected:
    GAMEOBJECT* parent{};
public:
    COMPONENT() {};
    COMPONENT(GAMEOBJECT* t, std::shared_ptr<COMPONENT_DATA>data) {};
    /// <summary>
    /// <para> Virtual Function. Called when component is created </para>
    /// <para> ���z�֐��B�������ɌĂяo���܂�</para>
    /// </summary>
    /// <returns></returns>
    virtual HRESULT Initialize() { return S_OK; }
    /// <summary>
    /// <para> Virtual Function. Called every frame </para>
    /// <para> ���z�֐��B�t���[���������ɌĂяo���� </para>
    /// </summary>
    virtual void Execute() {};
    /// <summary>
    /// <para> Virtual  Function. Called after Execute() to perform any render functions </para>
    /// <para> ���z�֐��BExecute���s��ɕ`��p�֐����Ăяo���֐�</para>
    /// </summary>
    virtual void Render() {};
    /// <summary>
    /// <para> Virtual Function. Renders the UI of the component </para>
    /// <para> ���z�֐��BUI��`�悷��֐� </para>
    /// </summary>
    virtual void UI() {};
    /// <summary>
    /// <para> Returns the GameObject of which this component is stored in </para>
    /// <para> ���̃R���|�l���g�̐e�ƂȂ�Q�[���I�u�W�F�N�g��߂�@</para>
    /// </summary>
    /// <returns></returns> 
    GAMEOBJECT* Parent() { return parent; };

    /// <summary>
    /// Returns a component of the type specified from the GameObject. Returns nullptr if said component does not exist
    /// </summary>
    /// <param name="id">Used for when a GameObject has several components of the same type. Generally starts from 0.</param>
    /// <returns></returns>
    template <class T>
    T* GetComponent(int id = 0)
    {
        return parent->GetComponent<T>(id);
    }

};
/// <summary>
/// Base Audio Component. Should only be used when creating a new audio component and nothing else.
/// </summary>
class BASE_AUDIO_COMPONENT : public COMPONENT
{
protected:
    std::shared_ptr<AUDIO>audio;
    //AUDIO_DATA* data;
public:
    BASE_AUDIO_COMPONENT() {};
    BASE_AUDIO_COMPONENT(GAMEOBJECT* g, COMPONENT_DATA* d) {};
    std::shared_ptr<AUDIO>Audio() { return audio; }
    //AUDIO_DATA* Data() { return data; }
    //std::wstring FilePath() { return data->file_path; }
    //bool LoopFlag() { return data->loopFlag; }
    //float Volume() { return data->volume; }
};
/// <summary>
/// <para> Base class for characters such as Player and Enemy. </para>
/// <para> �v���C���[��G�l�~�[�̂悤�ȃL�����N�^�[�̊�b�N���X</para>
/// </summary>
class BASE_CHARACTER_COMPONENT : public COMPONENT
{
protected:
    //CHARACTER_DATA* data;
    virtual void UpdateRotation() {};
    virtual void AnimationSettings() {};
    virtual void Hit() {};
    virtual void Kill() {};

};
/// <summary>
/// Base collider component. Should only used when creating a new collider component and nothing else
/// </summary>
class BASE_COLLIDER_COMPONENT : public COMPONENT
{
public:
    virtual std::shared_ptr<COLLIDERS::COLLIDER_BASE>Collider() { return 0; }
    virtual bool Collide(GAMEOBJECT* target) { return false; };
    virtual bool Collide(VECTOR3 p) { return false; }
    virtual void Execute(XMMATRIX transform) {};
    virtual VECTOR3 DistanceToPlayer(PLAYER_CONTROLLER* target) { return {}; }
};


#pragma endregion



