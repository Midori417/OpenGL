/**
* @file Animator.h
*/
#ifndef FGENGINE_ANIMATOR_H_INCLUDED
#define FGENGINE_ANIMATOR_H_INCLUDED
#include "Component.h"

namespace FGEngine
{
	struct AnimationClip;
	using AnimationClipPtr = std::shared_ptr<AnimationClip>;

	/**
	* �A�j���[�V��������R���|�[�l���g
	*/
	class Animator : public Component
	{
		friend ObjectSystem::ObjectManager;
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		Animator() = default;
		virtual ~Animator() = default;

		/**
		* �A�j���[�V�����̍Đ����
		*/
		enum class AnimationState
		{
			// ��~
			Stop,

			// �Đ�
			Play,

			// �ꎞ��~
			Pause,
		};

		/**
		* �A�j���[�V�������Đ�
		*/
		void Play();

		/**
		* �A�j���[�V�������~
		*/
		void Stop();

		/**
		* �A�j���[�V�������ꎞ��~
		*/
		void Pause();

		/**
		* �A�j���[�V�����̏�Ԃ��擾
		*/
		AnimationState GetAnimState() const;

		/**
		* �A�j���[�V�������w��
		*
		* @param animClip	�A�j���[�V�����N���b�v
		* @parma isLoop		���[�v�̗L��
		*
		* @retval true	�ݒ萬��
		* @retval false	�ݒ莸�s
		*/
		bool SetAnimation(const AnimationClipPtr& animClip, bool isLoop = false);

		/**
		* �A�j���[�V�������w��
		*
		* @param animName	�A�j���[�V�����̖��O
		* @parma isLoop		���[�v�̗L��
		*
		* @retval true	�ݒ萬��
		* @retval false	�ݒ莸�s
		*/
		bool SetAnimation(const std::string& animName, bool isLoop = false);

		/**
		* �Đ����̃A�j���[�V�������擾
		*/
		const AnimationClipPtr& GetAnimationClip() const;

	private:

		/**
		* �A�j���[�^���X�V
		*/
		void Update();

	public:

		// ���݂̍Đ�����
		float time = 0;

		// �A�j���[�V�����̍Đ��X�s�[�h
		float animationSpeed = 1;

		// ���[�v�Đ�
		bool isLoop = false;

		// �A�j���[�V�����z��
		std::vector<AnimationClipPtr> animationClips;

	private:

		// �A�j���[�V�����̏��
		AnimationState state = AnimationState::Stop;

		// �A�j���[�V�����N���b�v
		AnimationClipPtr animationClip;

	};
	using AnimatorPtr = std::shared_ptr<Animator>;
}

#endif // !FGEGNIEN_ANIMATOR_H_INCLUDED
