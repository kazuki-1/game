#include "AudioStates.h"
#include "AudioStatePlay.h"
#include "AudioStateFade.h"
#include "AudioStatePause.h"
using namespace AUDIO_STATES;

/*-------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------AudioStateMachine Class----------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------AudioStateMachine Initialize()---------------------------------------------*/
/// <summary>
/// <para> Called when AudioStateMachine is initialized </para>
/// <para> ステートマシンが生成時に呼び出す </para>
/// </summary>
void AudioStateMachine::Initialize()
{
    audioStates.emplace(AudioStateEnum::AudioStatePlay, std::make_shared<AudioStatePlay>());
    audioStates.emplace(AudioStateEnum::AudioStatePause, std::make_shared<AudioStatePause>());
    audioStates.emplace(AudioStateEnum::AudioStateFade, std::make_shared<AudioStateFade>());
    current_state = {};
    Transition(AudioStateEnum::AudioStatePause);
}

/*----------------------------------------AudioStateMachine Transition()---------------------------------------------*/
/// <summary>
/// <para> Called to transition to a different state </para>
/// <para> ステートを遷移する　</para>
/// </summary>
void AudioStateMachine::Transition(AudioStateEnum next_state)
{
    enum_state = next_state;
    if (current_state)
        current_state->Finalize(parent);
    current_state = audioStates.find(next_state)->second;
    current_state->Initialize(parent);
}

/*----------------------------------------AudioStateMachine Execute()---------------------------------------------*/
/// <summary>
/// <para> Called every frame to perform any functions </para>
/// <para> 毎フレームに呼び出す </para>
/// </summary>
void AudioStateMachine::Execute()
{
    if (current_state)
        current_state->Execute(parent);
}

/*----------------------------------------AudioStateMachine FadeTo()---------------------------------------------*/
/// <summary>
/// <para> Perform fade to the specified volume in the specified time</para>
/// <para> 指定された音量を指定された時間にフェード </para>
/// </summary>
/// <param name="fade_time"> : Fade will be done in this. Unit is second</param>
/// <param name="fade_vol"> : Fade volume target</param>
void AudioStateMachine::FadeTo(float fade_time, float fade_vol)
{
    if (enum_state == AudioStateEnum::AudioStateFade)
        return;
    Transition(AudioStateEnum::AudioStateFade);
    dynamic_cast<AudioStateFade*>(current_state.get())->SetTime(fade_time);
    dynamic_cast<AudioStateFade*>(current_state.get())->SetVolume(fade_vol);
    dynamic_cast<AudioStateFade*>(current_state.get())->CalculateRate(parent);
}

/*----------------------------------------AudioStateMachine CurrentState()---------------------------------------------*/
/// <summary>
/// <para> Returns the current audioStateEnum</para>
/// <para> 現在のステートEnumを返す </para>
/// </summary>
/// <returns></returns>
AudioStateEnum AudioStateMachine::CurrentState()
{
    return enum_state;
}
