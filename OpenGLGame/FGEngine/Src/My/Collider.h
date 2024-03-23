/**
* @file Collider.h
*/
#ifndef COLLIDER_H_INCLUDED
#define COLLIDER_H_INCLUDED

#include "Component.h"
#include "VectorFrd.h"
#include "MatrixFrd.h"
#include <memory>

namespace FGEngine
{

	// 先行宣言
	class Collider;
	using ColliderPtr = std::shared_ptr<Collider>;

	/**
	* コライダー基底クラス
	*/
	class Collider : public Component
	{
	public:

		Collider() = default;
		virtual ~Collider() = default;

		enum class Type
		{
			AABB,	// 軸平行境界ボックス
			Sphere, // 球体
			Box,	// 有向境界ボックス
		};
		virtual Type GetType() const = 0;

		// 座標を変更する
		virtual void AddPosition(const Vector3& translate) = 0;

		// 座標変換したコライダーを取得する
		virtual ColliderPtr GetTransformedCollider(const Matrix4x4& transform) const = 0;

	public:

		bool isTrigger = false;	// true=重複可、false=重複不可
		bool isStatic = false;	// true=動かない物体、false=動く物体
	};
}
#endif // !COLLIDER_H_INCLUDED
