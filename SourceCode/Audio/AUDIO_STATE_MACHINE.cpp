#include "AUDIO_STATE_MACHINE.h"
#include "AUDIOSTATE_BASE.h"
#include "../Engine/Audio.h"
#include "../Engine/IMGUI.h"
#define AUDIOS AUDIOENGINE::Instance()->Audios()
#define TRANSITION_TIME 1.0f
#define TRANSITION_THRESHOLD 0.2f

std::string states[] = { "Idle", "Tension", "Climax", "Cooldown" };
bool play{ false };
bool duck{};
int index{};


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------AUDIO STATE MACHINE Class------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------AUDIO STATE MACHINE Initialize()------------------------------------------------*/
/// <summary>
/// <para> Initializes the engine by inserting the audio into the map </para>
/// <para> オーディオをマップに登録するようにクラスを初期化する</para>
/// </summary>
/// <returns></returns>
HRESULT AUDIO_STATE_MACHINE::Initialize()
{
    audioMap.insert(std::make_pair(AudioStates::State_Idle, AUDIOENGINE::Instance()->Retrieve("Idle")));
    audioMap.insert(std::make_pair(AudioStates::State_Tension, AUDIOENGINE::Instance()->Retrieve("Tension")));
    audioMap.insert(std::make_pair(AudioStates::State_Climax, AUDIOENGINE::Instance()->Retrieve("Climax")));
    audioMap.insert(std::make_pair(AudioStates::State_Cooldown, AUDIOENGINE::Instance()->Retrieve("Cooldown")));
    cur_BGM = audioMap.find(AudioStates::State_Idle)->second;
    Enter();
    return S_OK;
}

/*---------------------------------------------------AUDIO STATE MACHINE Enter()------------------------------------------------*/

void AUDIO_STATE_MACHINE::Enter()
{
    cur_BGM->Stop();
    cur_BGM->Play();
}

/*---------------------------------------------------AUDIO STATE MACHINE Execute()------------------------------------------------*/
/// <summary>
/// <para> Called every frame. Performs fadeIn and fadeOut effects of current and next bgm</para>
/// <para> 各Audioのフェードインとフェードアウトエフェクトを処理するように毎フレームに呼び出す</para> 
/// </summary>
void AUDIO_STATE_MACHINE::Execute()
{
    if (isDucking)
    {
        for (auto& audio : AUDIOS)
        {
            if (ducking_target && ducking_target == audio.second)
                continue;
            audio.second->PerformDucking(0.3f);
        }
        return;
    }
    else
    {
        for (auto& audio : AUDIOS)
            audio.second->StopDucking();
    }

    if (pause)
        return;
    if (!transitioning && cur_BGM->Volume() <= 1.0f)
        cur_BGM->FadeIn(2.0f);

    if (transitioning && !isDucking)
    {
        cur_BGM->FadeOut(TRANSITION_TIME);
        next_BGM->SetVolume(0.0f);
        next_BGM->Play();
        next_BGM->FadeIn(TRANSITION_TIME);
        transitioning = true;
        if (cur_BGM->Volume() <= TRANSITION_THRESHOLD)
        {
            Exit();
            Enter();
            next_BGM->Stop();
            next_BGM = {};
            transitioning = false;
            cur_BGM->Play();
        }
    }



}

/*---------------------------------------------------AUDIO STATE MACHINE DebugUI()------------------------------------------------*/

void AUDIO_STATE_MACHINE::DebugUI()
{
    if (ImGui::Begin("Audio Test"))
    {
        int ind{};
        if (ImGui::BeginCombo("AudioStates", states[index].c_str()))
        {

            for (auto& s : states)
            {
                if (ImGui::Selectable(s.c_str()))
                {
                    index = ind;
                    break;
                }
                ++ind;
            }
            ImGui::EndCombo();
        }
        if (ImGui::Button("Transition"))
            Transition((AudioStates)index);
        if (ImGui::TreeNode("AudioState"))
        {
            if (cur_BGM)
                ImGui::InputFloat("Cur BGM Volume", &cur_BGM->volume);
            if (next_BGM)
                ImGui::InputFloat("Next BGM Volume", &next_BGM->volume);
            ImGui::TreePop();
        }
        ImGui::Checkbox("Play", &play);
        ImGui::Checkbox("Perform Ducking", &duck);
        if (duck)
            PerformDucking(cur_BGM);
        else
            StopDucking();

        play ? Resume() : Pause();
        ImGui::End();
    }

}

