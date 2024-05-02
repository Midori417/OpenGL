/**
* @file Collider.cpp
*/
#include "Collider.h"
#include "GameObject.h"

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