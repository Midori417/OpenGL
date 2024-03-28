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

		template<typename T>
		std::shared_ptr<T> GetComponent() const;

	private:

		std::string tag = "None";	// タグ
		std::weak_ptr<GameObject> ownerObject;		// コンポーネントの所有オブジェクト
		std::weak_ptr<Transform> transform;			// 所有オブジェクトのTransform
	};
}