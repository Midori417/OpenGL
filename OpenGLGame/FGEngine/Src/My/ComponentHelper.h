/**
* @file ComponentHelper.h
*/
#include "Component.h"
#include "GameObject.h"

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
	return gameObject->GetComponent<T>();
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
inline std::shared_ptr<T> Component::GetComponentParent() const
{
	return gameObject->GetComponentParent<T>();
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
inline std::shared_ptr<T> Component::GetComponentChildren() const
{
	return gameObject->GetComponenChildren<T>();
}