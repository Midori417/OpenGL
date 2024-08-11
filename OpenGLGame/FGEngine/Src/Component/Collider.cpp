/**
* @file Collider.cpp
*/
#include "FGEngine/Component/Collider.h"
#include "FGEngine/GameObject.h"

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