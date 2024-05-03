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
	* アニメーション制御コンポーネント
	*/
	class Animator : public Component
	{
		friend ObjectSystem::ObjectManager;
	public:

		// コンストラクタ・デストラクタ
		Animator() = default;
		virtual ~Animator() = default;

		/**
		* アニメーションの再生状態
		*/
		enum class AnimationState
		{
			// 停止
			Stop,

			// 再生
			Play,

			// 一時停止
			Pause,
		};

		/**
		* アニメーションを再生
		*/
		void Play();

		/**
		* アニメーションを停止
		*/
		void Stop();

		/**
		* アニメーションを一時停止
		*/
		void Pause();

		/**
		* アニメーションの状態を取得
		*/
		AnimationState GetAnimState() const;

		/**
		* アニメーションを指定
		*
		* @param animClip	アニメーションクリップ
		* @parma isLoop		ループの有無
		*
		* @retval true	設定成功
		* @retval false	設定失敗
		*/
		bool SetAnimation(const AnimationClipPtr& animClip, bool isLoop = false);

		/**
		* アニメーションを指定
		*
		* @param animName	アニメーションの名前
		* @parma isLoop		ループの有無
		*
		* @retval true	設定成功
		* @retval false	設定失敗
		*/
		bool SetAnimation(const std::string& animName, bool isLoop = false);

		/**
		* 再生中のアニメーションを取得
		*/
		const AnimationClipPtr& GetAnimationClip() const;

	private:

		/**
		* アニメータを更新
		*/
		void Update();

	public:

		// 現在の再生時間
		float time = 0;

		// アニメーションの再生スピード
		float animationSpeed = 1;

		// ループ再生
		bool isLoop = false;

		// アニメーション配列
		std::vector<AnimationClipPtr> animationClips;

	private:

		// アニメーションの状態
		AnimationState state = AnimationState::Stop;

		// アニメーションクリップ
		AnimationClipPtr animationClip;

	};
	using AnimatorPtr = std::shared_ptr<Animator>;
}

#endif // !FGEGNIEN_ANIMATOR_H_INCLUDED
