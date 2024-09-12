/**
* @file BoxCollider.h
*/
#ifndef FGENGINE_BOXCOLLIDER_H_INCLUDED
#define FGENGINE_BOXCOLLIDER_H_INCLUDED
#include "Collider.h"

namespace FGEngine
{
	/**
	* ボックスコライダー
	*/
	class BoxCollider : public Collider
	{
	public:

		// コンストラクタ・デストラクタ
		BoxCollider() = default;
		virtual ~BoxCollider() = default;

		/**
		* コリジョンタイプを取得
		*/
		virtual CollisionType GetType() const;

		/**
		* 図形を取得
		*/
		const Box& GetShape() const;

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

		virtual ComponentPtr Clone() const override;

	public:

		// ロカール座標でのコライダーの中心座標を返す
		Vector3 center = Vector3::zero;

		// ローカルサイズでのコライダーの大きさを返す
		Vector3 size = Vector3::one;

	private:

		// 図形
		Box box;
	};
}

#endif // !FGENGINE_BOXCOLLIDER_H_INCLUDEED
