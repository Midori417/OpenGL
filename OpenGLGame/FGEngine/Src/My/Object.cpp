/**
* @file Object.cpp
*/
#include "Object.h"
#include "GameObject.h"
#include "ObjectManager.h"

namespace FGEngine
{
	/**
	* オブジェクトの名前を取得する
	*/
	std::string Object::ToString() const
	{
		return name;
	}

	/**
	* オブジェクトの名前を設定する
	*
	* @param value 設定する名前
	*/
	void Object::SetName(const std::string& value)
	{
		name = value;
	}

	/**
	* オブジェクトの状態を取得
	*/
	Object::HideFlag Object::GetHideFlag() const
	{
		return hideFlag;
	}

	/**
	* ゲームオブジェクトを生成する
	* 
	* @param name　オブジェクトの名前
	* 
	* @return 生成したオブジェクト
	*/
	GameObjectPtr Object::Instantate(const std::string& name)
	{
		auto obj = ObjectSystem::ObjectManager::GetInstance()->CreateGameObject(name);

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
	GameObjectPtr Object::Instantate(const std::string& name, const Transform& transform)
	{
		auto obj = ObjectSystem::ObjectManager::GetInstance()->CreateGameObject(name, transform);

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
	GameObjectPtr Object::Instantate(const std::string& name, const Vector3& position, const Quaternion& rotation)
	{
		auto obj = ObjectSystem::ObjectManager::GetInstance()->CreateGameObject(name, position, rotation);

		return obj;
	}

	/**
	* オブジェクトの状態を破壊予定にする
	*
	* @param obj 破棄予定にするオブジェクト
	* @parma t	破壊される時間
	*/
	void Object::Destory(ObjectPtr obj, float t)
	{
		// すでに破棄予定
		if (obj->isDestroyed)
		{
			return;
		}

		// 破棄予定にする
		obj->isDestroyed = true;

		if (t > 0)
		{
			// 破棄時間を設定
			obj->destroyTime = t;
		}
		else
		{
			obj->hideFlag = HideFlag::Destory;
		}
	}

}