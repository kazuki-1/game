#pragma once
#include "AudioStates.h"

namespace AUDIO_STATES
{
    class AudioStateFade : public AudioStateBase
    {
    protected:
        float fade_target{ 0.5f };   // fade in will fade to this volume
        float fade_in_time{ 1.0f };     // Fade in will occur within this time, measured in seconds
        float fade_increment{};      // Volume will increase or decrease by this amount when fading
    public:
        AudioStateFade() {};
        /// <summary>
        /// <para> Called when transitioned into this state </para>
        /// <para> 他のステートから遷移のときに呼び出す　</para>
        /// </summary>
        void Initialize(AUDIO* parent) override;
        /// <summary>
        /// <para>Called when transitioning away from this state </para>
        /// <para> ステート遷移の丒に呼び出す </para>
        /// </summary>
        void Finalize(AUDIO* parent) override;
        /// <summary>
        /// <para> Sets the volume to be faded to </para>
        /// <para> フェードボE濠`ムを設定すE</para>
        /// </summary>
        void SetTargetVolume(float vol);
        /// <summary>
        /// <para> Sets the fade timer</para>
        /// <para> フェードタイムを設定すE/para>
        /// </summary>
        void SetTime(float t);
        /// <summary>
        /// <para> Calculates the rate of fading. Call after SetVolume and SetTime</para>
        /// <para> フェード速度を計算すEetVolumeとSetTime呼び出してから呼び出す </para>
        /// </summary>
        void CalculateRate(AUDIO* parent);
    };
}