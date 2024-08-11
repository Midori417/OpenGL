/**
* @file CollisionType.h
*/
#ifndef FGENGINE_COLLISIONTYPE_H_INCLUDED
#define FGENGINE_COLLISIONTYPE_H_INCLUDED
#include "FGEngine/Math/Vector3.h"

namespace FGEngine::PhysicsSystem
{
	/**
	* �R���W�����̃^�C�v
	*/
	enum class CollisionType
	{
		// �����s���E�{�b�N�X
		AABB,

		// ����
		Sphere,

		// �L�����E�{�b�N�X
		Box,
	};

	/**
	* �����s�{�b�N�X
	*/
	struct AABB
	{
		Vector3 min = Vector3(-0.5f);
		Vector3 max = Vector3(0.5f);
	};

	/**
	* ����
	*/
	struct Sphere
	{
		// ���S���W
		Vector3 position = Vector3::zero;

		// �ό`
		float radius = 0;
	};

	/**
	* �L�����E�{�b�N�X
	*/
	struct Box
	{
		// ���S���W
		Vector3 position = Vector3::zero;

		// ���̌����x�N�g��
		Vector3 axis[3] = {
			Vector3::right,
			Vector3::up,
			Vector3::forward
		};

		// �������̑傫��
		Vector3 scale = Vector3::one;
	};

}

#endif // !FGENGINE_SHAPE_H_INCLUDED
