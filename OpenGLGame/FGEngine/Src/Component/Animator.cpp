/**
* @file Animator.cpp
*/
#include "FGEngine/Component/Animator.h"
#include "FGEngine/Other/Time.h"
#include "FGEngine/Asset/AnimationClip.h"
#include "FGEngine/Math/Mathf.h"
#include <cmath>

namespace FGEngine
{
	/**
	* �A�j���[�V�������Đ�
	*/
	void Animator::Play()
	{
		switch (state)
		{
		case FGEngine::Animator::AnimationState::Stop:
			time = 0;
			state = AnimationState::Play;
			break;
		case FGEngine::Animator::AnimationState::Play:
			break;
		case FGEngine::Animator::AnimationState::Pause:
			state = AnimationState::Play;
			break;
		}
	}

	/**
	* �A�j���[�V�������~
	*/
	void Animator::Stop()
	{
		switch (state)
		{
		case FGEngine::Animator::AnimationState::Stop:
			break;
		case FGEngine::Animator::AnimationState::Play:
			state = AnimationState::Stop;
			break;
		case FGEngine::Animator::AnimationState::Pause:
			state = AnimationState::Stop;
			break;
		}
	}

	/**
	* �A�j���[�V�������ꎞ��~
	*/
	void Animator::Pause()
	{
		switch (state)
		{
		case FGEngine::Animator::AnimationState::Stop:
			break;
		case FGEngine::Animator::AnimationState::Play:
			state = AnimationState::Pause;
			break;
		case FGEngine::Animator::AnimationState::Pause:
			break;
		}
	}

	/**
	* �A�j���[�V�����̏�Ԃ��擾
	*/
	Animator::AnimationState Animator::GetAnimState() const
	{
		return state;
	}

	/**
	* �A�j���[�V�������w��
	*
	* @param animClip	�A�j���[�V�����N���b�v
	* @parma isLoop		���[�v�̗L��
	*
	* @retval true	�ݒ萬��
	* @retval false	�ݒ莸�s
	*/
	bool Animator::SetAnimation(const AnimationClipPtr& animClip, bool isLoop)
	{
		// �����A�j���[�^���w�肳�ꂽ�ꍇ�͉������Ȃ�
		if (this->animationClip == animClip)
		{
			return true;
		}

		// �A�j���[�V������ݒ�
		this->animationClip = animClip;

		// ��Ԃ��u��~���v�ɐݒ�
		time = 0;
		state = AnimationState::Stop;
		this->isLoop = isLoop;

		return true;
	}

	/**
	* �A�j���[�V�������w��
	*
	* @param animName	�A�j���[�V�����̖��O
	* @parma isLoop		���[�v�̗L��
	*
	* @retval true	�ݒ萬��
	* @retval false	�ݒ莸�s
	*/
	bool Animator::SetAnimation(const std::string& animName, bool isLoop)
	{
		// �A�j���[�V�����z�񂪑��݂��Ȃ�
		if (animationClips.empty())
		{
			return false;
		}
		for (const auto& x : animationClips)
		{
			if (x->name == animName)
			{
				return SetAnimation(x, isLoop);
			}
		}

		return false;
	}

	/**
	* �Đ����̃A�j���[�V�������擾
	*/
	const AnimationClipPtr& Animator::GetAnimationClip() const
	{
		return animationClip;
	}

	/**
	* �A�j���[�^�̃N���[�����쐬
	*/
	ComponentPtr Animator::Clone() const
	{
		AnimatorPtr p = std::make_shared<Animator>();

		p->time = this->time;
		p->animationSpeed = this->animationSpeed;
		p->isLoop = this->isLoop;
		p->animationClips = this->animationClips;

		p->state = this->state;
		p->animationClip = this->animationClip;

		return p;
	}

	/**
	* �A�j���[�^���X�V
	*/
	void Animator::Update()
	{
		// �A�j���[�V�����z��܂��͍Đ��A�j���[�V�������Ȃ��ꍇ�͉������Ȃ�
		if (animationClips.empty() || !animationClip)
		{
			return;
		}

		// �A�j���[�V�����̏�Ԃ��X�V
		switch (state)
		{
		case FGEngine::Animator::AnimationState::Stop:
			break;
		case FGEngine::Animator::AnimationState::Play:

			// �Đ��������X�V
			time += animationSpeed * Time::DeltaTime();
			if (isLoop)
			{
				time -= animationClip->totalTime * std::floorf(time / animationClip->totalTime);
			}
			else
			{
				time = Mathf::Clamp(time, 0.0f, animationClip->totalTime);
				if (time >= animationClip->totalTime)
				{
					state = AnimationState::Stop;
				}
			}

			break;
		case FGEngine::Animator::AnimationState::Pause:
			break;
		}
	}
}