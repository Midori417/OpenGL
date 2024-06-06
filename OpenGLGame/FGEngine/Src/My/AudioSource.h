/**
* @file AudioSource.h
*/
#ifndef FGENGINE_AUDIOSOURCE_H_INCLUDED
#define FGENGINE_AUDIOSOURCE_H_INCLUDED
#include "Component.h"

namespace FGEngine
{
	/**
	* �T�E���h��炷
	*/
	class AudioSource : public Component
	{
	public:

		friend GameObject;
		friend ObjectSystem::ObjectManager;

		// �R���X�g���N�^�E�f�X�g���N�^
		AudioSource() = default;
		virtual ~AudioSource() = default;

		/**
		* �I�[�f�B�IID��ݒ�
		*/
		void SetAudioId(int id);

		/**
		* �T�E���h���Đ�
		*/
		void Play();

		/**
		* �T�E���h���~
		*/
		void Stop();

		/**
		* �T�E���h���ꎞ��~
		*/
		void Pause();
		
		/**
		* �T�E���h���ĊJ(�ꎞ��~������)
		*/
		void Resume(); 

		/**
		* �T�E���h��P���Đ�
		* 
		* @param filename �Đ�����T�E���h�̃t�@�C��
		*/
		void PlayOneShot(const char* filename);

		/**
		* �T�E���h�t�@�C������ݒ�
		*/
		void SetSoundFilename(const std::string& filename);
		void SetSoundFilename(const char* filename);

		// ���ʂ̐ݒ�E�擾
		void SetVolume(float volume);
		float GetVolume();

		// �s�b�`�̐ݒ�E�擾
		void SetPitch(float pitch);
		float GetPitch();

		// �p���̐ݒ�E�擾
		void SetPan(float pan);
		float GetPan();

	private:

		void Awake();

		/**
		* ���̉����p�̍X�V
		*/
		void Set3DSoundPos();

	private:

		// �T�E���h�̃t�@�C����
		std::string filename = "NoFile";


		int id = -1;

		// ����
		float volume = 1;
		
		// �s�b�`
		float picth = 1;
		
		// �p��
		float pan = 0;

	public:

		// ���̉����̉e�����󂯂邩
		bool is3DSound = false;

		// ���[�v�Đ������邩true=���[�v�Đ�:false=���[�v�Đ����Ȃ�
		bool isLooop = true;
	};
}
#endif // !FGENGINE_AUDIOSOURCE_H_INCLUDED
