/**
* @file Component.h
*/
#ifndef FGENGINE_COMPONENT_H_INCLUDED
#define FGENGINE_COMPONENT_H_INCLUDED
#include "FGEngine/Object.h"

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
		friend GameObject;

		// コンストラクタ・デストラクタ
		Component() = default;
		virtual ~Component() = default;

		/**
		* コンポーネントを所有しているオブジェクトを取得
		*/
		GameObjectPtr OwnerObject() const
		{
			std::shared_ptr<GameObject> ptr(ownerObject);
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

	private:

		// コンポーネントの所有オブジェクト
		std::weak_ptr<GameObject> ownerObject;
	};
}
#endif // !FGENGINE_COMPONENT_H_INCLUDED