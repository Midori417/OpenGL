/**
* @file Transform.h
*/
#ifndef FGENGINE_TRANSFORM_H_INCLUDED
#define FGENGINE_TRANSFORM_H_INCLUDED
#include "Component.h"

namespace FGEngine
{
	/**
	* オブジェクトの位置、回転、拡大縮小を扱うコンポーネント
	*/
	class Transform : public Component
	{
	public:

		// コンストラクタ・デストラクタ
		Transform() = default;
		virtual ~Transform() = default;

		/**
		* 前方ベクトルを取得
		*/
		Vector3 Forward() const;

		/**
		* 右方ベクトルを取得
		*/
		Vector3	Right() const;

		/**
		* 上方ベクトルを取得
		*/
		Vector3 Up() const;

		/**
		* 位置と回転を設定する
		* 
		* @param pos 位置
		* @param rot 回転
		*/
		void SetPositionAndRotation(const Vector3& pos, const Quaternion& rot);

		/**
		* translationの方向と距離に移動する
		* 
		* @param translation 移動する方向と距離
		*/
		void Translate(const Vector3& translation);

		/**
		* オイラー角を取得
		*/
		Vector3 GetEulerAngle() const;

		/**
		* 現在の角度からeuler加算する
		* 
		* @param euler 回転量(オイラー角)
		*/
		void Rotate(const Vector3& eulers);

		/**
		* 対象のTransformを設定し、その方向へ向く
		* 
		* @param target		向ける対象オブジェクトのTransform
		* @param worldUp	上方ベクトル
		*/
		void LookAt(const TransformPtr target, const Vector3& worldUp = Vector3::up);

		/**
		* 親Transformを設定する
		* 
		* @param parent 設定する親のTransform
		*/
		void SetParent(const TransformPtr parent);

		/**
		* 親Transformを取得する
		*/
		TransformPtr GetParent() const;

		/**
		* 子オブジェクトの数を取得する
		*/
		size_t GetChildrenCount() const;

		/**
		* indexから子のTransformを取得する
		* 
		* @param 子Transformのindex
		*/
		TransformPtr GetChildren(size_t index) const;

		/**
		* 全ての子オブジェクトを切り離す
		*/
		void AllChildrenPurge();



	public:

		// 位置
		Vector3 position = Vector3::zero;

		// 回転
		Quaternion rotation = Quaternion::identity;

		// 拡大縮小
		Vector3 scale = Vector3::one;

	private:

		// ワールド座標からローカル座標に変換した行列
		Matrix4x4 worldToLocalMatrix = Matrix4x4(1);

		// 親オブジェクトのTransfoom
		std::weak_ptr<Transform> parent;

		// 子オブジェクトのTransform
		std::vector<std::weak_ptr<Transform>> childrens;
	};
}

#endif // !FGENGINE_TRANSFORM_H_INCLUDED
