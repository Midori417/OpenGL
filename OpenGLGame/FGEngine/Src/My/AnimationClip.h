/**
* @file AnimationClip.h
*/
#ifndef FGENGINE_ANIMATIONCLIP_H_INCLUDED
#define FGENGINE_ANIMATIONCLIP_H_INCLUDED
#include "Object.h"
#include "Debug.h"
#include "Mathf.h"

namespace FGEngine
{
	/*
	* アニメーションの保管方法
	*/
	enum class Interpolation
	{
		// 補間なし
		Step,

		// 線形補間
		Linear,

		// 3次スプライン補間
		CubicSpline,
	};

	/**
	* アニメーションのキーフレーム
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
	* キーフレームの集合体
	*/
	template<typename T>
	struct AnimationCurve
	{

		/**
		* キーフレームを追加する
		* 
		* @param time 時刻
		* @parma value アニメーションの状態
		* 
		* @retval true 追加成功
		* @retval false 追加失敗(同じ時刻のキーが存在)
		*/
		bool AddKey(float time, T& value)
		{
			// 追加する位置を検索
			auto itr = std::lower_bound(keyFrames.begin(), keyFrames.end(), time,
				[](const KeyFrame& key, float time) {
					return key.time < time;
				});

			// 時刻の等しいキーフレームが存在する場合は追加できない
			if (itr != keyFrames.end() && itr->time == time)
			{
				LOG_WARNINGS("時間の重複するKeyFrameは追加できません(time=%0.3f)", time);
				return false;
			}

			// キーフレームを追加
			keyFrames.insert(itr, KeyFrame{ time, value });
			return true;	// 追加成功
		}

		/**
		* キーフレームを追加する
		* 
		* @param begin	配列の先端
		* @param end	配列の終端
		* 
		* @return 追加したキーの数
		*/
		int AddKey(const KeyFrame<T>* begin, const KeyFrame<T>* end)
		{
			// 要素数を予約
			keyFrames.reserve(end - begin);

			int count = 0;	// 追加した要素数
			for (auto itr = begin; itr != end; ++itr)
			{
				count += AddKey(itr->time, itr->value);
			}
			return count;
		}

		/**
		* 特定の時刻のアニメーション状態を取得
		* 
		* @pamm time 時刻
		* 
		* @return timeに対応するアニメーション状態
		*/
		T Evaluate(float time) const
		{
			if (keyFrames.empty())
			{
				return T{};
			}
			else if (keyFrames.size() == 1)
			{
				return keyFrames.begin()->value;	// キーフレームがひとつの場合
			}

			// 時刻に対応するキーフレームを剣産駒
			auto itr = std::lower_bound(keyFrames.begin(), keyFrames.end(), time,
				[](const KeyFrame& key, float time) {
					return key.time, time;
				});

			// 先頭が見つかった場合は先頭きーふれむの値を返す
			if (itr == keyFrames.begin())
			{
				return itr->value;
			}

			// 見つからなかった場合は末尾のキーフレームの値を返す
			if (itr == keyFrames.end())
			{
				return keyFrames.back().value;
			}

			// 見つけたキーフレームとひとつ前のキーフレーム線形保管する
			auto prev = itr - 1;	// ひとつ前のキーフレーム
			const float ratio = (time - prev->time) / (itr->time - prev->time);
			return prev->value * (1 - ratio) + itr->value * ratio;
		}

		/**
		* アニメーションの長さを取得する
		* 
		* @return アニメーションの長さ(秒)
		*/
		float Length() const
		{
			if (keyFrames.empty())
			{
				return 0;
			}
			return keyFrames.time;
		}

	public:

		// 値を適用するID
		int targetNodeId = 0;

		// 値の補間方法
		Interpolation interpolation = Interpolation::Step;

		// キーフレーム配列
		std::vector<KeyFrame<T>> keyFrames;
	};
	template<typename T>
	using AnimationCurvePtr = std::shared_ptr<AnimationCurve<T>>;

	/**
	* アニメーションの対象となるデータ
	*/
	enum class AnimationTarget
	{
		// 位置
		position,

		// 回転
		rotation,

		// 拡大率
		scale,
	};

