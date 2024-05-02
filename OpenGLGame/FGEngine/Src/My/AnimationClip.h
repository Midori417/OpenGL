/**
* @file AnimationClip.h
*/
#ifndef FGENGINE_ANIMATIONCLIP_H_INCLUDED
#define FGENGINE_ANIMATIONCLIP_H_INCLUDED
#include <string>
#include <vector>
#include <memory>
#include "VectorPoint.h"
#include "MatrixPoint.h"
#include "Quaternion.h"

namespace FGEngine
{
	/**
* アニメーションの値の保管方法
*/
	enum class GltfIterpolation
	{
		// 補間なし
		None,

		// 線形補間
		Linear,

		// 3次スプライン補間
		CubicSphline,
	};

	/**
	* アニメーションキーフレーム
	*/
	template<typename T>
	struct KeyFrame
	{
		// 時刻
		float time = 0;

		// 適応する値
		T value;
	};

	/**
	* アニメーションカーブ
	*/
	template<typename T>
	struct AnimationCurve
	{
		// 値を適用するノードId
		int targetNodeid = -1;

		// 補間方法
		GltfIterpolation interpolation = GltfIterpolation::None;

		// キーフレーム配列
		std::vector<KeyFrame<T>> keyFrames;
	};

	/**
	* アニメーションクリップ
	*/
	struct AnimationClip
	{
		// アニメーションクリップ名
		std::string name;

		// 廃坑移動チャネル配列
		std::vector<AnimationCurve<Vector3>> translations;

		// 回転チャネル配列
		std::vector<AnimationCurve<Quaternion>> rotations;

		// 拡大率チャネルの配列
		std::vector<AnimationCurve<Vector3>> scales;

		// アニメーションしないノードIDの配列
		std::vector<int> staticNodes;

		// アニメーション時間
		float totalTime = 0;
	};
	using AnimationClipPtr = std::shared_ptr<AnimationClip>;

}
#endif // !FGENGINE_ANIMATIONCLIP_H_INCLUDED
