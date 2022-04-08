#pragma once
#include <d3d11.h>
#include <xaudio2.h>
#include <wrl.h>
#include <string>
#include <memory>
#include <map>
#include "Singleton.h"
#include "AudioStates/AudioStates.h"

using namespace Microsoft::WRL;
class AUDIO;
/// <summary>
/// Use this to create an AUDIO object by calling AUDIOENGINE::Instance()->Insert(std::string name, std::wstring file_path)
/// </summary>
class AUDIOENGINE : public SINGLETON<AUDIOENGINE>
{
    
    ComPtr<IXAudio2>xAudio;
    IXAudio2MasteringVoice* masteringVoice;
    //IXAudio2SourceVoice* SourceVoice;
    std::map<std::string, std::shared_ptr<AUDIO>>audios;

    WAVEFORMATEXTENSIBLE format;

public:
    /// <summary>
    /// Initializes the audioengine, initializing the IXAudio2 and IXAudio2MasteringVoice
    /// </summary>
    /// <returns></returns>
    HRESULT Initialize();
    /// <summary>
    /// <para> Called every frame to perform functions </para>
    /// <para> 毎フレームに呼び出す </para>
    /// </summary>
    void Execute();
    /// <summary>
    /// <para> Create an AUDIO object and insert it into the map </para>
    /// <para> AUDIO傪惗惉偟丄儅僢僾偵搊榐</para>
    /// </summary>
    /// <param name="name"> : Name of audio file</param>
    /// <param name="file_path"> : File path of audio file</param>
    void Insert(std::string name, std::wstring file_path);
    /// <summary>
    /// Finalizes the class, generally not needed
    /// </summary>
    void Finalize();
    IXAudio2MasteringVoice* MasteringVoice();
    ComPtr<IXAudio2>XAudio();
    std::shared_ptr<AUDIO>Retrieve(std::string name);
    std::map<std::string, std::shared_ptr<AUDIO>>Audios();
    
};

class AUDIO
{
protected:
    IXAudio2SourceVoice* sourceVoice{};
    WAVEFORMATEXTENSIBLE format{};
    XAUDIO2_BUFFER buffer{};


    std::wstring file_path;
    bool isDucking{};
    bool isPlaying{};


    HRESULT FindChunk(HANDLE h, DWORD fourcc, DWORD& cSize, DWORD& cDataPosition);
    HRESULT ReadChunk(HANDLE h, void* buffer, DWORD buffer_Size, DWORD offset);
public:
    std::shared_ptr<AUDIO_STATES::AudioStateMachine>stateMachine;

    float volume{ 1.0f };
    float fade_in_volume{};
    AUDIO() {};
    AUDIO(std::wstring path);
    virtual void Play();
    /// <summary>
    /// <para> Call this to perform fade in and play the file </para>
    /// </summary>
    /// <param name="fade_time"></param>
    void FadeInAndPlay(float fade_time);
    void FadeOutAndPause(float fade_time);
    void Stop();
    void Finalize();
    /// <summary>
    /// <para> Loops the audio. Default parameter is infinite. CALL BEFORE Play()</para>
    /// <para> 僆乕僨傿僆傪儖乕僾偡傞丅僨僼僅儖僩堷悢偼柍尷 . Play()傪屇傃弌偡慜偵屇傃弌偡</para>
    /// </summary>
    void Loop(UINT loopCount = XAUDIO2_LOOP_INFINITE);
    /// <summary>
    /// <para> Loops the audio from parameters begin till end. CALL BEFORE Play() </para>
    /// <para> 僆乕僨傿僆傪堷悢偱偁傞斖埻撪偵儖乕僾偡傞. Play()傪屇傃弌偡慜偵屇傃弌偡 </para>
    /// </summary>
    void LoopInRange(UINT begin, UINT end);
    /// <summary>
    /// <para> Perform a fadeIn effect from the audio. CALL BEFORE Play() </para>
    /// <para> 僆乕僨傿僆偵僼僃乕僪僀儞僄僼僃僋僩傪偐偗傞丅Play()傪屇傃弌偡慜偵屇傃弌偡 </para>
    /// </summary>
    /// <param name="fade_time"> : Time taken for effect to finish</param>
    void FadeIn(float fade_time);
    /// <summary>
    /// <para> Perform a fadeOut effect from the audio. CALL BEFORE Play() </para>
    /// <para> 僆乕僨傿僆偵僼僃乕僪傾僂僩僄僼僃僋僩傪偐偗傞丅Play()傪屇傃弌偡慜偵屇傃弌偡 </para>
    /// </summary>
    /// <param name="fade_time"> : Time taken for effect to finish</param>
    void FadeOut(float fade_time);
    /// <summary>
    /// <para> Perform a fade effect to the target volume. CALL BEFORE Play() </para>
    /// <para> 指定されたボリュームまでフェードエフェクトを掛ける </para>
    /// </summary>
    /// <param name = "fade_vol"> : Volume to be faded to </param>
    /// <param name="fade_time"> : Time taken for effect to finish</param>
    void FadeTo(float fade_vol, float fade_time = 1.0f);
    void DisableLoop();
    void SetVolume(float vol);
    /// <summary>
    /// <para> Creates the sourceVoice using the buffer </para>
    /// <para> 僶僢僼傽乕傪偮偐偭偰sourceVoice傪惗惉偡傞</para>
    /// </summary>
    /// <param name="buffer"></param>
    void SetBuffer(XAUDIO2_BUFFER buffer);
    /// <summary>
    /// <para> Performs ducking and fades the volume to 0.3f</para>
    /// <para>ダッキングを行い、音量を０．３に調整する </para>
    /// </summary>
    void PerformDucking(float fade_vol);
    /// <summary>
    /// <para> stops the ducking state</para>
    /// <para> ダッキングを中止する</para>
    /// </summary>
    void StopDucking();
    /// <summary>
    /// <para> Sets the fade in volume for the stateMachine </para>
    /// <para> フェードボリュームを設定する</para>
    /// </summary>
    void SetFadeInVolume(float fade_in_vol);
    std::wstring FilePath();
    /// <summary>
    /// <para> Called to initialize the object </para>
    /// <para> オブジェクトを初期化する </para>
    /// </summary>
    /// <returns></returns>
    HRESULT Initialize();
    /// <summary>
    /// <para> Called every frame to perform functions </para>
    /// <para> 毎フレームに呼び出す </para>
    /// </summary>
    void Execute();
    float Volume();
    XAUDIO2_BUFFER Buffer();
    IXAudio2SourceVoice* SourceVoice();
    bool IsPlaying();
    bool IsDucking();
};






















#ifdef _XBOX //Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif

#ifndef _XBOX //Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif