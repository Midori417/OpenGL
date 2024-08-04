/**
* @file InputManager.cpp
*/
#include "FGEngine/Input/InputManager.h"
#include "FGEngine/Input/InputKey.h"
#include "FGEngine/Input/InputMouse.h"
#include "FGEngine/Debug/Debug.h"
#include <GLFW/glfw3.h>

namespace FGEngine
{
	// �ÓI�ϐ��̏�����
	std::shared_ptr<InputKey> InputManager::inputKey = nullptr;
	std::shared_ptr<InputMouse> InputManager::inputMouse = nullptr;

	/**
	* �C���v�b�g�}�l�[�W����������
	* 
	* @retval 0		����ɏ�����
	* @retval 0�ȊO	�G���[����
	*/
	int InputManager::Initialize()
	{
		// �L�[�{�[�h�f�o�C�X����
		inputKey = std::shared_ptr<InputKey>(new InputKey{});
		if (inputKey->Initialize() != 0)
		{
			LOG_ERROR("�L�[�{�[�h�f�o�C�X�̏������Ɏ��s");
			return 1;
		}

		// �}�E�X�f�o�C�X����
		inputMouse = std::shared_ptr<InputMouse>(new InputMouse{});
		if (inputMouse->Initialize() != 0)
		{
			LOG_ERROR("�}�E�X�f�o�C�X�̏������Ɏ��s");
			return 1;
		}

		// ����������
		return 0;
	}

	/**
	* �C���v�b�g�}�l�[�W�����X�V
	*/
	void InputManager::Update()
	{
		if (!window)
		{
			LOG_WARNINGS("(InputManger)�E�B���h�E�I�u�W�F�N�g�����݂��܂���");
			return;
		}

		// ���̓f�o�C�X�̏�Ԃ��X�V

		if (inputKey)
		{
			inputKey->Update(window);
		}

		if (inputMouse)
		{
			inputMouse->Update(window);
		}
	}

	/**
	* �L�[�{�[�h�f�o�C�X���擾
	*/
	std::shared_ptr<InputKey> InputManager::GetInputKey()
	{
		if (!inputKey)
		{
			LOG_ERROR("�L�[�{�[�h�f�o�C�X�����݂��܂���");
			return nullptr;
		}
		return inputKey;
	}

	/**
	* �}�E�X�f�o�C�X���擾
	*/
	std::shared_ptr<InputMouse> InputManager::GetInputMouse()
	{
		if (!inputMouse)
		{
			LOG_ERROR("�}�E�X�f�o�C�X�����݂��܂���");
			return nullptr;
		}
		return inputMouse;
	}

#pragma region Key

	/**
	* �L�[��������Ă��邩���擾
	*
	* @param keyCode �Ή����Ă���L�[
	*
	* @retval true	�����Ă���
	* @retval false	�����Ă��Ȃ�
	*/
	bool InputManager::GetKey(KeyCode keyCode)
	{
		return GetInputKey()->GetKey(keyCode);
	}

	/**
	* �L�[���オ���������擾
	*
	* @param keyCode �Ή����Ă���L�[
	*
	* @retval true	�����������Ă���
	* @retval false	�����グ���Ă��Ȃ�
	*/
	bool InputManager::GetKeyUp(KeyCode keyCode)
	{
		return GetInputKey()->GetKeyUp(keyCode);
	}

	/**
	* �L�[���������������擾
	*
	* @param keyCode �Ή����Ă���L�[
	*
	* @retval true	������������
	* @retval false	�����������Ă��Ȃ�
	*/
	bool InputManager::GetKeyDown(KeyCode keyCode)
	{
		return GetInputKey()->GetKeyDown(keyCode);
	}

	/**
	* ��������̃L�[��������Ă��邩�擾
	*
	* @retval true ������Ă���
	* @retval false ������Ă��Ȃ�
	*/
	bool InputManager::AnyKey()
	{
		return GetInputKey()->AnyKey();
	}

#pragma endregion

#pragma region Mouse

	/**
	* �}�E�X�̈ʒu���擾
	*/
	Vector2 InputManager::GetMousePosition()
	{
		return GetInputMouse()->GetMousePosition();
	}

	/**
	* �}�E�X�̃{�^���������Ă�����擾
	*
	* @param mouseButton �Ή����Ă���{�^��
	*
	* @retval true	�����Ă���
	* @retval false	�����Ă��Ȃ�
	*/
	bool InputManager::GetMouseButton(MouseButton mouseButton)
	{
		return GetInputMouse()->GetMouseButton(mouseButton);
	}

	/**
	* �}�E�X�̃{�^�����オ���������擾
	*
	* @param mouseButton �Ή����Ă���{�^��
	*
	* @retval true	�����������Ă���
	* @retval false	�����グ���Ă��Ȃ�
	*/
	bool InputManager::GetMouseButtonUp(MouseButton mouseButton)
	{
		return GetInputMouse()->GetMouseButtonUp(mouseButton);
	}

	/**
	* �}�E�X�̃{�^�����������������擾
	*
	* @param mouseButton �Ή����Ă���{�^��
	*
	* @retval true	������������
	* @retval false	�����������Ă��Ȃ�
	*/
	bool InputManager::GetMouseButtonDown(MouseButton mouseButton)
	{
		return GetInputMouse()->GetMouseButtonDown(mouseButton);
	}

	/**
	* �}�E�X���N���b�N���������擾
	*
	* @param mouseButton �Ή����Ă���{�^��
	*
	* @retval true �N���b�N����
	* @retval false �N���b�N���Ă��Ȃ�
	*/
	bool InputManager::GetMouseButtonClick(MouseButton mouseButton)
	{
		return GetInputMouse()->GetMouseButtonClick(mouseButton);
	}

#pragma endregion
}