/**
* @file Transform.h
*/
#ifndef FGENGINE_TRANSFORM_H_INCLUDED
#define FGENGINE_TRANSFORM_H_INCLUDED
#include "Component.h"
#include "FGEngine/Math/Vector3.h"
#include "FGEngine/Math/Quaternion.h"
#include "FGEngine/Math/Matrix3x3.h"
#include "FGEngine/Math/Matrix4x4.h"

namespace FGEngine
{
	/**
	* オブジェクトの位置、回転、拡大縮小を扱うコンポーネント
	*/
	class Transform : public Component
	{
		friend Scene;
	public:

		// コンストラクタ・デストラクタ
		Transform() = default;
		virtual ~Transform() = default;

	public:	// 方向ベクトルの取得

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

	public:

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
		void LookAt(const Transform* target, const Vector3& worldUp = Vector3::up);
		void LookAt(const TransformPtr target, const Vector3& worldUp = Vector3::up);

	public:		// 親子

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

	public:	// 座標行列

		/**
		* ローカル座標変換行列を取得
		*/
		Matrix4x4 GetLocalTransformMatrix() const;

		/**
		* ワールド座標行列を取得
		*/
		Matrix4x4 GetWorldTransformMatrix() const;

		/**
		* 法線行列を取得
		*/
		Matrix3x3 GetNormalMatrix() const;

	private:

		/**
		* ローカル座標変換行列を更新
		*/
		void LocalTransformUpdate();

	public:

		// 位置
		Vector3 position = Vector3::zero;

		// 回転
		Quaternion rotation = Quaternion::identity;

		// 拡大縮小
		Vector3 scale = Vector3::one;

	private:

		// ローカル座標行列
		Matrix4x4 localTransformMatrix = Matrix4x4(1);

		// ワールド座標行列
		Matrix4x4 worldTransformMatrix = Matrix4x4(1);

		// 法線変換行列
		Matrix3x3 normalMatrix = Matrix3x3(1);

		// 親オブジェクトのTransfoom
		std::weak_ptr<Transform> parent;

		// 子オブジェクトのTransform
		std::vector<std::weak_ptr<Transform>> childrens;
	};
}

#endif // !FGENGINE_TRANSFORM_H_INCLUDED