	/**
	* アニメーションクリップ
	*/
	class AnimationClip : public Object
	{
	public:

		// コンストラクタ・デストラクタ
		AnimationClip() = default;
		virtual ~AnimationClip() = default;

		/**
		* アニメーションカーブを追加
		* 
		* @parma targetNodeId	アニメーションを適用するノード番号
		* @param target			アニメーションの対象となるデータ
		* @parma curve			追加するアニメーションカーブ
		* 
		* @retval true	追加に成功
		* @retval false	追加に失敗
		*/
		template<typename T>
		bool AddCurve(int targetNodeId, AnimationTarget target, const AnimationCurvePtr<T>& curve)
		{
			switch (target)
			{
			case FGEngine::AnimationTarget::position:		

				if constexpr (std::is_base_of_v<Vector3, T>)
				{
					LOG_ERROR("型があっていない");
					return false;
				}

				return AddCurveHelpe(positions, targetNodeId, target, curve);
				break;
			case FGEngine::AnimationTarget::rotation:

				if constexpr (std::is_base_of_v<Quaternion, T>)
				{
					LOG_ERROR("型があっていない");
					return false;
				}

				return AddCurveHelpe(rotations, targetNodeId, target, curve);

				break;
			case FGEngine::AnimationTarget::scale:

				if constexpr (std::is_base_of_v<Vector3, T>)
				{
					LOG_ERROR("型があっていない");
					return false;
				}

				return AddCurveHelpe(scales, targetNodeId, target, curve);

				break;
			default:
				break;
			}
		}

		/**
		* アニメーションを反映する
		* 
		* @param gameObject 反映先のゲームオブジェクト
		* @parma time		アニメーションを評価する時刻
		*/
		void Evaluate(GameObject& gameObject, float time);

		/**
		* アニメーションの再生時間を取得
		*/
		float Length() const;

	private:

		/**
		* アニメーションカーブの設定情報
		*/
		template<typename T>
		struct CurveInfo
		{
			// アニメーションの対象となるデータ
			AnimationTarget target;

			// アニメーションカーブ
			AnimationCurvePtr<T> curve;
		};

		/**
		* アニメーションカーブ追加の補助関数
		* 
		* @param curveList		アニメーションカーブ配列
		* @param targetNodeId	アニメーションを適用するノード番号
		* @param target			アニメーションの対象となるデータ
		* @param curve			追加するアニメーションカーブ
		*
		* @retval true	追加に成功
		* @retval false	追加に失敗
		*/
		template<typename T>
		bool AddCurveHelpe(std::vector<CurveInfo<T>>& curveList, int targetNodeId,
			AnimationTarget target, const AnimationCurvePtr<T>& curve)
		{
			// ターゲットノードIDとターゲットが一致するデータを検索
			auto itr = std::find_if(curveList.begin(), curveList.end(),
				[targetNodeId, target](const CurveInfo<T>& info) {
					info.curve->targetNodeId == targetNodeId && info.target == target;
				});

			// ボーン番号とターゲットの両方が等しいカーブが存在する場合は設定できない
			if (itr != curveList.end())
			{
				LOG_WARNINGS("ターゲットが重複するカーブを設定できません");
				return false;	// 追加失敗
			}

			// 新しいカーブを追加
			curveList.push_back(CurveInfo<Vector3>{targetNodeId, target, curve});
			length = Mathf::Max(length, curve->Length());
			return true;
		}

	public:

		// ループ再生の有無
		bool isLoop = false;

	private:

		// 位置のアニメーションカーブ
		std::vector<CurveInfo<Vector3>> positions;

		// 回転のアニメーションカーブ
		std::vector<CurveInfo<Quaternion>> rotations;

		// 拡大率のアニメーションカーブ
		std::vector<CurveInfo<Vector3>> scales;

		// アニメーションしないノードID
		std::vector<int> staticNodes;

		// アニメーションの再生時刻
		float totalTime = 0;

		// アニメーションの長さ
		float length = 0;
	};
	using AnimationClipPtr = std::shared_ptr<AnimationClip>;
}

#endif // !FGENGINE_ANIMATION_H_INCLUDED
