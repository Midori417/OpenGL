/**
* @file ObjectManager.cpp
*/
#include "ObjectManager.h"
#include "Transform.h"

namespace FGEngine
{
	/**
	* オブジェクトマネージャーを初期化
	*
	* @retval 0		正常に初期化
	* @retval 0以外 初期化失敗
	*/
	int ObjectManager::Initialize()
	{
		return 0;
	}

	/**
	* オブジェクトマネージャーを更新
	*/
	void ObjectManager::Update()
	{
	}

	/**
	* ゲームオブジェクトを作成
	* 
	* @param name オブジェクトの名前
	* 
	* @return 作成したゲームオブジェクト
	*/
	GameObjectPtr ObjectManager::CreateGameObject(const std::string& name)
	{
		auto obj = CreateObject<GameObject>(name);

		// Transformを追加
		obj->AddComponent<Transform>();

		// ゲームオブジェクト配列に登録
		gameObjects.push_back(obj);

		// 作成したゲームオブジェクト
		return obj;
	}

	/**
	* ゲームオブジェクトを作成
	* 
	* @param name		オブジェクトの名前
	* @param transform	オブジェクトのTransfrom
	*/
	GameObjectPtr ObjectManager::CreateGameObject(const std::string& name, const Transform& transform)
	{
		// ゲームオブジェクトを作成
		auto obj = CreateGameObject(name);

		// Tranformを設定

		// 位置
		obj->transform->position = transform.position;

		// 回転
		obj->transform->rotation = transform.rotation;

		// 拡大縮小
		obj->transform->scale = transform.scale;

		// 作成したゲームオブジェクト
		return obj;
	}

	/**
	* ゲームオブジェクトを作成
	* 
	* @param name オブジェクトの名前
	* @param 
	*/
	GameObjectPtr ObjectManager::CreateGameObject(const std::string& name, const Vector3& position, const Quaternion& rotation)
	{
		// ゲームオブジェクトを作成
		auto obj = CreateGameObject(name);

		// 位置
		obj->transform->position = position;

		// 回転
		obj->transform->rotation = rotation;

		// 作成したゲームオブジェクト
		return obj;
	}
}