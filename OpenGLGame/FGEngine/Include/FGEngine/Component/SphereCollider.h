/**
* @file SphereCollider.h
*/
#ifndef FGENGINE_SPHERECOLLIDER_H_INCLUDED
#define FGENGINE_SPHERECOLLIDER_H_INCLUDED
#include "Collider.h"

namespace FGEngine
{
	/**
	* スフィアコライダー
	*/
	class SphereCollider : public Collider
	{
	public:

		// コンストラクタ・デストラクタ
		SphereCollider() = default;
		virtual ~SphereCollider() = default;

		/**
		* コリジョンタイプを取得
		*/
		virtual CollisionType GetType() const;

		/**
		* 図形を取得
		*/
		const Sphere& GetShape() const;

		/**
		* 図形を変更する
		* 
		* @param translate 移動量
		*/
		virtual void AddPosition(const Vector3& translate) override;

		/**
		* 座標変換したコライダーを取得する
		*
		* @param transform 変換する座標変換行列
		*
		* @return 変換したコライダーコンポーネント
		*/
		virtual ColliderPtr GetTransformedCollider(const Matrix4x4& transform) const override;

	public:

		virtual ComponentPtr Clone() const override;

	public:

		// オブジェクトのローカル座標でのコライダーの中心座標
		Vector3 ceneter = Vector3::zero;

		// オブジェクトのロカールサイズのコライダーの半径
		float radius = 1;

	private:

		// 図形
		Sphere sphere;
	};
}

#endif // !FGENGINE_SPHERECOLLIDER_H_INCLUDED
