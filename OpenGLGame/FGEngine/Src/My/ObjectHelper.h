/**
* @file ObjectHelper.h
*/
#ifndef OBJECTHELPER_H_INCLUDED
#define OBJECTHELPER_H_INCLUDED
#include "Object.h"

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

	}
}

#endif // !OBJECTHELPER_H_INCLUDED
