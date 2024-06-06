/**
* @file SoundManager.cpp
*/
#include "SoundManager.h"
#include "EasyAudio/EasyAudio.h"
#include "AudioListner.h"

namespace FGEngine::SoundSystem
{
    /**
    * リスナーを設定
    */
    void SoundManager::SetListner(const AudioListnerPtr audioListner)
    {
        this->audioListner = audioListner;
    }
    
    /**
    * リスナーを取得
    */
    AudioListnerPtr SoundManager::GetListner() const
    {
        if (!audioListner)
        {
            nullptr;
        }

        return audioListner;
    }

    /**
    * マスターボリュームを設定
    *
    * @param volume 設定する音量
    */
    void SoundManager::SetMasterVolume(float volume)
    {
        EasyAudio::SetMasterVolume(volume);
    }

    /**
    * マスターボリュームを取得
    *
    * @return マスターボリューム
    */
    float SoundManager::GetMasterVolume() const
    {
        return EasyAudio::GetMasterVolume();
    }
    /**
    * サウンドマネージャーを初期化
    *
    * @retval true	初期化成功
    * @retval false	初期化失敗
    */
    int SoundManager::Inititalize()
    {
        // 音声ライブラリを初期化
        if (!EasyAudio::Initialize())
        {
            return 1;
        }

        return 0;
    }

    /**
    * サウンドマネージャーを更新
    */
    void SoundManager::Update()
    {

        // リスナーが存在していたら更新する
        if (audioListner)
        {
            audioListner->PosUpdate();
        }
        // 音声ライブラリを更新
        EasyAudio::Update();
    }

    /**
    * サウンドマネージャーを終了
    */
    void SoundManager::Fainalize()
    {
        // 音声ライブラリを終了
        EasyAudio::Finalize();
    }

    int SoundManager::AudioIdAdd()
    {
        audioIdList++;
        return audioIdList;
    }
}
