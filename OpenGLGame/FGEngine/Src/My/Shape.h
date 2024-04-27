/**
* @file Shape.h
*/
#ifndef FGENGINE_SHAPE_H_INCLUDED
#define FGENGINE_SHAPE_H_INCLUDED
#include "Vector3.h"

namespace FGEngine
{
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
