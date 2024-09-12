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
	* ���g�̏��L�҂̃R���|�[�l���g���擾
	*
	* @param T �擾�������R���|�[�l���g
	*
	* @return �������R���|�[�l���g
	*/
	template<class T>
	inline std::shared_ptr<T> Component::GetComponent() const
	{
		return OwnerObject()->GetComponent<T>();
	}
}
#endif // !FGENGINE_COMPONENT_HELPER_H_INCLUDED
