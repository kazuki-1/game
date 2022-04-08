#pragma once
#include "AudioStates.h"

namespace AUDIO_STATES
{
    class AudioStateFade : public AudioStateBase
    {

        float fade_volume{ 0.5f };   // fade in will fade to this volume
        float fade_in_time{ 1.0f };     // Fade in will occur within this time, measured in seconds
        float fade_in_increment{};      // Volume will increase or decrease by this amount when fading
    public:
        AudioStateFade() {};
        /// <summary>
        /// <para> Called when transitioned into this state </para>
        /// <para> ���Υ��Ʃ`�Ȥ����w�ƤΤȤ��˺��ӳ�����</para>
        /// </summary>
        void Initialize(AUDIO* parent) override;
        /// <summary>
        /// <para> Called every frame to perform any functions </para>
        /// <para> ���ե�`��˺��ӳ��� </para>
        /// </summary>
        void Execute(AUDIO* parent) override;
        /// <summary>
        /// <para>Called when transitioning away from this state </para>
        /// <para> ���Ʃ`���w�Ƥ��H�˺��ӳ��� </para>
        /// </summary>
        void Finalize(AUDIO* parent) override;
        /// <summary>
        /// <para> Sets the volume to be faded to </para>
        /// <para> �ե��`�ɥܥ��`����O������ </para>
        /// </summary>
        void SetVolume(float vol);
        /// <summary>
        /// <para> Sets the fade timer</para>
        /// <para> �ե��`�ɥ�������O������</para>
        /// </summary>
        void SetTime(float t);
        /// <summary>
        /// <para> Calculates the rate of fading. Call after SetVolume and SetTime</para>
        /// <para> �ե��`���ٶȤ�Ӌ�㤹�롣SetVolume��SetTime���ӳ����Ƥ�����ӳ��� </para>
        /// </summary>
        void CalculateRate(AUDIO* parent);
    };
}