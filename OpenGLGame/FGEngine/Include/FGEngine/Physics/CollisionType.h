/**
* @file CollisionType.h
*/
#ifndef FGENGINE_COLLISIONTYPE_H_INCLUDED
#define FGENGINE_COLLISIONTYPE_H_INCLUDED
#include "FGEngine/Math/Vector3.h"

namespace FGEngine::PhysicsSystem
{
	/**
	* コリジョンのタイプ
	*/
	enum class CollisionType
	{
		// 軸平行境界ボックス
		AABB,

		// 球体
		Sphere,

		// 有向境界ボックス
		Box,
	};

	/**
	* 軸平行ボックス
	*/
	struct AABB
	{
		Vector3 min = Vector3(-0.5f);
		Vector3 max = Vector3(0.5f);
	};

	/**
	* 球体
	*/
	struct Sphere
	{
		// 中心座標
		Vector3 position = Vector3::zero;

		// 変形
		float radius = 0;
	};

	/**
	* 有向境界ボックス
	*/
	struct Box
	{
		// 中心座標
		Vector3 position = Vector3::zero;

		// 軸の向きベクトル
		Vector3 axis[3] = {
			Vector3::right,
			Vector3::up,
			Vector3::forward
		};

		// 軸方向の大きさ
		Vector3 scale = Vector3::one;
	};

}

#endif // !FGENGINE_SHAPE_H_INCLUDED
