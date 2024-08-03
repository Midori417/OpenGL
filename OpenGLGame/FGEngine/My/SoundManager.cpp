/**
* @file SoundManager.cpp
*/
#include "SoundManager.h"
#include "EasyAudio/EasyAudio.h"
#include "AudioListner.h"

namespace FGEngine::SoundSystem
{
    /**
    * ���X�i�[��ݒ�
    */
    void SoundManager::SetListner(const AudioListnerPtr audioListner)
    {
        this->audioListner = audioListner;
    }
    
    /**
    * ���X�i�[���擾
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
    * �}�X�^�[�{�����[����ݒ�
    *
    * @param volume �ݒ肷�鉹��
    */
    void SoundManager::SetMasterVolume(float volume)
    {
        EasyAudio::SetMasterVolume(volume);
    }

    /**
    * �}�X�^�[�{�����[�����擾
    *
    * @return �}�X�^�[�{�����[��
    */
    float SoundManager::GetMasterVolume() const
    {
        return EasyAudio::GetMasterVolume();
    }
    /**
    * �T�E���h�}�l�[�W���[��������
    *
    * @retval true	����������
    * @retval false	���������s
    */
    int SoundManager::Inititalize()
    {
        // �������C�u������������
        if (!EasyAudio::Initialize())
        {
            return 1;
        }

        return 0;
    }

    /**
    * �T�E���h�}�l�[�W���[���X�V
    */
    void SoundManager::Update()
    {

        // ���X�i�[�����݂��Ă�����X�V����
        if (audioListner)
        {
            audioListner->PosUpdate();
        }
        // �������C�u�������X�V
        EasyAudio::Update();
    }

    /**
    * �T�E���h�}�l�[�W���[���I��
    */
    void SoundManager::Fainalize()
    {
        // �������C�u�������I��
        EasyAudio::Finalize();
    }

    int SoundManager::AudioIdAdd()
    {
        audioIdList++;
        return audioIdList;
    }
}
