/**
* @file WorldCollider,h
*/
#ifndef FGENGINE_WORLDCOLLIDER_H_INCLUDED
#define FGENGINE_WORLDCOLLIDER_H_INCLUDED
#include "Vector3.h"
#include "Collider.h"
#include "Transform.h"

namespace FGEngine::PhysicsSystem
{
	/**
	* ���[���h���W�n�̃R���C�_�[
	*/
	struct WorldCollider
	{
		/**
		* ���W��ύX����
		*
		* @param v �ύX����l
		*/
		void AddPosition(const Vector3& v)
		{
			origin->GetTransform()->position += v;
			world->AddPosition(v);
		}
		ColliderPtr origin;
		ColliderPtr world;
	};
	using WorldColliderList = std::vector<WorldCollider>;
}

#endif // !FGENGINE_WORLDCOLLIDER_H_INCLUDED
