/**
* @file ComponentHelper.h
*/
#include "Component.h"
#include "GameObject.h"

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
	return gameObject->GetComponent<T>();
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
inline std::shared_ptr<T> Component::GetComponentParent() const
{
	return gameObject->GetComponentParent<T>();
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
inline std::shared_ptr<T> Component::GetComponentChildren() const
{
	return gameObject->GetComponenChildren<T>();
}