/*---------------------------------------------------AUDIO STATE MACHINE Exit()------------------------------------------------*/
/// <summary>
/// Changes the current BGM to the next BGM
/// </summary>
void AUDIO_STATE_MACHINE::Exit()
{
    cur_BGM->Stop();
    cur_BGM = next_BGM;
}

/*---------------------------------------------------AUDIO STATE MACHINE Transition()------------------------------------------------*/
/// <summary>
/// <para> Performs transition to the next audio </para>
/// <para> 次のオーディオにトランジションする</para>
/// </summary>
/// <param name="next_state"> : State to be transitioned to </param>
void AUDIO_STATE_MACHINE::Transition(AudioStates next_state)
{
    next_BGM = audioMap.find(next_state)->second;
    transitioning = true;
}

/*---------------------------------------------------AUDIO STATE MACHINE Pause()------------------------------------------------*/
/// <summary>
/// <Para> Call in Execute() to perform fadeOut and pause </para> 
/// <para> Execute()に呼び出したらフェードアウトしてオーディオをPauseする </para>
/// </summary>
void AUDIO_STATE_MACHINE::Pause()
{
    if (transitioning)
        return;
    cur_BGM->FadeOutAndPause(TRANSITION_TIME);
    pause = true;
}

/*---------------------------------------------------AUDIO STATE MACHINE Resume()------------------------------------------------*/
/// <summary>
/// <Para> Call in Execute() to perform fadeOut and resume</para> 
/// <para> Execute()に呼び出したらフェードアウトしてオーディオをResumeする </para>
/// </summary>
void AUDIO_STATE_MACHINE::Resume()
{
    if (transitioning)
        return;
    cur_BGM->Play();
    cur_BGM->FadeIn(TRANSITION_TIME);
    pause = false;
}

/*---------------------------------------------------AUDIO STATE MACHINE PerformDucking()------------------------------------------------*/
/// <summary>
/// <para> Performs audio douking. dock_target variable will be exempt </para>
/// <para> ･ｪｩ`･ﾇ･｣･ｪ･ﾀ･ﾃ･ｭ･�･ｰ､�ﾐﾐ､ｦ｡｣dock_target､ﾏｳ�ﾍ筅ｵ､�､�</para>
/// </summary>
/// <param name="dock_target"></param>
void AUDIO_STATE_MACHINE::PerformDucking(std::shared_ptr<AUDIO>duck_target)
{
    if (isDucking)
        return;
    if(duck_target)
        ducking_target = duck_target;
    isDucking = true;
}

/*---------------------------------------------------AUDIO STATE MACHINE PerformDucking()------------------------------------------------*/
/// <summary>
/// <para> Stops audio ducking if is ducking. </para>
/// <para> ･ﾀ･ﾃ･ｭ･�･ｰ､�ﾖｹ､皃� </para>
/// </summary>
void AUDIO_STATE_MACHINE::StopDucking()
{
    if (!isDucking)
        return;
    isDucking = false;
    ducking_target = {};
}

/*---------------------------------------------------AUDIO STATE MACHINE IsDucking()------------------------------------------------*/
/// <summary>
/// <para> Returns true if audio is in ducking state </para>
/// <para> ･ｪｩ`･ﾇ･｣･ｪ､ﾏ･ﾀ･ﾃ･ｭ･�･ｰ･ｹ･ﾆｩ`･ﾈ､ﾇ､｢､�､ﾐTrue､�ｷｵ､ｹ</para>
/// </summary>
/// <returns></returns>
bool AUDIO_STATE_MACHINE::IsDucking()
{
    return isDucking;
}