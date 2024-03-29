/**
* @file Component.h
*/
#pragma once
#include "Object.h"
#include <memory>

namespace FGEngine
{
	// 先行宣言
	class GameObject;
	using GameObjectPtr = std::shared_ptr<GameObject>;
	class Component;
	using ComponentPtr = std::shared_ptr<Component>;
	class Transform;

	/**
	* コンポーネントの基底クラス
	*/
	class Component : public Object
	{
	public:

		// コンストラクタ・デストラクタ
		Component() = default;
		virtual ~Component() = default;

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
		TransformPtr GetTransform() const
		{
			auto ptr = transform.lock();
			if (!ptr)
			{
				return nullptr;
			}
			return ptr;
		}

		/**
		* T型のコンポーネントを取得
		*/
		template<typename T>
		std::shared_ptr<T> GetComponent() const;

		/**
		* 親のT型のコンポーネントを取得
		*/
		template<typename T>
		std::shared_ptr<T> GetComponentInChildren() const;

		/**
		* 子のT型のコンポーネントを取得
		*/
		template<typename T>
		std::shared_ptr<T> GetComponentInParent() const;

		/**
		* Tagを取得
		*/
		std::string GetTag() const;

	private:

		std::weak_ptr<GameObject> ownerObject;		// コンポーネントの所有オブジェクト
		std::weak_ptr<Transform> transform;			// 所有オブジェクトのTransform
	};
}