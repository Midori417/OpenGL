/**
* @file Collider.cpp
*/
#include "FGEngine/Component/Collider.h"
#include "FGEngine/Component/ComponentHelper.h"
#include "FGEngine/Component/Rigidbody.h"

namespace FGEngine
{
	/**
	* オーナーゲームオブジェクトのRigidbodyを取得
	*
	* @return オーナーのRigidbody
	*/
	RigidbodyPtr Collider::GetAttachedRigidbody() const
	{
		return GetComponent<Rigidbody>();
	}
}