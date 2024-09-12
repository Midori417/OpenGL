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
	* アニメーションを再生
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
	* アニメーションを停止
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
	* アニメーションを一時停止
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
	* アニメーションの状態を取得
	*/
	Animator::AnimationState Animator::GetAnimState() const
	{
		return state;
	}

	/**
	* アニメーションを指定
	*
	* @param animClip	アニメーションクリップ
	* @parma isLoop		ループの有無
	*
	* @retval true	設定成功
	* @retval false	設定失敗
	*/
	bool Animator::SetAnimation(const AnimationClipPtr& animClip, bool isLoop)
	{
		// 同じアニメータが指定された場合は何もしない
		if (this->animationClip == animClip)
		{
			return true;
		}

		// アニメーションを設定
		this->animationClip = animClip;

		// 状態を「停止中」に設定
		time = 0;
		state = AnimationState::Stop;
		this->isLoop = isLoop;

		return true;
	}

	/**
	* アニメーションを指定
	*
	* @param animName	アニメーションの名前
	* @parma isLoop		ループの有無
	*
	* @retval true	設定成功
	* @retval false	設定失敗
	*/
	bool Animator::SetAnimation(const std::string& animName, bool isLoop)
	{
		// アニメーション配列が存在しない
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
	* 再生中のアニメーションを取得
	*/
	const AnimationClipPtr& Animator::GetAnimationClip() const
	{
		return animationClip;
	}

	/**
	* アニメータのクローンを作成
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
	* アニメータを更新
	*/
	void Animator::Update()
	{
		// アニメーション配列または再生アニメーションがない場合は何もしない
		if (animationClips.empty() || !animationClip)
		{
			return;
		}

		// アニメーションの状態を更新
		switch (state)
		{
		case FGEngine::Animator::AnimationState::Stop:
			break;
		case FGEngine::Animator::AnimationState::Play:

			// 再生時刻を更新
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