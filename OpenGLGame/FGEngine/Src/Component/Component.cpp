/**
* @file Component.cpp
*/
#include "FGEngine/Component/Component.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/Scene/Scene.h"
#include "FGEngine/Math/Quaternion.h"

namespace FGEngine
{
	/**
	* ゲームオブジェクトを生成する
	*
	* @param name　オブジェクトの名前
	*
	* @return 生成したオブジェクト
	*/
	GameObjectPtr Component::Instantate(const std::string& name)
	{
		auto obj = OwnerObject()->GetScene()->CreateGameObject(name);

		return obj;
	}

	/**
	* ゲームオブジェクトを生成する
	*
	* @param name		オブジェクトの名前
	* @param transform	オブジェクトのTransform
	*
	* @return 生成したオブジェクト
	*/
	GameObjectPtr Component::Instantate(const std::string& name, const TransformPtr transform)
	{
		auto obj = OwnerObject()->GetScene()->CreateGameObject(name, transform);

		return obj;
	}

	/**
	* ゲームオブジェクトを生成する
	*
	* @param name		オブジェクトの名前
	* @param position	生成する位置
	* @param rotation	生成したときの回転度
	*
	* @return 生成したオブジェクト
	*/
	GameObjectPtr Component::Instantate(const std::string& name, const Vector3& position, const Quaternion& rotation)
	{
		auto obj = OwnerObject()->GetScene()->CreateGameObject(name, position, rotation);

		return obj;
	}

	GameObjectPtr Component::Instantate(const std::string& name, const Vector3& position)
	{
		return Instantate(name, position, Quaternion::identity);
	}

	/**
	* 破棄予定か取得
	*
	* @return true 破棄予定
	* @return false 破棄予定じゃない
	*/
	bool Component::IsDestroyed() const
	{
		return isDestroyed;
	}
}