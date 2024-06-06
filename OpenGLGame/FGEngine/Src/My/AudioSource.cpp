/**
* @file AudioSource.cpp
*/
#include "AudioSource.h"
#include "EasyAudio/EasyAudio.h"
#include "Transform.h"
#include "SoundManager.h"

namespace FGEngine
{
	/**
	* �I�[�f�B�IID��ݒ�
	*/
	void AudioSource::SetAudioId(int id)
	{
		this->id = id;
	}

	/**
	* �T�E���h���Đ�
	*/
	void AudioSource::Play()
	{
		if (filename != "NoFile")
		{
			EasyAudio::Play(id, filename.c_str(), volume, isLooop);
		}
	}

	/**
	* �T�E���h���~
	*/
	void AudioSource::Stop()
	{
		EasyAudio::Stop(id);
	}

	/**
	* �T�E���h���ꎞ��~
	*/
	void AudioSource::Pause()
	{
		EasyAudio::Pause(id);
	}

	/**
	* �T�E���h���ĊJ(�ꎞ��~������)
	*/
	void AudioSource::Resume()
	{
		EasyAudio::Resume(id);
	}

	/**
	* �T�E���h��P���Đ�
	*
	* @param filename �Đ�����T�E���h�̃t�@�C��
	*/
	void AudioSource::PlayOneShot(const char* filename)
	{
		EasyAudio::PlayOneShot(filename, volume, picth);
	}

	/**
	* �T�E���h�t�@�C������ݒ�
	*/
	void AudioSource::SetSoundFilename(const std::string& filename)
	{
		this->filename = filename;
	}

	/**
	* �T�E���h�t�@�C������ݒ�
	*/
	void AudioSource::SetSoundFilename(const char* filename)
	{
		this->filename = filename;
	}

	/**
	* ���ʂ̐ݒ�
	*/
	void AudioSource::SetVolume(float volume)
	{
		this->volume = volume;
		EasyAudio::SetVolume(id, this->volume);
	}

	/**
	* ���ʂ��擾
	*/
	float AudioSource::GetVolume()
	{
		return volume;
	}

	/**
	* �s�b�`��ݒ�
	*/
	void AudioSource::SetPitch(float pitch)
	{
		this->picth = pitch;
		EasyAudio::SetPitch(id, this->picth);
	}

	/**
	* �s�b�`���擾
	*/
	float AudioSource::GetPitch()
	{
		return picth;
	}

	/**
	* �p����ݒ�
	*/
	void AudioSource::SetPan(float pan)
	{
		this->pan = pan;
		EasyAudio::SetPan(id, this->pan);
	}

	/**
	* �p�����擾
	*/
	float AudioSource::GetPan()
	{
		return pan;
	}

	void AudioSource::Awake()
	{
		id = SoundSystem::SoundManager::GetInstance()->AudioIdAdd();
	}

	void AudioSource::Set3DSoundPos()
	{
		if (is3DSound)
		{
			EasyAudio::SetPanAndVolumeFromPosition(id, GetTransform()->position, volume);
		}
	}

}
