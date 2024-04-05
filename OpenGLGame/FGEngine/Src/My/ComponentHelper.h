/**
* @file ComponentHelper.h
*/
#ifndef FGENGINE_COMPONENT_HELPER_H_INCLUDED
#define FGENGINE_COMPONENT_HELPER_H_INCLUDED
#include "Component.h"
#include "GameObject.h"

namespace FGEngine
{
	/**
	* 自身の所有者のコンポーネントを取得
	*
	* @param T 取得したいコンポーネント
	*
	* @return 見つけたコンポーネント
	*/
	template<class T>
	inline std::shared_ptr<T> Component::GetComponent() const
	{
		return OwnerObject()->GetComponent<T>();
	}

	/**
	* 自身の所有者の親のコンポーネントを取得
	*
	* @param T 取得したいコンポーネント
	*
	* @return 見つけたコンポーネント
	* @return nullptr 見つからない
	*/
	template<class T>
	inline std::shared_ptr<T> Component::GetComponentInParent() const
	{
		return OwnerObject()->GetComponentInParent<T>();
	}

	/**
	* 自身の所有者の子供のコンポーネントを取得
	*
	* @param T 所有したいコンポーネント
	*
	* @return 見つけたコンポーネント
	* @return nullptr 見つからない
	*/
	template<class T>
	inline std::shared_ptr<T> Component::GetComponentInChildren() const
	{
		return OwnerObject()->GetComponentInChildren();
	}

	/**
	* Tagを取得
	*/
	inline std::string Component::GetTag() const
	{
		return OwnerObject()->tag;
	}
}
#endif // !FGENGINE_COMPONENT_HELPER_H_INCLUDED
