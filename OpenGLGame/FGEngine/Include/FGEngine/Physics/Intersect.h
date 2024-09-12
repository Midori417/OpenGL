/**
* @file Intersect.h
*/
#ifndef FGENGINE_INTERSECT_H_INCLUDED
#define FGENGINE_INTERSECT_H_INCLUDED
#include "CollisionType.h"

namespace FGEngine
{

	/**
	* AABB���m�̌�������
	*
	* @param a				����Ώۂ�AABB����1
	* @param b				����Ώۂ�AABB����2
	* @param penetration	�ђʃx�N�g��
	*
	* @retval true	�������Ă���
	* @retval false	�������Ă��Ȃ�
	*/
	bool Intersect(const AABB& a, const AABB& b, Vector3& penetration);

	/**
	* AABB��Sphere�̌�������
	*
	* @param aabb			����Ώۂ�AABB
	* @param sphere			����Ώۂ�Sphere
	* @param penetration	�ђʃx�N�g��
	*
	* @retval true	�������Ă���
	* @retval false	�������Ă��Ȃ�
	*/
	bool Intersect(const AABB& aabb, const Sphere& sphere, Vector3& penetration);

	/**
	* AABB��Box�̌�������
	*
	* @param aabb			����Ώۂ�AABB
	* @param sphere			����Ώۂ�Sphere
	* @@param penetration	�ђʃx�N�g��
	*
	* @retval true	�������Ă���
	* @retval false	�������Ă��Ȃ�
	*/
	bool Intersect(const AABB& aabb, const Box& box, Vector3& penetration);

	/**
	* Sphere���m�̌�������
	*
	* @param a				����Ώۂ�Sphere����1
	* @param b				����Ώۂ�Sphere����2
	* @@param penetration	�ђʃx�N�g��
	*
	* @retval true	�������Ă���
	* @retval false	�������Ă��Ȃ�
	*/
	bool Intersect(const Sphere& a, const Sphere& b, Vector3& penetration);

	/**
	* Sphere��Box�̌�������
	*
	* @param sphere			����Ώۂ�Sphere
	* @param box			����Ώۂ�Box
	* @@param penetration	�ђʃx�N�g��
	*
	* @retval true	�������Ă���
	* @retval false	�������Ă��Ȃ�
	*/
	bool Intersect(const Sphere& sphere, const Box& box, Vector3& penetration);

	/**
	* Box���m�̌�������
	*
	* @param a				����Ώۂ�Box����1
	* @param b				����Ώۂ�Box����2
	* @@param penetration		�ђʃx�N�g��
	*
	* @retval true	�������Ă���
	* @retval false	�������Ă��Ȃ�
	*/
	bool Intersect(const Box& a, const Box& b, Vector3& penetration);

}

#endif // !FGENGINE_INTERSECT_H_INCLUDED
