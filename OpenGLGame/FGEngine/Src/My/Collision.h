/**
* @file Collision.h
*/
#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED

#include "Vector3.h"

namespace FGEngine
{

	/**
	* �����s���E�{�b�N�X
	*/
	struct AABB
	{
		Vector3 min;
		Vector3 max;
	};

	/**
	* ����
	*/
	struct Sphere
	{
		Vector3 position;	// ���S���W
		float radius;	// ���a
	};

	/**
	* �L�����E�{�b�N�X(OBB)
	*/
	struct Box
	{
		Vector3 position;	// ���S���W
		Vector3 axis[3];	// ���̌����x�N�g��
		Vector3 scale;		// �������̑傫��
	};

	/**
	* ����
	*/
	struct Ray
	{
		Vector3 start;	// �����̎n�_
		Vector3 direction;	// �����̌���
	};

	// === ��������֐� === //
	bool Intersect(const AABB& a, const AABB& b, Vector3& penetration);
	bool Intersect(const Sphere& a, const Sphere& b, Vector3& penetration);
	bool Intersect(const AABB& aabb, const Sphere& sphere, Vector3& penetration);
	bool Intersect(const Box& box, const Sphere& sphere, Vector3& penetration);

	bool Intersect(const AABB& aabb, const Ray& ray, float& distance);
	bool Intersect(const Sphere& sphere, const Ray& ray, float& distance);
	bool Intersect(const Box& box, const Ray& ray, float& distance);

}
#endif // !COLLISION_H_INCLUDED
