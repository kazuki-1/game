#include "AudioStateFade.h"
#include "../Audio.h"
using namespace AUDIO_STATES;


/*----------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------AudioStateFade Class----------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------AudioStateFade Initialize()---------------------------------------------*/
/// <summary>
/// <para> Called when transitioned into this state </para>
/// <para> 他のステートから遷移のときに呼び出す　</para>
/// </summary>
void AudioStateFade::Initialize(AUDIO* parent)
{
    float current_volume{ parent->Volume() };
    float fade_in_frame{ fade_in_time * 60.0f };
    float difference{ current_volume - fade_volume };
    fade_in_increment = difference / fade_in_frame;

}

/*----------------------------------------AudioStateFade Execute()-------------------------------------------*/
/// <summary>
/// <para> Called every frame to perform any functions </para>
/// <para> 毎フE`ムに呼び出す </para>
/// </summary>
void AudioStateFade::Execute(AUDIO* parent)
{
    float volume{ parent->Volume() };
    if (fade_volume > volume && volume == 0.0f)
        parent->SourceVoice()->Start();
    if (fabsf(volume - fade_volume) > 0.01f)
        parent->SetVolume(volume - fade_in_increment);
    




    
    if (fade_volume == 0.0f && fabs(fade_volume - volume) < 0.01f)
        parent->stateMachine->Transition(AudioStateEnum::AudioStatePause);
    else if (fabs(fade_volume - volume) < 0.01f)
        parent->stateMachine->Transition(AudioStateEnum::AudioStatePlay);


}

/*----------------------------------------AudioStateFade Finalize()-------------------------------------------*/
/// <summary>
/// <para>Called when transitioning away from this state </para>
/// <para> ステート遷移の丒に呼び出す </para>
/// </summary>
void AudioStateFade::Finalize(AUDIO* parent)
{
    fade_in_increment = fade_volume = 0.0f;
}

/*----------------------------------------AudioStateFade SetVolume()-------------------------------------------*/
/// <summary>
/// <para> Sets the volume to be faded to </para>
/// <para> フェードボE濠`ムを設定すE</para>
/// </summary>
void AudioStateFade::SetVolume(float vol)
{
    fade_volume = vol;
}

/*----------------------------------------AudioStateFade SetTime()-------------------------------------------*/
/// <summary>
/// <para> Sets the fade timer</para>
/// <para> フェードタイムを設定すE/para>
/// </summary>
void AudioStateFade::SetTime(float t)
{
    fade_in_time = t;
}

/*----------------------------------------AudioStateFade CalculateRate()-------------------------------------------*/
/// <summary>
/// <para> Calculates the rate of fading. Call after SetVolume and SetTime</para>
/// <para> フェード速度を計算すEetVolumeとSetTime呼び出してから呼び出す </para>
/// </summary>
void AudioStateFade::CalculateRate(AUDIO* parent)
{
    float current_volume{ parent->Volume() };
    float fade_in_frame{ fade_in_time * 60.0f };
    float difference{ current_volume - fade_volume };
    fade_in_increment = difference / fade_in_frame;

}
