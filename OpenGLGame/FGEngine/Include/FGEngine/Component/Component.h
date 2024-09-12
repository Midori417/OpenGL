/**
* @file Component.h
*/
#ifndef FGENGINE_COMPONENT_H_INCLUDED
#define FGENGINE_COMPONENT_H_INCLUDED
#include "FGEngine/UsingNames/UsingGameObject.h"
#include "FGEngine/UsingNames/UsingComponent.h"
#include "FGEngine/UsingNames/UsingMath.h"
#include "FGEngine/UsingNames/UsingScene.h"
#include <string>

namespace FGEngine
{
	/**
	* コンポーネントの基底クラス
	*/
	class Component
	{
		friend GameObject;
	protected:	// このクラスは実体化しない

		/**
		* デフォルトコンストラクタ
		*/
		Component() = default;

		/**
		* デフォルトデストラクタ
		*/
		virtual ~Component() = default;

	public:

		/**
		* コンポーネントを所有しているオブジェクトを取得
		*/
		GameObjectPtr OwnerObject() const
		{
			auto ptr = ownerObject.lock();
			if (!ptr)
			{
				return nullptr;
			}
			return ptr;
		}

		/**
		* トランスフォームを取得
		*/
		TransformPtr GetTransform() const;

		/**
		* T型のコンポーネントを取得
		*/
		template<typename T>
		std::shared_ptr<T> GetComponent() const;

		/**
		* Tagを取得
		*/
		std::string GetTag() const;

		/**
		* ゲームオブジェクトを生成する
		*/
		GameObjectPtr Instantate(const std::string& name);
		GameObjectPtr Instantate(const std::string& name, const TransformPtr transform);
		GameObjectPtr Instantate(const std::string& name, const Vector3& position, const Quaternion& rotation);
		GameObjectPtr Instantate(const std::string& name, const Vector3& position);

		/**
		* 破棄予定か取得
		*
		* @return true 破棄予定
		* @return false 破棄予定じゃない
		*/
		bool IsDestroyed() const;

		/**
		* コンポーネントのクローンを作成する
		*/
		virtual ComponentPtr Clone() const = 0;

	private:

		// コンポーネントの所有オブジェクト
		std::weak_ptr<GameObject> ownerObject;

		// trueなら破壊予定
		bool isDestroyed = false;
	};
}
#endif // !FGENGINE_COMPONENT_H_INCLUDED