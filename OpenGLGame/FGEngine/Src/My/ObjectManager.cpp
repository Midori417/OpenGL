/**
* @file ObjectManager.cpp
*/
#include "ObjectManager.h"
#include "Time.h"
#include <algorithm>


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
		// ゲームオブジェクト配列の容量をを予約
		gameObjects.reserve(1000);

		return 0;
	}

	/**
	* オブジェクトマネージャーを更新
	*/
	void ObjectManager::Update()
	{
	}

	void ObjectManager::UpdateGameObject()
	{
	}

	void ObjectManager::UpdateTransform()
	{
	}

	void ObjectManager::UpdateRenderer()
	{
	}

	void ObjectManager::UpdateRigidbody()
	{
	}

	/**
	* ゲームオブジェクトの削除処理
	*/
	void ObjectManager::DestoryGameObject()
	{
		// オブジェクト配列がからなら何もしない
		if (gameObjects.empty())
		{
			return;
		}

		// 破棄予定濃霧でゲームオブジェクトを分ける
		const auto iter = std::stable_partition(
			gameObjects.begin(), gameObjects.end(),
			[](const GameObjectPtr p) { return !p->IsDestroyed(); });

		// 破棄予定の破壊時間が0以上ならタイマーを減らす
		// 0以下なら破棄状態にする
		for (auto i = iter; i < gameObjects.end(); ++i)
		{
			if (i->get()->destroyTime > 0)
			{
				i->get()->destroyTime -= Time::deltaTime();
				if (i->get()->destroyTime <= 0)
				{
					i->get()->hideFlag = Object::HideFlag::Destory;
					isDestoryObject = true;
				}
			}
		}

		// 破棄状態のオブジェクトがなければ何もしない
		if (!isDestoryObject)
		{
			return;
		}

		// 破棄状態の有無でオブジェクトを分ける
		auto destroyIter = std::stable_partition(
			gameObjects.begin(), gameObjects.end(),
			[](const GameObjectPtr p) { return p->GetHideFlag() == Object::HideFlag::Destory; });
		
		// 破棄状態のゲームオブジェクトを別の配列に移動
		GameObjectList destroyList(
			std::move_iterator(iter),
			std::move_iterator(gameObjects.end()));

		// 破壊オブジェクトがないにする
		isDestoryObject = false;
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
		//obj->AddComponent<Transform>();

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
		//obj->transform->position = transform.position;

		//// 回転
		//obj->transform->rotation = transform.rotation;

		//// 拡大縮小
		//obj->transform->scale = transform.scale;

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
		//obj->transform->position = position;

		//// 回転
		//obj->transform->rotation = rotation;

		// 作成したゲームオブジェクト
		return obj;
	}
}