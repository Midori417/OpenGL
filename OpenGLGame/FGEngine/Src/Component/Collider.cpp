/**
* @file Collider.cpp
*/
#include "FGEngine/Component/Collider.h"
#include "FGEngine/GameObject.h"

namespace FGEngine
{
	/**
	* �I�[�i�[�Q�[���I�u�W�F�N�g��Rigidbody���擾
	*
	* @return �I�[�i�[��Rigidbody
	*/
	RigidbodyPtr FGEngine::Collider::GetAttachedRigidbody() const
	{
		return OwnerObject()->rigidbody;
	}
}