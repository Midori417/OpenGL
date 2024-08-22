/**
* @file Collider.cpp
*/
#include "FGEngine/Component/Collider.h"
#include "FGEngine/Component/ComponentHelper.h"
#include "FGEngine/Component/Rigidbody.h"

namespace FGEngine
{
	/**
	* �I�[�i�[�Q�[���I�u�W�F�N�g��Rigidbody���擾
	*
	* @return �I�[�i�[��Rigidbody
	*/
	RigidbodyPtr Collider::GetAttachedRigidbody() const
	{
		return GetComponent<Rigidbody>();
	}
}