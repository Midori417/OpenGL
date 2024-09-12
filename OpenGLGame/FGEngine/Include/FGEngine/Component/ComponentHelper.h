/**
* @file ComponentHelper.h
*/
#ifndef FGENGINE_COMPONENT_HELPER_H_INCLUDED
#define FGENGINE_COMPONENT_HELPER_H_INCLUDED
#include "Component.h"
#include "FGEngine/GameObject.h"

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
}
#endif // !FGENGINE_COMPONENT_HELPER_H_INCLUDED
