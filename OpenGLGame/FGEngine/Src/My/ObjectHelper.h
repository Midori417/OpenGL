/**
* @file ObjectHelper.h
*/
#ifndef OBJECTHELPER_H_INCLUDED
#define OBJECTHELPER_H_INCLUDED
#include "Object.h"
#include "ObjectManager.h"

namespace FGEngine
{
	/**
	* �I�u�W�F�N�g���쐬
	* 
	* @param name �I�u�W�F�N�g�̖��O
	* 
	* @return �쐬�����I�u�W�F�N�g
	*/
	template<typename T>
	std::shared_ptr<T> Object::Instantate(const std::string& name)
	{
		auto obj = ObjectManager::GetInstance()->CreateObject(name);
		return obj;
	}
}

#endif // !OBJECTHELPER_H_INCLUDED
