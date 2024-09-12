/**
* @file Intersect.h
*/
#ifndef FGENGINE_INTERSECT_H_INCLUDED
#define FGENGINE_INTERSECT_H_INCLUDED
#include "CollisionType.h"

namespace FGEngine
{

	/**
	* AABB同士の交差判定
	*
	* @param a				判定対象のAABBその1
	* @param b				判定対象のAABBその2
	* @param penetration	貫通ベクトル
	*
	* @retval true	交差している
	* @retval false	交差していない
	*/
	bool Intersect(const AABB& a, const AABB& b, Vector3& penetration);

	/**
	* AABBとSphereの交差判定
	*
	* @param aabb			判定対象のAABB
	* @param sphere			判定対象のSphere
	* @param penetration	貫通ベクトル
	*
	* @retval true	交差している
	* @retval false	交差していない
	*/
	bool Intersect(const AABB& aabb, const Sphere& sphere, Vector3& penetration);

	/**
	* AABBとBoxの交差判定
	*
	* @param aabb			判定対象のAABB
	* @param sphere			判定対象のSphere
	* @@param penetration	貫通ベクトル
	*
	* @retval true	交差している
	* @retval false	交差していない
	*/
	bool Intersect(const AABB& aabb, const Box& box, Vector3& penetration);

	/**
	* Sphere同士の交差判定
	*
	* @param a				判定対象のSphereその1
	* @param b				判定対象のSphereその2
	* @@param penetration	貫通ベクトル
	*
	* @retval true	交差している
	* @retval false	交差していない
	*/
	bool Intersect(const Sphere& a, const Sphere& b, Vector3& penetration);

	/**
	* SphereとBoxの交差判定
	*
	* @param sphere			判定対象のSphere
	* @param box			判定対象のBox
	* @@param penetration	貫通ベクトル
	*
	* @retval true	交差している
	* @retval false	交差していない
	*/
	bool Intersect(const Sphere& sphere, const Box& box, Vector3& penetration);

	/**
	* Box同士の交差判定
	*
	* @param a				判定対象のBoxその1
	* @param b				判定対象のBoxその2
	* @@param penetration		貫通ベクトル
	*
	* @retval true	交差している
	* @retval false	交差していない
	*/
	bool Intersect(const Box& a, const Box& b, Vector3& penetration);

}

#endif // !FGENGINE_INTERSECT_H_INCLUDED
