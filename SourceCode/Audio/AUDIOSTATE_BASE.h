#pragma once
#include <memory>
#include "../Engine/Audio.h"
class AUDIO_STATE_MACHINE;
/// <summary>
/// <para> Base class for Audio States </para> 
/// <para> �I�[�f�B�I�X�e�[�g�̊�b�N���X
/// </summary>
class AUDIOSTATE_BASE
{
protected:
    std::shared_ptr<AUDIO>audio;
    bool completed{};

    virtual void FadeIn()
    {
        audio->FadeIn(2.0f);
    }
    virtual void FadeOut()
    {
        audio->FadeOut(2.0f);
        if (audio->Volume() <= 0.0f)
            completed = true;
    }

    friend class AUDIO_STATE_MACHINE;
public:
    
    /// <summary>
    /// <para> Initializes the state. Only called once when created </para>
    /// <para> �X�e�[�g���������B�������ɌĂяo���܂��i���̂݁j</para>
    /// </summary>
    virtual HRESULT Initialize() {};
    /// <summary>
    /// <para> Called when transitioning into this state from a different state </para>
    /// <para> �X�e�[�g�����Ƃ��ɌĂяo�� </para>
    /// </summary>
    virtual void Enter();
    /// <summary>
    /// <para> Called every frame </para>
    /// <para> ���t���[���ɌĂяo�� </para>
    /// </summary>
    virtual void Execute() {};
    /// <summary>
    /// <para> Called before transitioning to a different state </para>
    /// <para> ���̃X�e�[�g�ɕς��O�ɌĂяo��</para>
    /// </summary>
    virtual void Exit() {};

    std::shared_ptr<AUDIO>Audio() { return audio; }
    bool Completed() { return completed; }
};


