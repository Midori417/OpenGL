/**
* @file SoundMnager.h
*/
#ifndef FGENGINE_SOUNDMANAGER_H_INCLUDED
#define FGENGINE_SOUNDMANAGER_H_INCLUDED
#include "FGEngine/Singleton.h"
#include "FGEngine/SystemFrd.h"

namespace FGEngine
{
	class AudioListner;
	using AudioListnerPtr = std::shared_ptr<AudioListner>;
	class AudioSource;
	namespace SoundSystem
	{
		/**
		* �T�E���h�Ǘ��N���X
		*/
		class SoundManager : public Singleton<SoundManager>
		{
		public:

			friend Singleton<SoundManager>;
			friend MainSystem::EngineCore;
			friend AudioSource;

			// �R���X�g���N�^�E�f�X�g���N�^
			SoundManager() = default;
			virtual ~SoundManager() = default;

			/**
			* ���X�i�[��ݒ�
			*/
			void SetListner(const AudioListnerPtr audioListner);

			/**
			* ���X�i�[���擾
			*/
			AudioListnerPtr GetListner() const;

			/**
			* �}�X�^�[�{�����[����ݒ�
			*
			* @param volume �ݒ肷�鉹��
			*/
			void SetMasterVolume(float volume);

			/**
			* �}�X�^�[�{�����[�����擾
			*
			* @return �}�X�^�[�{�����[��
			*/
			float GetMasterVolume() const;

		private:

			/**
			* �T�E���h�}�l�[�W���[��������
			*
			* @retval true	����������
			* @retval false	���������s
			*/
			int Inititalize();

			/**
			* �T�E���h�}�l�[�W���[���X�V
			*/
			void Update();

			/**
			* �T�E���h�}�l�[�W���[���I��
			*/
			void Fainalize();

			int AudioIdAdd();

		private:

			// ���݂̃��X�i�[
			AudioListnerPtr audioListner;

			int audioIdList = -1;
		};
	}
}
#endif // !FGENGINE_SOUNDMANAGER_H_INCLUDED
