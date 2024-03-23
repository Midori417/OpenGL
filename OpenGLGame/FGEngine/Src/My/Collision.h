/**
* @file Collision.h
*/
#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED

#include "Vector3.h"

namespace FGEngine
{

	/**
	* 軸平行境界ボックス
	*/
	struct AABB
	{
		Vector3 min;
		Vector3 max;
	};

	/**
	* 球体
	*/
	struct Sphere
	{
		Vector3 position;	// 中心座標
		float radius;	// 半径
	};

	/**
	* 有向境界ボックス(OBB)
	*/
	struct Box
	{
		Vector3 position;	// 中心座標
		Vector3 axis[3];	// 軸の向きベクトル
		Vector3 scale;		// 軸方向の大きさ
	};

	/**
	* 光線
	*/
	struct Ray
	{
		Vector3 start;	// 光線の始点
		Vector3 direction;	// 光線の向き
	};

	// === 交差判定関数 === //
	bool Intersect(const AABB& a, const AABB& b, Vector3& penetration);
	bool Intersect(const Sphere& a, const Sphere& b, Vector3& penetration);
	bool Intersect(const AABB& aabb, const Sphere& sphere, Vector3& penetration);
	bool Intersect(const Box& box, const Sphere& sphere, Vector3& penetration);

	bool Intersect(const AABB& aabb, const Ray& ray, float& distance);
	bool Intersect(const Sphere& sphere, const Ray& ray, float& distance);
	bool Intersect(const Box& box, const Ray& ray, float& distance);

}
#endif // !COLLISION_H_INCLUDED
