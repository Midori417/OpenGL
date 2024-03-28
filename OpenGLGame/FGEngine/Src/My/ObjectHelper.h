/**
* @file ObjectHelper.h
*/
#pragma once
#include "Object.h"
#include "ObjectManager.h"

namespace FGEngine
{
	/**
	* オブジェクトを作成
	* 
	* @param name オブジェクトの名前
	* 
	* @return 作成したオブジェクト
	*/
	template<typename T>
	std::shared_ptr<T> Object::Instantate(const std::string& name)
	{
		auto obj = ObjectManager::GetInstance()->CreateObject(name);
		return obj;
	}
}