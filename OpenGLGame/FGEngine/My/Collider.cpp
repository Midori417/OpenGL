/**
* @file Collider.cpp
*/
#include "Collider.h"
#include "GameObject.h"

namespace FGEngine
{
	/**
	* オーナーゲームオブジェクトのRigidbodyを取得
	*
	* @return オーナーのRigidbody
	*/
	RigidbodyPtr FGEngine::Collider::GetAttachedRigidbody() const
	{
		return OwnerObject()->rigidbody;
	}
}