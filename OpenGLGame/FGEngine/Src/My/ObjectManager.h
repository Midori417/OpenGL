/**
* @file ObjectManager.h
*/
#ifndef OBJECTMANAGER_H_INCLUDED
#define OBJECTMANAGER_H_INCLUDED
#include "Singleton.h"
#include "Object.h"
#include "GameObject.h"

namespace FGEngine
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

		std::vector<GameObjectPtr> gameObjects;	// ゲームオブジェクト配列
	};
}

#endif // !OBJECTMANAGER_H_INCLUDED
