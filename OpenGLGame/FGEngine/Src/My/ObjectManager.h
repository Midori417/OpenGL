/**
* @file ObjectManager.h
*/
#ifndef FGENGINE_OBJECTMANAGER_H_INCLUDED
#define FGENGINE_OBJECTMANAGER_H_INCLUDED
#include "Singleton.h"
#include "Object.h"
#include "GameObject.h"

namespace FGEngine::ObjectSystem
{
	/**
	* オブジェクト管理クラス
	*/
	class ObjectManager : public Singleton<ObjectManager>
	{
	private:

		friend Singleton<ObjectManager>;

		// コンストラクタ
		ObjectManager() = default;

		/**
		* オブジェクトマネージャーを初期化
		*
		* @retval 0		正常に初期化
		* @retval 0以外 初期化失敗
		*/
		int Initialize();

		/**
		* オブジェクトマネージャーを更新
		*/
		void Update();

		/**
		* ゲームオブジェクトの更新
		*/
		void UpdateGameObject();

		/**
		* ゲームオブジェクトの削除処理
		*/
		void DestoryGameObject();

	public:

		/**
		* オブジェクトを作成
		*/
		template<typename T>
		std::shared_ptr<T> CreateObject(const std::string& name)
		{
			auto obj = std::make_shared<T>();
			obj->SetName(name);
			return obj;
		}

		/**
		* ゲームオブジェクトを作成
		*/
		GameObjectPtr CreateGameObject(const std::string& name);
		GameObjectPtr CreateGameObject(const std::string& name, const Transform& transform);
		GameObjectPtr CreateGameObject(const std::string& name, const Vector3& position, const Quaternion& rotation);

		/**
		* ゲームオブジェクトを取得
		*/
		GameObjectList& GetGameObjects()
		{
			return gameObjects;
		}

		/**
		* 全てのゲームオブジェクトを削除
		*/
		void AllClearGameObject()
		{
			gameObjects.clear();
		}

	private:

		// ゲームオブジェクト配列
		std::vector<GameObjectPtr> gameObjects;

		// 破壊オブジェクトが存在するかどうか
		bool isDestoryObject = false;

	};
}

#endif // !OBJECTMANAGER_H_INCLUDED
