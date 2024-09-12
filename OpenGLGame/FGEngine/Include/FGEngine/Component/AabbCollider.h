/**
* @file AabbCollider.h
*/
#ifndef FGENGINE_AABBCOLLIDER_H_INCLUDED
#define FGENGINE_AABBCOLLIDER_H_INCLUDED
#include "Collider.h"

namespace FGEngine
{
	/**
	* 軸平行ボックスコライダー
	*/
	class AabbCollider : public Collider
	{
	public:

		// コンストラクタ・デストラクタ
		AabbCollider() = default;
		virtual ~AabbCollider() = default;

		/**
		* コライダーのタイプを取得
		*/
		virtual CollisionType GetType() const;

		/**
		* 図形を取得する
		*/
		const AABB& GetShape() const;

		/**
		* 座標を変更する
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
		virtual ColliderPtr GetTransformedCollider(const Matrix4x4& transform) const;

	public:

		virtual ComponentPtr Clone() const override;

	public:

		// 最小値
		Vector3 min = Vector3(-1);

		// 最大値
		Vector3 max = Vector3(1);

	private:

		// 図形
		AABB aabb;
	};
}

#endif // !FGENGINE_AABBCOLLIDER_H_INCLUDED
