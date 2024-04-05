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

	/**
	* ���g�̏��L�҂̐e�̃R���|�[�l���g���擾
	*
	* @param T �擾�������R���|�[�l���g
	*
	* @return �������R���|�[�l���g
	* @return nullptr ������Ȃ�
	*/
	template<class T>
	inline std::shared_ptr<T> Component::GetComponentInParent() const
	{
		return OwnerObject()->GetComponentInParent<T>();
	}

	/**
	* ���g�̏��L�҂̎q���̃R���|�[�l���g���擾
	*
	* @param T ���L�������R���|�[�l���g
	*
	* @return �������R���|�[�l���g
	* @return nullptr ������Ȃ�
	*/
	template<class T>
	inline std::shared_ptr<T> Component::GetComponentInChildren() const
	{
		return OwnerObject()->GetComponentInChildren();
	}

	/**
	* Tag���擾
	*/
	inline std::string Component::GetTag() const
	{
		return OwnerObject()->tag;
	}
}
#endif // !FGENGINE_COMPONENT_HELPER_H_INCLUDED
