/**
* @file Component.cpp
*/
#include "FGEngine/Component/Component.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/Scene/Scene.h"
#include "FGEngine/Math/Quaternion.h"

namespace FGEngine
{
	/**
	* 自身を所有しているオブジェクトを取得
	*/
	GameObjectPtr Component::OwnerObject() const
	{
		auto ptr = ownerObject.lock();
		if (!ptr)
		{
			return nullptr;
		}
		return ptr;
	}

	/**
	* Transformを取得
	*/
	TransformPtr Component::GetTransform() const
	{
		GameObjectPtr obj = OwnerObject();
		if (!obj)
		{
			return nullptr;
		}

		return obj->GetTransform();
	}

	/**
	* Tagを取得
	*/
	std::string Component::GetTag() const
	{
		GameObjectPtr obj = OwnerObject();
		if (!obj)
		{
			return "";
		}

		return obj->tag;
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

#pragma region Instantate

	/**
	* typeにあったオブジェクトを生成する
	*
	* @param type 生成したいオブジェクトのタイプ
	* namespace CreateObjectから選択推奨
	*
	* @return 生成したオブジェクト
	*/
	GameObjectPtr Component::Instantate(const std::string& type)
	{
		auto owner = OwnerObject();
		if (!owner)
		{
			return nullptr;
		}

		auto scene = owner->GetScene();
		if (!scene)
		{
			return nullptr;
		}

		auto obj = scene->Instantate(type);

		return obj;
	}

	/**
	* typeにあったオブジェクトを生成する
	*
	* @param type 生成したいオブジェクトのタイプ
	* namespace CreateObjectから選択推奨
	* @param position 位置
	* @param rotation 回転
	*
	* @return 生成したオブジェクト
	*/
	GameObjectPtr Component::Instantate(const std::string& type, const Vector3& position, const Quaternion& rotation)
	{
		auto obj = Instantate(type);
		if (!obj)
		{
			return nullptr;
		}

		obj->GetTransform()->position = position;
		obj->GetTransform()->rotation = rotation;

		return obj;
	}

	/**
	* gameObjectのクローンを作成
	*
	* @param gameObject クローンもとのゲームオブジェクト
	*
	* @return 生成したゲームオブジェクト
	*/
	GameObjectPtr Component::Instantate(const GameObjectPtr& gameObject)
	{
		// クローン元が存在しない場合は何もしない
		if (!gameObject)
		{
			return nullptr;
		}

		auto obj = OwnerObject();
		if (!obj)
		{
			return nullptr;
		}

		auto scene = obj->GetScene();
		if (!scene)
		{
			return nullptr;
		}

		return scene->Instantate(gameObject);
	}

	/**
	* gameObjectのクローンを作成
	*
	* @param gameObject クローン元のゲームオブジェクト
	* @param transform	クローンするトランスフォーム
	*
	* @return 作成したゲームオブジェクト
	*/
	GameObjectPtr Component::Instantate(const GameObjectPtr& gameObject, const TransformPtr& tranform)
	{
		// クローン元が存在しない場合は何もしない
		if (!gameObject)
		{
			return nullptr;
		}

		auto obj = OwnerObject();
		if (!obj)
		{
			return nullptr;
		}

		auto scene = obj->GetScene();
		if (!scene)
		{
			return nullptr;
		}

		return scene->Instantate(gameObject, tranform);
	}

	/**
	* gameObjectのクローンを作成
	*
	* @param gameObject クローン元のゲームオブジェクト
	* @param position	クローンした時の位置
	* @param rotation	クローンした時の回転
	*
	* @return 作成したゲームオブジェクト
	*/
	GameObjectPtr Component::Instantate(const GameObjectPtr& gameObject, const Vector3& position, const Quaternion& rotation)
	{
		// クローン元が存在しない場合は何もしない
		if (!gameObject)
		{
			return nullptr;
		}

		auto owner = OwnerObject();
		if (!owner)
		{
			return nullptr;
		}

		auto scene = owner->GetScene();
		if (!scene)
		{
			return nullptr;
		}

		auto obj = scene->Instantate(gameObject);

		// トランスフォームを取得して位置と回転を設定
		auto transform = obj->GetTransform();
		transform->position = position;
		transform->rotation = rotation;

		return obj;
	}

#pragma endregion

}