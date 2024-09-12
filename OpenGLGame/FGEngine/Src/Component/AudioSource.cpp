/**
* @file AudioSource.cpp
*/
#include "FGEngine/Component/AudioSource.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Audio/EasyAudio.h"
#include "FGEngine/MainSystem/SoundManager.h"

namespace FGEngine
{
	/**
	* オーディオIDを設定
	*/
	void AudioSource::SetAudioId(int id)
	{
		this->id = id;
	}

	/**
	* サウンドを再生
	*/
	void AudioSource::Play()
	{
		if (filename != "NoFile")
		{
			EasyAudio::Play(id, filename.c_str(), volume, isLooop);
			if (is3DSound)
			{
				EasyAudio::SetPanAndVolumeFromPosition(id, GetTransform()->position, volume);
			}
		}
	}

	/**
	* サウンドを停止
	*/
	void AudioSource::Stop()
	{
		EasyAudio::Stop(id);
	}

	/**
	* サウンドを一時停止
	*/
	void AudioSource::Pause()
	{
		EasyAudio::Pause(id);
	}

	/**
	* サウンドを再開(一時停止を解除)
	*/
	void AudioSource::Resume()
	{
		EasyAudio::Resume(id);
	}

	/**
	* サウンドを単発再生
	*
	* @param filename 再生するサウンドのファイル
	*/
	void AudioSource::PlayOneShot(const char* filename)
	{
		EasyAudio::PlayOneShot(filename, volume, picth);
	}

	/**
	* サウンドファイル名を設定
	*/
	void AudioSource::SetSoundFilename(const std::string& filename)
	{
		this->filename = filename;
	}

	/**
	* サウンドファイル名を設定
	*/
	void AudioSource::SetSoundFilename(const char* filename)
	{
		this->filename = filename;
	}

	/**
	* 音量の設定
	*/
	void AudioSource::SetVolume(float volume)
	{
		this->volume = volume;
		EasyAudio::SetVolume(id, this->volume);
	}

	/**
	* 音量を取得
	*/
	float AudioSource::GetVolume()
	{
		return volume;
	}

	/**
	* ピッチを設定
	*/
	void AudioSource::SetPitch(float pitch)
	{
		this->picth = pitch;
		EasyAudio::SetPitch(id, this->picth);
	}

	/**
	* ピッチを取得
	*/
	float AudioSource::GetPitch()
	{
		return picth;
	}

	/**
	* パンを設定
	*/
	void AudioSource::SetPan(float pan)
	{
		this->pan = pan;
		EasyAudio::SetPan(id, this->pan);
	}

	/**
	* パンを取得
	*/
	float AudioSource::GetPan()
	{
		return pan;
	}

	ComponentPtr AudioSource::Clone() const
	{
		AudioSourcePtr p = std::make_shared<AudioSource>();

		p->filename = this->filename;
		p->id = this->id;
		p->volume = this->volume;
		p->picth = this->picth;
		p->pan = this->pan;
		p->is3DSound = this->is3DSound;
		p->isLooop = this->isLooop;
		
		return p;
	}

	void AudioSource::Awake()
	{
		id = SoundManager::GetInstance()->AudioIdAdd();
	}

	void AudioSource::Set3DSoundPos()
	{
		if (is3DSound)
		{
			EasyAudio::SetPanAndVolumeFromPosition(id, GetTransform()->position, volume);
		}
	}

}
