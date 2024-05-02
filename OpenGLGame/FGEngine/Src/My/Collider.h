/**
* @file Collider.h
*/
#ifndef FGENGINE_COLLIDER_H_INCLUDED
#define FGENGINE_COLLIDER_H_INCLUDED
#include "Component.h"

namespace FGEngine
{
	// 先行宣言
	class Rigidbody;
	using RigidbodyPtr = std::shared_ptr<Rigidbody>;
	class Collider;
	using ColliderPtr = std::shared_ptr<Collider>;

	/**
	* コライダーのタイプ
	*/
	enum class ColliderType
	{
		// 軸平行境界ボックス
		AABB,

		// 球体
		Sphere,

		// 有向境界ボックス
		Box,
	};

	/**
	* コライダーコンポーネント基底クラス
	*/
	class Collider : public Component
	{
	public:

		friend PhysicsSystem::PhysicsEngine;

		// コンストラクタ・デストラクタ
		Collider() = default;
		virtual ~Collider() = default;

	public:


		/**
		* コライダーのタイプを取得
		*/
		virtual ColliderType GetType() const = 0;

		/**
		* 座標を変更する
		* 
		* @param v 変更する値
		*/
		virtual void AddPosition(const Vector3& translate) = 0;

		/**
		* 座標変換したコライダーを取得する
		*
		* @param transform 変換する座標変換行列
		*
		* @return 変換したコライダーコンポーネント
		*/
		virtual ColliderPtr GetTransformedCollider(const Matrix4x4& transform) const = 0;

		/**
		* オーナーゲームオブジェクトのRigidbodyを取得
		* 
		* @return オーナーのRigidbody
		*/
		RigidbodyPtr GetAttachedRigidbody() const;

	public:

		// 有効か無効化
		bool enabled = true;

		// 貫通するかの有無
		bool isTrigger = false;

	private:

		// 前回のフレームで衝突しているか
		bool old = false;
	};
}

#endif // !FGENGINE_COLLIDER_H_INCLUDED
